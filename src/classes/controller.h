#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>

#include <godot_cpp/core/class_db.hpp>

#include "classes/character.h"
#include "classes/input_handler.h"
#include "interfaces/icontrollable.h"

using namespace godot;

class Controller : public Node
{

    GDCLASS(Controller, Node);

private:
    Input *input;
    Character *character;

public:
    Controller();
    ~Controller();

    static void _register_methods();

    void possess(Character *character);
    Character *depossess();
    Character *get_character() const { return character; }

    void _process(double delta) override;
    void _input(const Ref<InputEvent> &event) override;
    void _ready() override;

protected:
    static void _bind_methods();
};

#endif