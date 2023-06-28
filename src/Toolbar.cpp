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

    auto clear = hBox->addWidget(std::make_unique<WPushButton>());
    clear->setText("Clear");
    clear->clicked().connect(content, &Content::clearCanvas);

    auto save = hBox->addWidget(std::make_unique<WPushButton>());
    save->setText("Save");
    save->clicked().connect(content, &Content::saveToPNG);

    auto button3 = hBox->addWidget(std::make_unique<WPushButton>());
}
