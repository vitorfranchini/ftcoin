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
        virtual ~Oracle();
        tm getDate();
        double getExchange();
};

#endif