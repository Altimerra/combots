#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

struct SlaveNode {
  ros::NodeHandle node;
  ros::Publisher master;
  ros::Subscriber slaveOne;
  
  SlaveNode(){
    master = node.advertise<std_msgs::String>("master", 1000);
    slaveOne = node.subscribe("slaveOne", 1000, &SlaveNode::receiveMsg, this);
  }

  void receiveMsg(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("SlaveOne heard: [%s]", msg->data.c_str());
    std::stringstream ss;
    ss  << "SlaveOne got this message: "<< msg->data ;
    std_msgs::String msgOut;
    msgOut.data = ss.str();
    master.publish(msgOut);
  }

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "slaveOne");
  SlaveNode slavenode;
  ros::spin();
  return 0;
}

