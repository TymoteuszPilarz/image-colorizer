//
// Created by dedboi on 15.06.23.
//

#include "Canvas.h"

Canvas::Canvas(int w, int h) : Wt::WPaintedWidget()
{
    Wt::WPaintedWidget::resize(w,h);

    mouseDragged().connect(this, &Canvas::mouseDrag);
    mouseWentDown().connect(this, &Canvas::mouseDown);
    touchStarted().connect(this, &Canvas::touchStart);
    touchMoved().connect(this, &Canvas::touchMove);

    color_ = Wt::WColor(Wt::StandardColor::Black);


}

void Canvas::clear()
{
    update();
}

void Canvas::setColor(const Wt::WColor &c)
{
    color_ = c;
}

void Canvas::paintEvent(Wt::WPaintDevice *paintDevice)
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

void Canvas::mouseDown(const Wt::WMouseEvent& e)
{
    Wt::Coordinates c = e.widget();
    path_ = Wt::WPainterPath(Wt::WPointF(c.x, c.y));
}

void Canvas::mouseDrag(const Wt::WMouseEvent& e)
{
    Wt::Coordinates c = e.widget();
    path_.lineTo(c.x,c.y);
    update(Wt::PaintFlag::Update);
}
void Canvas::touchStart(const Wt::WTouchEvent& e)
{
    Wt::Coordinates c = e.touches()[0].widget();
    path_ = Wt::WPainterPath(Wt::WPointF(c.x,c.y));

}
void Canvas::touchMove(const Wt::WTouchEvent& e)
{
    Wt::Coordinates c = e.touches()[0].widget();
    path_.lineTo(c.x,c.y);
    update(Wt::PaintFlag::Update);
}