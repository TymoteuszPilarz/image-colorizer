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
#include <Wt/WFileUpload.h>

#include "Content.h"

class Toolbar : public Wt::WContainerWidget
{
private:
    Content* content;

    Wt::WPushButton* downloadButton;
    Wt::WPushButton* colorizeButton;
    Wt::WPushButton* hideButton;

    std::string sessionId;
    int uploadFileSuffix = 0;
    int downloadFileSuffix = 0;

    std::unique_ptr<Wt::WHBoxLayout> createLayout();

    std::unique_ptr<Wt::WContainerWidget> createFileMenu();
    std::unique_ptr<Wt::WPushButton> createUploadButton();
    std::unique_ptr<Wt::WPushButton> createDownloadButton();

    std::unique_ptr<Wt::WContainerWidget> createEditMenu();
    std::unique_ptr<Wt::WPushButton> createUndoButton();
    std::unique_ptr<Wt::WPushButton> createRedoButton();
    std::unique_ptr<Wt::WPushButton> createClearButton();

    std::unique_ptr<Wt::WColorPicker> createColorPicker();

    std::unique_ptr<Wt::WPushButton> createColorizeButton();
    std::unique_ptr<Wt::WPushButton> createHideButton();

    std::string generateUploadFileName();
    std::string getUploadFileName() const;

    std::string generateDownloadFileName();
    std::string getDownloadFileName() const;

public:
    Toolbar(Content* content);
    ~Toolbar();
};

#endif //IMAGECOLORIZATION_TOOLBAR_H
