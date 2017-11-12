#include "helper.h"
#include "errors.h"
#include <fstream>
#include <string>

using std::string;
using std::ifstream;

int char_to_digit(string str){
    int i = stoi(str);
    return i;
  }

char digit_to_char(int index){
      return (static_cast<char>(index + 65));
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

const char* error_description(int code){
  switch (code){
    case NO_ERROR:
      return "NO ERROR";
    case INSUFFICIENT_NUMBER_OF_PARAMETERS:
      return "INSUFFICIENT NUMBER OF PARAMETERS ON COMMAND LINE";
    case INVALID_INPUT_CHARACTER:
      return "INVALID CHARACTER INPUTTED";
    case INVALID_INDEX:
      return "INVALID INDEX";
    case NON_NUMERIC_CHARACTER:
      return "NON NUMERIC CHARACTER";
    case IMPOSSIBLE_PLUGBOARD_CONFIGURATION:
      return "IMPOSSIBLE PLUGBOARD CONFIGURATION";
    case INCORRECT_NUMBER_OF_PLUGBOARD_PARAMETERS:
      return "INCORRECT NUMBER OF PLUGBOARD PARAMETERS";
    case INVALID_ROTOR_MAPPING:
      return "INVALID ROTOR MAPPING";
    case NO_ROTOR_STARTING_POSITION:
      return "NO ROTOR STARTNG POSITION";
    case INVALID_REFLECTOR_MAPPING:
      return "INVALID REFLECTOR MAPPING";
    case INCORRECT_NUMBER_OF_REFLECTOR_PARAMETERS:
      return "INCORRECT NUMBER OF REFLECTOR PARAMETERS";
    case ERROR_OPENING_CONFIGURATION_FILE:
      return "ERROR OPENING CONFIGURATION FILE";
  }
  return "Unknown error";
}
