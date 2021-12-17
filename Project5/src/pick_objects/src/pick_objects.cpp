#include <ros/ros.h>
#include <move_base_msgs/MoveBaseAction.h>
#include <actionlib/client/simple_action_client.h>

typedef actionlib::SimpleActionClient<move_base_msgs::MoveBaseAction> MoveBaseClient;

float P_X = 3.0;
float P_Y = 1.0;
float D_X = -6.0;
float D_Y = -1.0;

int main(int argc, char **argv)
{
  ros::init(argc, argv, "pick_objects");

  //tell the action client that we want to spin a thread by default
  MoveBaseClient ac("move_base", true);

  //wait for the action server to come up
  while (!ac.waitForServer(ros::Duration(2.0)))
  {
    ROS_INFO("Waiting for the move_base action server to come up");
  }

  move_base_msgs::MoveBaseGoal goal;

  goal.target_pose.header.frame_id = "map";
  goal.target_pose.header.stamp = ros::Time::now();

  goal.target_pose.pose.position.x = P_X;
  goal.target_pose.pose.position.y = P_Y;
  goal.target_pose.pose.orientation.w = 1.0;

  ROS_INFO("Robot is travelling to the pickup zone");
  ac.sendGoal(goal);
  ac.waitForResult();

  if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
  {

    ROS_INFO("Robot picked up the virtual object");
    
    ros::Duration(2).sleep();

    goal.target_pose.pose.position.x = D_X;
    goal.target_pose.pose.position.y = D_Y;
    goal.target_pose.pose.orientation.w = 1.0;

    ROS_INFO("Robot -> dropoff zone");
    ac.sendGoal(goal);
    ac.waitForResult();
    if (ac.getState() == actionlib::SimpleClientGoalState::SUCCEEDED)
    { 
      ROS_INFO("Robot -> drop the object");
    }else
    {
      ROS_INFO("Dropoff zone Error");
    }
    }else
    {
      ROS_INFO("Pickup zone Error");
    }

  return 0;
}
