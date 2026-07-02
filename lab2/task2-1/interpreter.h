#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <iostream>
#include <cstring>
#include <cctype>
#include <stdexcept>
#include <cstdio>
#include "trie.h"

class interpreter {
private:

    char const* _var_alph = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789";

	trie _variables;
	const char* _commands[12] = {"Load", "Save", "Print", "Shuffle", "Free", "Concat", "", "", "", "", ""};
public:
    interpreter() : _variables(_var_alph) {   
       
    }

public: 

    void interpret( const char* my_str) {

        char* copy_str = new char[strlen(my_str) + 1];
        strcpy(copy_str, my_str);
        char* ptr = copy_str;
        int i = 0;
        int ind = 0;
        char line[BUFSIZ];
        char* sep_instruction[9];
        char* instruction[9];
        line[0] = 0;
        for (int i = 0; i < 9; i++) {
            instruction[i] = new char[BUFSIZ];
            sep_instruction[i] = new char[BUFSIZ];
        }

        for (int i = 0; i < 9; ++i) {
            instruction[i] = nullptr;
            sep_instruction[i] = nullptr;
        }

        while (*ptr != 0) {

            if (isalnum(*ptr)) {
                line[i] = *ptr;
                i++;
            }

            else if ((*ptr == ' ' || *ptr == ';' || *ptr == ',')) {

                if (line[0] != 0) {
                    line[i] = 0;

                    sep_instruction[ind] = instruction[ind];
                    strcpy(instruction[ind], line);

                    line[0] = 0;

                    i = 0;
                    ind++;
                }
                if (*ptr == ',') {
                    ind++;
                    strcpy(sep_instruction[ind], ",");
                    ptr++;
                    continue;
                }
                else if (*ptr == ';') {
                    strcpy(sep_instruction[ind], ";");
                    instruction[ind] = 0;
                    ptr++;
                    continue;
                }
            }

            ptr++;

        }

        i = 0;
        while (sep_instruction[i] != 0) {
            std::cout << sep_instruction[i] << std::endl;
            i++;
        }

    }

};

#endif