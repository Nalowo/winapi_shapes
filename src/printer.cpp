#include "printer.h"

namespace NS_Printer
{
    void Printer::SetAdapter(std::unique_ptr<Adapter> adapter)
    {
        adapter_ = std::move(adapter);
    }

    void Printer::AddObjToPrint(std::shared_ptr<const Shapes::Object> obj)
    {
        if (adapter_ == nullptr) return;
        objs_to_print_.push_back(std::shared_ptr<const Shapes::Object>(obj));
    }

    void Printer::Print()
    {
        if (!adapter_) return;
        for (auto& obj : objs_to_print_)
        {
            adapter_->Print(obj);
        }
    }
} // end namespace Printer