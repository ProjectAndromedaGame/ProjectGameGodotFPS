#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/classes/engine.hpp>

#include "world_controller.h"
#include "character.h"
#include "icontrollable.h"
#include "gd_utils.h"
#include "gd_bridge.h"

using namespace godot;

class Controller : public Node
{

    GDCLASS(Controller, Node);

private:
    Character *character;
    // InputHandler *input_handler = nullptr;
    bool is_ingame = false;
    GDBridge *bridge = nullptr;
    UserCmd player_cmd;

public:
    Controller();
    ~Controller();

    void possess(Character *character);
    Character *depossess();
    Character *get_character() const { return character; }

    void _physics_process(double delta) override;
    void _ready() override;

protected:
    static void _bind_methods();
};

#endif