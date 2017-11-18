#include "helper.h"
#include "errors.h"
#include <fstream>
#include <string>

using std::string;
using std::ifstream;

int str_to_digit(string str){
    int i = stoi(str);
    return i;
  }

int char_to_int(char character){
  return (static_cast<int>(character - 65));
}

bool is_digit(string str){
  for (int i = 0; str[i] != '\0'; i++){
    if (!isdigit(str[i])){
      return false;
    }
  }
  return true;
}

bool check_file(const char* file){
  ifstream in_stream;
  in_stream.open(file);
  if (in_stream.fail()){
    return true;
  }
  in_stream.close();
  return false;
}

bool check_duplicate(int index, int a[]){
  for (int i = index - 1; i>=0; i--){
    if((a[index]) == a[i]){
      return true;
    }
  }
  return false;
}

bool check_invalid_char(int index){
  if (index <0 || index > 25){
    return true;
  }
  return false;
}

int check_input(char input){
  int input_int;
  input_int = char_to_int(input);
  if (check_invalid_char(input_int) == true){
    return INVALID_INPUT_CHARACTER;
  }
else
  return NO_ERROR;
}

const char* error_description(int code){
  switch (code){
    case NO_ERROR:
      return "NO ERROR";
    case INSUFFICIENT_NUMBER_OF_PARAMETERS:
      return "usage: enigma plugboard-file reflector-file (<rotor-file>* rotor-positions)?";
    case INVALID_INPUT_CHARACTER:
      return " is not a valid input character (input characters must be upper case letters A-Z)!";
    case INVALID_INDEX:
      return " Invalid number (must be between 0 - 25) in ";
    case NON_NUMERIC_CHARACTER:
      return "Non-numeric character ";
    case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
      return "Impossible plugboard configuration. Attempted to map a contact to itself or more than one contact";
    case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
      return "Incorrect number of parameters in plugboard file ";
    case INVALID_ROTOR_MAPPING:
      return "Invalid mapping of rotors";
    case NO_ROTOR_STARTING_POSITION:
      return "No starting position for rotor ";
    case INVALID_REFLECTOR_MAPPING:
      return "INVALID REFLECTOR MAPPING";
    case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS:
      return "INCORRECT NUMBER OF REFLECTOR PARAMETERS";
    case ERROR_OPENING_CONFIGURATION_FILE:
      return "Error opening configuration file ";
  }
  return "Unknown error";
}
