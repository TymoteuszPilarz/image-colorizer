//
// Created by Tymoteusz Pilarz on 24/06/2023.
//

#include <Wt/WRectF.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WEvent.h>
#include <Wt/WPainter.h>
#include <Wt/WPainterPath.h>
#include <Wt/WPen.h>
#include <Wt/WPointF.h>
#include <Wt/WPushButton.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WToolBar.h>

#include "ImagePainter.h"

using namespace Wt;

void ImagePainter::mouseDown(const Wt::WMouseEvent& e)
{
    Wt::Coordinates c = e.widget();
    buffer.push_back({pen, WPainterPath(Wt::WPointF(c.x, c.y)), static_cast<int>(WWebWidget::width().toPixels()), static_cast<int>(WWebWidget::height().toPixels())});
    painterPath = WPainterPath(Wt::WPointF(c.x, c.y));
}

void ImagePainter::mouseDrag(const Wt::WMouseEvent& e)
{
    Wt::Coordinates c = e.widget();
    buffer.back().painterPath.lineTo(c.x, c.y);
    painterPath.lineTo(c.x, c.y);

    update(PaintFlag::Update);
}

void ImagePainter::paintEvent(WPaintDevice* paintDevice)
{
    WPainter painter(paintDevice);
    painter.setRenderHint(RenderHint::Antialiasing);
    painter.setPen(pen);

    if (repaintRequired)
    {
        painter.drawImage(WRectF(0.0, 0.0, WWebWidget::width().toPixels(), WWebWidget::height().toPixels()), *image);

        for (auto& element : buffer)
        {
            painter.save();
            painter.setPen(element.pen);
            painter.scale(WWebWidget::width().toPixels() / element.currentWidth, WWebWidget::height().toPixels() / element.currentHeight);
            painter.drawPath(element.painterPath);
            painter.restore();
        }

        repaintRequired = false;
    }
    else
    {
        painter.drawPath(painterPath);
        painterPath = painterPath.currentPosition();
    }

    painter.end();
}

ImagePainter::ImagePainter()
{
    mouseDragged().connect(this, &ImagePainter::mouseDrag);
    mouseWentDown().connect(this, &ImagePainter::mouseDown);

    pen.setWidth(3);
    pen.setColor(StandardColor::Black);
    pen.setCapStyle(Wt::PenCapStyle::Round);
    pen.setJoinStyle(Wt::PenJoinStyle::Miter);
}

void ImagePainter::resize(const Wt::WLength& width, const Wt::WLength& height)
{
    if (width != WWebWidget::width() || height != WWebWidget::height())
    {
        repaintRequired = true;
        WPaintedWidget::resize(width, height);
    }
}

void ImagePainter::setImage(Wt::WPainter::Image* image)
{
    buffer.clear();
    this->image = image;
}

void ImagePainter::setPenColor(const Wt::WColor& color)
{
    pen.setColor(color);
}

void ImagePainter::setPenWidth(int width)
{
    pen.setWidth(width);
}

void ImagePainter::undo()
{
    buffer.pop_back();
    repaintRequired = true;
    update();
}

void ImagePainter::clear()
{
    buffer.clear();
}