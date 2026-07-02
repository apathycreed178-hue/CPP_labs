#include <iostream>
#include "interpreter.h"


int main()
{
    interpreter i;
    i.interpret("add x, y;");
    
    return 0;
}