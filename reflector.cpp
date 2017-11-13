#include "reflector.h"
#include "helper.h"
#include "errors.h"
#include <string>
#include <iostream>

using std::string;
using std::endl;

Reflector::Reflector(const char* filename): reflector_file(filename){}

void Reflector::set_rotor(Rotor* a){
  rotor_to_the_right = a;
}

int Reflector::check_reflector(){

  if(check_file(reflector_file)){
    return ERROR_OPENING_CONFIGURATION_FILE;
  }
  reflector_config.open(reflector_file);
  int count = 0;
  int digit;
  string next;
  while(reflector_config >> next){

    //Non-numeric character
    if (!is_digit(next)){
      return NON_NUMERIC_CHARACTER;
    }
    digit = char_to_digit(next);

      //Invalid index
    if(check_invalid_char(digit)){
      return INVALID_INDEX;
    }

    reflector_configuration[count] = digit;

    //no duplicates in plugboard
    if (check_duplicate(count, reflector_configuration)){
        return INVALID_REFLECTOR_MAPPING;
      }

    count++;
  }

  //INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  if (count != 26 ) {
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
  }
  reflector_config.close();
  return NO_ERROR;
}

void Reflector::swap(){
  for (int i = 0; i < 26; i++){
    if (rotor_to_the_right->get_current_input() == reflector_configuration[i] && (i%2 == 0)){
      rotor_to_the_right->set_current_output(reflector_configuration[i+1]);
      break;
    }
    else if (rotor_to_the_right->get_current_input() == reflector_configuration[i] && (i%2 != 0)){
      rotor_to_the_right->set_current_output(reflector_configuration[i-1]);
      break;
    }
  }
  rotor_to_the_right->map_right(rotor_to_the_right->get_current_input());
}
