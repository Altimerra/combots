#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
from std_msgs.msg import ByteMultiArray
from cryptography.fernet import Fernet

class Slave:
    def __init__(self):
        rospy.init_node('slave', anonymous=True)
        self.pub = rospy.Publisher('master', ByteMultiArray, queue_size=10)
        self.sub = rospy.Subscriber("slave", ByteMultiArray, self.callback)
        self.fernet = Fernet(self.readkeyfile())

        self.rate = rospy.Rate(1) # 10hz
        #rospy.spin()
        while not rospy.is_shutdown():
            hello_str = "hello master %s" % rospy.get_time()
            rospy.loginfo(hello_str)
            self.rate.sleep()
    
    def callback(self,data):
        strdata = self.fernet.decrypt(bytes(bytearray(data.data))).decode()
        rospy.loginfo(rospy.get_caller_id() + " I heard %s", strdata)
        hello_str = "hello master %s" % rospy.get_time()
        encMessage = self.fernet.encrypt(hello_str.encode())
        msg = ByteMultiArray()
        msg.data = encMessage
        self.pub.publish(msg)
    

    def readkeyfile(self):
        self.file = open("key", "rb")
        key = self.file.read()
        self.file.close()
        return key

if __name__ == '__main__':
    try:
        node = Slave()
    except rospy.ROSInterruptException:
        pass
