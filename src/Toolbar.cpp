//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include <memory>
#include <filesystem>
#include <string>

#include <Wt/WHBoxLayout.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WMenuItem.h>
#include <Wt/WMessageBox.h>
#include <Wt/WPopupMenu.h>
#include <Wt/WPushButton.h>
#include <Wt/WText.h>
#include <Wt/WPoint.h>
#include <Wt/WFileUpload.h>
#include <Wt/WFileResource.h>
#include <Wt/WApplication.h>

#include "Toolbar.h"

using namespace Wt;

void Toolbar::hBoxSetup()
{
    hBox = setLayout(std::make_unique<WHBoxLayout>());
    hBox->setContentsMargins(0, 0, 10, 0);
    hBox->setSpacing(0);
}

void Toolbar::fileMenuSetup()
{
    fileMenu = std::make_unique<WPopupMenu>();
    fileMenu->setStyleClass("menu");

    uploadButtonSetup();
    downloadButtonSetup();
    fileButtonSetup();
}

void Toolbar::uploadButtonSetup()
{
    uploadButton = fileMenu->addItem("Upload");
    uploadButton->setStyleClass("menu-item");
//    uploadButton->clicked().connect([fileMenu = fileMenu.get()]()
//    {
//        fileMenu->hide();
//    });

    auto fileUpload = uploadButton->addWidget(std::make_unique<Wt::WFileUpload>());
    fileUpload->setDisplayWidget(uploadButton);
    fileUpload->hide();
    fileUpload->setMultiple(false);
    fileUpload->setFilters("image/png, image/jpeg");
    fileUpload->changed().connect(fileUpload, &WFileUpload::upload);
    fileUpload->uploaded().connect([this, fileUpload]()
    {
        std::string tempFileName = fileUpload->spoolFileName();
        fileUpload->stealSpooledFile();

        std::string fileName = generateUploadFileName();

        std::filesystem::rename(tempFileName, fileName);

        content->setImage(fileName);
        colorizeButton->enable();
    });
    fileUpload->fileTooLarge().connect([content = content, fileUpload = fileUpload]()
    {
        log("error") << "File too large";
    });
}

void Toolbar::downloadButtonSetup()
{
    downloadButton = fileMenu->addItem("Download");
    downloadButton->setStyleClass("menu-item");

    auto imageFile = std::make_shared<Wt::WFileResource>("image/png", getDownloadFileName());
    imageFile->suggestFileName("color_image.png");

    Wt::WLink link = Wt::WLink(imageFile);
    link.setTarget(Wt::LinkTarget::NewWindow);

    downloadButton->setLink(link);
//    downloadButton->clicked().connect([fileMenu = fileMenu.get()]()
//    {
//        fileMenu->hide();
//    });
}

void Toolbar::fileButtonSetup()
{
    fileButton = hBox->addWidget(std::make_unique<WPushButton>());
    fileButton->setStyleClass("button");
    fileButton->setText("File");
    fileButton->setMenu(std::move(fileMenu));

    fileButton->clicked().connect([fileButton = fileButton, fileMenu = fileMenu.get()]()
    {
        fileButton->setFocus(true);
    });

    fileButton->menu()->aboutToHide().connect([fileButton = fileButton]()
    {
        fileButton->setFocus(false);
    });
}

void Toolbar::editMenuSetup()
{
    editMenu = std::make_unique<WPopupMenu>();
    editMenu->setStyleClass("menu");

    undoButton = editMenu->addItem("Undo");
    undoButton->setStyleClass("menu-item");
    undoButton->clicked().connect(content, &Content::undo);
//    undoButton->clicked().connect([editMenu = editMenu.get()]()
//    {
//        editMenu->hide();
//    });

    redoButton = editMenu->addItem("Redo");
    redoButton->setStyleClass("menu-item");
    redoButton->clicked().connect(content, &Content::redo);
//    redoButton->clicked().connect([editMenu = editMenu.get()]()
//    {
//        editMenu->hide();
//    });

    clearButton = editMenu->addItem("Clear");
    clearButton->setStyleClass("menu-item");
    clearButton->clicked().connect(content, &Content::clearCanvas);
//    clearButton->clicked().connect([editMenu = editMenu.get()]()
//    {
//        editMenu->hide();
//    });

    editButton = hBox->addWidget(std::make_unique<WPushButton>());
    editButton->setStyleClass("button");
    editButton->setText("Edit");
    editButton->setMenu(std::move(editMenu));
    editButton->clicked().connect([editButton = editButton, editMenu = editMenu.get()]()
    {
        editButton->setFocus(true);
    });
    editButton->menu()->aboutToHide().connect([editButton = editButton]()
    {
        editButton->setFocus(false);
    });
}

void Toolbar::colorPickerSetup()
{
    colorPicker = hBox->addWidget(std::make_unique<WColorPicker>(StandardColor::Red));
    colorPicker->setStyleClass("color-picker");
    colorPicker->colorInput().connect([content = content, colorPicker = colorPicker]()
    {
        content->setPenColor(colorPicker->color());
    });
}

void Toolbar::colorizeButtonSetup()
{
    colorizeButton = hBox->addWidget(std::make_unique<WPushButton>());
    colorizeButton->setStyleClass("colorize-button");
    colorizeButton->setText("Colorize");
    colorizeButton->disable();
    colorizeButton->clicked().connect([this]()
    {
        content->colorize(generateDownloadFileName());
        hideButton->enable();
    });
}

void Toolbar::hideButtonSetup()
{
    hideButton = hBox->addWidget(std::make_unique<WPushButton>());
    hideButton->setStyleClass("colorize-button");
    hideButton->setText("Hide");
    hideButton->disable();
    hideButton->clicked().connect([this]()
    {
        hideButton->disable();
        content->hideResult();
    });
}

std::string Toolbar::generateUploadFileName()
{
    // File name must be changed every time new image is uploaded and ready to be displayed, because WPaintDevice caches images based on their URI
    std::filesystem::create_directories(sessionId);
    std::string fileName = sessionId + "/in";
    std::filesystem::remove(fileName + std::to_string(uploadFileSuffix));
    ++uploadFileSuffix;
    return fileName + std::to_string(uploadFileSuffix);
}

std::string Toolbar::getUploadFileName() const
{
    return sessionId + "/in" + std::to_string(uploadFileSuffix);
}

std::string Toolbar::generateDownloadFileName()
{
    // File name must be changed every time new colorized image is created and ready to be displayed, because WPaintDevice caches images based on their URI
    std::string fileName = sessionId + "/out";
    std::filesystem::remove(fileName + std::to_string(downloadFileSuffix) + ".png");
    ++uploadFileSuffix;
    return fileName + std::to_string(downloadFileSuffix) + ".png";
}

std::string Toolbar::getDownloadFileName() const
{
    return sessionId + "/out" + std::to_string(downloadFileSuffix) + ".png";
}

Toolbar::Toolbar(Content* content) : content(content), sessionId(WApplication::instance()->sessionId())
{
    setStyleClass("toolbar");

    hBoxSetup();
    fileMenuSetup();
    editMenuSetup();
    colorPickerSetup();

    auto dropdown = hBox->addWidget(std::make_unique<WContainerWidget>());
    dropdown->setStyleClass("dropdown");

    auto dropdownButton = dropdown->addWidget(std::make_unique<WPushButton>());
    dropdownButton->setStyleClass("dropdown-button");
    dropdownButton->setText("Options");
    auto dropdownContent = dropdown->addWidget(std::make_unique<WContainerWidget>());
    dropdownContent->setStyleClass("dropdown-content");
    auto button1 = dropdownContent->addWidget(std::make_unique<WPushButton>());
    button1->setStyleClass("dropdown-element");
    button1->setText("Upload");
    auto button2 = dropdownContent->addWidget(std::make_unique<WPushButton>());
    button2->setText("Download");
    button2->setStyleClass("dropdown-element");
    button2->clicked().connect([&]()
    {
        dropdownContent->hide();
    });


    // spacing
    hBox->addWidget(std::make_unique<WContainerWidget>(), 1);

    colorizeButtonSetup();
    hideButtonSetup();
}

Toolbar::~Toolbar()
{
    //std::filesystem::remove_all(sessionId);
}