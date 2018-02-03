# --------------------------------------------------
# cmake version
# --------------------------------------------------
cmake_minimum_required (VERSION 2.6)

# --------------------------------------------------
# project name
# --------------------------------------------------
project (senseless_soccer)

# --------------------------------------------------
# environment variables
# --------------------------------------------------
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# --------------------------------------------------
# include dirs
# --------------------------------------------------
#include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(/usr/local/include)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(${PROJECT_SOURCE_DIR}/libs)
link_directories(/usr/local/lib)

# --------------------------------------------------
# compiler flags
# --------------------------------------------------
add_definitions(-std=c++11 -DSFML_STATIC)

# --------------------------------------------------
# add files
# --------------------------------------------------
add_executable(senseless_soccer
src/main.cpp
src/graphics/pitch_renderable.cpp
src/graphics/player_sprite.cpp
src/graphics/ball_sprite.cpp
src/kit/kit_factory.cpp
src/player/player.cpp
src/player/player_factory.cpp
src/player/player_states/player_state.cpp
src/player/player_states/standing.cpp
src/player/player_states/running.cpp
src/player/player_states/sliding.cpp
src/player/brain/brain.cpp
src/player/brain/brainstates/brainstate.cpp
src/player/brain/brainstates/brainstate_idle.cpp
src/player/brain/brainstates/brainstate_dribble.cpp
src/player/brain/brainstates/brainstate_getball.cpp
src/player/brain/brainstates/brainstate_cover.cpp
src/player/brain/brainstates/brainstate_support.cpp
src/player/brain/brainstates/brainstate_dribble.cpp
src/player/brain/brainstates/brainstate_pass.cpp
src/player/brain/brainstates/brainstate_receive.cpp
src/player/brain/brainstates/brainstate_shoot.cpp
src/player/brain/brainstates/brainstate_press.cpp
src/player/brain/brainstates/brainstate_clear.cpp
src/player/locomotion/locomotion_manager.cpp
src/player/locomotion/locomotion.cpp
src/player/locomotion/arrive.cpp
src/player/locomotion/pursue.cpp
src/player/locomotion/head.cpp
src/player/locomotion/intercept.cpp
src/ball/ball.cpp
src/match/match.cpp
src/match/match_states/match_state.cpp
src/match/match_states/state_play.cpp
src/team/team.cpp
src/team/team_states/team_state.cpp
src/team/team_states/team_play.cpp
src/team/roles/role.cpp
src/metrics/metrics.cpp
src/pitch/pitch.cpp
src/joysticker/controller.cpp
src/joysticker/cpu/controller_simulator.cpp
src/joysticker/cpu/simulated_actions/simulated_sequence.cpp
src/joysticker/cpu/simulated_actions/simulate_clearance.cpp
src/joysticker/cpu/simulated_actions/simulate_nothing.cpp
src/game/game.cpp
src/globals.cpp
)

# --------------------------------------------------
# link libs
# --------------------------------------------------
target_link_libraries (senseless_soccer gamelib)
target_link_libraries (senseless_soccer sfml-graphics-d)
target_link_libraries (senseless_soccer sfml-window-d)
target_link_libraries (senseless_soccer sfml-system-d)


#target_link_libraries (senseless_soccer gamelib)
#target_link_libraries (senseless_soccer sfml-graphics-s)
#target_link_libraries (senseless_soccer sfml-window-s)
#target_link_libraries (senseless_soccer sfml-system-s)

#target_link_libraries (senseless_soccer X11)
#target_link_libraries (senseless_soccer X11-xcb)
#target_link_libraries (senseless_soccer xcb)
#target_link_libraries (senseless_soccer xcb-randr)
#target_link_libraries (senseless_soccer freetype)
#target_link_libraries (senseless_soccer Xrandr)
#target_link_libraries (senseless_soccer GL)
#target_link_libraries (senseless_soccer jpeg)
#target_link_libraries (senseless_soccer udev)
#target_link_libraries (senseless_soccer pthread)


