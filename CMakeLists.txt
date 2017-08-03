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
include_directories(${PROJECT_SOURCE_DIR}/src)
include_directories(/usr/local/include)

# --------------------------------------------------
# lib dirs
# --------------------------------------------------
link_directories(/usr/local/lib)

# --------------------------------------------------
# compiler flags
# --------------------------------------------------
add_definitions(-std=c++11)

# --------------------------------------------------
# add files
# --------------------------------------------------
add_executable(senseless_soccer
src/main.cpp

src/graphics/pitch_renderable.cpp
src/graphics/player_sprite.cpp
src/graphics/ball_sprite.cpp

src/player/player.cpp
src/player/player_states/player_state.cpp
src/player/player_states/standing.cpp
src/player/player_states/running.cpp

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

src/player/locomotion/locomotion_manager.cpp
src/player/locomotion/locomotion.cpp
src/player/locomotion/arrive.cpp
src/player/locomotion/pursue.cpp
src/player/locomotion/cover.cpp

src/player/brain/brain.cpp

src/game/game.cpp

)

# --------------------------------------------------
# link libs
# --------------------------------------------------
target_link_libraries (senseless_soccer gamelib)
target_link_libraries (senseless_soccer sfml-graphics)
target_link_libraries (senseless_soccer sfml-window)
target_link_libraries (senseless_soccer sfml-system)
