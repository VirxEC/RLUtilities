#pragma once

#include <array>
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include "simulation/ball.h"
#include "simulation/car.h"
#include "simulation/goal.h"
#include "simulation/boost_pad.h"

#include "rust/cxx.h"

#ifdef GENERATE_PYTHON_BINDINGS
#include <pybind11/pybind11.h>
#endif

enum class GameState {
  Inactive,
  Countdown,
  Kickoff,
  Active,
  GoalScored,
  Replay,
  Paused,
  Ended
};

enum class GameMode {
  Unknown, 
  Soccar, 
  Hoops, 
  Snowday, 
  Rumble, 
  Dropshot 
};

struct Game {
  Game();

  int frame;
  int score[2];

  float time;
  float time_remaining;

  float time_delta;

  GameState state;

  static vec3 gravity;
  static std::string map;
  static std::string mode;

  Ball ball;

  std::vector<Car> cars;

  std::vector<BoostPad> pads;

  std::vector<Goal> goals;

  static void set_mode(std::string);

  #ifdef GENERATE_PYTHON_BINDINGS
  void read_field_info(const pybind11::object& field_info);
  void read_packet(const pybind11::object& packet);
  #endif

  void resize_goals(int num_goals);
  void reset_goal(int index, vec<3> position, vec<3> direction, float width, float height, int team);

  void resize_cars(int num_cars);
  void reset_car_physics(int index, vec<3> position, vec<3> velocity, vec<3> angular_velocity, vec<3> rotation);
  const Car& get_car(int index) const;
};

void set_mode(const rust::String);

std::unique_ptr<std::vector<BoostPad>> new_boostpad_vec();
std::unique_ptr<std::vector<Goal>> new_goal_vec();
