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
}

ImagePainter::ImagePainter()
{
    setLayoutSizeAware(true);
    //Canvas(image->height(),image->width());
}

void ImagePainter::setImage(Wt::WPainter::Image* image)
{
    buffer.clear();
    this->image = image;
}

int ImagePainter::gerWidth()
{
    return image->width();
}
int ImagePainter::getHeight()
{
    return image->height();
}
