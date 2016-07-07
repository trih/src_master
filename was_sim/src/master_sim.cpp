#include "ros/ros.h"
#include "std_msgs/UInt32.h"
#include "std_msgs/String.h"
#include "sensor_msgs/Range.h"

float range;

void range_sensor_callback(const sensor_msgs::Range::ConstPtr& msg) {
        ROS_INFO("Range: [%.2f] mm", msg->range);
	range = msg->range;
}

void lineTracking_sensor_callback(const std_msgs::UInt32::ConstPtr& msg) {
        ROS_INFO("Line Tracking value: [%d]", msg->data);
}

int main(int argc, char **argv) {
        ros::init(argc, argv, "master");

        ros::NodeHandle masterNode;
        ros::Subscriber range_sub = masterNode.subscribe("/was_sensor/range/ultrasound", 1000, range_sensor_callback);
        ros::Subscriber lineTracking_sub = masterNode.subscribe("/was_sensor/movement/lineTracking", 1000, lineTracking_sensor_callback);

	ros::Publisher motor_pub = masterNode.advertise<std_msgs::String>("motor", 1000);
	while (ros::ok()) {
		std_msgs::String motor_msg;
	 	if (range>1000)
			motor_msg.data = "Going";
		else
			motor_msg.data = "Stop";	
		motor_pub.publish(motor_msg);
		
		ros::spinOnce();
	}
        //ros::spin();
        
        return 0;
}
