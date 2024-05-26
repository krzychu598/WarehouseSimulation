#pragma once
#ifdef _DEBUG
#include <iostream>
#define PRINT_MSG(msg) std::cout << msg << "\n"
#else
#define PRINT_MSG(msg)
#endif