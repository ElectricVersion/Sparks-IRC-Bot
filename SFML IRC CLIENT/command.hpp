#ifndef COMMAND_HPP
#define COMMAND_HPP
#include <string>
#include "line.hpp"
using namespace std;

class Command
{
public:
    Command(string new_nick_condition, string new_channel_condition, string new_msg_condition); // this constructor will set the conditions for the command
    void check_conditions(Line & input); // function used to check if the line meets the conditions to start the command
protected:
    virtual void result(Line & input)=0;
private:
    Line conditions;
};

#endif // COMMAND_HPP
