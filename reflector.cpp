#include "reflector.h"
#include "helper.h"
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
    return 11;
  }
  reflector_config.open(reflector_file);
  int count = 0;
  int digit;
  string next;
  while(reflector_config >> next){

    //Non-numeric character
    if (!is_digit(next)){
      return 4;
    }
    digit = char_to_digit(next);

      //Invalid index
    if(check_invalid_char(digit)){
      return 3;
    }

    reflector_configuration[count] = digit;

    //no duplicates in plugboard
    if (check_duplicate(count, reflector_configuration)){
        return 9;
      }

    count++;
  }

  //INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  if (count != 26 ) {
    return 10;
  }
  reflector_config.close();
  return 0;
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
