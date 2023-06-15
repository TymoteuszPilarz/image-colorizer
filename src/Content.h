
//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#ifndef IMAGECOLORIZATION_CONTENT_H
#define IMAGECOLORIZATION_CONTENT_H

#include <Wt/WContainerWidget.h>
#include <Wt/WPaintedWidget.h>

class Content : public Wt::WPaintedWidget
{
public:
    Content(int width, int height) : Wt::WPaintedWidget(){};

    void clear(){ update();}

    void setColor(const Wt::WColor& c);

protected:
    virtual void paintEvent(Wt::WPaintDevice *paintDevice);

private:
    Wt::WPainterPath path_;
    Wt::WColor color_;

    void mouseDown(const Wt::WMouseEvent& e);
    void mouseDrag(const Wt::WMouseEvent& e);
    void touchStart(const Wt::WTouchEvent& e);
    void touchMove(const Wt::WTouchEvent& e);
};


#endif //IMAGECOLORIZATION_CONTENT_H
