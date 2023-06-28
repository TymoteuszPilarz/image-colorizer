//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#ifndef IMAGECOLORIZATION_TOOLBAR_H
#define IMAGECOLORIZATION_TOOLBAR_H

#include <Wt/WContainerWidget.h>

#include "Content.h"

class Toolbar : public Wt::WContainerWidget
{
private:
    Content* content;

public:
    Toolbar(Content* content);
};

#endif //IMAGECOLORIZATION_TOOLBAR_H
