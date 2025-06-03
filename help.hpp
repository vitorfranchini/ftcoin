#ifndef HELP_HPP
#define HELP_HPP

#include <string>
#include <ctime>
using namespace std;

class Help {
private:
    static  string authors;
    static  tm date;
    static  string copyright;
    static  string version;

public:
    static void displayHelp();
    static void displayCredits();
};

#endif
