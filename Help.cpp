#include "help.hpp"
#include <iostream>
using namespace std;


string Help::authors = "Equipe de Desenvolvimento";
tm Help::date = []{
    time_t now = time(nullptr);
    tm t = *localtime(&now);
    return t;
}();
string Help::copyright = "© 2025 Sua Empresa";
string Help::version = "1.0.0";


void Help::displayHelp() {
    cout << "=== Ajuda ===" << endl;
    cout << "Este programa faz X, Y e Z." << endl;
}

void Help::displayCredits() {
    cout << "=== Créditos ===" << endl;
    cout << "Autores: " << authors << endl;
    cout << "Data: " 
              << (date.tm_mday) << "/" << (date.tm_mon + 1) << "/" << (date.tm_year + 1900) << endl;
    cout << "Versão: " << version << endl;
    cout << "Copyright: " << copyright << endl;
}
