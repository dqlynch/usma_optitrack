#include "mocap_optitrack/Quad.h"
#include "mocap_optitrack/QuadScripts.h"

int main(int argc, char** argv) {
  ros::init(argc, argv, "multiquad_script_test");
  ros::NodeHandle node;
  ros::Rate rate(FRAMES_PER_SEC);

  // Create quads
  Quad fake_point("_wand_proj");
  Quad quad1("quad01");
  Quad quad2("quad02");

  // Group quads together
  Formation form;
  form.add_quad(fake_point);
  form.add_quad(quad1);
  form.add_quad(quad2);

  form.add_script<Takeoff>(new Takeoff(0.4));
  //
  quad1.add_script(new SetPose(-1, -0.7, 1,   0, 0, 0, -1));
  quad1.back()->set_needsWandCheck(true);

  quad2.add_script(new SetPose(-1, 0.7, 1,   0, 0, 0, -1));
  quad2.back()->set_needsWandCheck(true);
  //
  quad1.add_script(new FollowOffset(WAND_ROTATE_TOP, 0));
  quad2.add_script(new FollowOffset(WAND_ROTATE_BOTTOM, 0));

  // quad1.add_script(new CatchBall);

  ROS_INFO("Starting...");

  while(node.ok()) {
    form.run();
    rate.sleep();
  }

  return 0;
}