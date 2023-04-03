#include "telephonia.h"
#include <iostream>

int main() 
{
    global_telephonia a;
    country *rf = a.create_country("+7");
    // country *rf1 = a.create_country("+7в");
    // country *rf2 = a.create_country("7");
    // country *rf3 = a.create_country("+7435");
    operat *tele2 = rf->create_operat("985");
    // operat *tele1 = rf->create_operat("9a5");
    // operat *tele3 = rf->create_operat("95");
    // operat *tele4 = rf->create_operat("");
    tele2->create_abonent(number("+79853722161"));
    tele2->create_abonent(number("+79863722161"));
    tele2->create_abonent(number("+7986372211"));
    tele2->create_abonent(number("+79863722g61"));
    tele2->create_abonent(number(""));
    
    tele2->create_abonent(to_number("+79850000000", "+79853722161"));
    a.send("+79853722161", "mes 1");
    a.send("+79850000000", "mes 2");
    a.read("+79853722161");
    return 0;
}