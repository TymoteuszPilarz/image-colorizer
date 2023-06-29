//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include <memory>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPushButton.h>

#include "Toolbar.h"

using namespace Wt;

Toolbar::Toolbar(Content* content) : content(content)
{
    setStyleClass("toolbar");

    Wt::WWebWidget::setMargin(0);

    auto hBox = setLayout(std::make_unique<WHBoxLayout>());

    auto undo = hBox->addWidget(std::make_unique<WPushButton>());
    undo->setText("Undo");
    undo->clicked().connect(content, &Content::undo);
    undo->setStyleClass("button");

    auto clear = hBox->addWidget(std::make_unique<WPushButton>());
    clear->setText("Clear");
    clear->clicked().connect(content, &Content::clearCanvas);
    clear->setStyleClass("button");

    auto save = hBox->addWidget(std::make_unique<WPushButton>());
    save->setText("Colorize");
    save->clicked().connect(content, &Content::colorize);
    save->setStyleClass("button");

    auto button3 = hBox->addWidget(std::make_unique<WPushButton>());
    button3->setStyleClass("button");
}
