#include "ros/ros.h"
#include "ball_chaser/DriveToTarget.h"
#include <sensor_msgs/Image.h>
using namespace std;

// Define a global client that can request services
ros::ServiceClient client;

// This function calls the command_robot service to drive the robot in the specified direction
void drive_robot(float lin_x, float ang_z)
{
    ROS_INFO_STREAM("Driving the robot");

    // TODO: Request a service and pass the velocities to it to drive the robot
    ball_chaser::DriveToTarget srv;

    srv.request.linear_x = lin_x;
    srv.request.angular_z = ang_z;

    // Call the command_robot service and pass the requested motor commands
    if (!client.call(srv))
    {
        ROS_ERROR("Failed to call service command_robot");
    }

}

// This callback function continuously executes and reads the image data
void process_image_callback(const sensor_msgs::Image img)
{

    // TODO: Loop through each pixel in the image and check if there's a bright white one
    // Then, identify if this pixel falls in the left, mid, or right side of the image
    // Depending on the white ball position, call the drive_bot function and pass velocities to it
    // Request a stop when there's no white ball seen by the camera


    
    int ball_position;
    float ball_position_ture = 0;
    int width_max_index = img.data.size();
    bool ball_detector = false;
    int i = 0;

    while (ball_detector == false)
    {
	

        if ((img.data[i] == 255) && (img.data[i+1] == 255) && (img.data[i+2] == 255))
        {
            
	    ball_position = i+1;
	    ball_detector = true;
        }
	else if(i < img.data.size()-2){

	i++;
	
	}
	else if(i == img.data.size()-2){
	break;
	}

    }
    
    if (ball_detector == false)
    {
        drive_robot(0, 0);
    }

    else
    {
        ball_position_ture = (ball_position/3) % img.width;
        
        if(ball_position_ture < img.width / 3)
        {
            drive_robot(0.1, 0.2);
        }
        else if(ball_position_ture > img.width * 2/3)
        {
            drive_robot(0.1, -0.2);
        }
        else
        {
            drive_robot(0.1, 0);
        }
    }


}

int main(int argc, char** argv)
{
    // Initialize the process_image node and create a handle to it
    ros::init(argc, argv, "process_image");
    ros::NodeHandle n;

    // Define a client service capable of requesting services from command_robot
    client = n.serviceClient<ball_chaser::DriveToTarget>("/ball_chaser/command_robot");

    // Subscribe to /camera/rgb/image_raw topic to read the image data inside the process_image_callback function
    ros::Subscriber sub1 = n.subscribe("/camera/rgb/image_raw", 10, process_image_callback);

    // Handle ROS communication events
    ros::spin();

    return 0;
}

