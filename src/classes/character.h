#ifndef CHARACTER_H
#define CHARACTER_H

#include <godot_cpp/classes/character_body3d.hpp>
#include <godot_cpp/classes/project_settings.hpp>
#include <godot_cpp/classes/camera3d.hpp>
#include <godot_cpp/classes/node.hpp>

#include <godot_cpp/core/class_db.hpp>

#include "world_controller.h"
#include "Icontrollable.h"
#include "Ientity.h"

using namespace godot;

class Character : public CharacterBody3D, public IControllable, public IEntity
{
    GDCLASS(Character, CharacterBody3D);

private:
    float health = 100.0f;
    float yaw = 0.0f;
    float pitch = 0.0f;
    Vector3 direction = Vector3(0, 0, 0);
    Vector2 view_angle = Vector2(0, 0);
    float speed = 5.0f;         // velocidad de movimiento
    int current_actions = NONE; // Flags de acciones actuales
    Camera3D *camera1p = nullptr;
    Camera3D *camera3p = nullptr;
    Camera3D *active_camera = nullptr;
    bool third_person = false;
    bool set_camera = false;
    bool noclip = false;
    float gravity_force = ProjectSettings::get_singleton()->get_setting("physics/3d/default_gravity").operator float();

public:
    Character();
    ~Character();

    virtual void move(float forward, float right, float up) override;
    virtual void rotate(Vector2 delta) override;
    virtual void do_action(int32_t action) override;

    virtual EntityType get_entity_type() const override;
    virtual int32_t get_entity_id() const override;
    virtual int get_team() const override;

    virtual Vector3 get_world_position() const override;

    virtual float get_health() const override;
    virtual bool is_alive() const override;
    virtual void take_damage(float damage, IEntity *source = nullptr) override;

    virtual void destroy() override;

    void _physics_process(double delta) override;
    void _ready() override;

protected:
    static void _bind_methods();

private:
    virtual void moving(double delta) override;
    virtual void looking(double delta) override;
    virtual void in_action(int32_t action) override;
    virtual void apply_physics(double delta) override;
};
#endif