#include "command.hpp"
#include <random>

using namespace std;

class Command_RNG : public Command
{
public:
    Command_RNG(string new_nick_condition, string new_channel_condition, string new_msg_condition);
    void result(Line & input);
private:
    uniform_int_distribution<int> distribution;
    default_random_engine generator;
};
