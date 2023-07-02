//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#ifndef IMAGECOLORIZATION_TOOLBAR_H
#define IMAGECOLORIZATION_TOOLBAR_H

#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WMenuItem.h>
#include <Wt/WMessageBox.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WPoint.h>
#include <Wt/WColorPicker.h>

#include "Content.h"

class Toolbar : public Wt::WContainerWidget
{
private:
    Content* content;

    Wt::WHBoxLayout* hBox;

    std::unique_ptr<Wt::WPopupMenu> fileMenu;
    Wt::WPushButton* fileButton;
    Wt::WMenuItem* uploadButton;
    Wt::WMenuItem* downloadButton;

    std::unique_ptr<Wt::WPopupMenu> editMenu;
    Wt::WPushButton* editButton;
    Wt::WMenuItem* undoButton;
    Wt::WMenuItem* redoButton;
    Wt::WMenuItem* clearButton;
    Wt::WColorPicker* colorPicker;

    Wt::WPushButton* colorizeButton;
    Wt::WPushButton* showButton;

    void hBoxSetup();
    void fileMenuSetup();
    void editMenuSetup();
    void colorPickerSetup();
    void colorizeButtonSetup();
    void showButtonSetup();

public:
    Toolbar(Content* content);
};

#endif //IMAGECOLORIZATION_TOOLBAR_H
