//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include <memory>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPushButton.h>

#include "Toolbar.h"

using namespace Wt;

Toolbar::Toolbar()
{
    setStyleClass("toolbar");

    Wt::WWebWidget::setMargin(0);

    auto hBox = setLayout(std::make_unique<WHBoxLayout>());

    auto fileButton = hBox->addWidget(std::make_unique<WPushButton>());
    auto button1 = hBox->addWidget(std::make_unique<WPushButton>());
    auto button2 = hBox->addWidget(std::make_unique<WPushButton>());
    auto button3 = hBox->addWidget(std::make_unique<WPushButton>());
}
