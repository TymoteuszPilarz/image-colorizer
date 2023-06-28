//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include <memory>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>

#include "Content.h"

using namespace Wt;

std::tuple<int, int> Content::getScaledSize(int sourceWidth, int sourceHeight, int destinationWidth, int destinationHeight)
{
    auto widthRatio = static_cast<double>(destinationWidth) / sourceWidth;
    auto heightRatio = static_cast<double>(destinationHeight) / sourceHeight;

    auto scaleRatio = (widthRatio < heightRatio) ? widthRatio : heightRatio;

    auto width = static_cast<int>(sourceWidth * scaleRatio);
    auto height = static_cast<int>(sourceHeight * scaleRatio);

    return {width, height};
}

void Content::layoutSizeChanged(int width, int height)
{
    auto [imagePainterWidth, imagePainterHeight] = getScaledSize(image->width(), image->height(), width, height);

    imagePainter->resize(imagePainterWidth, imagePainterHeight);

    WWidget::layoutSizeChanged(width, height);
}

Content::Content()
{
    setStyleClass("content");
    setLayoutSizeAware(true);
    setContentAlignment(AlignmentFlag::Center);
    WWebWidget::setMargin(0);

    imagePainter = addWidget(std::make_unique<ImagePainter>());
    imagePainter->setPenColor(StandardColor::Red);

    setImage("res/image.jpg");
}

void Content::setImage(const std::string& fileName)
{
    image = std::make_unique<WPainter::Image>(fileName, fileName);
    imagePainter->setImage(image.get());
}