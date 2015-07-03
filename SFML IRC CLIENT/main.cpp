#include <SFML/Network.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <math.h>
#include <fstream>
#include <sstream>
#include "parser.hpp"
#include "line.hpp"
#include "command_rng.hpp"

using namespace std;

template < typename T > std::string to_string_fake( const T& n )
{
    std::ostringstream stm ;
    stm << n ;
    return stm.str() ;
}

vector<Command*> commands;

sf::TcpSocket socket;
sf::TcpSocket client;
sf::TcpListener listener;
sf::Socket::Status status;

bool firstping;

vector<string> grabWord(string input, string delim = " ", bool includedelim=false)
{
    vector<string> output;
    size_t lastFound=0;
    size_t startingPoint=0;
    while (lastFound!=string::npos)
    {
        lastFound=(input.find(delim, startingPoint));
        if (includedelim==false)
        {
            string outstring = input.substr(startingPoint, lastFound-startingPoint);
            output.push_back(outstring);
        }
        else
        {
            string outstring = input.substr(startingPoint, (lastFound-startingPoint)+delim.length());
            output.push_back(outstring);
        }
        startingPoint=lastFound+delim.length();
    }
    return output;
}

void send_message(string input)
{
    socket.send(string(input+"\r\n").c_str(), input.length()+2);
    cout << "Message sent:" << input << endl;
}

string leftovers;

void receive()
{
    char output[512] = "";
    string stringoutput;
    std::size_t amount_received;
    socket.receive(output, 512, amount_received);
    stringoutput=string(leftovers + output); // convert to a string
    while (stringoutput.find("\r\n")!=string::npos) //while there are newlines left in stringoutput
    {
        string line = stringoutput.substr(0, stringoutput.find("\r\n"));
        stringoutput=stringoutput.substr(stringoutput.find("\r\n")+2, string::npos);
        cout << "Message received: " << line << " :end message" << endl;
        if (grabWord(line)[0]==string("PING"))
        {
            send_message("PONG " + grabWord(line)[1]);
            firstping=true;
        }
        if (grabWord(line)[1]==string("PRIVMSG"))
        {
            Line lineobj(line);
            for (int cmdi=0; cmdi<commands.size(); cmdi++)
            {
                commands[cmdi]->check_conditions(lineobj);
            }
        }
    }
    leftovers=stringoutput.substr(stringoutput.find("\r\n"+2),string::npos);
}

int main()
{
    //server stuff
    string server = "irc.darkmyst.org";
    string channel = "#petrocelli";
    //init commands
    Command_RNG command_rng(string("*"), channel, string("!RNG"));
    //startup
    bool running=true;
    leftovers="";
    firstping=false;
    status = socket.connect(server.c_str(), 6667);
    send_message("USER Sparkbot 0 * :Spark Bot");
    send_message("NICK Sparkbot");
    while (firstping!=true)
    {
        receive();
    }
    receive();
    send_message(string("JOIN ") + channel);
    socket.setBlocking(false);
    while (running!=false)
    {
        receive();
    }
}
