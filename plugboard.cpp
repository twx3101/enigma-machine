#include "plugboard.h"
#include "helper.h"
#include <string>
#include <iostream>
using namespace std;

Plugboard::Plugboard (const char* file, Input_switch* a): filename(file), input(a){}

void Plugboard::set_rotor(Rotor* a){
  first_rotor = a;
}

int Plugboard::check_config(){
  if(check_file(filename)){
    return 11;
  }

  plugboard_config.open(filename);

  config_no = 0;
  int digit;
  string next;
  while(plugboard_config >> next){

    //Non-numeric character
    if (!is_digit(next)){
      return 4;
    }
    digit = char_to_digit(next);

    //Invalid index
    if(check_invalid_char(digit)){
      return 3;
    }

    configuration[config_no] = digit;

    //no duplicates in plugboard
    if (check_duplicate(config_no, configuration))
      return 5;

    config_no++;
  }

  //INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS
  if (config_no % 2 != 0 ) {
    return 6;
  }
  plugboard_config.close();
  return 0;
}

void Plugboard::swap(){
  int temp;
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
    }
    output_out = temp;
    first_rotor->map_left(output_out);
  }
}

void Plugboard::final_swap(){
  output_out = first_rotor->get_current_input();
    for (int i = 0; i < config_no; i++){
        if (output_out == configuration[i]  && (i%2 == 0) ){
          output_out = (configuration[i+1]);
          break;
        }
        else if (output_out == configuration[i]  && (i%2 != 0)){
          output_out = (configuration[i-1]);
          break;
        }
      }
    cout << digit_to_char(output_out);
}
