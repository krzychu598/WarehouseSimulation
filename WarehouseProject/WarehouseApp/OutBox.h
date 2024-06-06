//Maksymilian Zieliński
#pragma once
#include "Box.h"
class OutBox :
    public Box
{
public:
    OutBox();
    unsigned int getThisProductAmount(std::string& name) const;
};

