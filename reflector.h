#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <fstream>
#include "rotor.h"

class Rotor;

class Reflector{
    public:
      /* Reflector constructor */
      Reflector(const char* filename);

      /* check if reflector configuration is well formed */
      int check_reflector();

      /* swaps the input with the its paired index in the configuration file */
      void swap(int& input);

      /* links the rightmosst rotor to the reflector */
      void set_rotor(Rotor* linked_rotor);

    private:
      const char* reflector_file;
      std::ifstream reflector_config;
      int reflector_configuration[512];
      Rotor* rotor_to_the_right;
};

#endif
