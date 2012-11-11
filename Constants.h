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

const float SDL_WALKING_DISTANCE = 2;

const float BALL_SPEED_CONTROL = 25;
const float BALL_SPEED_JUMP = 5;

// speed(n+1) = speed(n)/BALL_SLOW_SPEED
const float BALL_SLOW_SPEED = 1.01;

enum CollisionGroups {
    COL_NOTHING = 0,     //<Collide with nothing
    COL_BALL = 1,        //<Collide with ships
    COL_FLOOR = 1<<1,    //<Collide with walls
    COL_OTHERS = 1<<2    //<Collide with powerups
};

#endif // CONSTANTS_H
