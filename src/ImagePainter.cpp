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

void ImagePainter::configurePainter()
{
    Wt::WPen pen;
    pen.setWidth(3);
    pen.setCapStyle(Wt::PenCapStyle::Flat);
    pen.setJoinStyle(Wt::PenJoinStyle::Miter);
    pen.setColor(StandardColor::Red);
    painter.setRenderHint(Wt::RenderHint::Antialiasing);
    painter.setPen(pen);
}

void ImagePainter::mouseDown(const Wt::WMouseEvent& e)
{
    Wt::Coordinates c = e.widget();
    buffer.push_back({painter.pen(), WPainterPath(Wt::WPointF(c.x, c.y))});

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
    log("info") << "paint";
    painter.begin(paintDevice);
    configurePainter();

    if (repaintRequired)
    {
        painter.drawImage(WRectF(0.0, 0.0, WWebWidget::width().toPixels(), WWebWidget::height().toPixels()), *image);

        WPen pen = painter.pen();

        for (auto& element : buffer)
        {
            painter.setPen(element.pen);
            painter.drawPath(element.painterPath);
        }

        painter.setPen(pen);

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
}

void ImagePainter::resize(const Wt::WLength& width, const Wt::WLength& height)
{
    if (width != WWebWidget::width() || height != WWebWidget::height())
    {
        log("info") << "resize";
        repaintRequired = true;
        WPaintedWidget::resize(width, height);
    }
}

void ImagePainter::setImage(Wt::WPainter::Image* image)
{
    buffer.clear();
    this->image = image;
}

void ImagePainter::setColor(const Wt::WColor& color)
{
    WPen pen = painter.pen();
    pen.setColor(color);
    painter.setPen(pen);
}

void ImagePainter::clear()
{
    buffer.clear();
}