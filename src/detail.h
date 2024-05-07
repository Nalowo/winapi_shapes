#pragma once

#include <string>
#include <unordered_map>
#include <stdexcept>

#include "tagged.h"

namespace detail
{
    enum class ShapesTag : uint8_t
    {
        CIRCLE,
        ELLIPSE,
        TRIANGLE,
        SQUARE,
        QUADRANGLE
    }; // end enum class Shapes

    struct ShapeTagHasher
    {
        std::size_t operator()(ShapesTag shape) const
        {
            return static_cast<std::size_t>(shape);
        }
    }; // end struct ShapeTagHash

    class ShapeTable
    {
    public:
        ShapesTag GetShapeType(const std::string& name) const
        {
            auto it = table_.find(name);
            if (it == table_.end())
            {
                throw std::invalid_argument("Invalid shape name");
            }
            return it->second;
        }
    private:
        std::unordered_map<std::string, ShapesTag> table_
        {
            { "circle", ShapesTag::CIRCLE },
            { "ellipse", ShapesTag::ELLIPSE },
            { "triangle", ShapesTag::TRIANGLE },
            { "square", ShapesTag::SQUARE },
            { "quadrangle", ShapesTag::QUADRANGLE }
        };
    }; // end class ShapeTable

    struct X_Axis {};
    struct Y_Axis {};

    struct Point
    {
        using x_axis = util::Tagged<uint32_t, X_Axis>;
        using y_axis = util::Tagged<uint32_t, Y_Axis>;

        explicit Point(x_axis x, y_axis y) : x_(x), y_(y) {}
        Point(const Point& p) : x_(*p.x_), y_(*p.y_) {}

        x_axis x_;
        y_axis y_;
    }; // end struct Point

} // end namespace detail