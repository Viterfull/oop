#include "telephonia.h"
#include <iostream>
#include <memory>
/*
ОШИБКИ:
    1 - не найдена страна
    2 - не найден оператор
    3 - не найден номер
    4 - не соотвествует номер при создании номера
*/

int number::save_mes(std::string messege)
{
    this->messeges_.push_back(messege);
    // std::cout << "сообщение:\""<< messege <<"\" доставлено на адрес " << this->name_ << "\n" ;
    return 0;
}

int number::print_mes()
{
    if (this->messeges_.empty())
    {
        std::cout << "Сообщений на " << this->name_ << " нет\n";
        return 0;
    }

    std::cout << "на " << this->name_ << " найдено " << this->messeges_.size() << " сообщений\n";

    for (size_t i = 0; i < this->messeges_.size(); i++)
    {
        std::cout << "\tСообщение " << i + 1 << ": \"" << messeges_[i] << "\"\n";
    }
    this->messeges_.clear();
    return 0;
}

int operat::send_to_nu(std::string adres, std::string messege)
{
    if (this->numbers_.contains(adres))
        return this->numbers_[adres].save_mes(messege);
    if (this->to_numbers_.contains(adres))
        return this->to_numbers_[adres].save_mes(messege);
    std::cout << "не существует номера " << adres << "для отправки\n";
    return 3;
}

int operat::read_to_nu(std::string adres)
{
    if (this->numbers_.contains(adres))
        return this->numbers_[adres].print_mes();
    if (this->to_numbers_.contains(adres))
        return this->to_numbers_[adres].print_mes();
    std::cout << "не существует номера " << adres << "для отправки\n";
    return 3;
}

int country::send_to_opp(std::string opp, std::string adres, std::string messege)
{
    if (this->operators_.contains(opp))
        return this->operators_[opp].send_to_nu(adres, messege);
    std::cout << "не существует оператора " << opp << "для отправки сообщения на" << adres << "\n";
    return 2;
}

int country::read_to_opp(std::string opp, std::string adres)
{
    if (this->operators_.contains(opp))
        return this->operators_[opp].read_to_nu(adres);
    
    std::cout << "не существует оператора " << opp << "для чтения сообщений на" << adres << "\n";
    return 2;
}

#define pars_number(adres)                                                                                             \
    ({                                                                                                                 \
        std::string s = adres;                                                                                         \
        s.erase(0, 1);                                                                                                 \
        std::reverse(s.begin(), s.end());                                                                              \
        countr = s.substr(10);                                                                                         \
        std::reverse(countr.begin(), countr.end());                                                                    \
        countr = "+" + countr;                                                                                         \
        s.erase(10, s.length());                                                                                       \
        opp = s.substr(7);                                                                                             \
        std::reverse(opp.begin(), opp.end());                                                                          \
    })

int global_telephonia::send(std::string adres, std::string messege)
{
    std::string countr, opp;
    pars_number(adres);
    // std::cout << "страна/оператор адресата " << countr << "\\" << opp <<"\n";
    if (this->countryes_.contains(countr))
        return this->countryes_[countr].send_to_opp(opp, adres, messege);
    std::cout << "не существует страны " << adres << "для отправки\n";
    return 1;
}

int global_telephonia::read(std::string adres)
{
    std::string countr, opp;
    pars_number(adres);
    // std::cout << "страна/оператор чтения " << countr << "\\" << opp <<"\n";
    if (this->countryes_.contains(countr))
        return this->countryes_[countr].read_to_opp(opp, adres);
    std::cout << "не существует страны " << adres << "для чтения\n";
    return 1;
}

country *global_telephonia::create_country(std::string name)
{
    if (name.size() < 2 || name[0] != '+' || name.find_first_not_of("0123456789", 1) != std::string::npos ||
        name.substr(1).size() > 3)
    {
        std::cout << "!!! ВНИМЕНИЕ НЕПРАВИЛЬНЫЙ ФОРМАТ ИМЕНИ СТРАНЫ (" << name
                  << "). ИСПОЛЬЗУЙТЕ ФОРМАТ: \"+XXX\", ГДЕ XXX - ОТ ОДНОЙ ДО ТРЕХ ЦИФР.!!!\n";
        return NULL;
    }
    country a(name, this);
    this->countryes_[name] = a;
    std::cout << "создана страна " << name << "\n";
    return &(this->countryes_[name]);
}

operat *country::create_operat(std::string name)
{
    if (name.size() != 3 || !std::isdigit(name[0]) || !std::isdigit(name[1]) || !std::isdigit(name[2]))
    {
        std::cout << "!!! ВНИМАНИЕ, СОЗДАНИЕ ОПЕРАТОРА (" << name << ") ДЛЯ СТРАНЫ С ПРЕФИКСОМ (" << this->name_
                  << ") НЕВОЗМОЖНО, ОДУМАЙТЕСЬ, ПОКА НЕ ПОЗДНО И ИСПОЛЬЗУЙТЕ ФОРМАТ ХХХ, ГДЕ ХХХ ЦИФРЫ !!!\n";
        return NULL;
    }
    operat a(name, this->name_, gl_);
    this->operators_[name] = a;
    std::cout << "создан оператор " << this->name_ << " " << name << "\n";
    return &(this->operators_[name]);
}

// void operat::create_abonent(number a)
// {
//

// }

int operat::create_abonent(number a)
{
    std::string number_telephone = a.get_number();
    if (number_telephone.length() == 0)
    {
        std::cout << "не возможно создать номер из пустой строки\n";
        return 4;
    }
    else if (number_telephone.substr(0, this->country_of_.length()) != this->country_of_)
    {
        std::cout << "неверно введен код страны при создании " << number_telephone
                  << ", он должен быть в виде +XXX, где XXX цифры от одной до трех штук, так же возможно что страна не "
                     "имеет такого оператора\n";
        return 4;
    }
    else if (number_telephone.substr(this->country_of_.length(), this->name_.length()) != this->name_)
    {
        std::cout << "неверный код оператора при создании " << number_telephone << " не соотвествует оператору "
                  << this->name_ << "\n";
        return 4;
    }
    else if (number_telephone.length() - (this->country_of_.length() + this->name_.length()) != 7)
    {
        std::cout << "при создании " << number_telephone
                  << " произошла ошибка, номер(без кода оператора и страны) состоит не из 7 символов\n";
        return 4;
    }
    else if (number_telephone.substr(this->country_of_.length() + this->name_.length())
                 .find_first_not_of("0123456789", 1) != std::string::npos)
    {
        std::cout << "при создании " << number_telephone
                  << " произошла ошибка, номер(без кода оператора и страны) состоит не из 7 цифр\n";
        return 4;
    }

    std::cout << "создан номер " << a.get_number() << "\n";
    this->numbers_[a.get_number()] = a;
    return 0;
}

//    [p, r, i, v, e, t, \0] в память об Александре
int operat::create_abonent(to_number a)
{
    a.set_gl(this->gl_);
    std::string number_telephone = a.get_number();
    if (number_telephone.length() == 0)
    {
        std::cout << "не возможно создать номер из пустой строки\n";
        return 4;
    }
    else if (number_telephone.substr(0, this->country_of_.length()) != this->country_of_)
    {
        std::cout << "неверно введен код страны при создании " << number_telephone
                  << ", он должен быть в виде +XXX, где XXX цифры от одной до трех штук, так же возможно что страна не "
                     "имеет такого оператора\n";
        return 4;
    }
    else if (number_telephone.substr(this->country_of_.length(), this->name_.length()) != this->name_)
    {
        std::cout << "неверный код оператора при создании " << number_telephone << " не соотвествует оператору "
                  << this->name_ << "\n";
        return 4;
    }
    else if (number_telephone.length() - (this->country_of_.length() + this->name_.length()) != 7)
    {
        std::cout << "при создании " << number_telephone
                  << " произошла ошибка, номер(без кода оператора и страны) состоит не из 7 символов\n";
        return 4;
    }
    else if (number_telephone.substr(this->country_of_.length() + this->name_.length())
                 .find_first_not_of("0123456789", 1) != std::string::npos)
    {
        std::cout << "при создании " << number_telephone
                  << " произошла ошибка, номер(без кода оператора и страны) состоит не из 7 цифр\n";
        return 4;
    }

    std::cout << "создан номер пересылки " << a.get_number() << " к " << a.get_number_to() << "\n";
    this->to_numbers_[a.get_number()] = a;
    return 0;
}

void to_number::set_gl(global_telephonia *gl)
{
    this->gl_ = gl;
}

int to_number::save_mes(std::string messege)
{
    static_cast<number *>(this)->save_mes(messege);
    this->gl_->send(this->name_to_, "СООБЩЕНИЕ: \"" + messege + "\" ПЕРЕНАПРАВЛЕНО ОТ " + this->get_number());
    return 0;
}

std::string to_number::get_number_to()
{
    return this->name_to_;
}

std::string number::get_number()
{
    return this->name_;
}