#include "plugboard.h"
#include "errors.h"
#include "helper.h"
#include <string>
#include <iostream>
using std::string;
using std::cerr;
using std::endl;

Plugboard::Plugboard (const char* file): pb_file(file){
  first_rotor = NULL;
  reflector = NULL;
}

void Plugboard::set_rotor(Rotor* attached_rotor){
  first_rotor = attached_rotor;
}

void Plugboard::set_rf(Reflector* linked_reflector){
  reflector = linked_reflector;
}

int Plugboard::check_config(){
  if(check_file(pb_file)){
    cerr << error_description(ERROR_OPENING_CONFIGURATION_FILE) << pb_file << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }


  config_no = 0;
  int digit;
  string next;
  plugboard_config.open(pb_file);

  while(plugboard_config >> next){
    //if plugboard reaches > 26 char return incoorect number of parameters
    if (config_no+1 > 26){
      cerr << error_description(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS) << pb_file << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    //Non-numeric character
    if (!is_digit(next)){
      cerr << error_description(NON_NUMERIC_CHARACTER) <<  next << " in plugboard file " << pb_file << endl;
      return NON_NUMERIC_CHARACTER;
    }
    digit = str_to_digit(next);

    //Invalid index
    if(check_invalid_char(digit)){
      cerr <<  digit << error_description(INVALID_INDEX) << "in plugboard file " << pb_file << endl;
      return INVALID_INDEX;
    }

    configuration[config_no] = digit;

    //no duplicates in plugboard
    if (check_duplicate(config_no, configuration)){
      cerr << error_description(IMPOSSIBLE_PLUGBOARD_CONFIGURATION) << "contact " << configuration[config_no] << endl;
      return IMPOSSIBLE_PLUGBOARD_CONFIGURATION;
    }
    config_no++;

  }

  //INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  if (config_no % 2 != 0 ) {
    cerr << error_description(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS) << pb_file << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }

  plugboard_config.close();
  return NO_ERROR;
}

char Plugboard::swap(char input){
  int to_rotor;
  to_rotor = static_cast<int>(input - 65);

  //first swap
  for (int i = 0; i < config_no; i++){
    if (to_rotor == configuration[i] && (i%2 == 0)){
        to_rotor = configuration[i+1];
        break;
    } else if (to_rotor == configuration[i] && (!i%2 == 0)){
        to_rotor = configuration[i-1];
        break;
      }
    }

    //to_rotor gets passed by reference to rotor and reflector
    first_rotor->map_left(to_rotor);

    //after returning from rotor do a final swap
    for (int i = 0; i < config_no; i++){
      if (to_rotor == configuration[i] && (i%2 == 0)){
          to_rotor = configuration[i+1];
          break;
      } else if (to_rotor == configuration[i] && (!i%2 == 0)){
          to_rotor = configuration[i-1];
          break;
        }
      }

      input = static_cast<char>(to_rotor + 65);
      return input;
    }


char Plugboard::swap_without_rotor(char input){
  int to_reflector;
  to_reflector = static_cast<int>(input - 65);


    //first swap
  for (int i = 0; i < config_no; i++){
    if (to_reflector == configuration[i] && (i%2 == 0)){
        to_reflector = configuration[i+1];
        break;
    } else if (to_reflector == configuration[i] && (!i%2 == 0)){
        to_reflector = configuration[i-1];
        break;
      }
    }

//to_rotor gets passed by reference to reflector
    reflector->swap(to_reflector);

//after returning from reflector do a final swap
    for (int i = 0; i < config_no; i++){
      if (to_reflector == configuration[i] && (i%2 == 0)){
          to_reflector = configuration[i+1];
          break;
      } else if (to_reflector == configuration[i] && (!i%2 == 0)){
          to_reflector = configuration[i-1];
          break;
        }
      }
      input = static_cast<char>(to_reflector + 65);
      return input;
}
