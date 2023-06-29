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

    //setStyleClass("yellow-box");

    Wt::WWebWidget::setMargin(0);


    auto hBox = setLayout(std::make_unique<WHBoxLayout>());



    auto fileButton = hBox->addWidget(std::make_unique<WPushButton>("Test"));
    auto button1 = hBox->addWidget(std::make_unique<WPushButton>("Test"));
    auto button2 = hBox->addWidget(std::make_unique<WPushButton>("Test"));
    auto button3 = hBox->addWidget(std::make_unique<WPushButton>());
    auto slider = hBox->addWidget(std::make_unique<WColorPicker>());
    button1->setStyleClass("button");
    button2->setStyleClass("button");
    button3->setStyleClass("button");
    fileButton->setStyleClass("button");
    slider->setStyleClass("color-picker");


}
