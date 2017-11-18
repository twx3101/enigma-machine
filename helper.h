#ifndef HELPER_H
#define HELPER_H

#include <string>

/* converts a string to its corresponding int */
int str_to_digit(std::string str);

/* converts an upper case character to an int value with A starting at 0 */
int char_to_int(char character);

/* check if str is a digit */
bool is_digit(std::string str);

/* checks if file is a valid file */
bool check_file(const char* file);

/* checks if any duplicate is found in the array of ints */
bool check_duplicate(int index, int a[]);

/* check if index is invalid ( < 0 or > 25) */
bool check_invalid_char(int index);

/* check if input is only a upper case character, if not returns INVALID_INPUT_CHARACTER */
int check_input(char input);

/* Prints out error descriptions according to the error code */
const char* error_description(int code);

#endif
