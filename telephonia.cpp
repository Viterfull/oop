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

void operat::create_abonent(number a){
    std::cout << "создан номер " << a.get_number() << "\n";
    this->numbers_[a.get_number()] = a;
}

int number::save_mes(std::string messege)
{
    this->messeges_.push_back(messege);
    std::cout << "сообщение:\""<< messege <<"\" доставлено на адрес " << this->name_ << "\n" ; 
    return 0;
}

int number::print_mes()
{
    if (this->messeges_.empty())
    {
        std::cout << "Сообщений на " << this->name_ << "нет\n";
    }
    
    std::cout << "на " << this->name_ << " найдено " << this->messeges_.size() << "сообщений\n";

    for (size_t i = 0; i < this->messeges_.size(); i++)
    {
        std::cout << "\tСообщение " << i + 1 << ": \"" << messeges_[i] << "\"\n";
    }
    this->messeges_.clear();
    return 0;
}



int operat::send(std::string adres, std::string messege){
    return this->numbers_[adres].save_mes(messege);
}

int operat::read(std::string adres)
{
    return this->numbers_[adres].print_mes();
}

int country::send(std::string opp, std::string adres, std::string messege){
    return this->operators_[opp].send(adres, messege);
}

int country::read(std::string opp, std::string adres)
{
    return this->operators_[opp].read(adres);
}

int global_telephonia::send(std::string adres, std::string messege){
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
    return this->countryes_[countr].send(opp, adres, messege);
}

int global_telephonia::read(std::string adres){
    std::string s = adres;
    s.erase(0, 1);

    std::reverse(s.begin(), s.end());
    std::string countr = s.substr(10);
    std::reverse(countr.begin(), countr.end());
    countr = "+" + countr;

    s.erase(10, s.length());
    std::string opp = s.substr(7);
    std::reverse(opp.begin(), opp.end());
    std::cout << "страна/оператор чтения " << countr << "\\" << opp <<"\n";
    return this->countryes_[countr].read(opp, adres);
}
// 12 34 567 988

std::string number::get_number(){
    return this->name_;
}