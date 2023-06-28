//
// Created by Tymoteusz Pilarz on 24/06/2023.
//

#ifndef IMAGECOLORIZATION_IMAGEPAINTER_H
#define IMAGECOLORIZATION_IMAGEPAINTER_H

#include <memory>
#include <vector>

#include <Wt/WBrush.h>
#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPaintDevice.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainter.h>
#include <Wt/WPainterPath.h>

class ImagePainter : public Wt::WPaintedWidget
{
private:
    struct BufferElement
    {
        Wt::WPen pen;
        Wt::WPainterPath painterPath;
        int currentWidth;
        int currentHeight;
    };
    std::vector<BufferElement> buffer;

    Wt::WPainter::Image* image = nullptr;

    Wt::WPainterPath painterPath;
    Wt::WPen pen;

    bool repaintRequired = true;

    void mouseDown(const Wt::WMouseEvent& e);
    void mouseDrag(const Wt::WMouseEvent& e);

protected:
    void paintEvent(Wt::WPaintDevice* paintDevice) override;

public:
    ImagePainter();

    void resize(const Wt::WLength& width, const Wt::WLength& height) override;
    void setImage(Wt::WPainter::Image* image);
    void setPenColor(const Wt::WColor& color);
    void setPenWidth(int width);
    void undo();
    void clear();
};


#endif //IMAGECOLORIZATION_IMAGEPAINTER_H
