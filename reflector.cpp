#include "reflector.h"
#include "helper.h"
#include "errors.h"
#include <string>
#include <iostream>

using std::string;
using std::endl;
using std::cerr;

Reflector::Reflector(const char* filename): reflector_file(filename){
  rotor_to_the_right = NULL;
}

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
    if (count+1 > 26){
      cerr << "Incorrect (odd) number of parameters in reflector file " << reflector_file << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }

    //Non-numeric character
    if (!is_digit(next)){
      cerr << error_description(NON_NUMERIC_CHARACTER) << "in reflector file " << reflector_file << endl;
      return NON_NUMERIC_CHARACTER;
    }
    digit = char_to_digit(next);

      //Invalid index
    if(check_invalid_char(digit)){
      cerr << error_description(INVALID_INDEX) << "reflector file " << reflector_file << endl;
      return INVALID_INDEX;
    }

    reflector_configuration[count] = digit;

    //no duplicates in plugboard
    if (check_duplicate(count, reflector_configuration)){
      cerr << "Invalid mapping of input " << count << " to output " << reflector_configuration[count] << " (output has already been mapped)" << endl;
        return INVALID_REFLECTOR_MAPPING;
      }

    count++;

  }

  //INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS

  if (count < 26 ) {
    if (count %2 == 0){
      cerr << "Insufficient number of mappings in reflector file: " << reflector_file << endl;
      return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
    else {
      cerr << "Incorrect (odd) number of parameters in reflector file " << reflector_file << endl;
    return INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS;
    }
  }
  reflector_config.close();
  return NO_ERROR;
}

void Reflector::swap(int &input){
  int pop = input;
  for (int i = 0; i < 26; i++){
    if (pop == reflector_configuration[i] && (i%2 == 0)){
      input = reflector_configuration[i+1];
      break;
    }
    else if (pop == reflector_configuration[i] && (i%2 != 0)){
      input = reflector_configuration[i-1];
      break;
    }
  }
  if (rotor_to_the_right != NULL){
    rotor_to_the_right->map_right(input);
  }
  else
    return;
}
