#include "wallet.hpp"
#include <iostream>
#include <string>

Wallet::Wallet(int id, std::string holderName, std::string brokerageName) : id(id), holderName(holderName), brokerageName(brokerageName) {}; 

Wallet::Wallet(std::string holderName, std::string brokerageName) : holderName(holderName), brokerageName(brokerageName) {}; 

Wallet::~Wallet() {};

void Wallet::setHolderName(std::string newHolderName)
{
    this->holderName = newHolderName;
}

void Wallet::setBrokerageName(std::string newBrokerageName)
{
    this->brokerageName = newBrokerageName;
}

std::ostream& operator<<(std::ostream& os, const Wallet& obj)
{
    os << obj.holderName << std::endl << obj.brokerageName;
}