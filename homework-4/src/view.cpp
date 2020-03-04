#include "ros/ros.h"
#include "std_msgs/String.h"
#include <limits.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/opencv.hpp>
#include <math.h>
#include <iostream>

//importa sensor_msg
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
	
	float min = sensore->angle_min;
	float max = sensore->angle_max;
	float i = sensore->angle_increment;
	
	cv::Mat img(1000, 1000, CV_8UC3, cv::Scalar(255,255,255));
	cv::namedWindow("Robot");
	count = 1;
	int c = (sensore->ranges).size();
	
	while(count < c)
	{
		int scala = -40;
		printf("x: %f, y: %f\n",scala*(sensore->ranges)[count]*cos(max),scala*(sensore->ranges)[count]*sin(max));
		cv::Point2f* p1 = new cv::Point2f(scala*(sensore->ranges)[count]*cos(max)+400,scala*(sensore->ranges)[count]*sin(max)+400);
		if((sensore->ranges)[count] == minimo)
		{
			cv::circle(img, *p1, 10, cv::Scalar(0,255,0), 1, cv::LINE_8, 0);
		}
		max -= i;
		count++;
		cv::Point2f* p2 = new cv::Point2f(scala*(sensore->ranges)[count]*cos(max)+400,scala*(sensore->ranges)[count]*sin(max)+400);
		cv::line(img, *p1, *p2, cv::Scalar(0,0,255), 1, cv::LINE_8, 0);
	}
	
	cv::imshow("Robot", img);
	cv::waitKey(30);
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
