#ifndef ORACLE_HPP
#define ORACLE_HPP

#include <iostream>
#include <ctime>

class Oracle {
    private:
        tm date;
        double exchange;
    public:
        Oracle();
        Oracle(tm date, double exchange);
        virtual ~Oracle();
        tm getDate();
        double getExchange();
};

#endif