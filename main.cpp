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
  char input_message[512];
  int length;
  int error_code;


  if (argc < 3){
    std::cerr << error_description(INSUFFICIENT_NUMBER_OF_PARAMETERS) << endl;
    return INSUFFICIENT_NUMBER_OF_PARAMETERS;
  }
  cin.getline(input_message, 512);
  length = strlen(input_message);
  Input_switch keys(input_message, length);

  error_code = keys.check_input();
  if (error_code > 0){
    cerr << error_description(error_code) << endl;
    return error_code;
  }

  keys.convert_to_int();

  Plugboard first_plug(argv[1], &keys);
    //first_plug.get_config();
  error_code = first_plug.check_config();

  if(error_code > 0){
    cerr << error_description(error_code) << endl;
    return error_code;
  }

  Reflector first_reflector(argv[2]);
  error_code = first_reflector.check_reflector();
  if (error_code > 0){
    cerr << error_description(error_code) << endl;
    return error_code;
  }

  vector<Rotor> rotors;
  if (argc > 4){
    rotors.resize(argc - 4);
    for (int i = 0; i < argc - 4; i++){
      rotors[i].setup(argv[i+3], argc-4);
      error_code = rotors[i].check_config();

      if (error_code > 0){
        cerr << error_description(error_code) << endl;
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
  /*Rotor first_rotor("rotors/III.rot");
  error_code = first_rotor.check_config();
  if (error_code > 0){
    cerr << error_description(error_code) << endl;
    return error_code;
  }
  else {
    cout << "Rotor configuration is OK.\n";
    first_rotor.set_pb(&first_plug);
    first_plug.set_rotor(&first_rotor);
  }

  Rotor second_rotor("rotors/II.rot");
  error_code = second_rotor.check_config();
  if (error_code > 0){
    cerr << error_description(error_code) << endl;
    return error_code;
  }
  else {
    cout << "Rotor configuration is OK.\n";
    first_rotor.add_Rotor(&second_rotor);
  }

  Rotor third_rotor("rotors/I.rot");
  error_code = third_rotor.check_config();
  if (error_code > 0){
    cerr << error_description(error_code) << endl;
    return error_code;
  }
  else {
    cout << "Rotor configuration is OK.\n";
    second_rotor.add_Rotor(&third_rotor);
  }*/
  if (rotors.size() > 0){
    error_code = rotors[0].start_open(argv[argc-1]);
    if (error_code > 0){
    cerr << error_description(error_code) << endl;
    return error_code;
  }
  for (unsigned int i = 0; i < rotors.size(); i++){
    rotors[i].set_offset(i);
  }
}



  first_plug.swap();
  return NO_ERROR;
}
