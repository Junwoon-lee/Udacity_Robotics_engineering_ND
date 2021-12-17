#include <gazebo/gazebo.hh>

namespace gazebo
{
  class WorldPluginHumanoidRobot : public WorldPlugin
  {
    public: WorldPluginHumanoidRobot() : WorldPlugin()
            {
              printf("Welcome to LEE's World!\n");
            }

    public: void Load(physics::WorldPtr _world, sdf::ElementPtr _sdf)
            {
            }
  };
  GZ_REGISTER_WORLD_PLUGIN(WorldPluginHumanoidRobot)
}

