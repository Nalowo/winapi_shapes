#pragma once

#include <unordered_map>
#include <memory>

#include "windef.h"
#include "detail.h"
#include "adapters.h"
#include "shapes.h"

namespace WinPrinter
{
    class ShapeAdapter
    {
    public:
        virtual LRESULT HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const = 0;
        virtual ~ShapeAdapter() = default;

    protected:
        ShapeAdapter(std::shared_ptr<const Shapes::Object> obj);
        std::shared_ptr<const Shapes::Object> shape_;
    }; // end class ShapeAdapter

    class WinAdaptImpl final : public NS_Printer::Adapter
    {
    public:
        WinAdaptImpl(HINSTANCE hInstance, int nCmdShow);
        virtual ~WinAdaptImpl() = default;

        void Print(std::shared_ptr<const Shapes::Object> shape) override;

    private:
        void InitWindow();
        static LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

        HINSTANCE hInstance_;
        HWND hwnd_;
        WNDCLASSEX wc_;
        int nCmdShow_;
    }; // end class WinAdaptImpl

    class AdaptCircle final : public ShapeAdapter
    {
    public:
        AdaptCircle(std::shared_ptr<const Shapes::Object> obj);
        LRESULT HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const override;
        virtual ~AdaptCircle() = default;

    private:
        void DrawCircle(HDC hdc, int x, int y, int radius) const;
    }; // end class AdaptCircle

    class AdaptSquare final : public ShapeAdapter
    {
    public:
        AdaptSquare(std::shared_ptr<const Shapes::Object> obj);
        LRESULT HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const override;
        virtual ~AdaptSquare() = default;

    private:
        void DrawSquare(HDC hdc, int x, int y, int size) const;
    }; // end class AdaptSquare

    class AdaptEllipse final : public ShapeAdapter
    {
    public:
        AdaptEllipse(std::shared_ptr<const Shapes::Object> obj);
        LRESULT HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const override;
        virtual ~AdaptEllipse() = default;

    private:
        void DrawEllipse(HDC hdc, int x1, int y1, int x2, int y2) const;
    }; // end class AdaptEllipse

    class AdaptTriangle final : public ShapeAdapter
    {
    public:
        AdaptTriangle(std::shared_ptr<const Shapes::Object> obj);
        LRESULT HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const override;
        virtual ~AdaptTriangle() = default;

    private:
        void DrawTriangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3) const;
    }; // end class AdaptTriangle

    class AdaptQuadrangle final : public ShapeAdapter
    {
    public:
        AdaptQuadrangle(std::shared_ptr<const Shapes::Object> obj);
        LRESULT HandleShape(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) const override;
        virtual ~AdaptQuadrangle() = default;

    private:
        void DrawQuadrangle(HDC hdc, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) const;
    }; // end class AdaptQuadrangle

} // end namespace WinPrinter