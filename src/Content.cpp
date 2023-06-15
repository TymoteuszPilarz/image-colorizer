//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include "Content.h"

void Content::mouseDown(const Wt::WMouseEvent &e)
{
    Wt::Coordinates c = e.widget();
    path_ = Wt::WPainterPath(Wt::WPointF(c.x,c.y));
}
