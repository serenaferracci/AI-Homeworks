#include "ros/ros.h"
#include "std_msgs/String.h"
#include <limits.h>

#include "sensor_msgs/LaserScan.h"
#include <time.h>
#include <tf/transform_listener.h>
ros::Publisher pub;

void riceviCallback(const sensor_msgs::LaserScan::ConstPtr& sensore,tf::TransformListener *listener)
{	

	tf::StampedTransform transform;
	ros::Time t = ros::Time::now();

    if(listener->canTransform("/base_laser_link", "/odom", t, NULL)){
		listener->lookupTransform("/base_laser_link", "/odom",t, transform);
		tf::Vector3 v = transform.getOrigin();
		
		float x = v.getX();
		float y = v.getY();
		
		tf::Quaternion q = transform.getRotation();
		
		float theta = q.getAngle();
		std_msgs::String msg;

		std::stringstream ss;
		ss << "Time: " << t;
		ss << " Coordinate: x = " << x;
		ss << "  y = " << y;
		ss << "  theta = " << theta;
		
		msg.data = ss.str();
		ROS_INFO("%s", msg.data.c_str());

		pub.publish(msg);
    }

  
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "trasf");
  tf::TransformListener listener;

  ros::NodeHandle n;

  pub = n.advertise<std_msgs::String>("trasformata", 1000);
  ros::Subscriber sub = n.subscribe<sensor_msgs::LaserScan>("base_scan", 1000, boost::bind(riceviCallback,_1,&listener));
	
  ros::spin();
  return 0;
}
