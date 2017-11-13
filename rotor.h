#ifndef ROTOR_H
#define ROTOR_H

#include "reflector.h"
#include "plugboard.h"
#include <fstream>

class Plugboard;
class Reflector;

class Rotor{
  public:
    Rotor();
    void setup(const char* a, int number);
    void add_Rotor(Rotor* new_rotor);
    int check_config();
    void set_offset(int index);
    int start_open(const char* file_start);
    void map_left(int input);
    void map_right(int input);
    int get_current_input();
    void set_current_output(int out);
    void set_pb(Plugboard* a);

    void set_rf(Reflector* a);



  private:
    const char* filename;
    std::ifstream rotor_file;
    std::ifstream start_position;
    Rotor* rotor_right;
    Rotor* rotor_left;
    Reflector* reflector;
    Plugboard* plugboard;
    int current_input;
    int config_length;
    int rotor_configuration[52];
    int start_configuration[512];
    int offset; //offset of rotor from absolute position A
    int rotor_no;
    static int no_of_rotors;
};

#endif
