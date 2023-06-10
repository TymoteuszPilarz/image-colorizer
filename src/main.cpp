#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WToolBar.h>
#include <Wt/WLink.h>
#include <Wt/WLinkedCssStyleSheet.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WColorPicker.h>
#include <memory>

#include "Toolbar.h"
#include "Sidebar.h"
#include "Content.h"

namespace {

    std::unique_ptr<Wt::WPushButton> createColorButton(const char *className,
                                                       const Wt::WString& text)
    {
        auto button = std::make_unique<Wt::WPushButton>();
        button->setTextFormat(Wt::TextFormat::XHTML);
        button->setText(text);
        button->addStyleClass(className);
        return button;
    }
}

class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment& env);
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
    using namespace Wt;

    useStyleSheet(Wt::WLink("css/styles.css"));

    auto container = root()->addWidget(std::make_unique<WContainerWidget>());
    container->setStyleClass("blue-box");

    auto vBox = container->setLayout(std::make_unique<WVBoxLayout>());
    vBox->setContentsMargins(0, 0, 0, 0);

    auto toolbar = vBox->addWidget(std::make_unique<Toolbar>());

    auto container2 = vBox->addWidget(std::make_unique<WContainerWidget>());
    auto hBox = container2->setLayout(std::make_unique<WVBoxLayout>());

    auto sidebar = hBox->addWidget(std::make_unique<Sidebar>());
    auto content = hBox->addWidget(std::make_unique<Content>());
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<HelloApplication>(env);
    });
}