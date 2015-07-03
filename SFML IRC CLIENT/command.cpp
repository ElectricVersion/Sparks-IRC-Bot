#include "command.hpp"
#include <vector>

Command::Command(string new_nick_condition, string new_channel_condition, string new_msg_condition) : conditions (new_nick_condition, new_channel_condition, new_msg_condition)
{
    conditions.set_nick(new_nick_condition);
    conditions.set_channel(new_channel_condition);
    conditions.set_msg(new_msg_condition);
    extern vector<Command*> commands;
    commands.push_back(this);
}

void Command::check_conditions(Line & input)
{
    bool nick_condition_met=false;
    bool channel_condition_met=false;
    bool msg_condition_met=false;
    if ((input.get_nick()==conditions.get_nick()) || (conditions.get_nick()=="*"))
    {
        nick_condition_met=true;
    }
    if ((input.get_channel()==conditions.get_channel()) || (conditions.get_channel()=="*"))
    {
        channel_condition_met=true;
    }
    if ((input.get_msg()==conditions.get_msg()) || (conditions.get_msg()=="*"))
    {
        msg_condition_met=true;
    }
    if ((nick_condition_met==true) && (channel_condition_met==true) && (msg_condition_met==true))
    {
        result(input);
    }
}
