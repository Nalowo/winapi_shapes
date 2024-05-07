#include <stdexcept>
#include <iostream>
#include <memory>

#include "windef.h"
#include "detail.h"
#include "printer.h"
#include "win_printer.h"

class CmdParser
{
public:
    explicit CmdParser()
    {
        Init();
    }

    ~CmdParser()
    {
        delete[] argv_;
    }

    std::string GetArg()
    {
        return argv_;
    }

private:
    void Init()
    {
        LPWSTR *lpArgv = CommandLineToArgvW(GetCommandLineW(), &argc_);

        if (argc_ != 2)
        {
            throw std::invalid_argument("Invalid number of arguments");
        }

        argv_ = new char[wcslen(lpArgv[1]) + 1];
        wcstombs(argv_, lpArgv[1], wcslen(lpArgv[1]) + 1);

        LocalFree(lpArgv);
    }

    int argc_ = 0;
    char* argv_ = nullptr;
};

detail::ShapesTag GetShapeTypeFromCmdArg()
{
    CmdParser parser;
    return detail::ShapeTable{}.GetShapeType(parser.GetArg());
}

std::shared_ptr<Shapes::Object> ShapesFactory(detail::ShapesTag shapeType)
{
    std::shared_ptr<Shapes::Object> shape;

    if (shapeType == detail::ShapesTag::CIRCLE)
    {
        shape = std::make_shared<Shapes::Circle>();
        auto &circle = static_cast<Shapes::Circle &>(*shape);
        circle.SetCenter(detail::Point{detail::Point::x_axis{400}, detail::Point::y_axis{300}});
        circle.SetRadius(100);
    }
    else if (shapeType == detail::ShapesTag::ELLIPSE)
    {
        shape = std::make_shared<Shapes::Ellipse>();
        auto &ellipse = static_cast<Shapes::Ellipse &>(*shape);
        ellipse.SetCenter(detail::Point{detail::Point::x_axis{400}, detail::Point::y_axis{300}});
        ellipse.SetRadiusX(100);
        ellipse.SetRadiusY(50);
    }
    else if (shapeType == detail::ShapesTag::TRIANGLE)
    {
        shape = std::make_shared<Shapes::Triangle>();
        auto &triangle = static_cast<Shapes::Triangle &>(*shape);
        triangle.SetPoint1(detail::Point{detail::Point::x_axis{100}, detail::Point::y_axis{100}});
        triangle.SetPoint2(detail::Point{detail::Point::x_axis{200}, detail::Point::y_axis{100}});
        triangle.SetPoint3(detail::Point{detail::Point::x_axis{150}, detail::Point::y_axis{200}});
    }
    else if (shapeType == detail::ShapesTag::SQUARE)
    {
        shape = std::make_shared<Shapes::Square>();
        auto &square = static_cast<Shapes::Square &>(*shape);
        square.SetPoint1(detail::Point{detail::Point::x_axis{300}, detail::Point::y_axis{200}});
        square.SetSize(200);
    }
    else if (shapeType == detail::ShapesTag::QUADRANGLE)
    {
        shape = std::make_shared<Shapes::Quadrangle>();
        auto &quadrangle = static_cast<Shapes::Quadrangle &>(*shape);
        quadrangle.SetPoint1(detail::Point{detail::Point::x_axis{100}, detail::Point::y_axis{100}});
        quadrangle.SetPoint2(detail::Point{detail::Point::x_axis{200}, detail::Point::y_axis{200}});
        quadrangle.SetPoint3(detail::Point{detail::Point::x_axis{300}, detail::Point::y_axis{150}});
        quadrangle.SetPoint4(detail::Point{detail::Point::x_axis{250}, detail::Point::y_axis{100}});
    }
    else
    {
        throw std::invalid_argument("Invalid shape type");
    }

    return shape;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
    try
    {
        NS_Printer::Printer printer;
        printer.SetAdapter(std::make_unique<WinPrinter::WinAdaptImpl>(hInstance, nCmdShow));

        auto shapeType = GetShapeTypeFromCmdArg();
        std::shared_ptr<Shapes::Object> shape = ShapesFactory(shapeType);

        printer.AddObjToPrint(shape);
        printer.Print();
    }
    catch (const std::exception &e)
    {
        std::cout << e.what() << std::endl;
        return 1;
    }

    return 0;
}