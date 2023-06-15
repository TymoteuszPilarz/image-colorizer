//
// Created by dedboi on 15.06.23.
//

#ifndef IMAGECOLORIZATION_CANVAS_H
#define IMAGECOLORIZATION_CANVAS_H

#include <Wt/WCssDecorationStyle.h>
#include <Wt/WColor.h>
#include <Wt/WContainerWidget.h>
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


class Canvas : public Wt::WPaintedWidget
{
public:
    Canvas(int w, int h);
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

namespace {


    Wt::WPushButton *createColorToggle(const char *className, const Wt::WColor& color,
                                       Canvas *canvas)
    {
        auto button = new Wt::WPushButton();
        button->setTextFormat(Wt::TextFormat::XHTML);
        button->setText("&nbsp;");
        button->setCheckable(true);
        button->addStyleClass(className);
        button->setWidth(30);
        button->checked().connect([=] {
            canvas->setColor(color);
        });

        return button;
    }

}

const Wt::WColor blue("#0d6efd");                              // btn-primary
const Wt::WColor red("#dc3545");                               // btn-danger
const Wt::WColor green("#198754");                             // btn-success
const Wt::WColor yellow("#ffc107");                            // btn-warning
const Wt::WColor black = Wt::WColor(Wt::StandardColor::Black); // btn-inverse
const Wt::WColor gray("#6c757d");

#endif //IMAGECOLORIZATION_CANVAS_H
