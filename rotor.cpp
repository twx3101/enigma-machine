#include "rotor.h"
#include "helper.h"
#include "errors.h"
#include <string>
#include <iostream>

using std::string;
using std::endl;
using std::cerr;

int Rotor::no_of_rotors = 0;
int Rotor::start_configuration[512];

Rotor::Rotor(){
  rotor_right = NULL;
  rotor_left = NULL;
  reflector = NULL;
  plugboard = NULL;
  notch_reached = false;
}

void Rotor::setup(const char* rotor_file, int number){
  filename = rotor_file;
  rotor_no = number - no_of_rotors - 1;
  no_of_rotors++;
}



void Rotor::add_Rotor(Rotor* new_rotor){
  rotor_right = new_rotor;
  new_rotor->rotor_left = this;
}

void Rotor::set_pb(Plugboard* a){
  plugboard = a;
}

void Rotor::set_rf(Reflector* a){
  reflector = a;
}

int Rotor::check_config(){

  if(check_file(filename)){
    cerr << error_description(ERROR_OPENING_CONFIGURATION_FILE) <<
    filename << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  int digit;
  string next;

  rotor_file.open(filename);

  while(rotor_file >> next){

    //Non-numeric character
    if (!is_digit(next)){
      cerr << error_description(NON_NUMERIC_CHARACTER) << next << " for mapping in rotorfile "
      << filename << endl;
      return NON_NUMERIC_CHARACTER;
    }
    digit = str_to_digit(next);

    //Invalid index
    if(check_invalid_char(digit)){
      cerr << digit << error_description(INVALID_INDEX) << "rotor file " << filename << endl;
      return INVALID_INDEX;
    }

    rotor_configuration[config_length] = digit;

    //no duplicates in rotor
    for (int i = config_length-1; i >= 0; i--){
      if (rotor_configuration[config_length] == rotor_configuration[i] &&
         config_length < 26){
        cerr << "Invalid mapping of input " << config_length << " to output "
        << rotor_configuration[i];
        cerr << " (output " << rotor_configuration[i] << " is already mapped to from input "
        << i  << ") "<< endl;

        return INVALID_ROTOR_MAPPING;
      }
    }

    config_length++;
  }

  //check for correct number of mappings (need 26 rotor characters and one or more notch)
  if (config_length < 26 ) {
    cerr << "Not all inputs mapped in rotor file: " << filename << endl;
    return INVALID_ROTOR_MAPPING;
  }
  rotor_file.close();
  return NO_ERROR;

}


int Rotor::check_start_positions(const char* file_start){

  if(check_file(file_start)){
    cerr << error_description(ERROR_OPENING_CONFIGURATION_FILE) << file_start
    << endl;
    return ERROR_OPENING_CONFIGURATION_FILE;
  }

  start_position.open(file_start);
  int digit;
  int count = 0;
  string next;

  while (start_position >> next){

    //check NON_NUMERIC_CHARACTER
    if (!is_digit(next)){
      cerr << error_description(NON_NUMERIC_CHARACTER) << next << " in rotor positions file " << file_start << endl;
      return NON_NUMERIC_CHARACTER;
    }

    digit = str_to_digit(next);

    //check invalid index
    if(check_invalid_char(digit)){
      cerr << digit << error_description(INVALID_INDEX) << "in rotor positions file "
      << file_start << endl;
      return INVALID_INDEX;
    }
    start_configuration[count] = digit;
    count++;
  }

  if (count < no_of_rotors){
    cerr << error_description(NO_ROTOR_STARTING_POSITION) << count <<
    " in rotor position file: " << file_start << endl;
    return NO_ROTOR_STARTING_POSITION;
  }

  start_position.close();
  return NO_ERROR;
}



void Rotor::map_left(int &input){
  if (rotor_no == 0){
    offset++;
    notch_reached = false;
    //reset notch if offset increased
  }
  if (offset > 25){
    offset -= 26;
  }

  for(int i = 26; i< config_length; i++){
    if (offset == rotor_configuration[i] && rotor_no != no_of_rotors - 1 && notch_reached == false){
      notch_reached = true;
      rotor_left->offset += 1;
      rotor_left->notch_reached = false;
    }
  }
  //if offset hit notch, then rotor_no + 1 increases offset and set notch_reached
  //of current notch to true and reset the notch_reached for the rotor to the left

  input = input + offset;
  if (input > 25){
    input -= 26;
  }

  input = rotor_configuration[input];

  input = input - offset;
  if (input < 0){
    input += 26;
  }


  if(rotor_left != NULL){
    rotor_left->map_left(input);
    return;
  }
  if(rotor_left == NULL){
      reflector->swap(input);
    return;
    }
}

void Rotor::map_right(int &input){
  input = input + offset;
  if (input > 25){
    input -= 26;
  }
  for (int i = 0; i < 26; i++){
    if (input == rotor_configuration[i]){
      input = i;
      break;
    }
  }
  input = input - offset;
  if (input < 0){
    input += 26;
  }

  if(rotor_right != NULL){
    rotor_right->map_right(input);
    return;
  }
  if(rotor_right == NULL){
      return;
    }
  }

void Rotor::set_offset(int index){
  offset = start_configuration[index];
  for(int i = 26; i< config_length; i++){
    if (offset == rotor_configuration[i]){
      notch_reached = true;
    }
  }
}
