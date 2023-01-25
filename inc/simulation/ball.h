#pragma once

#include "simulation/car.h"
#include "simulation/geometry.h"

#include "linear_algebra/math.h"

#include <array>

enum class BallShape : uint8_t {
  Sphere,
  Puck,
  Cube
};

class Ball {
 public:
  vec3 position;
  vec3 velocity;
  vec3 angular_velocity;
  float time;

  float dropshot_damage;
  float dropshot_absorbed;
  float dropshot_absorbed_recent;

  static const float m; // mass

  static const float drag; // viscous damping
  static const float mu; // coefficient of friction
  static const float restitution; // coefficient of restitution

  static const float v_max; // maximum velocity
  static const float w_max; // maximum angular velocity

  static const float soccar_radius;
  static const float hoops_radius;
  static const float dropshot_radius;
  static const float soccar_collision_radius;
  static const float hoops_collision_radius;
  static const float dropshot_collision_radius;

  static float radius;
  static float height;
  static float collision_radius;
  static float I; // moment of inertia

  Ball();

  void update_from_ball(Ball ball);

  float get_time() const;
  void set_time(float t);

  vec<3> get_position() const;
  void set_position(vec<3> pos);

  vec<3> get_velocity() const;
  void set_velocity(vec<3> vel);

  vec<3> get_angular_velocity() const;
  void set_angular_velocity(vec<3> ang_vel);

  sphere hitbox() const;
  void step(float dt);
  void step(float dt, const Car & c);
};
