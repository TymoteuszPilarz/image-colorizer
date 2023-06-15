//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include "Content.h"

Content::Content(int width, int height) : Wt::WPaintedWidget()
{
    Wt::WPaintedWidget::resize(width,height);

    mouseDragged().connect(this, &Content::mouseDrag);
    mouseWentDown().connect(this, &Content::mouseDown);
    touchStarted().connect(this, &Content::touchStart);
    touchMoved().connect(this, &Content::touchMove);
    touchMoved().preventDefaultAction();
    color_ = Wt::WColor(Wt::StandardColor::Black);
}

void Content::clear()
{
    update();
}

void Content::setColor(const Wt::WColor &c)
{
    color_ = c;
}

void Content::mouseDown(const Wt::WMouseEvent &e)
{
    Wt::Coordinates c = e.widget();
    path_ = Wt::WPainterPath(Wt::WPointF(c.x,c.y));
}

void Content::mouseDrag(const Wt::WMouseEvent &e)
{
    Wt::Coordinates c = e.widget();
    path_.lineTo(c.x,c.y);
    update(Wt::PaintFlag::Update);
}

void Content::touchStart(const Wt::WTouchEvent &e)
{
    Wt::Coordinates c = e.touches()[0].widget();
    path_ = Wt::WPainterPath(Wt::WPointF(c.x,c.y));

}

void Content::touchMove(const Wt::WTouchEvent &e)
{
    Wt::Coordinates c = e.touches()[0].widget();
    path_.lineTo(c.x,c.y);
    update(Wt::PaintFlag::Update);
}

void Content::paintEvent(Wt::WPaintDevice *paintDevice)
{
    Wt::WPainter painter(paintDevice);
    painter.setRenderHint(Wt::RenderHint::Antialiasing);

    Wt::WPen pen;
    pen.setWidth(3);
    pen.setColor(color_);
    pen.setCapStyle(Wt::PenCapStyle::Flat);
    pen.setJoinStyle(Wt::PenJoinStyle::Miter);
    painter.setPen(pen);
    painter.drawPath(path_);

    path_ = Wt::WPainterPath(path_.currentPosition());
}