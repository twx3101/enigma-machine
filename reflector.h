#ifndef REFLECTOR_H
#define REFLECTOR_H

#include <fstream>
#include "rotor.h"

class Rotor;

class Reflector{
    public:
      Reflector(const char* filename);
      int check_reflector();
      void swap(int& input);
      void set_rotor(Rotor* a);

    private:
      const char* reflector_file;
      std::ifstream reflector_config;
      int reflector_configuration[512];
      Rotor* rotor_to_the_right;
};

#endif
