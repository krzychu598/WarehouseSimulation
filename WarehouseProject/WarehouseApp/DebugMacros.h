#pragma once
#ifdef _DEBUG
#include <iostream>
#define PRINT_MSG(msg1, var, msg2) std::cout << msg1 << var << msg2 << "\n"
#else
#define PRINT_MSG(msg1, var, msg2)
#endif

