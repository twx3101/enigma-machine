#ifndef PLUGBOARD_H
#define PLUGBOARD_H


#include "input.h"
#include "rotor.h"
#include <fstream>

class Rotor;

class Plugboard
{
  public:
    Plugboard(const char* file, Input_switch* a);
    int check_config();
    void swap();
    void final_swap();
    void set_rotor(Rotor* a);

  private:
    std::ifstream plugboard_config;
    const char* filename;
    Input_switch* input;
    Rotor* first_rotor;
    int configuration[26];
    int output_out;
    int config_no;
};

#endif