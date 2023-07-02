//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include <memory>
#include <filesystem>

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

#include "Toolbar.h"

using namespace Wt;

Toolbar::Toolbar(Content* content) : content(content)
{
    setStyleClass("toolbar");

    hBoxSetup();
    fileMenuSetup();
    editMenuSetup();
    colorPickerSetup();

    // spacing
    hBox->addWidget(std::make_unique<WContainerWidget>(), 1);

    colorizeButtonSetup();
    showButtonSetup();
}

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
    fileMenu->hideOnSelect();

    uploadButton = fileMenu->addItem("Upload");
    uploadButton->setStyleClass("menu-item");
    uploadButton->clicked().connect([fileMenu = fileMenu.get()]()
    {
        fileMenu->hide();
    });
    auto fileUpload = uploadButton->addWidget(std::make_unique<Wt::WFileUpload>());
    fileUpload->setDisplayWidget(uploadButton);
    fileUpload->hide();
    fileUpload->setMultiple(false);
    fileUpload->setFilters("image/png, image/jpeg");
    fileUpload->changed().connect(fileUpload, &WFileUpload::upload);
    fileUpload->uploaded().connect([content = content, fileUpload = fileUpload]()
    {
        fileUpload->stealSpooledFile();

        // File name must be changed every time new image is uploaded, because WPaintDevice caches images based on their URI
        static int suffix = 0;
        std::filesystem::remove("in/image" + std::to_string(suffix));
        ++suffix;
        std::string fileName = "in/image" + std::to_string(suffix);

        std::filesystem::rename(fileUpload->spoolFileName(), fileName);
        content->setImage(fileName);
    });
    fileUpload->fileTooLarge().connect([content = content, fileUpload = fileUpload]()
    {
        log("error") << "File too large";
    });

    downloadButton = fileMenu->addItem("Download");
    downloadButton->setStyleClass("menu-item");
    //downloadButton->clicked().connect(content, &Content::downloadImage);
    auto imageFile = std::make_shared<Wt::WFileResource>("image/png", "out/out1.png");
    imageFile->suggestFileName("out.png");
    Wt::WLink link = Wt::WLink(imageFile);
    link.setTarget(Wt::LinkTarget::NewWindow);
    downloadButton->setLink(link);
    downloadButton->clicked().connect([fileMenu = fileMenu.get()]()
    {
        fileMenu->hide();
    });

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
    undoButton->clicked().connect([editMenu = editMenu.get()]()
    {
        editMenu->hide();
    });

    redoButton = editMenu->addItem("Redo");
    redoButton->setStyleClass("menu-item");
    redoButton->clicked().connect(content, &Content::redo);
    redoButton->clicked().connect([editMenu = editMenu.get()]()
    {
        editMenu->hide();
    });

    clearButton = editMenu->addItem("Clear");
    clearButton->setStyleClass("menu-item");
    clearButton->clicked().connect(content, &Content::clearCanvas);
    clearButton->clicked().connect([editMenu = editMenu.get()]()
    {
        editMenu->hide();
    });

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
    colorizeButton->clicked().connect([content = content]()
    {
        // File name must be changed every time new image is uploaded, because WPaintDevice caches images based on their URI
        static int suffix = 0;
        std::filesystem::remove("out/out" + std::to_string(suffix) + "png");
        ++suffix;
        std::string fileName = "out/out" + std::to_string(suffix) + ".png";
        content->colorize(fileName);
    });
}

void Toolbar::showButtonSetup()
{
    showButton = hBox->addWidget(std::make_unique<WPushButton>());
    showButton->setStyleClass("colorize-button");
    showButton->setText("Hide");
    showButton->clicked().connect([content = content, showButton = showButton]()
    {
        content->hideResult();
    });
}