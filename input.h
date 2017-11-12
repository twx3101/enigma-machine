#ifndef INPUT_H
#define INPUT_H


class Input_switch
{
  public:
    Input_switch();
    Input_switch(char* a, int size);

    int check_input();
    bool check_valid_char(char a);
    bool check_whitespace(char a);
    char* get_input();
    int get_input_int(int position);
    int get_input_int_count();
    void convert_to_int();
    
  private:
    char* input;
    char without_ws[512];
    int length;
    int input_int[512];
    int input_int_count;
};

#endif
