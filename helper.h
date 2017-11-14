#ifndef HELPER_H
#define HELPER_H

#include <string>

int char_to_digit(std::string str);
int char_to_int(char character);
char digit_to_char(int index);
bool is_digit(std::string str);
const char* error_description(int code);
bool check_file(const char* file);
bool check_duplicate(int index, int a[]);
bool check_invalid_char(int index);
int check_input(char input);

#endif
