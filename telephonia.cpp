#include "telephonia.h"
#include <iostream>
#include <memory>


int number::save_mes(std::string messege){
    this->messeges_.push_back(messege);
    //std::cout << "сообщение:\""<< messege <<"\" доставлено на адрес " << this->name_ << "\n" ; 
    return 0;
}

int number::print_mes(){
    if (this->messeges_.empty()){
        std::cout << "Сообщений на " << this->name_ << "нет\n";
        return 0;
    }
    
    std::cout << "на " << this->name_ << " найдено " << this->messeges_.size() << "сообщений\n";

    for (size_t i = 0; i < this->messeges_.size(); i++){
        std::cout << "\tСообщение " << i + 1 << ": \"" << messeges_[i] << "\"\n";
    }
    this->messeges_.clear();
    return 0;
}



int operat::send_to_nu(std::string adres, std::string messege){
    if (this->numbers_.contains(adres)) return this->numbers_[adres].save_mes(messege);
    if (this->to_numbers_.contains(adres)) return this->to_numbers_[adres].save_mes(messege);
    return 0;
}

int operat::read_to_nu(std::string adres){
    return this->numbers_[adres].print_mes();
}

int country::send_to_opp(std::string opp, std::string adres, std::string messege){
    return this->operators_[opp].send_to_nu(adres, messege);
}

int country::read_to_opp(std::string opp, std::string adres){
    return this->operators_[opp].read_to_nu(adres);
}

#define pars_number(adres) ({\
    std::string s = adres;\
    s.erase(0, 1);\
    std::reverse(s.begin(), s.end());\
    countr = s.substr(10);\
    std::reverse(countr.begin(), countr.end());\
    countr = "+" + countr;\
    s.erase(10, s.length());\
    opp = s.substr(7);\
    std::reverse(opp.begin(), opp.end());\
})

int global_telephonia::send(std::string adres, std::string messege){
    std::string countr, opp;
    pars_number(adres);
    //std::cout << "страна/оператор адресата " << countr << "\\" << opp <<"\n";
    return this->countryes_[countr].send_to_opp(opp, adres, messege);
}

int global_telephonia::read(std::string adres){
    std::string countr, opp;
    pars_number(adres);
    //std::cout << "страна/оператор чтения " << countr << "\\" << opp <<"\n";
    return this->countryes_[countr].read_to_opp(opp, adres);
}
// 12 34 567 988

std::string number::get_number(){
    return this->name_;
}

country *global_telephonia::create_country(std::string name){
    country a(name, this);
    this->countryes_[name] = a;
    std::cout << "создана страна " << name << "\n";
    return &(this->countryes_[name]);
}

operat *country::create_operat(std::string name){
    operat a(name, gl_);
    this->operators_[name] = a;
    std::cout << "создан оператор " << this->name_ << " " << name << "\n";
    return &(this->operators_[name]);
}

void operat::create_abonent(number a){
    std::cout << "создан номер " << a.get_number() << "\n";
    // this->numbers_.emplace(a.get_number(), std::make_unique<number>(a));
    this->numbers_[a.get_number()] = a;
}

void operat::create_abonent(to_number a){
    a.set_gl(this->gl_); 
    std::cout << "создан номер пересылки " << a.get_number() << " к " << a.get_number_to()  <<"\n";
    // this->numbers_.emplace(a.get_number(), std::make_unique<to_number>(a));
    this->to_numbers_[a.get_number()] = a;
}

void to_number::set_gl(global_telephonia *gl){
    this->gl_ = gl;
}

int to_number::save_mes(std::string messege)
{
    static_cast<number*>(this)->save_mes(messege);
    this->gl_->send(this->name_to_, "СООБЩЕНИЕ: \"" + messege + "\" ПЕРЕНАПРАВЛЕНО ОТ " + this->get_number());
    return 0;
}

std::string to_number::get_number_to(){
    return this->name_to_;
}