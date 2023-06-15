
//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#ifndef IMAGECOLORIZATION_CONTENT_H
#define IMAGECOLORIZATION_CONTENT_H

#include <Wt/WContainerWidget.h>
#include <Wt/WCssDecorationStyle.h>
#include <Wt/WColor.h>
#include <Wt/WEvent.h>
#include <Wt/WPainter.h>
#include <Wt/WPaintedWidget.h>
#include <Wt/WPainterPath.h>
#include <Wt/WPen.h>
#include <Wt/WPointF.h>
#include <Wt/WPushButton.h>
#include <Wt/WRectF.h>
#include <Wt/WTemplate.h>
#include <Wt/WText.h>
#include <Wt/WToolBar.h>


class Content : Wt::WPaintedWidget
{
public:
    Content(int width, int height);

    void clear();

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
