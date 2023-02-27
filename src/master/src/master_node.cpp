#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>

struct MasterNode {
  ros::NodeHandle node;
  ros::Publisher slaveOne;
  ros::Subscriber master;

  MasterNode(){
    slaveOne = node.advertise<std_msgs::String>("slaveOne", 1000);
    master = node.subscribe("master", 1000, &MasterNode::receiveMsg, this);
  }

  void receiveMsg(const std_msgs::String::ConstPtr& msg){
    ROS_INFO("Master heard: [%s]", msg->data.c_str());
  }

};

int main(int argc, char **argv)
{
  ros::init(argc, argv, "master");
  MasterNode masternode;

  ros::Rate loop_rate(10);

  while (ros::ok())
    {

      std_msgs::String msg;

      std::stringstream ss;
      ss << "hello world ";
      msg.data = ss.str();

      ROS_INFO("%s", msg.data.c_str());
    
      masternode.slaveOne.publish(msg);

      ros::spinOnce();

      loop_rate.sleep();

    }

  return 0;
}