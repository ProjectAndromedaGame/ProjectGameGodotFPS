#include "gd_bridge.h"

GDBridge *GDBridge::instance = nullptr;

GDBridge::GDBridge()
{
    if (instance == nullptr)
    {
        instance = this;
        print_line("bridge iniciado");
    }
    else
    {
        print_line("Warning: Multiple instances of GDBridge detected!");
    }
}

GDBridge::~GDBridge()
{
    if (instance == this)
    {
        instance = nullptr;
    }
}

GDBridge *GDBridge::get_singleton()
{
    return instance;
}

void GDBridge::set_user_cmd(Dictionary user_cmd_dict)
{
    current_user_cmd_dict = user_cmd_dict;
    current_user_cmd.seq = int64_t(user_cmd_dict["seq"]);
    current_user_cmd.tick = int64_t(user_cmd_dict["tick"]);
    current_user_cmd.dt = double(user_cmd_dict["dt"]);
    current_user_cmd.view_delta = Vector2(user_cmd_dict["view_delta"]);
    current_user_cmd.view_angles = Vector2(user_cmd_dict["view_angles"]);
    current_user_cmd.forward_move = float(user_cmd_dict["forward_move"]);
    current_user_cmd.side_move = float(user_cmd_dict["side_move"]);
    current_user_cmd.up_move = float(user_cmd_dict["up_move"]);
    current_user_cmd.buttons = uint32_t(user_cmd_dict["buttons"]);
}

UserCmd GDBridge::get_user_cmd() const
{
    return current_user_cmd;
}

Dictionary GDBridge::get_user_cmd_dict() const
{
    return current_user_cmd_dict;
}

void GDBridge::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_user_cmd", "user_cmd"), &GDBridge::set_user_cmd);
    ClassDB::bind_method(D_METHOD("get_user_cmd"), &GDBridge::get_user_cmd_dict);
}
