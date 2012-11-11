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

enum CollisionGroups {
    COL_NOTHING = 0,     //<Collide with nothing
    COL_BALL = 1,        //<Collide with ships
    COL_FLOOR = 1<<1,    //<Collide with walls
    COL_OTHERS = 1<<2    //<Collide with powerups
};

const float SDL_WALKING_DISTANCE = 0.5;

#endif // CONSTANTS_H
