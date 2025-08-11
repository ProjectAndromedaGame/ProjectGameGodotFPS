#ifndef ACTION_FLAGS_H
#define ACTION_FLAGS_H



enum ActionFlags {
    NONE = 0,
    JUMP = 1 << 0,
    CROUCH = 1 << 1,
    RUN = 1 << 2,
    SHOOT = 1 << 3,
    AIM = 1 << 4,
    RELOAD = 1 << 5,
    INTERACT = 1 << 6,
};

#endif // ACTION_FLAGS_H