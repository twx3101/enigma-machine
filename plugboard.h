#ifndef PLUGBOARD_H
#define PLUGBOARD_H


#include "input.h"
#include "rotor.h"
#include "reflector.h"
#include <fstream>

class Rotor;
class Reflector;

class Plugboard
{
  public:
    Plugboard(const char* file);
    int check_config();
    char swap(char input);
    char swap_without_rotor(char input);
    void set_rotor(Rotor* a);
    void set_rf(Reflector* a);

  private:
    std::ifstream plugboard_config;
    const char* filename;
    Input_switch* input;
    Reflector* reflector;
    Rotor* first_rotor;
    int configuration[26];
    int output_out;
    int config_no;
};

#endif
