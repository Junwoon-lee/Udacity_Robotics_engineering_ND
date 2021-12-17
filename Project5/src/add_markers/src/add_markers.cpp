#include <ros/ros.h>
#include <visualization_msgs/Marker.h>
#include <nav_msgs/Odometry.h>
#include <math.h>


float P_x = 3.0;
float P_y = 1.0;
float D_x = -6.0;
float D_y = -1.0;


float threshold = 0.1;

int state = -1; // state = 0 (pickup)  ,  state = 1 (dropoff)

void odometry_cb(const nav_msgs::Odometry::ConstPtr& msg) 
{
	float robot_x = msg->pose.pose.position.x;
	float robot_y = msg->pose.pose.position.y;
	
	float pickup_distance;
	float dropoff_distance;
	
	if(state != 0 && state != 1)
	{
		pickup_distance = abs(P_x - robot_x) + abs(P_y - robot_y);
		
		if(pickup_distance < threshold)
		{
			ROS_INFO("Robot in pick up zone");
			state = 0;
		}
	}
	if(state == 0)
	{
		dropoff_distance = abs(D_x - robot_x) + abs(D_y - robot_y);
		
		
		if(dropoff_distance < threshold)
		{
			ROS_INFO("Robot in dropoff up zone");
			state = 1;
		}
	}
}

int main( int argc, char** argv )
{
	ros::init(argc, argv, "add_markers");
  	ros::NodeHandle n;
  	ros::Rate r(1);
  	ros::Publisher marker_pub = n.advertise<visualization_msgs::Marker>("visualization_marker", 1);
  	ros::Subscriber odometry_sub = n.subscribe("/odom", 1000, odometry_cb);

  	uint32_t shape = visualization_msgs::Marker::CUBE;
  	visualization_msgs::Marker marker;
  	marker.header.frame_id = "map";
  	marker.header.stamp = ros::Time::now();
  	marker.ns = "basic_shapes";
  	marker.id = 0;
  	marker.type = shape;
  	marker.action = visualization_msgs::Marker::ADD;
  	marker.scale.x = 0.7;
  	marker.scale.y = 0.7;
  	marker.scale.z = 0.7;
  	marker.color.r = 0.0f;
  	marker.color.g = 1.0f;
  	marker.color.b = 0.0f;
  	marker.color.a = 1.0;
	marker.pose.position.x = P_x;
  	marker.pose.position.y = P_y;
  	marker.pose.position.z = 0;
  	marker.pose.orientation.x = 0.0;
  	marker.pose.orientation.y = 0.0;
  	marker.pose.orientation.z = 0.0;
  	marker.pose.orientation.w = 1.0;
	
	marker.lifetime = ros::Duration();

  	while (ros::ok())
  	{
		
		while (marker_pub.getNumSubscribers() < 1)
		{
			if (!ros::ok())
			{
				return 0;
			}
			ROS_WARN_ONCE("Please create a subscriber to the marker");
			sleep(1);
		}
		
		if(state == 0)
		{
			marker.action = visualization_msgs::Marker::DELETE;
			ros::Duration(5.0).sleep();
		}
		
		if(state == 1)
		{
			marker.pose.position.x = D_x;
			marker.pose.position.y = D_y;
			marker.action = visualization_msgs::Marker::ADD;
			ros::Duration(5.0).sleep();
		}
		
		marker_pub.publish(marker);
		
		ros::spinOnce();
	}
	
	return 0;
}
