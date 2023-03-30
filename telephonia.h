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
    void send(std::string adres, std::string messege);
};


class global_telephonia {
private:
    std::map <std::string, country> countryes_;


public:
    country *create_country(std::string name);
    void send(std::string adres, std::string messege);
};



