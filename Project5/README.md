# Project5. Home Service Robot

Goal
-----
   　First, Turtlebot map an environment (save the map file). Second, By using map turtlebot navigate to the virtual 　　　object. Finally, turtlebot pick up (virtually) then drop off it at the desirable location.
   
Packages & Files
--------------------
    add_markers
    map
    pick_objects
    rviz_Config
    scripts
    slam_gmapping
    turtlebot
    turtlebot_interations
    turtlebot_simulator
    
Description
-------------
    Environment Construction: Gazebo Building editor + turtlebot_gazebo pkg for robot model.
    Mapping: turtlebot_telop pkg (for Manually test) + slam_gmapping pkg (Slam pkg) intergrated by test_slam.sh
    Navigation: Map by <test_slam.sh> + Amcl pkg for localization of turtlebot + navigation algorithm using   
                Dijkstra's algorithm, a variant of the Uniform Cost Search algorithm (roscpp pkg) intergrated by  
                test_navigation.sh, pick_objects.sh
    Virtual object Modeling (Add_markers): First, taking robot_pose from odometry information (nav_msg/Odometry.h) 
                             Second, calculate distance between robot and goals 
                             Third, according to distance visualize virtual object (visualization_msgs/Marker.h)
                             
    Finally, home_service.sh intergrate rviz launcher + turtlebot_gazebo + add_markers(Virtual object Modeling) + 
       pick_objects.sh(amcl localization algorithm based mapped map, route search algorithm)
                          
                             