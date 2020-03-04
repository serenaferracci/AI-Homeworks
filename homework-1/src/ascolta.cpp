#include "ros/ros.h"
#include "std_msgs/String.h"
#include <limits.h>
#include "sensor_msgs/LaserScan.h"

ros::Publisher pub;

void riceviCallback(const sensor_msgs::LaserScan::ConstPtr& sensore)
{	
    double minimo = DBL_MAX;
	
    int count = (sensore->ranges).size();
    count--;
    
    while(count >= 0)
    {	
	double n = (sensore->ranges)[count];
	if(n < minimo) minimo = n;
	count--;
    }
	
  if(ros::ok())
  {
	std_msgs::String msg;
	std::stringstream ss;
	ss << "Minimo misurato: " << minimo;
	msg.data = ss.str();
	ROS_INFO("%s", msg.data.c_str());
	pub.publish(msg);
   }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "ascolta");

  ros::NodeHandle n;
	
  pub = n.advertise<std_msgs::String>("stampa", 1000);
  ros::Subscriber sub = n.subscribe("base_scan", 1000, riceviCallback);

  ros::spin();
  return 0;
}
