#pragma once

#include "detail.h"

namespace Shapes
{
    class Object
    {
    public:
        virtual ~Object() = default;
        virtual detail::ShapesTag GetShapeType() const;

    protected:
        Object(detail::ShapesTag shape_type);
        Object(const Object& other);
    private:
        detail::ShapesTag shape_type_;
    }; // end class Object

    class Circle final: public Object
    {
    public:
        Circle();
        Circle(const Circle& other);
        Circle& SetCenter(detail::Point center);
        Circle& SetRadius(uint32_t radius);
        detail::Point GetCenter() const;
        
        uint32_t GetRadius() const;
        virtual ~Circle() = default;
    private:
        detail::Point center_;
        uint32_t radius_;
    }; // end class Circle

    class Ellipse final: public Object
    {
    public:
        Ellipse();
        Ellipse(const Ellipse& other);
        Ellipse& SetCenter(detail::Point center);
        Ellipse& SetRadiusX(uint32_t radiusX);
        Ellipse& SetRadiusY(uint32_t radiusY);
        detail::Point GetCenter() const;
        
        uint32_t GetRadiusX() const;
        uint32_t GetRadiusY() const;
        virtual ~Ellipse() = default;
    private:
        detail::Point center_;
        uint32_t radiusX_;
        uint32_t radiusY_;
    }; // end class Ellipse

    class Triangle final: public Object
    {
    public:
        Triangle();
        Triangle(const Triangle& other);
        Triangle& SetPoint1(detail::Point p1);
        Triangle& SetPoint2(detail::Point p2);
        Triangle& SetPoint3(detail::Point p3);

        detail::Point GetPoint1() const;
        detail::Point GetPoint2() const;
        detail::Point GetPoint3() const;
        virtual ~Triangle() = default;
    private:
        detail::Point p1_;
        detail::Point p2_;
        detail::Point p3_;
    }; // end class Triangle

    class Square final: public Object
    {
    public:
        Square();
        Square(const Square& other);
        Square& SetPoint1(detail::Point p1);
        // Square& SetPoint2(detail::Point p2);
        Square& SetSize(uint32_t size);

        detail::Point GetPoint1() const;
        // detail::Point GetPoint2() const;
        uint32_t GetSize() const;
        virtual ~Square() = default;
    private:
        detail::Point p1_;
        // detail::Point p2_;
        uint32_t size_;
    }; // end class Square

    class Quadrangle final: public Object
    {
    public:
        Quadrangle();
        Quadrangle(const Quadrangle& other);
        Quadrangle& SetPoint1(detail::Point p1);
        Quadrangle& SetPoint2(detail::Point p2);
        Quadrangle& SetPoint3(detail::Point p3);
        Quadrangle& SetPoint4(detail::Point p4);

        detail::Point GetPoint1() const;
        detail::Point GetPoint2() const;
        detail::Point GetPoint3() const;
        detail::Point GetPoint4() const;
        virtual ~Quadrangle() = default;
    private:
        detail::Point p1_;
        detail::Point p2_;
        detail::Point p3_;
        detail::Point p4_;
    }; // end class Quadrangle
} // end namespace Shapes