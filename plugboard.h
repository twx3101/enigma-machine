#ifndef PLUGBOARD_H
#define PLUGBOARD_H



#include "rotor.h"
#include "reflector.h"
#include <fstream>

class Rotor;
class Reflector;

class Plugboard
{
  public:
    /*Plugboard constructor, initializes Reflector* to NULL and Rotor* to NULL*/
    Plugboard(const char* file);

    /* Check if plugbaord configuration file is well_formed */
    int check_config();

    /*swaps input with paired index in plugbaord configuration, if not available,
    then input remains the same, then calls the first mapping left rotor function*/
    char swap(char input);

    /*swaps input with paired index in plugbaord configuration, if not available,
    then input remains the same, then calls the reflector swap function */
    char swap_without_rotor(char input);

    /*links the rightmost rotor to te plugboard */
    void set_rotor(Rotor* attached_rotor);

    /*Links the plugboard to reflector if no rotors are in the configuration */
    void set_rf(Reflector* linked_reflector);

  private:
    std::ifstream plugboard_config;
    const char* pb_file;
    Reflector* reflector;
    Rotor* first_rotor;
    int configuration[26];
    int config_no;
};

#endif
