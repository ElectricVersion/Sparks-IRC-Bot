#ifndef LINE_HPP
#define LINE_HPP
#include <string>

using namespace std;

class Line //class used for getting info from a string you've received
{
public:
    Line(string input);
    Line(string input_nick, string input_channel, string input_msg);
    string get_nick();
    string get_channel();
    string get_msg();
    void set_nick(string input_nick);
    void set_channel(string input_channel);
    void set_msg(string input_msg);
private:
    string nick; // the speaker
    string channel; // the channel in which the message was spoken
    string msg; // the contents of the message
};

#endif // LINE_HPP
