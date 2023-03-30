#include "telephonia.h"
#include <iostream>

country *global_telephonia::create_country(std::string name){
    country a(name);
    this->countryes_[name] = a;
    std::cout << "создана страна " << name << "\n";
    return &(this->countryes_[name]);
}

operat *country::create_operat(std::string name){
    operat a(name);
    this->operators_[name] = a;
    std::cout << "создан оператор " << name << "\n";
    return &(this->operators_[name]);
}

void country::send(std::string adres, std::string messege){
    
}

void operat::create_abonent(number a){
    std::cout << "создан номер " << a.get_number() << "\n";
    this->numbers_[a.get_number()] = a;
}

void global_telephonia::send(std::string adres, std::string messege){
    std::string s = adres;
    s.erase(0, 1);

    std::reverse(s.begin(), s.end());
    std::string countr = s.substr(10);
    std::reverse(countr.begin(), countr.end());
    countr = "+" + countr;

    s.erase(10, s.length());
    std::string opp = s.substr(7);
    std::reverse(opp.begin(), opp.end());
    std::cout << "страна/оператор адресата " << countr << "\\" << opp <<"\n";
    //this->countryes_[countr].send(opp, adres, messege);
}
// 12 34 567 988

std::string number::get_number(){
    return this->name_;
}
