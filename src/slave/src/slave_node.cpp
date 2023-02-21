#include "ros/ros.h"
#include "std_msgs/String.h"

#include <sstream>


struct Slave
{
    Slave(){
        ros::Publisher master = node.advertise<std_msgs::String>("master", 1000);
        ros::Subscriber slaveOne = node.subscribe("slaveOne", 1000, receiveMsg);
    }
    
    void receiveMsg(const std_msgs::String::ConstPtr& msg)
};

ros::NodeHandle node;

void receiveMsg(const std_msgs::String::ConstPtr& msg) {
    ROS_INFO("SlaveOne heard: [%s]", msg->data.c_str());

    std::stringstream ss;
    ss  << "SlaveOne got this message: "<< msg->data ;
    std_msgs::String msgOut;
    msgOut.data = ss.str();
    master.publish(msgOut);
};
  

  
ros::Rate loop_rate(10);



int main(int argc, char **argv)
{
  
  ros::init(argc, argv, "master");

  int count = 0;
  while (ros::ok())
  {
    
    ros::spinOnce();

    loop_rate.sleep();
    ++count;
  }


  return 0;
}

