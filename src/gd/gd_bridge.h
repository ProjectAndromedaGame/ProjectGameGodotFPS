#ifndef GD_BRIDGE
#define GD_BRIDGE

#include <godot_cpp/classes/node.hpp>
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/dictionary.hpp>
#include "user_cmd.h"

using namespace godot;

class GDBridge : public godot::Node
{

    GDCLASS(GDBridge, Node);

private:
    String message = "test message";
    UserCmd current_user_cmd;
    Dictionary current_user_cmd_dict;
    static GDBridge *instance;

public:
    GDBridge();
    ~GDBridge();
    static GDBridge *get_singleton();

    void set_user_cmd(Dictionary user_cmd_dict);
    UserCmd get_user_cmd() const;
    Dictionary get_user_cmd_dict() const;

protected:
    static void _bind_methods();
};

#endif