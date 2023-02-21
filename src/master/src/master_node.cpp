#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>


void receiveMsg(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("Master heard: [%s]", msg->data.c_str());
};


int main(int argc, char **argv)
{

  ros::init(argc, argv, "master");


  ros::NodeHandle node;


  ros::Publisher slaveOne = node.advertise<std_msgs::String>("slaveOne", 1000);
  ros::Subscriber master = node.subscribe("master", 1000, receiveMsg);
  
  ros::Rate loop_rate(10);

  int count = 0;
  while (ros::ok())
  {

    std_msgs::String msg;

    std::stringstream ss;
    ss << "hello world " << count;
    msg.data = ss.str();

    ROS_INFO("%s", msg.data.c_str());

    slaveOne.publish(msg);

    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}