#include <cstdlib>

#include "Oracle.hpp"

Oracle::Oracle(){
    time_t now = time(nullptr);
    tm *date = localtime(&now);
    this->date = *date;
    
    int seed = date->tm_mon + 1 + date->tm_mday;
    srand(seed);

    this->exchange = (rand() % 90 + 10) * 0.1;
}

Oracle::~Oracle(){}

tm Oracle::getDate(){return this->date;}

double Oracle::getExchange(){return this->exchange;}