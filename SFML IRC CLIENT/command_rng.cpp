#include "command_rng.hpp"
#include <random>
#include <sstream>

template < typename T > std::string to_string_fake( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

void send_message(string input);

Command_RNG::Command_RNG(string new_nick_condition, string new_channel_condition, string new_msg_condition) : Command(new_nick_condition, new_channel_condition, new_msg_condition), distribution(1, 32)
{

}

void Command_RNG::result(Line & input)
{
    send_message(string("PRIVMSG ") + input.get_channel() + " " + to_string_fake<int>(distribution(generator)));
}
