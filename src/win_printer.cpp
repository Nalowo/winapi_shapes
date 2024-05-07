#include <stdexcept>

#include "win_printer.h"

namespace WinPrinter
{
    std::unique_ptr<ShapeAdapter> MakeShapeAdapter(std::shared_ptr<const Shapes::Object> shape)
    {
        switch (shape->GetShapeType())
        {
        case detail::ShapesTag::CIRCLE:
            return std::make_unique<AdaptCircle>(shape);
            break;
        case detail::ShapesTag::ELLIPSE:
            return std::make_unique<AdaptEllipse>(shape);
            break;
        case detail::ShapesTag::TRIANGLE:
            return std::make_unique<AdaptTriangle>(shape);
            break;
        case detail::ShapesTag::SQUARE:
            return std::make_unique<AdaptSquare>(shape);
            break;
        case detail::ShapesTag::QUADRANGLE:
            return std::make_unique<AdaptQuadrangle>(shape);
            break;
        default:
            throw std::runtime_error("Unknown shape type");
            break;
        }

        return nullptr;
    }

    LRESULT CALLBACK WinAdaptImpl::WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        ShapeAdapter *pWindow = reinterpret_cast<ShapeAdapter *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
        if (pWindow)
        {
            return pWindow->HandleShape(hwnd, uMsg, wParam, lParam);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }
    }

    WinAdaptImpl::WinAdaptImpl(HINSTANCE hInstance, int nCmdShow) : hInstance_(hInstance), nCmdShow_(nCmdShow) {}

    void WinAdaptImpl::Print(std::shared_ptr<const Shapes::Object> shape)
    {
        InitWindow();

        auto shape_adapter = MakeShapeAdapter(shape);

        SetWindowLongPtr(hwnd_, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(shape_adapter.get()));

        ShowWindow(hwnd_, nCmdShow_);

        MSG msg;
        while (GetMessage(&msg, nullptr, 0, 0))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    void WinAdaptImpl::InitWindow()
    {
        ZeroMemory(&wc_, sizeof(WNDCLASSEX));
        wc_.cbSize = sizeof(WNDCLASSEX);
        wc_.style = CS_HREDRAW | CS_VREDRAW;
        wc_.lpfnWndProc = WinAdaptImpl::WindowProc;
        wc_.hInstance = hInstance_;
        wc_.hCursor = LoadCursor(nullptr, IDC_ARROW);
        wc_.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc_.lpszClassName = L"WindowClass";

        RegisterClassEx(&wc_);

        hwnd_ = CreateWindowEx(0,
                               L"WindowClass",
                               L"WinAPI Фигуры",
                               WS_OVERLAPPEDWINDOW,
                               300,
                               300,
                               800,
                               600,
                               nullptr,
                               nullptr,
                               hInstance_,
                               nullptr);
    }

    ShapeAdapter::ShapeAdapter(std::shared_ptr<const Shapes::Object> obj) : shape_(obj) {}

    //=======================AdaptShaps========================
    AdaptCircle::AdaptCircle(std::shared_ptr<const Shapes::Object> obj) : ShapeAdapter(obj) {}

    void AdaptCircle::DrawCircle(HDC hdc, int x, int y, int radius) const
    {
        Ellipse(hdc, x - radius, y - radius, x + radius, y + radius);
    }

    LRESULT AdaptCircle::HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const
    {
        if (uMsg == WM_PAINT)
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Рисование круга
            const auto &circle = static_cast<const Shapes::Circle &>(*shape_);
            DrawCircle(hdc, *circle.GetCenter().x_, *circle.GetCenter().y_, circle.GetRadius());

            EndPaint(hwnd, &ps);
        }
        else if (uMsg == WM_DESTROY)
        {
            PostQuitMessage(0);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    //===============AdaptSquare=======================================
    AdaptSquare::AdaptSquare(std::shared_ptr<const Shapes::Object> obj) : ShapeAdapter(obj) {}

    void AdaptSquare::DrawSquare(HDC hdc, int x, int y, int size) const
    {
        Rectangle(hdc, x, y, x + size, y + size);
    }

    LRESULT AdaptSquare::HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const
    {
        if (uMsg == WM_PAINT)
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Рисование квадрата
            const auto &square = static_cast<const Shapes::Square &>(*shape_);
            DrawSquare(hdc, *square.GetPoint1().x_, *square.GetPoint1().y_, square.GetSize());

            EndPaint(hwnd, &ps);
        }
        else if (uMsg == WM_DESTROY)
        {
            PostQuitMessage(0);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    //===============AdaptEllipse=======================================
    AdaptEllipse::AdaptEllipse(std::shared_ptr<const Shapes::Object> obj) : ShapeAdapter(obj) {}

    void AdaptEllipse::DrawEllipse(HDC hdc, int x1, int y1, int x2, int y2) const
    {
        Ellipse(hdc, x1, y1, x2, y2);
    }

    LRESULT AdaptEllipse::HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const
    {
        if (uMsg == WM_PAINT)
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Рисование эллипса
            auto &ellipse = static_cast<const Shapes::Ellipse &>(*shape_);
            DrawEllipse(hdc,
                        *ellipse.GetCenter().x_ - ellipse.GetRadiusX(),
                        *ellipse.GetCenter().y_ - ellipse.GetRadiusY(),
                        *ellipse.GetCenter().x_ + ellipse.GetRadiusX(),
                        *ellipse.GetCenter().y_ + ellipse.GetRadiusY());

            EndPaint(hwnd, &ps);
        }
        else if (uMsg == WM_DESTROY)
        {
            PostQuitMessage(0);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    //===============AdaptTriangle=======================================
    AdaptTriangle::AdaptTriangle(std::shared_ptr<const Shapes::Object> obj) : ShapeAdapter(obj) {}

    void AdaptTriangle::DrawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3) const
    {
        POINT points[] = {{x1, y1}, {x2, y2}, {x3, y3}};
        Polygon(hdc, points, sizeof(points) / sizeof(POINT));
    }

    LRESULT AdaptTriangle::HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const
    {
        if (uMsg == WM_PAINT)
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Рисование треугольника
            const auto &triangle = static_cast<const Shapes::Triangle &>(*shape_);
            DrawTriangle(hdc,
                         *triangle.GetPoint1().x_, *triangle.GetPoint1().y_,
                         *triangle.GetPoint2().x_, *triangle.GetPoint2().y_,
                         *triangle.GetPoint3().x_, *triangle.GetPoint3().y_);

            EndPaint(hwnd, &ps);
        }
        else if (uMsg == WM_DESTROY)
        {
            PostQuitMessage(0);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return 0;
    }

    //===============AdaptQuadrangle=======================================
    AdaptQuadrangle::AdaptQuadrangle(std::shared_ptr<const Shapes::Object> obj) : ShapeAdapter(obj) {}

    void AdaptQuadrangle::DrawQuadrangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const
    {
        POINT points[] = {{x1, y1}, {x2, y2}, {x3, y3}, {x4, y4}};
        Polygon(hdc, points, sizeof(points) / sizeof(POINT));
    }

    LRESULT AdaptQuadrangle::HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const
    {
        if (uMsg == WM_PAINT)
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hwnd, &ps);

            // Рисование четырёхугольника
            const auto &quadrangle = static_cast<const Shapes::Quadrangle &>(*shape_);
            DrawQuadrangle(hdc,
                           *quadrangle.GetPoint1().x_, *quadrangle.GetPoint1().y_,
                           *quadrangle.GetPoint2().x_, *quadrangle.GetPoint2().y_,
                           *quadrangle.GetPoint3().x_, *quadrangle.GetPoint3().y_,
                           *quadrangle.GetPoint4().x_, *quadrangle.GetPoint4().y_);

            EndPaint(hwnd, &ps);
        }
        else if (uMsg == WM_DESTROY)
        {
            PostQuitMessage(0);
        }
        else
        {
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
        }

        return 0;
    }
} // end namespace WinPrinter