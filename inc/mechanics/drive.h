#pragma once

#include "simulation/car.h"
#include "simulation/input.h"
#include "simulation/curve.h"

#include "mechanics/dodge.h"
#include "mechanics/wavedash.h"
#include "mechanics/boostdash.h"

#include "linear_algebra/math.h"

#include <list>
#include <vector>

class Drive {

 public:
  vec3 target;
  float speed;
  float reaction_time;

  bool finished;
  Input controls;

  Drive();

  void step(Car const& car, float dt);

  static const float max_speed;
  static const float max_throttle_speed;
  static const float boost_accel;
  static const float brake_accel;
  static const float coasting_accel;

  static float throttle_accel(float speed);
  static float max_turning_curvature(float speed);
  static float max_turning_speed(float curvature);

 private:

  void steer_controller(Car const& car, float);
  void speed_controller(Car const& car, float);


};
