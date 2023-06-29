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
#include "Canvas.h"

class ImagePainter : public Wt::WPaintedWidget
{


private:
    struct BufferElement
    {
        Wt::WPainter painter;
        Wt::WPainterPath painterPath;
    };
    std::vector<BufferElement> buffer;

    Wt::WPainter::Image* image;

    Wt::WPainterPath path_;
    Wt::WColor color_;

    void mouseDown(const Wt::WMouseEvent& e);
    void mouseDrag(const Wt::WMouseEvent& e);
    void touchStart(const Wt::WTouchEvent& e);
    void touchMove(const Wt::WTouchEvent& e);

protected:
    void paintEvent(Wt::WPaintDevice* paintDevice) override;

public:
    ImagePainter();

    void setImage(Wt::WPainter::Image* image);

    void clear();
    void setColor(const Wt::WColor& c);








};


#endif //IMAGECOLORIZATION_IMAGEPAINTER_H
