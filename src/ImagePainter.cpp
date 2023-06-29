//
// Created by Tymoteusz Pilarz on 24/06/2023.
//

#include <Wt/WRectF.h>

#include "ImagePainter.h"

using namespace Wt;

void ImagePainter::paintEvent(WPaintDevice* paintDevice)
{
    Wt::WPainter painter(paintDevice);


    painter.drawImage(WRectF(0.0, 0.0, WWebWidget::width().toPixels(), WWebWidget::height().toPixels()), *image);

    painter.setRenderHint(Wt::RenderHint::Antialiasing);
    Wt::WPen pen;
    pen.setWidth(3);
    pen.setColor(color_);
    pen.setCapStyle(Wt::PenCapStyle::Flat);
    pen.setJoinStyle(Wt::PenJoinStyle::Miter);
    painter.setPen(pen);
    painter.drawPath(path_);

    //path_ = Wt::WPainterPath(path_.currentPosition());
    //ehhhh

    mouseDragged().connect(this, &ImagePainter::mouseDrag);
    mouseWentDown().connect(this, &ImagePainter::mouseDown);
    touchStarted().connect(this, &ImagePainter::touchStart);
    touchMoved().connect(this, &ImagePainter::touchMove);




}

ImagePainter::ImagePainter()
{
    setLayoutSizeAware(true);
    //Wt::WPaintedWidget::resize(image->width(),image->height());
    color_ = Wt::WColor(Wt::StandardColor::Black);

}

void ImagePainter::setImage(Wt::WPainter::Image* image)
{
    buffer.clear();
    this->image = image;
}

void ImagePainter::mouseDown(const Wt::WMouseEvent& e)
{
    Wt::Coordinates c = e.widget();
    path_ = Wt::WPainterPath(Wt::WPointF(c.x, c.y));
}

void ImagePainter::mouseDrag(const Wt::WMouseEvent& e)
{
    Wt::Coordinates c = e.widget();
    path_.lineTo(c.x,c.y);
    update(Wt::PaintFlag::Update);
}
void ImagePainter::touchStart(const Wt::WTouchEvent& e)
{
    Wt::Coordinates c = e.touches()[0].widget();
    path_ = Wt::WPainterPath(Wt::WPointF(c.x,c.y));

}
void ImagePainter::touchMove(const Wt::WTouchEvent& e)
{
    Wt::Coordinates c = e.touches()[0].widget();
    path_.lineTo(c.x,c.y);
    update(Wt::PaintFlag::Update);
}

void ImagePainter::clear()
{
    update();
}

void ImagePainter::setColor(const Wt::WColor &c)
{
    color_ = c;
}
