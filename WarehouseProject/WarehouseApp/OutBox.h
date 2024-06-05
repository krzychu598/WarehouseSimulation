#pragma once
#include "Box.h"
class OutBox :
    public Box
{
public:
    OutBox();
    unsigned int getProductAmount(std::string& name) const;
};

