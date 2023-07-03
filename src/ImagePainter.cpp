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
    if (!isImageSet() || action == Action::result)
    {
        return;
    }

    Wt::Coordinates c = e.widget();
    buffer.push_back({pen, WPainterPath(Wt::WPointF(c.x, c.y)), static_cast<int>(WWebWidget::width().toPixels()), static_cast<int>(WWebWidget::height().toPixels())});
    painterPath = WPainterPath(Wt::WPointF(c.x, c.y));
}

void ImagePainter::mouseDrag(const Wt::WMouseEvent& e)
{
    if (!isImageSet() || action == Action::result || buffer.empty())
    {
        return;
    }

    Wt::Coordinates c = e.widget();

    buffer.back().painterPath.lineTo(c.x, c.y);
    redoBuffer.clear();
    painterPath.lineTo(c.x, c.y);

    update(PaintFlag::Update);
}

void ImagePainter::paintEvent(WPaintDevice* paintDevice)
{
    if (!isImageSet())
    {
        return;
    }

    WPainter painter(paintDevice);
    painter.setRenderHint(RenderHint::Antialiasing);

    if (action == Action::result)
    {
        painter.drawImage(WRectF(0.0, 0.0, WWebWidget::width().toPixels(), WWebWidget::height().toPixels()), *resultImage);
    }
    else if (action == Action::update)
    {
        painter.setPen(pen);

        painter.drawPath(painterPath);
        painterPath = painterPath.currentPosition();
    }
    else if (action == Action::repaint)
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

        action = Action::update;
    }

    painter.end();
}

ImagePainter::ImagePainter()
{
    mouseDragged().connect(this, &ImagePainter::mouseDrag);
    mouseWentDown().connect(this, &ImagePainter::mouseDown);

    pen.setWidth(3);
    pen.setColor(StandardColor::Red);
    pen.setCapStyle(Wt::PenCapStyle::Round);
    pen.setJoinStyle(Wt::PenJoinStyle::Miter);
}

void ImagePainter::resize(const Wt::WLength& width, const Wt::WLength& height)
{
    if (width != WWebWidget::width() || height != WWebWidget::height())
    {
        if (action != Action::result)
        {
            action = Action::repaint;
        }
        WPaintedWidget::resize(width, height);
    }
}

void ImagePainter::setImage(std::unique_ptr<WPainter::Image> image)
{
    buffer.clear();
    redoBuffer.clear();
    this->image = std::move(image);
    action = Action::repaint;
    update();
}

bool ImagePainter::isImageSet() const
{
    return image != nullptr;
}

int ImagePainter::getImageWidth() const
{
    if (isImageSet())
    {
        return image->width();
    }

    return 0;
}

int ImagePainter::getImageHeight() const
{
    if (isImageSet())
    {
        return image->height();
    }

    return 0;
}

std::string ImagePainter::getImageFileName() const
{
    if (isImageSet())
    {
        return image->uri();
    }

    return "";
}

void ImagePainter::setPenColor(const WColor& color)
{
    pen.setColor(color);
}

void ImagePainter::setPenWidth(int width)
{
    pen.setWidth(width);
}

void ImagePainter::undo()
{
    if (buffer.empty() || action == Action::result)
    {
        return;
    }

    redoBuffer.push_back(buffer.back());
    buffer.pop_back();
    action = Action::repaint;
    update();
}

void ImagePainter::redo()
{
    if (redoBuffer.empty() || action == Action::result)
    {
        return;
    }

    buffer.push_back(redoBuffer.back());
    redoBuffer.pop_back();
    action = Action::repaint;
    update();
}

void ImagePainter::clearCanvas()
{
    if (action == Action::result)
    {
        return;
    }

    buffer.clear();
    redoBuffer.clear();
    action = Action::repaint;
    update();
}

void ImagePainter::saveScribblesToPNG(const std::string& fileName)
{
    if (!isImageSet())
    {
        return;
    }

    WRasterImage pngScribbles("png", image->width(), image->height());
    {
        WPainter painter(&pngScribbles);
        painter.setRenderHint(RenderHint::Antialiasing);

        painter.drawImage(WRectF(0.0, 0.0, image->width(), image->height()), *image);

        for (auto& element: buffer)
        {
            painter.save();

            auto scaledPen = element.pen;
            scaledPen.setWidth(scaledPen.width().toPixels() / (static_cast<double>(image->width()) / element.currentWidth));

            painter.setPen(scaledPen);
            painter.scale(static_cast<double>(image->width()) / element.currentWidth,
                          static_cast<double>(image->height()) / element.currentHeight);

            painter.drawPath(element.painterPath);

            painter.restore();
        }
    }

    std::ofstream scribblesFile(fileName, std::ios::out | std::ios::binary);
    pngScribbles.write(scribblesFile);
}

void ImagePainter::showResult(std::unique_ptr<Wt::WPainter::Image> image)
{
    resultImage = std::move(image);
    action = Action::result;
    update();
}

void ImagePainter::hideResult()
{
    resultImage.reset();
    action = Action::repaint;
    update();
}