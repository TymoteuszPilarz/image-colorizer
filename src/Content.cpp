//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include "Content.h"

Content::Content()
{
    auto result = std::make_unique<Wt::WContainerWidget>();

    auto canvas = std::make_unique<Canvas>(800, 600);
    auto canvas_ = canvas.get();
    canvas->setColor(blue);
    canvas->decorationStyle().setBorder
            (Wt::WBorder(Wt::BorderStyle::Solid, Wt::BorderWidth::Medium, black));

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

   this->addWidget(std::move(toolBar));
    this->addWidget(std::move(canvas));

}