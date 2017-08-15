#include "player_sprite.h"

#include <cmath>
#include <iostream>
#include <gamelib/math/vector3.h>

namespace SenselessSoccer {

PlayerSprite::PlayerSprite(const std::string &filename, unsigned int number_rows, unsigned int number_cols) :
    GameLib::Sprite(filename, number_rows, number_cols) {
    z_order = 10;
    last_angle = 0;
    int anim_speed = 100;

    //  set up animation frames - dependent on the spriteset png image
    std::vector<int> frames_stand_east;
    std::vector<int> frames_stand_southeast;
    std::vector<int> frames_stand_south;
    std::vector<int> frames_stand_southwest;
    std::vector<int> frames_stand_west;
    std::vector<int> frames_stand_northwest;
    std::vector<int> frames_stand_north;
    std::vector<int> frames_stand_northeast;

    std::vector<int> frames_run_east;
    std::vector<int> frames_run_southeast;
    std::vector<int> frames_run_south;
    std::vector<int> frames_run_southwest;
    std::vector<int> frames_run_west;
    std::vector<int> frames_run_northwest;
    std::vector<int> frames_run_north;
    std::vector<int> frames_run_northeast;

//     std::vector<int> frames_throw_east;
//     std::vector<int> frames_throw_southeast;
//     std::vector<int> frames_throw_south;
//     std::vector<int> frames_throw_southwest;
//     std::vector<int> frames_throw_west;
//     std::vector<int> frames_throw_northwest;
//     std::vector<int> frames_throw_north;
//     std::vector<int> frames_throw_northeast;

    //
    // STANDING FRAMES
    //
    frames_stand_east.push_back(1);
    frames_stand_southeast.push_back(4);
    frames_stand_south.push_back(7);
    frames_stand_southwest.push_back(10);
    frames_stand_west.push_back(13);
    frames_stand_northwest.push_back(16);
    frames_stand_north.push_back(19);
    frames_stand_northeast.push_back(22);

    //
    // RUNNING FRAMES
    //
    frames_run_east.push_back(0);
    frames_run_east.push_back(1);

    frames_run_southeast.push_back(3);
    frames_run_southeast.push_back(5);

    frames_run_south.push_back(6);
    frames_run_south.push_back(8);

    frames_run_southwest.push_back(9);
    frames_run_southwest.push_back(11);

    frames_run_west.push_back(12);
    frames_run_west.push_back(13);

    frames_run_northwest.push_back(15);
    frames_run_northwest.push_back(17);

    frames_run_north.push_back(18);
    frames_run_north.push_back(20);

    frames_run_northeast.push_back(21);
    frames_run_northeast.push_back(23);

    AddAnimation("stand_east", anim_speed, true, frames_stand_east);
    AddAnimation("stand_southeast", anim_speed, true, frames_stand_southeast);
    AddAnimation("stand_south", anim_speed, true, frames_stand_south);
    AddAnimation("stand_southwest", anim_speed, true, frames_stand_southwest);
    AddAnimation("stand_west", anim_speed, true, frames_stand_west);
    AddAnimation("stand_northwest", anim_speed, true, frames_stand_northwest);
    AddAnimation("stand_north", anim_speed, true, frames_stand_north);
    AddAnimation("stand_northeast", anim_speed, true, frames_stand_northeast);

    standing_animation_map.insert(std::make_pair(45, "stand_southeast"));
    standing_animation_map.insert(std::make_pair(90, "stand_south"));
    standing_animation_map.insert(std::make_pair(135, "stand_southwest"));
    standing_animation_map.insert(std::make_pair(180, "stand_west"));
    standing_animation_map.insert(std::make_pair(-135, "stand_northwest"));
    standing_animation_map.insert(std::make_pair(-90, "stand_north"));
    standing_animation_map.insert(std::make_pair(-45, "stand_northeast"));
    standing_animation_map.insert(std::make_pair(0, "stand_east"));


    AddAnimation("run_east", anim_speed, true, frames_run_east);
    AddAnimation("run_southeast", anim_speed, true, frames_run_southeast);
    AddAnimation("run_south", anim_speed, true, frames_run_south);
    AddAnimation("run_southwest", anim_speed, true, frames_run_southwest);
    AddAnimation("run_west", anim_speed, true, frames_run_west);
    AddAnimation("run_northwest", anim_speed, true, frames_run_northwest);
    AddAnimation("run_north", anim_speed, true, frames_run_north);
    AddAnimation("run_northeast", anim_speed, true, frames_run_northeast);

    movement_animation_map.insert(std::make_pair(45, "run_southeast"));
    movement_animation_map.insert(std::make_pair(90, "run_south"));
    movement_animation_map.insert(std::make_pair(135, "run_southwest"));
    movement_animation_map.insert(std::make_pair(180, "run_west"));
    movement_animation_map.insert(std::make_pair(-135, "run_northwest"));
    movement_animation_map.insert(std::make_pair(-90, "run_north"));
    movement_animation_map.insert(std::make_pair(-45, "run_northeast"));
    movement_animation_map.insert(std::make_pair(0, "run_east"));

    SetAnimation("stand_south");
}

void PlayerSprite::UpdateAnimation(GameLib::Vector3 &vel, float angle) {
    if(vel.magnitude()) {

        // run direction of magnitude
        last_angle = vel.roundAngle(45).angle();
        auto it = movement_animation_map.find(round(last_angle));

        if(it != movement_animation_map.end()) {
            SetAnimation((*it).second);

            if(shadow) {
                shadow->SetAnimation((*it).second);
            }
        }

    } else {

        // face ball
        auto it = standing_animation_map.find(round(angle));

        if(it != standing_animation_map.end()) {
            SetAnimation((*it).second);

            if(shadow) {
                shadow->SetAnimation((*it).second);
            }
        }
    }
}

void PlayerSprite::Render(GameLib::Window &window) {
    GameLib::Sprite::Render(window);

#ifdef RENDER_DEBUG

    if(circle1.radius) {
        GameLib::Primitives::Circle(window, circle1.x, circle1.y, circle1.radius);
    }

    if(circle2.radius) {
        GameLib::Primitives::Circle(window, circle2.x, circle2.y, circle2.radius);
    }

#endif
}

}// SenselessSoccer




