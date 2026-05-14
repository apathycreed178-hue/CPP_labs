#include <iostream>
#include <cstring>
#include <cctype>
#include <stdexcept>
#include <cstdio>

void plus(const char *, const char *);
void min(const char *, const char *);

int convert(char *);

bool checkInstruction(char *instruction[], const char* actions[], int actions_amount);

void interpret(char *);

int main() {
    
    char my_str[] = "add x, y    ; ";


    try {
        interpret(my_str);
    } catch (std::logic_error &ex) {
        std::cout << "Error caught: " << ex.what() << std::endl;
    } catch (std::runtime_error &ex) {
        std::cout << "Error caught: " << ex.what() << std::endl;
    }

    return 0;
}

void plus(char *a, char *b) {
    std::cout << convert(a) << " + " << convert(b) << std::endl;
}

void min(char *a, char *b) {
    std::cout << convert(a) << " - " << convert(b) << std::endl;
}

bool checkInstruction(char instruction[][BUFSIZ], const char* actions[], int actions_amount) {
    for (int i = 0; i < actions_amount; i++) {
        if (strcmp(instruction[0], actions[i]) == 0) {
            return true;
        }
    }

    return false;
}

int convert( char * variable) {

    if (variable == nullptr) {
        throw std::runtime_error("Not exsisting variable");
    }

    char *p;
    p = variable;

    int result = 0;

    while (*p) {
        result = result * 10 + (*p - '0');
        p++;
    }

    return result;
}

void interpret(char* my_str) {

    const char *actions[] = { "add", "min" };

    char *ptr = my_str;
    int i = 0;
    int ind = 0;
    char instruction[BUFSIZ];
    instruction[0] = 0;

    int coma_flag = 0;
    int cp_flag = 0;

    char array[3][BUFSIZ];

    while(*ptr != 0) {
        if (isalnum(*ptr)) {
            instruction[i] = *ptr;
            i++;
        } else if (( *ptr == ' ' || *ptr == ';' || *ptr == ',') && instruction[0] != 0) {

            if (*ptr == ',') {
                coma_flag = 1;
            } else if (*ptr = ';') {
                cp_flag = 1;
            }

            instruction[i] = 0;

            std::cout << instruction << std::endl;
            strcpy(array[ind], instruction);

            instruction[0] = 0;

            i = 0;
            ind++;

        }

        ptr++;

    }

    if (coma_flag != 1) {
        throw std::logic_error(" ',' not found between arguments");
    }
    if (cp_flag != 1) {
        throw std::logic_error(" missing ';' in instruction");
    }

    if (checkInstruction(array, actions, 2)) {
        if (strcmp(array[0], actions[0]) == 0) {
            plus(array[1], array[2]);
        } else if (strcmp(array[0], actions[1]) == 0) {
            min(array[1], array[2]);
        }
    } else {
        throw std::logic_error("Unknown instruction");
    }

}

// TODO: nullptr for variables