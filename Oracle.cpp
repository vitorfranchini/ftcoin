#include <cstdlib>

#include "Oracle.hpp"


Oracle::Oracle(tm date, double exchange) : date(date), exchange(exchange) {}


Oracle::Oracle(){
    time_t now = time(nullptr);
    tm date;
    localtime_s(&date, &now); // Using localtime_s for safer implementation
    this->date = date;
    
    int seed = date.tm_mon + 1 + date.tm_mday;
    srand(seed);

    this->exchange = (rand() % 90 + 10) * 0.1;
}

Oracle::~Oracle(){}

tm Oracle::getDate(){return this->date;}


double Oracle::getExchange(){return this->exchange;}