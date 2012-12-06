#ifndef CONSTANTS_H
#define CONSTANTS_H

enum StrategyType
{
    SDL_STRATEGY,
    VRJUGGLER_STRATEGY
};

enum ReturnStatus
{
    RETURN_NORMAL,
    RETURN_EXIT
};

enum WalkingDirection
{
    WALKING_PARALLEL,
    WALKING_FRONT
};

enum CameraDirection
{
    CAMERA_DIRECTION_X,
    CAMERA_DIRECTION_Y
};

enum CollisionGroups
{
    COL_NOTHING = 0,     //<Collide with nothing
    COL_BALL = 1,        //<Collide with ships
    COL_FLOOR = 1<<1,    //<Collide with walls
    COL_OTHERS = 1<<2    //<Collide with powerups
};

const float SDL_WALKING_DISTANCE = 2;

const float BALL_HORIZONTAL_FORCE = 1700;
const float BALL_JUMP_FORCE = 5000;
const float PLATFORM_UNSTABLE_SMOOTHING = 110;
const float PLATFORM_UNSTABLE_SMOOTHING_THRESHOLD = 10;
const float PLATFORM_UNSTABLE_FALLING_THRESHOLD = 100;
const float PLATFORM_UNSTABLE_ANGLE = 50;

const float ALLOWING_MOVEMENT_LATENCY = 0.2;
#endif // CONSTANTS_H
