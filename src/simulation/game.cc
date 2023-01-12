#include "simulation/game.h"
#include "simulation/ball.h"
#include "simulation/field.h"

#include <thread>
#include <chrono>
#include <fstream>
#include <iostream>

vec3 Game::gravity = {0.0f, 0.0f, -650.0f};
std::string Game::map = "map_not_set";
std::string Game::mode = "mode_not_set";

Game::Game() {
  frame = -1;

  score[0] = 0;
  score[1] = 0;

  time = -1.0f;
  time_remaining = -1.0f;

  state = GameState::Inactive;
}

void Game::set_mode(std::string gamemode) {
  mode = gamemode;

  std::cout << "setting mode: " << mode << std::endl;

  if (mode == std::string("soccar")) {
    Field::initialize_soccar();
    Ball::radius = Ball::soccar_radius;
    Ball::collision_radius = Ball::soccar_collision_radius;
    Ball::I = 0.4f * Ball::m * Ball::radius * Ball::radius;
  } else if (mode == std::string("hoops")) {
    Field::initialize_hoops();
    Ball::radius = Ball::hoops_radius;
    Ball::collision_radius = Ball::hoops_collision_radius;
    Ball::I = 0.4f * Ball::m * Ball::radius * Ball::radius;
  } else if (mode == std::string("dropshot")) {
    Field::initialize_dropshot();
    Ball::radius = Ball::dropshot_radius;
    Ball::collision_radius = Ball::dropshot_collision_radius;
    Ball::I = 0.4f * Ball::m * Ball::radius * Ball::radius;
  } else if (mode == std::string("throwback")) {
    Field::initialize_throwback();
    Ball::radius = Ball::soccar_radius;
    Ball::collision_radius = Ball::soccar_collision_radius;
    Ball::I = 0.4f * Ball::m * Ball::radius * Ball::radius;
  } else {
    std::cout << "invalid gametype, use one of the following:" << std::endl;
    std::cout << "\"soccar\"" << std::endl;
    std::cout << "\"hoops\"" << std::endl;
    std::cout << "\"dropshot\"" << std::endl;
    std::cout << "\"throwback\"" << std::endl;
  }
}

void Game::resize_pads(int num_pads) {
  if (num_pads != pads.size()) {
    pads.resize(num_pads);
  }
}

void Game::reset_pad(int index, std::array<float, 3> position, bool is_full_boost) {
  pads[index].position = { position[0], position[1], position[2] };
  pads[index].type = is_full_boost ? BoostPadType::Full : BoostPadType::Partial;
  pads[index].state = BoostPadState::Available;
  pads[index].timer = 0.0f;
  pads[index].actor_id = 0;
}

void Game::resize_goals(int num_goals) {
  if (num_goals != goals.size()) {
    goals.resize(num_goals);
  }
}

void Game::reset_goal(int index, std::array<float, 3> position, std::array<float, 3> direction, float width, float height, int team) {
  goals[index].position = { position[0], position[1], position[2] };
  goals[index].direction = { direction[0], direction[1], direction[2] };
  goals[index].width = width;
  goals[index].height = height;
  goals[index].team = team;
  goals[index].state = GoalState::Unknown;
}

void Game::set_game_info(float current_time, float game_time_remaining, float gravity_z, bool is_match_ended, bool is_round_active, bool is_kickoff_pause) {
  time_delta = current_time - time;
  time = current_time;
  time_remaining = game_time_remaining;
  gravity = {0.0f, 0.0f, gravity_z};

  if (is_match_ended) {
    state = GameState::Ended;
  } else {
    if (is_round_active) {
      if (is_kickoff_pause) {
        state = GameState::Kickoff;
      } else {
        state = GameState::Active;
      }
    } else {
      state = GameState::Inactive;
    }
  }
}

void Game::resize_cars(int num_cars) {
  if (num_cars != cars.size()) {
      cars.resize(num_cars);
  }
}

Ball Game::get_ball() {
  return ball;
}
