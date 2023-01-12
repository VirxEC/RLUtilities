#pragma once

#include <array>
#include <fstream>
#include <string>
#include <vector>

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

  void resize_pads(int num_pads);
  void reset_pad(int index, std::array<float, 3> position, bool is_full_boost);

  void resize_goals(int num_goals);
  void reset_goal(int index, std::array<float, 3> position, std::array<float, 3> direction, float width, float height, int team);

  void set_game_info(float current_time, float time_remaining, float gravity_z, bool is_match_ended, bool is_round_active, bool is_kickoff_pause);

  void resize_cars(int num_cars);
};
