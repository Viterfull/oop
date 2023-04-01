#include "telephonia.h"

int main() {
    global_telephonia a;
    country *rf = a.create_country("+7");
    operat *tele2 = rf->create_operat("985");
    tele2->create_abonent(number("+79853722161"));
    tele2->create_abonent(to_number("+79850000000", "+79853722161"));
    a.send("+79853722161", "mes 1");
    a.send("+79850000000", "mes 2");
    a.read("+79853722161");
}