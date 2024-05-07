#pragma once

#include "shapes.h"

namespace NS_Printer
{
    class Adapter
    {
    public:
        virtual ~Adapter() = default;
        virtual void Print(std::shared_ptr<const Shapes::Object>) = 0;
    }; // end class Adapter
} // end namespace Printer