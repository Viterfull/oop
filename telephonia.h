#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class global_telephonia;

class number
{
  protected:
    std::string name_;
    std::vector<std::string> messeges_;

  public:
    number(std::string name) : name_(name){};
    number() : name_("empty"){};
    std::string get_number();
    int save_mes(std::string messege);
    int print_mes();
};

class to_number : public number
{
  protected:
    std::string name_to_;
    global_telephonia *gl_;

  public:
    to_number(std::string name, std::string name_to) : number(name), name_to_(name_to){};
    to_number() : number("empty"){};
    void set_gl(global_telephonia *gl);
    int save_mes(std::string messege);
    std::string get_number_to();
};

class operat
{
  private:
    std::string name_, country_of_;
    global_telephonia *gl_;
    std::unordered_map<std::string, number> numbers_;
    std::unordered_map<std::string, to_number> to_numbers_;

  public:
    operat(std::string name, std::string country_of,  global_telephonia *gl) : name_(name), country_of_(country_of), gl_(gl){};
    operat() : name_("empty"){};
    int create_abonent(number name);
    int create_abonent(to_number a);
    int send_to_nu(std::string adres, std::string messege);
    int read_to_nu(std::string adres);
};

class country
{
  private:
    std::string name_;
    global_telephonia *gl_;
    std::unordered_map<std::string, operat> operators_;

  public:
    country(std::string name, global_telephonia *gl) : name_(name), gl_(gl){};
    country() : name_("empty"){};
    operat *create_operat(std::string name);
    int send_to_opp(std::string opp, std::string adres, std::string messege);
    int read_to_opp(std::string opp, std::string adres);
};

class global_telephonia
{
  private:
    std::unordered_map<std::string, country> countryes_;

  public:
    country *create_country(std::string name);
    int send(std::string adres, std::string messege);
    int read(std::string adres);
};