#include <iostream>
#include <string>

#ifndef WALLET_HPP
#define WALLET_HPP

class Wallet
{
    private:
        unsigned int id;
        std::string holderName;
        std::string brokerageName;

    public:
        Wallet(int id, std::string holderName, std::string brokerageName);
        Wallet(std::string holderName, std::string brokerageName);
        ~Wallet();

        void setHolderName(std::string newHolderName);
        void setBrokerageName(std::string newBrokerageName);
		std::string getHolderName();
		std::string getBrokerageName();
		int getId();

        friend std::ostream& operator<<(std::ostream& os, const Wallet& obj);
};

#endif