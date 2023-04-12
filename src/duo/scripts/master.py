#!/usr/bin/env python
# license removed for brevity
import rospy
from std_msgs.msg import String
from std_msgs.msg import ByteMultiArray
from cryptography.fernet import Fernet

class Master:
    def __init__(self):
        rospy.init_node('master')
        self.pub = rospy.Publisher('slave', ByteMultiArray, queue_size=10)
        self.sub = rospy.Subscriber("master", ByteMultiArray, self.callback)
        self.rate = rospy.Rate(1) # 10hz
        self.key = Fernet.generate_key()
        self.writekeyfile(self.key)
        self.fernet = Fernet(self.key)
        while not rospy.is_shutdown():
            hello_str = "hello slave %s" % rospy.get_time()
            encMessage = self.fernet.encrypt(hello_str.encode())
            rospy.loginfo(hello_str)
            msg = ByteMultiArray()
            msg.data = encMessage
            self.pub.publish(msg)
            self.rate.sleep()

    def callback(self,data):
        strdata = self.fernet.decrypt(bytes(bytearray(data.data))).decode()
        rospy.loginfo(rospy.get_caller_id() + " I heard %s", strdata)

    def writekeyfile(self, key):
        self.file = open("key", "wb")
        self.file.write(key)
        self.file.close()



if __name__ == '__main__':
    try:
        node = Master()
    except rospy.ROSInterruptException:
        pass
