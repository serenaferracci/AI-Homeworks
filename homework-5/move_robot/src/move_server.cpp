#include <ros/ros.h>
#include <actionlib/server/simple_action_server.h>
#include <move_robot/moveAction.h>
#include <math.h>

class moveAction{

protected:

  ros::NodeHandle nh_;
  actionlib::SimpleActionServer<move_robot::moveAction> as_; // NodeHandle instance must be created before this line. Otherwise strange error occurs.
  std::string action_name_;
  // create messages that are used to published feedback/result
  move_robot::moveResult result_;

  ros::Subscriber sub;
  bool success;
  bool set;
  float vel;
  float dis;
  float x;
  float y;

public:

  moveAction(std::string name) :
    as_(nh_, name, boost::bind(&moveAction::executeCB, this, _1), false),
    action_name_(name){
		success = false;
		set = false;
		dis = -1.0;
		sub = nh_.subscribe("odom", 10, &moveAction::chatterCallback, this);
		as_.start();
	}

  ~moveAction(void){}

  void chatterCallback(const nav_msgs::Odometry::ConstPtr& msg){
		float ax = msg->pose.pose.position.x;
		float ay = msg->pose.pose.position.y;
		if(!set) {
			x = ax;
			y = ay;
			set = true;
		}
		else if(dis >= 0){
			if(sqrt(pow(ax-x,2) + pow(ay-y,2) >= dis)) {
				success = true;
				result_.odom = *msg;
			}
		}
	}

  void executeCB(const move_robot::moveGoalConstPtr &goal){

		 dis = goal -> goal_d;
	     vel = goal -> goal_s;

		geometry_msgs::Twist m;

		ros::Publisher pub = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 10);


    while(!success){

		  m.linear.x = vel;

		  pub.publish(m);

	      if (as_.isPreemptRequested() || !ros::ok()){
	        ROS_INFO("%s: Preempted", action_name_.c_str());
	        as_.setPreempted();
	        success = false;
	        break;
	      }
    }

    if(success){
      ROS_INFO("%s: Succeeded", action_name_.c_str());
      as_.setSucceeded(result_);
    }
		success = false;
		set = false;
  }
};


int main(int argc, char** argv) {
  ros::init(argc, argv, "move_server");

  moveAction move("move_server");
  ros::spin();

  return 0;
}
