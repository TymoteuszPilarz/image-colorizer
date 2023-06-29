//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#ifndef IMAGECOLORIZATION_CONTENT_H
#define IMAGECOLORIZATION_CONTENT_H

#include <tuple>

#include <Wt/WContainerWidget.h>

#include "ImagePainter.h"

class Content : public Wt::WContainerWidget
{
private:
    ImagePainter* imagePainter;
    std::unique_ptr<Wt::WPainter::Image> image;

    double gamma = 2.0;
    int threshold = 10;

    static std::tuple<int, int> getScaledSize(int sourceWidth, int sourceHeight, int destinationWidth, int destinationHeight);

protected:
    void layoutSizeChanged(int width, int height) override;

public:
    Content();

    void setImage(const std::string& fileName);
    void setPenColor(const Wt::WColor& color);
    void setPenWidth(int width);
    void undo();
    void clearCanvas();

    void setGamma(double gamma);
    void setThreshold(int threshold);
    void colorize();

    void downloadPNG();
};


#endif //IMAGECOLORIZATION_CONTENT_H
