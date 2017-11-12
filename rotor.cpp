#include "rotor.h"
#include "helper.h"
#include <string>
#include <iostream>

using std::string;
using std::endl;
using std::cout;

Rotor::Rotor(const char* f) : filename(f){
  rotor_right = NULL;
  rotor_left = NULL;
  reflector = NULL;
  rotor_no = no_of_rotors;
  no_of_rotors++;
}

void Rotor::add_Rotor(Rotor* new_rotor){
  rotor_left = new_rotor;
  new_rotor->rotor_right = this;
}

int Rotor::check_config(){

  if(check_file(filename)){
    return 11;
  }
  rotor_file.open(filename);

  int digit;
  string next;
  while(rotor_file >> next){

    //Non-numeric character
    if (!is_digit(next)){
      return 4;
    }
    digit = char_to_digit(next);

    //Invalid index
    if(check_invalid_char(digit)){
      return 3;
    }

    rotor_configuration[config_length] = digit;

    //no duplicates in rotor
    for (int i = config_length-1; i >= 0; i--){
      if (rotor_configuration[config_length] == rotor_configuration[i] && config_length < 26){
        return 7;
      }
    }

    //configuration[count] = digit;
    config_length++;
  }

  //DOES NOT MAP TO ALL CHARACTERS (need 26 rotor characters and one or more notch)
  if (config_length < 27 ) {
    return 7;
  }
  rotor_file.close();
  return 0;

}

void Rotor::set_offset(int config[]){
  offset = config[no_of_rotors - rotor_no - 1];
  //set offset from left to right
}

void Rotor::set_pb(Plugboard* a){
  plugboard = a;
}

void Rotor::set_rf(Reflector* a){
  reflector = a;
}
int Rotor::start_open(const char* file_start){

  if(check_file(filename)){
    return 11;
  }
  start_position.open(file_start);

  string next;
  int digit;
  int start_configuration[512];
  int count = 0;
  while (start_position >> next){
    if (!is_digit(next)){
      return 4;
    }
    digit = char_to_digit(next);
    if(check_invalid_char(digit)){
      return 3;
    }
    start_configuration[count] = digit;
    count++;
  }
  if (count < no_of_rotors){
    return 8;
  }
  set_offset(start_configuration);
  start_position.close();
  return 0;
}



void Rotor::map_left(int input){
  current_input = input;
  if (rotor_no == 0){
    offset++;
  }
  if (offset > 25){
    offset -= 26;
  }

  for(int i = 26; i< config_length; i++){
    if (offset == rotor_configuration[i]){
      rotor_left->offset += 1;
    }
  }
  //if offset hit notch, then rotor_no + 1 offset increase

  current_input = current_input + offset;
  if (current_input > 25){
    current_input -= 26;
  }

  current_input = rotor_configuration[current_input];

  current_input = current_input - offset;
  if (current_input < 0){
    current_input += 26;
  }


  if(rotor_left != NULL){
    rotor_left->map_left(current_input);
    return;
  }
  if(rotor_left == NULL){
      reflector->swap();
    return;
    }
}

void Rotor::map_right(int input){
  current_input = input;
  current_input = current_input + offset;
  if (current_input > 25){
    current_input -= 26;
  }
  for (int i = 0; i < 26; i++){
    if (current_input == rotor_configuration[i]){
      current_input = i;
      break;
    }
  }
  current_input = current_input - offset;
  if (current_input < 0){
    current_input += 26;
  }

  if(rotor_right != NULL){
    rotor_right->map_right(current_input);
    return;
  }
  if(rotor_right == NULL){
      plugboard->final_swap();
      return;
    }
  }

int Rotor::get_current_input(){
  return current_input;
}

void Rotor::set_current_output(int out){
  current_input = out;
}
