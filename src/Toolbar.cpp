//
// Created by Tymoteusz Pilarz on 10/06/2023.
//

#include <memory>
#include <filesystem>
#include <string>

#include <Wt/WHBoxLayout.h>
#include <Wt/WBreak.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WPushButton.h>
#include <Wt/WFileUpload.h>
#include <Wt/WFileResource.h>
#include <Wt/WApplication.h>
#include <Wt/WOverlayLoadingIndicator.h>

#include "Toolbar.h"

using namespace Wt;

std::unique_ptr<Wt::WHBoxLayout> Toolbar::createLayout()
{
    auto layout = std::make_unique<WHBoxLayout>();
    layout->setContentsMargins(0, 0, 10, 0);
    layout->setSpacing(0);
    return layout;
}

std::unique_ptr<Wt::WContainerWidget> Toolbar::createFileMenu()
{
    auto dropdown = std::make_unique<WContainerWidget>();
    dropdown->setStyleClass("dropdown");

    auto dropdownButton = dropdown->addWidget(std::make_unique<WPushButton>("File"));
    dropdownButton->setStyleClass("dropdown-button");

    auto dropdownContent = dropdown->addWidget(std::make_unique<WContainerWidget>());
    dropdownContent->setStyleClass("dropdown-content");
    dropdownContent->addWidget(createUploadButton());
    dropdownContent->addWidget(createDownloadButton());

    return dropdown;
}

std::unique_ptr<WPushButton> Toolbar::createUploadButton()
{
    auto button = std::make_unique<WPushButton>("Upload");
    button->setStyleClass("dropdown-element");

    auto fileUpload = static_cast<WHBoxLayout*>(layout())->addWidget(std::make_unique<Wt::WFileUpload>());
    fileUpload->setDisplayWidget(button.get());
    fileUpload->setWidth(0);
    fileUpload->setHeight(0);
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
    fileUpload->fileTooLarge().connect([]()
    {
        log("error") << "File too large";
    });

    return button;
}

std::unique_ptr<Wt::WPushButton> Toolbar::createDownloadButton()
{
    auto button = std::make_unique<WPushButton>("Download");
    button->setStyleClass("dropdown-element");
    button->disable();

    auto imageFile = std::make_shared<Wt::WFileResource>("image/png", getDownloadFileName());
    imageFile->suggestFileName("color_image.png");

    Wt::WLink link = Wt::WLink(imageFile);
    link.setTarget(Wt::LinkTarget::NewWindow);

    button->setLink(link);

    downloadButton = button.get();

    return button;
}

std::unique_ptr<Wt::WContainerWidget> Toolbar::createEditMenu()
{
    auto dropdown = std::make_unique<WContainerWidget>();
    dropdown->setStyleClass("dropdown");

    auto dropdownButton = dropdown->addWidget(std::make_unique<WPushButton>("Edit"));
    dropdownButton->setStyleClass("dropdown-button");

    auto dropdownContent = dropdown->addWidget(std::make_unique<WContainerWidget>());
    dropdownContent->setStyleClass("dropdown-content");
    dropdownContent->addWidget(createUndoButton());
    dropdownContent->addWidget(createRedoButton());
    dropdownContent->addWidget(createClearButton());

    return dropdown;
}

std::unique_ptr<Wt::WPushButton> Toolbar::createUndoButton()
{
    auto button = std::make_unique<WPushButton>("Undo");
    button->setStyleClass("dropdown-element");
    button->clicked().connect(content, &Content::undo);

    return button;
}

std::unique_ptr<Wt::WPushButton> Toolbar::createRedoButton()
{
    auto button = std::make_unique<WPushButton>("Redo");
    button->setStyleClass("dropdown-element");
    button->clicked().connect(content, &Content::redo);

    return button;
}

std::unique_ptr<Wt::WPushButton> Toolbar::createClearButton()
{
    auto button = std::make_unique<WPushButton>("Clear");
    button->setStyleClass("dropdown-element");
    button->clicked().connect(content, &Content::clearCanvas);

    return button;
}

std::unique_ptr<Wt::WColorPicker> Toolbar::createColorPicker()
{
    auto colorPicker = std::make_unique<WColorPicker>(StandardColor::Red);
    colorPicker->setStyleClass("color-picker");
    colorPicker->colorInput().connect([content = content, colorPicker = colorPicker.get()]()
    {
        content->setPenColor(colorPicker->color());
    });

    return colorPicker;
}

std::unique_ptr<Wt::WPushButton> Toolbar::createColorizeButton()
{
    auto button = std::make_unique<WPushButton>("Colorize");
    button->setStyleClass("colorize-button");
    button->disable();
    button->clicked().connect([this]()
    {
        colorizeButton->disable();
        content->colorize(generateDownloadFileName());
        downloadButton->enable();
        hideButton->enable();
    });

    colorizeButton = button.get();

    return button;
}

std::unique_ptr<Wt::WPushButton> Toolbar::createHideButton()
{
    auto button = std::make_unique<WPushButton>("Hide");
    button->setStyleClass("colorize-button");
    button->disable();
    button->clicked().connect([this, button = button.get()]()
    {
        content->hideResult();
        colorizeButton->enable();
        button->disable();
    });

    hideButton = button.get();

    return button;
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

    auto layout = setLayout(createLayout());
    layout->addWidget(createFileMenu());
    layout->addWidget(createEditMenu());
    layout->addWidget(createColorPicker());

    // spacing
    layout->addWidget(std::make_unique<WContainerWidget>(), 1);

    layout->addWidget(createColorizeButton());
    layout->addWidget(createHideButton());
}

Toolbar::~Toolbar()
{
    std::filesystem::remove_all(sessionId);
}