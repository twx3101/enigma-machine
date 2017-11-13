#include "input.h"
#include "errors.h"
#include <cstring>
#include <cstdlib>
#include <iostream>

using namespace std;
Input_switch::Input_switch(){}
Input_switch::Input_switch(char* a, int size) : input(a), length(size){}

int Input_switch::check_input(){
  int count = 0;
  for (int i = 0; i < length; i++){
    if (check_whitespace(input[i])){
      //do nothing
    }
    else if (check_valid_char(input[i]) == false){
      return INVALID_INPUT_CHARACTER;
    }
    else {
    without_ws[count] = input[i];
    count++;
    }
  }
  without_ws[count] = '\0';
  return NO_ERROR;
  }

bool Input_switch::check_valid_char(char a){
  if ((a > 64 && a < 91))
    return true;
  else
    return false;
  }


bool Input_switch::check_whitespace(char a){
    if (a == ' ' || a == '\t' || a == '\n' || a == '\r'){
      return true;
    }
    else
      return false;

  }

char* Input_switch::get_input(){
    return without_ws;
  }

int Input_switch::get_input_int(int position){
    unsigned int index = position;
    if (index > strlen(without_ws)){
      exit(1);
    }
    return (input_int[index]);
}

int Input_switch::get_input_int_count(){
    return input_int_count;
}

void Input_switch::convert_to_int(){
    int i = 0;
    while(without_ws[i] != '\0'){
      input_int[i] = without_ws[i] - 65;
      i++;
    }
    input_int_count = i;
}
