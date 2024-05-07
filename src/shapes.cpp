#include "shapes.h"

namespace Shapes
{
    using namespace detail;

    Object::Object(ShapesTag shape_type) : shape_type_(shape_type) {}

    Object::Object(const Object &other) : shape_type_(other.shape_type_) {}

    ShapesTag Object::GetShapeType() const
    {
        return shape_type_;
    }

    //=======================Circle=======================

    Circle::Circle() : Object(ShapesTag::CIRCLE),
                       center_(Point{Point::x_axis{0}, Point::y_axis{0}}),
                       radius_(0) {}

    Circle::Circle(const Circle &other) : Object(other),
                                          center_(other.center_),
                                          radius_(other.radius_) {}

    Circle &Circle::SetCenter(Point center)
    {
        center_ = center;
        return *this;
    }
    Circle &Circle::SetRadius(uint32_t radius)
    {
        radius_ = radius;
        return *this;
    }

    detail::Point Circle::GetCenter() const
    {
        return center_;
    }
    uint32_t Circle::GetRadius() const
    {
        return radius_;
    }

    //=======================Ellipse=======================

    Ellipse::Ellipse() : Object(ShapesTag::ELLIPSE),
                         center_(Point{Point::x_axis{0}, Point::y_axis{0}}),
                         radiusX_(0),
                         radiusY_(0) {}

    Ellipse::Ellipse(const Ellipse &other) : Object(other),
                                             center_(other.center_),
                                             radiusX_(other.radiusX_),
                                             radiusY_(other.radiusY_) {}

    Ellipse &Ellipse::SetCenter(Point center)
    {
        center_ = center;
        return *this;
    }
    Ellipse &Ellipse::SetRadiusX(const uint32_t radiusX)
    {
        radiusX_ = radiusX;
        return *this;
    }
    Ellipse &Ellipse::SetRadiusY(const uint32_t radiusY)
    {
        radiusY_ = radiusY;
        return *this;
    }

    detail::Point Ellipse::GetCenter() const
    {
        return center_;
    }
    uint32_t Ellipse::GetRadiusX() const
    {
        return radiusX_;
    }
    uint32_t Ellipse::GetRadiusY() const
    {
        return radiusY_;
    }

    //=======================Triangle=======================

    Triangle::Triangle() : Object(ShapesTag::TRIANGLE),
                           p1_(Point{Point::x_axis{0}, Point::y_axis{0}}),
                           p2_(Point{Point::x_axis{0}, Point::y_axis{0}}),
                           p3_(Point{Point::x_axis{0}, Point::y_axis{0}}) {}

    Triangle::Triangle(const Triangle &other) : Object(other),
                                                p1_(other.p1_),
                                                p2_(other.p2_),
                                                p3_(other.p3_) {}

    Triangle &Triangle::SetPoint1(detail::Point p1)
    {
        p1_ = p1;
        return *this;
    }
    Triangle &Triangle::SetPoint2(detail::Point p2)
    {
        p2_ = p2;
        return *this;
    }
    Triangle &Triangle::SetPoint3(detail::Point p3)
    {
        p3_ = p3;
        return *this;
    }

    detail::Point Triangle::GetPoint1() const
    {
        return p1_;
    }
    detail::Point Triangle::GetPoint2() const
    {
        return p2_;
    }
    detail::Point Triangle::GetPoint3() const
    {
        return p3_;
    }

    //=======================Square=======================

    Square::Square() : Object(ShapesTag::SQUARE),
                       p1_(Point{Point::x_axis{0}, Point::y_axis{0}}),
                    //    p2_(Point{Point::x_axis{0}, Point::y_axis{0}}),
                       size_(0) {}

    Square::Square(const Square &other) : Object(other),
                                          p1_(other.p1_),
                                        //   p2_(other.p2_),
                                          size_(other.size_) {}

    Square &Square::SetPoint1(detail::Point p1)
    {
        p1_ = p1;
        return *this;
    }
    // Square &Square::SetPoint2(detail::Point p2)
    // {
    //     p2_ = p2;
    //     return *this;
    // }

    Square& Square::SetSize(uint32_t size)
    {
        size_ = size;
        return *this;
    }

    detail::Point Square::GetPoint1() const
    {
        return p1_;
    }
    // detail::Point Square::GetPoint2() const
    // {
    //     return p2_;
    // }

    uint32_t Square::GetSize() const
    {
        return size_;
    }

    //=======================Quadrangle=======================

    Quadrangle::Quadrangle() : Object(ShapesTag::QUADRANGLE),
                               p1_(Point{Point::x_axis{0}, Point::y_axis{0}}),
                               p2_(Point{Point::x_axis{0}, Point::y_axis{0}}),
                               p3_(Point{Point::x_axis{0}, Point::y_axis{0}}),
                               p4_(Point{Point::x_axis{0}, Point::y_axis{0}}) {}

    Quadrangle::Quadrangle(const Quadrangle &other) : Object(other),
                                                      p1_(other.p1_),
                                                      p2_(other.p2_),
                                                      p3_(other.p3_),
                                                      p4_(other.p4_) {}

    Quadrangle &Quadrangle::SetPoint1(detail::Point p1)
    {
        p1_ = p1;
        return *this;
    }
    Quadrangle &Quadrangle::SetPoint2(detail::Point p2)
    {
        p2_ = p2;
        return *this;
    }
    Quadrangle &Quadrangle::SetPoint3(detail::Point p3)
    {
        p3_ = p3;
        return *this;
    }
    Quadrangle &Quadrangle::SetPoint4(detail::Point p4)
    {
        p4_ = p4;
        return *this;
    }

    detail::Point Quadrangle::GetPoint1() const
    {
        return p1_;
    }
    detail::Point Quadrangle::GetPoint2() const
    {
        return p2_;
    }
    detail::Point Quadrangle::GetPoint3() const
    {
        return p3_;
    }
    detail::Point Quadrangle::GetPoint4() const
    {
        return p4_;
    }

} // end namespace Shapes