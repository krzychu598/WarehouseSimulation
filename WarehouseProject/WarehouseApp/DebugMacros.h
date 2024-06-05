#pragma once
#ifdef _DEBUG
#include <iostream>
#define PRINT_MSG(msg1, var, msg2) std::cout << msg1 << var << msg2 << "\n"
#define PRINT_MSG_N(msg1, var, true_false, msg2) std::string True; if(true_false == true) {True = "";} else {True = " not";} std::cout << msg1 << var << True << msg2 <<'\n'
#define PRINT(msg) std::cout << msg << "\n"
#define PRINT_MSG_L(msg1, var, msg2) std::cout << msg1 << var << msg2
#else
#define PRINT_MSG(msg1, var, msg2)
#define PRINT_MSG_N(msg1, var, true_false, msg2)
#define PRINT(msg
#endif

