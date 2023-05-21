#!/bin/bash
set -e

# setup ros environment
source "/opt/ros/$ROS_DISTRO/setup.bash" --
cd /tmp
catkin config --init
catkin clean --yes
#catkin build diyazen_base
#catkin build commander
catkin build duo
source devel/setup.bash
#byobu new-session -s "main" "roslaunch launch/test.launch"
#roslaunch launch/test.launch
exec "$@"
