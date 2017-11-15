#include "plugboard.h"
#include "errors.h"
#include "helper.h"
#include <string>
#include <iostream>
using namespace std;

Plugboard::Plugboard (const char* file): filename(file){}

void Plugboard::set_rotor(Rotor* a){
  first_rotor = a;
}

void Plugboard::set_rf(Reflector* a){
  reflector = a;
}

int Plugboard::check_config(){
  if(check_file(filename)){
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  plugboard_config.open(filename);

  config_no = 0;
  int digit;
  string next;
  while(plugboard_config >> next){
    if (config_no+1 > 26){
      cerr << error_description(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS) << filename << endl;
      return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
    }
    //Non-numeric character
    if (!is_digit(next)){
      cerr << error_description(NON_NUMERIC_CHARACTER) << "in plugboard file " << filename << endl;
      return NON_NUMERIC_CHARACTER;
    }
    digit = char_to_digit(next);

    //Invalid index
    if(check_invalid_char(digit)){
      cerr << error_description(INVALID_INDEX) << "in plugboard file " << filename << endl;
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
    cerr << error_description(INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS) << filename << endl;
    return INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS;
  }
  plugboard_config.close();
  return NO_ERROR;
}

char Plugboard::swap(char input){
  /*int temp;
  int length = input->get_input_int_count();
  for (int count = 0; count < length; count++){
    temp = (input->get_input_int(count));

    for (int i = 0; i < config_no; i++){
      if (temp == configuration[i] && (i%2 == 0)){
        temp = configuration[i+1];
        break;
      } else if (temp == configuration[i] && (!i%2 == 0)){
        temp = configuration[i-1];
        break;
      }
    }*/
  int to_rotor;
  to_rotor = static_cast<int>(input - 65);
  for (int i = 0; i < config_no; i++){
    if (to_rotor == configuration[i] && (i%2 == 0)){
        to_rotor = configuration[i+1];
        break;
    } else if (to_rotor == configuration[i] && (!i%2 == 0)){
        to_rotor = configuration[i-1];
        break;
      }
    }

    first_rotor->map_left(to_rotor);
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


  /*output_out = temp;
    first_rotor->map_left(output_out);
  }
}*/

char Plugboard::swap_without_rotor(char input){
  int to_rotor;
  to_rotor = static_cast<int>(input - 65);
  for (int i = 0; i < config_no; i++){
    if (to_rotor == configuration[i] && (i%2 == 0)){
        to_rotor = configuration[i+1];
        break;
    } else if (to_rotor == configuration[i] && (!i%2 == 0)){
        to_rotor = configuration[i-1];
        break;
      }
    }
    reflector->swap(to_rotor);

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
