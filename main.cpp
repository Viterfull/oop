#include <iostream>
#include "telephonia.h"

int main() {
    global_telephonia a;
    country *rf = a.create_country("+7");
    country *am = a.create_country("+94");
    operat *bib = am->create_operat("668");
    operat *tele2 = rf->create_operat("985");
    bib->create_abonent(number("+946685464637"));
    tele2->create_abonent(number("+79853722161"));
    a.send("+79853722161", "Hi!");
    a.send("+946685464637", "Hi2");
}