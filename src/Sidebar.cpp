//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include <memory>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>

#include "Sidebar.h"

using namespace Wt;

Sidebar::Sidebar()
{
    setStyleClass("green-box");

    Wt::WWebWidget::setMargin(0);

    auto vBox = setLayout(std::make_unique<WVBoxLayout>());
    auto fileButton = vBox->addWidget(std::make_unique<WPushButton>());
    auto button1 = vBox->addWidget(std::make_unique<WPushButton>());
    auto button2 = vBox->addWidget(std::make_unique<WPushButton>());
    auto button3 = vBox->addWidget(std::make_unique<WPushButton>());
}
