#include <string>
#include <vector>
#include <map>

class number{
private:
    std::string name_;
    std::vector <std::string> messeges_;
public:
    number (std::string name)
        : name_(name){};
    number ()
        : name_("empty"){};
    std::string get_number();
    int save_mes(std::string messege);
    int print_mes();
};

class operat{
private:
    std::string name_;
    std::map <std::string, number> numbers_;
public:
    operat (std::string name)
        : name_(name){};
    operat ()
        : name_("empty"){};
    void create_abonent(number name);
    int send(std::string adres, std::string messege);
    int read(std::string adres);
};

class country {
private:
    std::string name_;
    std::map <std::string, operat> operators_; 
public:
    country (std::string name)
      : name_(name){};
    country ()
      : name_("empty"){};
    operat *create_operat(std::string name);
    int send(std::string opp, std::string adres, std::string messege);
    int read(std::string opp, std::string adres);
};


class global_telephonia {
private:
    std::map <std::string, country> countryes_;


public:
    country *create_country(std::string name);
    int send(std::string adres, std::string messege);
    int read(std::string adres);
};
