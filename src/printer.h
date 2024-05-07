#pragma once

#include <memory>
#include <vector>

#include "adapters.h"
#include "shapes.h"

namespace NS_Printer
{
    class Printer
    {
    public:
        explicit Printer() = default;
        void SetAdapter(std::unique_ptr<Adapter> adapter);
        void AddObjToPrint(std::shared_ptr<const Shapes::Object> obj);
        void Print();
    private:
        std::unique_ptr<Adapter> adapter_;
        std::vector<std::shared_ptr<const Shapes::Object>> objs_to_print_;
    }; // end class Printer
} // end namespace Printer