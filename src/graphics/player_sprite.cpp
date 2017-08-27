#include "player_sprite.h"

#include <cmath>
#include <iostream>
#include <gamelib/math/vector3.h>


namespace SenselessSoccer {

PlayerSprite::PlayerSprite(const std::string &filename, unsigned int number_rows, unsigned int number_cols) :
    GameLib::Sprite(filename, number_rows, number_cols),
    text("fonts/terminus.ttf", 18, "test") {
    z_order = 10;
    last_angle = 0;
    int anim_speed = 100;

    // tmp vector for standing frames
    std::vector<int> frames_stand_east;
    std::vector<int> frames_stand_southeast;
    std::vector<int> frames_stand_south;
    std::vector<int> frames_stand_southwest;
    std::vector<int> frames_stand_west;
    std::vector<int> frames_stand_northwest;
    std::vector<int> frames_stand_north;
    std::vector<int> frames_stand_northeast;

    // tmp vector for running frames
    std::vector<int> frames_run_east;
    std::vector<int> frames_run_southeast;
    std::vector<int> frames_run_south;
    std::vector<int> frames_run_southwest;
    std::vector<int> frames_run_west;
    std::vector<int> frames_run_northwest;
    std::vector<int> frames_run_north;
    std::vector<int> frames_run_northeast;

    // tmp vector for sliding frames
    std::vector<int> frames_slide_east;
    std::vector<int> frames_slide_southeast;
    std::vector<int> frames_slide_south;
    std::vector<int> frames_slide_southwest;
    std::vector<int> frames_slide_west;
    std::vector<int> frames_slide_northwest;
    std::vector<int> frames_slide_north;
    std::vector<int> frames_slide_northeast;

    // specify animation frames from spritesheet (standing)
    frames_stand_east.      push_back(1);
    frames_stand_southeast. push_back(4);
    frames_stand_south.     push_back(7);
    frames_stand_southwest. push_back(10);
    frames_stand_west.      push_back(13);
    frames_stand_northwest. push_back(16);
    frames_stand_north.     push_back(19);
    frames_stand_northeast. push_back(22);

    // add animations
    AddAnimation("stand_east",      anim_speed, true, frames_stand_east);
    AddAnimation("stand_southeast", anim_speed, true, frames_stand_southeast);
    AddAnimation("stand_south",     anim_speed, true, frames_stand_south);
    AddAnimation("stand_southwest", anim_speed, true, frames_stand_southwest);
    AddAnimation("stand_west",      anim_speed, true, frames_stand_west);
    AddAnimation("stand_northwest", anim_speed, true, frames_stand_northwest);
    AddAnimation("stand_north",     anim_speed, true, frames_stand_north);
    AddAnimation("stand_northeast", anim_speed, true, frames_stand_northeast);

    // specify animation frames from spritesheet (running)
    frames_run_east.        push_back(0);
    frames_run_east.        push_back(1);

    frames_run_southeast.   push_back(3);
    frames_run_southeast.   push_back(5);

    frames_run_south.       push_back(6);
    frames_run_south.       push_back(8);

    frames_run_southwest.   push_back(9);
    frames_run_southwest.   push_back(11);

    frames_run_west.        push_back(12);
    frames_run_west.        push_back(13);

    frames_run_northwest.   push_back(15);
    frames_run_northwest.   push_back(17);

    frames_run_north.       push_back(18);
    frames_run_north.       push_back(20);

    frames_run_northeast.   push_back(21);
    frames_run_northeast.   push_back(23);

    // add animations
    AddAnimation("run_east",        anim_speed, true, frames_run_east);
    AddAnimation("run_southeast",   anim_speed, true, frames_run_southeast);
    AddAnimation("run_south",       anim_speed, true, frames_run_south);
    AddAnimation("run_southwest",   anim_speed, true, frames_run_southwest);
    AddAnimation("run_west",        anim_speed, true, frames_run_west);
    AddAnimation("run_northwest",   anim_speed, true, frames_run_northwest);
    AddAnimation("run_north",       anim_speed, true, frames_run_north);
    AddAnimation("run_northeast",   anim_speed, true, frames_run_northeast);

    // specify animation frames from spritesheet (running)
//     frames_slide_east.        push_back(24);
//     frames_slide_east.        push_back(25);
    frames_slide_east.        push_back(26);

//     frames_slide_southeast.   push_back(27);
//     frames_slide_southeast.   push_back(28);
    frames_slide_southeast.   push_back(29);

//     frames_slide_south.       push_back(30);
//     frames_slide_south.       push_back(31);
    frames_slide_south.       push_back(32);

//     frames_slide_southwest.   push_back(33);
//     frames_slide_southwest.   push_back(34);
    frames_slide_southwest.   push_back(35);

//     frames_slide_west.        push_back(36);
//     frames_slide_west.        push_back(37);
    frames_slide_west.        push_back(38);

//     frames_slide_northwest.   push_back(39);
//     frames_slide_northwest.   push_back(40);
    frames_slide_northwest.   push_back(41);

//     frames_slide_north.       push_back(42);
//     frames_slide_north.       push_back(43);
    frames_slide_north.       push_back(44);

//     frames_slide_northeast.   push_back(45);
//     frames_slide_northeast.   push_back(46);
    frames_slide_northeast.   push_back(47);

    // add animations
    AddAnimation("slide_east",        anim_speed, false, frames_slide_east);
    AddAnimation("slide_southeast",   anim_speed, false, frames_slide_southeast);
    AddAnimation("slide_south",       anim_speed, false, frames_slide_south);
    AddAnimation("slide_southwest",   anim_speed, false, frames_slide_southwest);
    AddAnimation("slide_west",        anim_speed, false, frames_slide_west);
    AddAnimation("slide_northwest",   anim_speed, false, frames_slide_northwest);
    AddAnimation("slide_north",       anim_speed, false, frames_slide_north);
    AddAnimation("slide_northeast",   anim_speed, false, frames_slide_northeast);

    // map for easy access to animation frames depedning on direction (standing)
    standing_animation_map.insert(std::make_pair(45, "stand_southeast"));
    standing_animation_map.insert(std::make_pair(90, "stand_south"));
    standing_animation_map.insert(std::make_pair(135, "stand_southwest"));
    standing_animation_map.insert(std::make_pair(180, "stand_west"));
    standing_animation_map.insert(std::make_pair(-135, "stand_northwest"));
    standing_animation_map.insert(std::make_pair(-90, "stand_north"));
    standing_animation_map.insert(std::make_pair(-45, "stand_northeast"));
    standing_animation_map.insert(std::make_pair(0, "stand_east"));

    // map for easy access to animation frames depedning on direction (running)
    running_animation_map.insert(std::make_pair(45, "run_southeast"));
    running_animation_map.insert(std::make_pair(90, "run_south"));
    running_animation_map.insert(std::make_pair(135, "run_southwest"));
    running_animation_map.insert(std::make_pair(180, "run_west"));
    running_animation_map.insert(std::make_pair(-135, "run_northwest"));
    running_animation_map.insert(std::make_pair(-90, "run_north"));
    running_animation_map.insert(std::make_pair(-45, "run_northeast"));
    running_animation_map.insert(std::make_pair(0, "run_east"));

    // map for easy access to animation frames depedning on direction (sliding)
    sliding_animation_map.insert(std::make_pair(45, "slide_southeast"));
    sliding_animation_map.insert(std::make_pair(90, "slide_south"));
    sliding_animation_map.insert(std::make_pair(135, "slide_southwest"));
    sliding_animation_map.insert(std::make_pair(180, "slide_west"));
    sliding_animation_map.insert(std::make_pair(-135, "slide_northwest"));
    sliding_animation_map.insert(std::make_pair(-90, "slide_north"));
    sliding_animation_map.insert(std::make_pair(-45, "slide_northeast"));
    sliding_animation_map.insert(std::make_pair(0, "slide_east"));

    // set a default animation
    SetAnimation("stand_south");
}

void PlayerSprite::SetStandingAnimation(GameLib::Vector3 direction) {
    // face ball
    auto it = standing_animation_map.find(round(direction.angle()));

    if(it != standing_animation_map.end()) {
        SetAnimation((*it).second);
    }
}

void PlayerSprite::SetRunningAnimation(GameLib::Vector3 direction) {
    int angle = round(direction.angle());
    auto it = running_animation_map.find(angle);

    if(it != running_animation_map.end()) {
        SetAnimation((*it).second);
    }

}
void PlayerSprite::SetSlidingAnimation(GameLib::Vector3 direction) {
    auto it = sliding_animation_map.find(round(direction.angle()));

    if(it != sliding_animation_map.end()) {
        SetAnimation((*it).second);
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
    GameLib::Primitives::FillColor(triangle1_color);
    GameLib::Primitives::Triangle(window, triangle1.p1.x, triangle1.p1.y, triangle1.p2.x, triangle1.p2.y, triangle1.p3.x, triangle1.p3.y);
    GameLib::Primitives::RestoreColors();

    float width = text.GetWidth();
    float height = text.GetHeight();
    GameLib::Primitives::FillColor(GameLib::Color(0, 0, 0, 255));
    GameLib::Primitives::OutlineColor(GameLib::Color(0, 0, 0, 255));
    GameLib::Primitives::Rectangle(window, this->GetPosition().x-20, this->GetPosition().y - height, width, height * 1.3f);
    GameLib::Primitives::RestoreColors();
    text.SetPosition(this->GetPosition().x-20, this->GetPosition().y - height);
    text.Render(window);
}

void PlayerShadowSprite::Render(GameLib::Window &window) {
    GameLib::Sprite::Render(window);
}

}// SenselessSoccer




