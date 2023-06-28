//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#ifndef IMAGECOLORIZATION_SIDEBAR_H
#define IMAGECOLORIZATION_SIDEBAR_H

#include <Wt/WContainerWidget.h>
#include <Wt/WVBoxLayout.h>

#include "Content.h"

class Sidebar : public Wt::WContainerWidget
{
private:
    Content* content;

public:
    Sidebar(Content* content);
};


#endif //IMAGECOLORIZATION_SIDEBAR_H
