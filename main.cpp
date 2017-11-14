#include "helper.h"
#include "input.h"
#include "reflector.h"
#include "rotor.h"
#include "reflector.h"
#include "errors.h"
#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <cstdlib>
#include <cctype>
#include <vector>

using namespace std;

int Rotor::no_of_rotors = 0;
int Rotor::start_configuration[512];

int main(int argc, char** argv){

  int error_code;


  if (argc < 3){
    cerr << error_description(INSUFFICIENT_NUMBER_OF_PARAMETERS) << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }

  //length = strlen(input_message);
  //Input_switch keys(input_message, length);

//  error_code = keys.check_input();
//  if (error_code > 0){
//    cerr << error_description(error_code) << endl;
//    return error_code;
//  }

//  keys.convert_to_int();

  Plugboard first_plug(argv[1]);
    //first_plug.get_config();
  error_code = first_plug.check_config();

  if(error_code > 0){
    return error_code;
  }

  Reflector first_reflector(argv[2]);
  error_code = first_reflector.check_reflector();
  if (error_code > 0){
    return error_code;
  }

  vector<Rotor> rotors;
  if (argc > 4){
    rotors.resize(argc - 4);
    for (int i = 0; i < argc - 4; i++){
      rotors[i].setup(argv[i+3], argc-4);
      error_code = rotors[i].check_config();

      if (error_code > 0){
        return error_code;
      }
      if (i == 0){
        rotors[i].set_rf(&first_reflector);
        first_reflector.set_rotor(&rotors[0]);
      }
      if (i > 0 ){
        rotors[i-1].add_Rotor(&rotors[i]);
      }
      if(i == argc - 5){
        rotors[i].set_pb(&first_plug);
        first_plug.set_rotor(&rotors[i]);
      }
    }
  }

  if (rotors.size() > 0){
    error_code = rotors[0].start_open(argv[argc-1]);
    if (error_code > 0){
    return error_code;
  }
  for (unsigned int i = 0; i < rotors.size(); i++){
    rotors[i].set_offset(i);
  }
}

  char next;
  while(cin >> ws >> next){
  error_code = check_input(next);
  if (error_code > 0){
    cerr << next << error_description(error_code) << endl;
    return error_code;
  }
  next = first_plug.swap(next);
  cout << next;
  }
  return NO_ERROR;
}
