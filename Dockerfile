FROM ros:noetic-ros-core-focal 
RUN apt update 
RUN apt install -y pip
RUN apt install -y byobu
RUN apt install -y build-essential

RUN pip install catkin-tools

COPY ["customEntrypoint.sh","/customEntrypoint.sh"]
RUN chmod +x customEntrypoint.sh
COPY ["src","/tmp/src"]
RUN chmod -R 775 /tmp
ENTRYPOINT ["/customEntrypoint.sh"]
#CMD ["source", "/opt/ros/noetic/setup.bash"]
#CMD ["catkin", "clean", "--yes"]
#CMD ["catkin", "build", "diyazen_base"]
#CMD ["catkin", "build", "commander"]
#CMD ["source", "devel/setup.bash"]
#CMD ["roslaunch", "launch/test.launch"]

