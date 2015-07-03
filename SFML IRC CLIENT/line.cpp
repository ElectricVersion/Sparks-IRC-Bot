#include "line.hpp"
#include <vector>

vector<string> grabWord(string input, string delim = " ", bool includedelim=false);


Line::Line(string input)
{
    nick=grabWord(grabWord(input)[0], "!")[0].substr(1, string::npos);
    channel=grabWord(input)[2];
    msg=input.substr(input.find(":", (input.find(" ", 1)))+1, string::npos);
}

Line::Line(string input_nick, string input_channel, string input_msg)
{
    nick = input_nick;
    channel = input_channel;
    msg = input_msg;
}

string Line::get_nick()
{
    return nick;
}

string Line::get_channel()
{
    return channel;
}

string Line::get_msg()
{
    return msg;
}

void Line::set_nick(string input_nick)
{
    nick = input_nick;
}


void Line::set_channel(string input_channel)
{
    channel = input_channel;
}


void Line::set_msg(string input_msg)
{
    msg = input_msg;
}

