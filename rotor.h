#ifndef ROTOR_H
#define ROTOR_H

#include "reflector.h"
#include "plugboard.h"
#include <fstream>

class Plugboard;
class Reflector;

class Rotor{
  public:
    /* Rotor constructor */
    Rotor();

    /* setup a rotor object used in an array or vector class. rotor_file is the
    configuration and number is the rotor_no */
    void setup(const char* rotor_file, int number);

    /* link adjacent rotors to each other with pointers*/
    void add_Rotor(Rotor* new_rotor);

    /* Link the plugboard to the rightmost rotor */
    void set_pb(Plugboard* a);

    /* Link the reflector to the leftmost rotor */
    void set_rf(Reflector* a);

    /* Check if the rotor configuration file is well-formed, if it is return 0
    else return a specific error code */
    int check_config();

    /*Check if the rotor startng positions file is well-formed, if it is return
    0 else return a specific error code */
    int check_start_positions(const char* file_start);

    /* Passes the input character (in int form) to the rotor to the left and
    changes the input according to rotor mapping. At the leftmost rotor, passes
    the input to the reflector */
    void map_left(int& input);

    /*Passes the input character (in int form) to the rotor to the right and
    changes the input according to rotor mapping. At the rotor_rightmost rotor,
    passes the input to the plugboard*/
    void map_right(int& input);

    /*Sets the starting positions of the rotor number (index). Also checks
    whether the starting position is a notch, if so set notch_reached to true*/
    void set_offset(int index);


  private:
    //name of file
    const char* filename;

    std::ifstream rotor_file;
    std::ifstream start_position;

    // pointer to rotor to the right. Initialized as NULL
    Rotor* rotor_right;

    // pointer to rotor to the left. Initialized as NULL
    Rotor* rotor_left;

    // pointer to the reflector. Initialized as NULL
    Reflector* reflector;

    // pointer to the plugboard. Initialized as NULL
    Plugboard* plugboard;

     // length of the rotor file.
    int config_length;

    // length of the rotor configuration
    int rotor_configuration[52];

    //offset of rotor from absolute position A
    int offset;

    bool notch_reached;

    // rotor ID
    int rotor_no;

    static int start_configuration[512];
    static int no_of_rotors;
};

#endif
