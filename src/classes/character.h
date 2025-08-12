#ifndef CHARACTER_H
#define CHARACTER_H


#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/node.hpp>

#include <godot_cpp/core/class_db.hpp>

#include "interfaces/icontrollable.h"

using namespace godot;

class Character : public CharacterBody3D, public IControllable{
    GDCLASS(Character, CharacterBody3D);
private:

    Vector3 direction = Vector3(0, 0, 0);
    Vector2 mouse_delta = Vector2(0, 0);
    float speed = 5.0f; // Default speed
    uint32_t current_actions = NONE; // Current actions flags
    
public:

    Character();
    ~Character();

    virtual void move(Vector3 direction) override;
    virtual void rotate(Vector2 delta) override;
    virtual void do_action(uint32_t action) override;
    virtual void moving(double delta) override;
    virtual void looking(double delta) override;

    void _process(double delta) override;
    void _physics_process(double delta) override;
    void _ready() override;

protected:
    static void _bind_methods();
};
#endif