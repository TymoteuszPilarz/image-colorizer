//
// Created by Tymoteusz Pilarz on 24/06/2023.
//

#include <fstream>

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
#include <Wt/WRasterImage.h>

#include "ImagePainter.h"

using namespace Wt;

void ImagePainter::mouseDown(const Wt::WMouseEvent& e)
{
    if (image == nullptr)
    {
        return;
    }

    Wt::Coordinates c = e.widget();
    buffer.push_back({pen, WPainterPath(Wt::WPointF(c.x, c.y)), static_cast<int>(WWebWidget::width().toPixels()), static_cast<int>(WWebWidget::height().toPixels())});
    painterPath = WPainterPath(Wt::WPointF(c.x, c.y));
}

void ImagePainter::mouseDrag(const Wt::WMouseEvent& e)
{
    if (image == nullptr)
    {
        return;
    }

    Wt::Coordinates c = e.widget();
    buffer.back().painterPath.lineTo(c.x, c.y);
    painterPath.lineTo(c.x, c.y);

    update(PaintFlag::Update);
}

void ImagePainter::paintEvent(WPaintDevice* paintDevice)
{
    if (image == nullptr)
    {
        return;
    }

    WPainter painter(paintDevice);
    painter.setRenderHint(RenderHint::Antialiasing);

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
        painter.setPen(pen);

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
    if (!buffer.empty())
    {
        buffer.pop_back();
        repaintRequired = true;
        update();
    }
}

void ImagePainter::clearCanvas()
{
    buffer.clear();
    repaintRequired = true;
    update();
}

void ImagePainter::saveToPNG(const std::string& filename)
{
    if (image == nullptr)
    {
        return;
    }

    WRasterImage pngImage("png", image->width(), image->height());

    WPainter painter(&pngImage);
    painter.setRenderHint(RenderHint::Antialiasing);

    painter.drawImage(WRectF(0.0, 0.0, image->width(), image->height()), *image);

    for (auto& element : buffer)
    {
        painter.save();
        painter.setPen(element.pen);
        painter.scale(static_cast<double>(image->width()) / element.currentWidth, static_cast<double>(image->height()) / element.currentHeight);
        painter.drawPath(element.painterPath);
        painter.restore();
    }

    std::ofstream file(filename, std::ios::out | std::ios::binary);
    pngImage.write(file);
}
