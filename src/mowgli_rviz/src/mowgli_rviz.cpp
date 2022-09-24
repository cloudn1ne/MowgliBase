/*
 * Mowgli RVIZ Interface V1.1
 * (c) Georg Swoboda <cn@warp.at> 2022
 *
 * https://github.com/cloudn1ne/MowgliRover
 *
 * v1.0: inital release
 * v1.1: added mowgli only topics (-DOPENMOWER_ONLY=1 only needed if you want OM only topics !)
 * 
 */

// Support OM only topics
//#define OPENMOWER_ONLY 1

#ifdef OPENMOWER_ONLY
 #warning ( "=============================================" )
 #warning ( "= Building OpenMower version of mowgli_rviz =" )
 #warning ( "= Available layers will be restricted !     =" ) 
 #warning ( "=============================================" )
 #warning ( "" )
#endif

#include <ros/ros.h>
#include <signal.h>
#include <grid_map_ros/grid_map_ros.hpp>
#include <grid_map_msgs/GridMap.h>
#include <cmath>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

// Rosbag for reading/writing the map to a file
#include <rosbag/bag.h>
#include <rosbag/view.h>

// MowerMap for interpreting the OM Bag file format
#include "mower_map/MapArea.h"
#include "mower_map/MapAreas.h"
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

/* GPS/ODOM */
#include <nav_msgs/Odometry.h>
#include <ublox_msgs/NavPVT.h>

/* IMU */
#include <sensor_msgs/Imu.h>

/* Status */
#ifndef OPENMOWER_ONLY
 #include <mowgli/status.h>
#endif


// #define MOWGLI_DEBUG 1

// Map resolution in m 
#define MAP_RESOLUTION 0.15

using namespace grid_map;

// We store navigation_areas (i.e. robot is allowed to move here) and
// mowing_areas (i.e. grass needs to be cut here)
std::vector<mower_map::MapArea> navigation_areas;
std::vector<mower_map::MapArea> mowing_areas;

// map paths
std::string mowgli_map_path = "mowgli_map.bag";
std::string openmower_map_path = "map.bag";

// Subscribers
ros::Subscriber subGPSQuality;          // /ublox/navpvt (GPS FIX Quality)
ros::Subscriber subOdom;		// /odom
ros::Subscriber subIMU;			// /imu/data
#ifndef OPENMOWER_ONLY
 ros::Subscriber subStatus;		// /mowgli/status
#endif
// GPS Quality flags
bool   gpsOdometryIsRTK = false;
double gpsXYAcc = 0.0;

// Robot position
double bot_x = 0.0;
double bot_y = 0.0;

// Z acceleration
double accel_z = 0.0;

#ifndef OPENMOWER_ONLY
  // Wheel power sum
  double status_wheelpower_sum = 0.0;
#endif

// true once we receive the first bot location via /odom
bool inital_odom_received = false;

// GridMap (global because we save it in the sigint handler )
GridMap map({"mowing_area"});

/**
 * Save the current map
 * 
 * @param sig signal type
 */ 
void mySigintHandler(int sig)
{
  // Do some custom action.
  // For example, publish a stop message to some other nodes.
  ROS_WARN("Saving GridMaps to '%s' ...", mowgli_map_path.c_str());  
  GridMapRosConverter::saveToBag(map, mowgli_map_path, "mowgli_rviz");
  // All the default sigint handler does is call shutdown()
  ros::shutdown();
}

/**
 * Read the recorded GridMap from a bag file
 *
 * @param filename The file to load.
 * @returns true if file was found and data was read, false if no data was available
 */
bool readMowgliMapFromFile(const std::string& filename)
{

  try 
  {
    ROS_WARN("Loading GridMaps from '%s' ...", mowgli_map_path.c_str());
    return GridMapRosConverter::loadFromBag(filename, "mowgli_rviz", map);
  } catch (rosbag::BagIOException &e) {
    return false; // reconstruct GridMap from openmower_map_path
  }
}


/**
 * Convert a geometry_msgs::Polygon to a grid_map::Polygon.
 * This is needed in order to add recorded polys to the map.
 *
 * @param poly input poly
 * @param out result
 */
void fromMessage(geometry_msgs::Polygon &poly, grid_map::Polygon &out) {
    out.removeVertices();
    for (auto &point: poly.points) {
        grid_map::Position pos;
        pos.x() = point.x;
        pos.y() = point.y;
        out.addVertex(pos);
    }
}

/**
 * Load the Polygons from the bag file and build a map.
 *
 * @param filename The file to load.
 * @param append True to append the loaded map to the current one.
 */
void readMapFromFile(const std::string& filename, bool append = false) {
    rosbag::Bag bag;

    try {
        bag.open(filename);
    } catch (rosbag::BagIOException &e) {
        ROS_ERROR_STREAM("mowgli_rviz: Error loading stored mowing areas from Openmower map.bag file in '" << filename << "'");
	ROS_ERROR_STREAM("mowgli_rviz:");
        ROS_ERROR_STREAM("mowgli_rviz: =========================================================");
        ROS_ERROR_STREAM("mowgli_rviz:  Unless you provide a Openmower bag file (map.bag)");
        ROS_ERROR_STREAM("mowgli_rviz:  mowgli_rviz will assume a square map of 10x10 meters");
	ROS_ERROR_STREAM("mowgli_rviz: =========================================================");
	ROS_ERROR_STREAM("mowgli_rviz:");
	return;
    }
    {
        rosbag::View view(bag, rosbag::TopicQuery("mowing_areas"));

        for (rosbag::MessageInstance const m: view) {
            auto area = m.instantiate<mower_map::MapArea>();
            mowing_areas.push_back(*area);
        }
    }
    ROS_INFO_STREAM("mowgli_rviz: Loaded " << mowing_areas.size() << " mowing areas and " << navigation_areas.size()
                              << " navigation areas from file.");
}

/**
 * Uses the polygons stored in navigation_areas and mowing_areas to build the final occupancy grid.
 *
 * First, the map is marked as completely occupied. Then navigation_areas and mowing_areas are marked as free.
 *
 * Then, all obstacles are marked as occupied.
 *
 * Finally, a blur is applied to the map so that it is expensive, but not completely forbidden to drive near boundaries.
 */
void buildMap(ros::Publisher publisher, ros::NodeHandle nh) {
    
    // First, calculate the size of the map by finding the min and max values for x and y.
    float minX = FLT_MAX;
    float maxX = FLT_MIN;
    float minY = FLT_MAX;
    float maxY = FLT_MIN;

    // loop through all areas and calculate a size where everything fits
    for (const auto &area: mowing_areas) {
        for (auto pt: area.area.points) {
            minX = std::min(minX, pt.x);
            maxX = std::max(maxX, pt.x);
            minY = std::min(minY, pt.y);
            maxY = std::max(maxY, pt.y);
        }
        for (const auto &obstacle: area.obstacles) {
            for (const auto &pt: obstacle.points) {
                minX = std::min(minX, pt.x);
                maxX = std::max(maxX, pt.x);
                minY = std::min(minY, pt.y);
                maxY = std::max(maxY, pt.y);
            }
        }
    }
    for (const auto &area: navigation_areas) {
        for (auto pt: area.area.points) {
            minX = std::min(minX, pt.x);
            maxX = std::max(maxX, pt.x);
            minY = std::min(minY, pt.y);
            maxY = std::max(maxY, pt.y);
        }
        for (const auto &obstacle: area.obstacles) {
            for (const auto &pt: obstacle.points) {
                minX = std::min(minX, pt.x);
                maxX = std::max(maxX, pt.x);
                minY = std::min(minY, pt.y);
                maxY = std::max(maxY, pt.y);
            }
        }
    }

    // Enlarge the map by 1m in all directions.
    // This guarantees that even after blurring, the map has an occupied border.
    maxX += 1.0;
    minX -= 1.0;
    maxY += 1.0;
    minY -= 1.0;

    // Check, if the map was empty. If so, we'd create a huge map. Therefore we build an empty 10x10m map instead.
    if (mowing_areas.empty() && navigation_areas.empty()) {
        maxX = 5.0;
        minX = -5.0;
        maxY = 5.0;
        minY = -5.0;
    }

    // create map object
    //GridMap map({"mowing_area"});
    map.add("gps_rtk_fix_type");
    map.add("gps_xy_acc");
#ifndef OPENMOWER_ONLY
    map.add("wheelpower_sum");
#endif
    map.add("accel_z");
    map.setFrameId("map");

    // calculate center of map
    grid_map::Position origin;
    origin.x() = (maxX + minX) / 2.0;
    origin.y() = (maxY + minY) / 2.0;

    // set map size, resolution, origin
    map.setGeometry(grid_map::Length(maxX - minX, maxY - minY), MAP_RESOLUTION, origin); 
    map.setTimestamp(ros::Time::now().toNSec());
    map.clearAll();
//    map["navigation_area"].setConstant(0.0); // value for outline to map border (quadratic)

    grid_map::Matrix &data = map["mowing_area"];
    ROS_INFO("mowgli_rviz: loaded map with size %f x %f m (%i x %i cells).", map.getLength().x(), map.getLength().y(), map.getSize()(0), map.getSize()(1));
    ROS_INFO_STREAM("mowgli_rviz: origin position: x=" << origin.x() << ", y=" << origin.y());

    for (auto mowingArea: mowing_areas) {
        grid_map::Polygon poly;
        fromMessage(mowingArea.area, poly);

        for (grid_map::PolygonIterator iterator(map, poly); !iterator.isPastEnd(); ++iterator) {
            const grid_map::Index index(*iterator);
            data(index[0], index[1]) = 0.2;
        }
        for (auto obstacle: mowingArea.obstacles) {
            fromMessage(obstacle, poly);
            for (grid_map::PolygonIterator iterator(map, poly); !iterator.isPastEnd(); ++iterator) {
                const grid_map::Index index(*iterator);
                data(index[0], index[1]) = -0.2;
            }
        }
    }
}


void publishMap(ros::Publisher publisher, ros::NodeHandle nh) {

    grid_map_msgs::GridMap message;
    GridMapRosConverter::toMessage(map, message);

    // Wait for inital /odom message
    ros::Duration d(0.5); 
    while (!inital_odom_received)
    {
       d.sleep();	
    }

    double old_point_val=0.0;
    double new_point_val=0.0;

    // Work with grid map in a loop.
    ros::Rate rate(30.0);
    while (ros::ok()) 
    {
      ros::Time time = ros::Time::now();
      grid_map::Position pos(bot_x, bot_y);
    
      // is the Bot (bot_x/bot_y) within our map ?
      if ( map.isInside(pos) )
      {
        grid_map::Index i; 
        map.getIndex(pos, i);

	//////////////////////////////////////////////////////
	// GPS RTK FIX TYPE
	//////////////////////////////////////////////////////
        old_point_val = map.at("gps_rtk_fix_type", i);
	new_point_val = gpsOdometryIsRTK?0.5:1.0;
//	ROS_INFO("new_point_val(gps_rtk_fix_type): %f old_point_val: %f", new_point_val, old_point_val);
 	if ( isnan(old_point_val) || old_point_val < 0.5 )
	{
	   map.at("gps_rtk_fix_type", i) = new_point_val;
	}
	else
	{
           map.at("gps_rtk_fix_type", i) = std::max(new_point_val, old_point_val); // only record the worst
	}
	//////////////////////////////////////////////////////
        // GPS X/Y ACCURACY
        //////////////////////////////////////////////////////
        old_point_val = map.at("gps_xy_acc", i);
        new_point_val = gpsXYAcc;
//      ROS_INFO("new_point_val: %f old_point_val: %f", new_point_val, old_point_val);
        if ( isnan(old_point_val) )
        {
           map.at("gps_xy_acc", i) = new_point_val;
        }
        else
        {
           map.at("gps_xy_acc", i) = std::max(new_point_val, old_point_val); // only record the worst
        }
        //////////////////////////////////////////////////////
        // ACCELERATION Z (Bumpiness)
        //////////////////////////////////////////////////////
        old_point_val = map.at("accel_z", i);
        new_point_val = accel_z; 
//      ROS_INFO("new_point_val: %f old_point_val: %f", new_point_val, old_point_val);
        if ( isnan(old_point_val) )
        {
           map.at("accel_z", i) = new_point_val;
        }
        else
        {
           map.at("accel_z", i) = std::max(new_point_val, old_point_val); // only record the worst
        }
#ifndef OPENMOWER_ONLY
 	//////////////////////////////////////////////////////
        // WHEELPOWER SUM
        //////////////////////////////////////////////////////
        old_point_val = map.at("wheelpower_sum", i);
        new_point_val = status_wheelpower_sum;
//      ROS_INFO("new_point_val: %f old_point_val: %f", new_point_val, old_point_val);
        if ( isnan(old_point_val) )
        {
           map.at("wheelpower_sum", i) = new_point_val;
        }
        else
        {
           map.at("wheelpower_sum", i) = std::max(new_point_val, old_point_val); // only record the worst
        }
#endif // MOWGLI
      }
      else
      {
          ROS_WARN_THROTTLE(1, "mowgli_rviz: The bot is outside of the recognized map !");
      }

      // now publish updated GridMap
      grid_map_msgs::GridMap message;
      GridMapRosConverter::toMessage(map, message);
      publisher.publish(message);
//      ROS_INFO_THROTTLE(1.0, "mowgli_rviz: Grid map (timestamp %f) published.", message.info.header.stamp.toSec());

      ros::spinOnce();
      rate.sleep();
    }
    ROS_WARN("Saving GridMaps to bag file");
}

/*
 * GPS quality extracted from /ublox/navpvt (flags)
 * We want to know if we have a solid 3D FIX
 */
void GPSFixQualityCB(const ublox_msgs::NavPVT::ConstPtr &msg) 
{        
#ifndef OPENMOWER_ONLY_DEBUG        
    ROS_INFO_STREAM("mowgli_rviz: GPSFixQualityCB");  
#endif    
    unsigned int gps_quality_flags = msg->flags;    
    unsigned int carrSoln = (gps_quality_flags >> 6) & 3;
    if (carrSoln != 0x2 )
    {
	// floating RTK signal
        gpsOdometryIsRTK = false;
    }    
    else
    {
	// fixed RTK signal
        gpsOdometryIsRTK = true;
    } 
    gpsXYAcc = msg->hAcc;
}

/*
 * /odom Robot coordinates
 */
void OdomCB(const nav_msgs::Odometry::ConstPtr &msg)
{
#ifndef OPENMOWER_ONLY_DEBUG    
    ROS_INFO_STREAM("mowgli_rviz: MowgliOdomCB");
#endif
    bot_x = msg->pose.pose.position.x;
    bot_y = msg->pose.pose.position.y;
    ROS_INFO_DELAYED_THROTTLE(5, "mowgli_rviz: recorded [ GPS-RTK?: %s] x = %0.2fm, y = %0.2fm", (gpsOdometryIsRTK?"yes":"no"), bot_x, bot_y);
    inital_odom_received = true;
}


#ifndef OPENMOWER_ONLY
 /**
  * Mowgli data
  * 
  */
 void MowgliStatusCB(const mowgli::status::ConstPtr &msg) 
 {
 #ifndef OPENMOWER_ONLY_DEBUG    
    ROS_INFO_STREAM("mowgli_rviz: MowgliStatusCB");
 #endif    
    status_wheelpower_sum = msg->left_power + msg->right_power;
 }
#endif

/*
* IMU data (Madgwick filtered) - get orientation, and yaw
*/
void IMUDataCB(const sensor_msgs::Imu::ConstPtr &msg) {
#ifndef OPENMOWER_ONLY_DEBUG    
    ROS_INFO_STREAM("mowgli_rviz: IMUDataCB");
#endif    

    accel_z = msg->linear_acceleration.z;
}


int main(int argc, char** argv)
{
  // Initialize node and publisher.
  ros::init(argc, argv, "mowgli_rviz");
  ros::NodeHandle nh;
  ros::NodeHandle paramNh("~");
  ros::Publisher publisher = nh.advertise<grid_map_msgs::GridMap>("grid_map", 1, true);

  subGPSQuality = nh.subscribe("ublox/navpvt", 100, GPSFixQualityCB);
  subOdom = nh.subscribe("odom", 50, OdomCB);
  subIMU = nh.subscribe("imu/data", 50, IMUDataCB);
#ifndef OPENMOWER_ONLY
  subStatus = nh.subscribe("mowgli/status", 50, MowgliStatusCB);
#endif

  ros::AsyncSpinner asyncSpinner(1);
  asyncSpinner.start();

  bool gotOMBagPath = false;
  bool gotMowgliMapPath = false;
  gotOMBagPath &= paramNh.getParam("openmower_map_path", openmower_map_path);
  gotMowgliMapPath &= paramNh.getParam("mowgli_map_path", mowgli_map_path);

  signal(SIGINT, mySigintHandler);
  if ( !readMowgliMapFromFile(mowgli_map_path) ) 
  { 
    // we dont have the mowing_area so we need the OM bag file to extract it once
    ROS_WARN("No recorded GridMap found, constructing mowing_area from OM '%s'", openmower_map_path.c_str()); 
    readMapFromFile(openmower_map_path);
    buildMap(publisher, nh);
    ROS_WARN("GridMap is now ready to record data");
  }

  ROS_WARN("Starting GridMap publisher ...");
  publishMap(publisher, nh); // never returns

  return 0;
}
