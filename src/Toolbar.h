//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#ifndef IMAGECOLORIZER_TOOLBAR_H
#define IMAGECOLORIZER_TOOLBAR_H

#include <memory>
#include <string>

#include <Wt/WContainerWidget.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WColorPicker.h>
#include <Wt/WDialog.h>

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

    std::unique_ptr<Wt::WPushButton> createOptionsButton();

    std::unique_ptr<Wt::WColorPicker> createColorPicker();

    std::unique_ptr<Wt::WPushButton> createColorizeButton();
    std::unique_ptr<Wt::WPushButton> createHideButton();

    std::unique_ptr<Wt::WDialog> createOptionsDialog();

    std::string generateUploadFileName();
    std::string getUploadFileName() const;

    std::string generateDownloadFileName();
    std::string getDownloadFileName() const;

public:
    Toolbar(Content* content);
    ~Toolbar();
};

#endif //IMAGECOLORIZER_TOOLBAR_H
