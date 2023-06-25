//
// Created by dedboi on 25.06.23.
//

#ifndef IMAGECOLORIZATION_DROPBOX_H
#define IMAGECOLORIZATION_DROPBOX_H

#include <Wt/WContainerWidget.h>
#include <Wt/WFileDropWidget.h>
#include <Wt/WText.h>

using namespace Wt;


class DropBox : public Wt::WContainerWidget
        {
public:
            DropBox();


            unsigned int getHeight();
            unsigned int getWidth();

            void setHeight(unsigned int h);
            void setWidth(unsigned int w);



private:
            unsigned int height;
            unsigned int width;


};


#endif //IMAGECOLORIZATION_DROPBOX_H
