//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include <memory>

#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>
#include <opencv2/highgui.hpp>

#include "Content.h"
#include "Colorize.h"

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

    setImage("in/image.jpg");
    imagePainter->setPenColor(StandardColor::Red);
    imagePainter->setImage(image.get());
}

void Content::setImage(const std::string& fileName)
{
    image = std::make_unique<WPainter::Image>(fileName, fileName);
    imagePainter->setImage(image.get());
}

void Content::setPenColor(const Wt::WColor& color)
{
    imagePainter->setPenColor(color);
}

void Content::setPenWidth(int width)
{
    imagePainter->setPenWidth(width);
}

void Content::undo()
{
    imagePainter->undo();
}

void Content::clearCanvas()
{
    imagePainter->clearCanvas();
}

void Content::setGamma(double gamma)
{
    this->gamma = gamma;
}

void Content::setThreshold(int threshold)
{
    this->threshold = threshold;
}

void Content::colorize()
{
    try
    {
        imagePainter->saveToPNG();

        auto imageFile = "in/image.png";
        auto scribblesFile = "out/scribbles.png";

        auto image = cv::imread(imageFile);
        auto scribbles = cv::imread(scribblesFile);
        auto mask = co::getScribbleMask(image, scribbles, threshold);
        auto colorImage = co::colorize(image, scribbles, mask, gamma);

        cv::imwrite("out/out.png", colorImage);
    }
    catch (const std::runtime_error& e)
    {
        log("error") << e.what();
    }
}

void Content::downloadPNG()
{
}