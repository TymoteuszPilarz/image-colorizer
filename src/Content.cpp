//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include "Content.h"

Content::Content(int width, int height) : Wt::WPaintedWidget()
{
    Wt::WPaintedWidget::resize(width, height);

    mouseDragged().connect(this, &Content::mouseDrag);
    mouseWentDown().connect(this, &Content::mouseDown);
    touchStarted().connect(this, &Content::touchStart);
    touchMoved().connect(this, &Content::touchMove);
    touchMoved().preventDefaultAction();
    color_ = Wt::WColor(Wt::StandardColor::Black);



    const Wt::WColor blue("#0d6efd");                              // btn-primary
    const Wt::WColor red("#dc3545");                               // btn-danger
    const Wt::WColor green("#198754");                             // btn-success
    const Wt::WColor yellow("#ffc107");                            // btn-warning
    const Wt::WColor black = Wt::WColor(Wt::StandardColor::Black); // btn-inverse
    const Wt::WColor gray("#6c757d");

    auto result = std::make_unique<Wt::WContainerWidget>();

    auto canvas = std::make_unique<Content>(800,600); // static for now
    auto canvas_ = canvas.get();
    canvas->setColor(blue);
    canvas->decorationStyle().setBorder(Wt::WBorder(Wt::BorderStyle::Solid, Wt::BorderWidth::Medium, black));

    std::vector<Wt::WPushButton *> colorButtons {
            createColorToggle("btn-blue", blue, canvas.get()),
            createColorToggle("btn-danger", red, canvas.get()),
            createColorToggle("btn-success", green, canvas.get()),
            createColorToggle("btn-warning", yellow, canvas.get()),
            createColorToggle("btn-black", black, canvas.get()),
            createColorToggle("btn-secondary", gray, canvas.get())
    };

    auto toolBar = std::make_unique<Wt::WToolBar>();

    for (unsigned i = 0; i < colorButtons.size(); ++i) {
        Wt::WPushButton *button = colorButtons[i];
        button->setChecked(i == 0);
        toolBar->addButton(std::unique_ptr<Wt::WPushButton>(button));

        // Implement a radio button group
        for (unsigned j = 0; j < colorButtons.size(); ++j) {
            if (i != j) {
                Wt::WPushButton * const other = colorButtons[j];
                button->checked().connect(other, &Wt::WPushButton::setUnChecked);
            }
        }
    }

    auto clearButton = std::make_unique<Wt::WPushButton>("Clear");

    clearButton->clicked().connect([=] {
        canvas_->clear();
    });

    toolBar->addSeparator();
    toolBar->addButton(std::move(clearButton));

    result->addWidget(std::move(toolBar));
    result->addWidget(std::move(canvas));
}

void Content::clear()
{
    update();
}

void Content::setColor(const Wt::WColor &c)
{
    color_ = c;
}

void Content::mouseDown(const Wt::WMouseEvent &e)
{
    Wt::Coordinates c = e.widget();
    path_ = Wt::WPainterPath(Wt::WPointF(c.x,c.y));
}

void Content::mouseDrag(const Wt::WMouseEvent &e)
{
    Wt::Coordinates c = e.widget();
    path_.lineTo(c.x,c.y);
    update(Wt::PaintFlag::Update);
}

void Content::touchStart(const Wt::WTouchEvent &e)
{
    Wt::Coordinates c = e.touches()[0].widget();
    path_ = Wt::WPainterPath(Wt::WPointF(c.x,c.y));

}

void Content::touchMove(const Wt::WTouchEvent &e)
{
    Wt::Coordinates c = e.touches()[0].widget();
    path_.lineTo(c.x,c.y);
    update(Wt::PaintFlag::Update);
}

void Content::paintEvent(Wt::WPaintDevice *paintDevice)
{
    Wt::WPainter painter(paintDevice);
    painter.setRenderHint(Wt::RenderHint::Antialiasing);

    Wt::WPen pen;
    pen.setWidth(3);
    pen.setColor(color_);
    pen.setCapStyle(Wt::PenCapStyle::Flat);
    pen.setJoinStyle(Wt::PenJoinStyle::Miter);
    painter.setPen(pen);
    painter.drawPath(path_);

    path_ = Wt::WPainterPath(path_.currentPosition());
}




