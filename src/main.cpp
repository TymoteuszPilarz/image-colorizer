#include <memory>

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WToolBar.h>
#include <Wt/WLink.h>
#include <Wt/WLinkedCssStyleSheet.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WFileUpload.h>
#include <Wt/WText.h>
#include <Wt/WCssStyleSheet.h>

#include "Toolbar.h"
#include "Sidebar.h"
#include "Content.h"

class HelloApplication : public Wt::WApplication
{
public:
    HelloApplication(const Wt::WEnvironment& env);
};

HelloApplication::HelloApplication(const Wt::WEnvironment& env) : Wt::WApplication(env)
{
    using namespace Wt;
    useStyleSheet("css/style.css");
    auto container = root()->addWidget(std::make_unique<WContainerWidget>());

    std::unique_ptr<Wt::WText> item = std::make_unique<Wt::WText>("Item 1");
    container->setStyleClass("body");

    //item->setStyleClass("green-box");
    auto vBox = container->setLayout(std::make_unique<WVBoxLayout>());

    vBox->setContentsMargins(0, 0, 0, 0);
    vBox->addWidget(std::move(item));







    auto subcontainer = vBox->addWidget(std::make_unique<WContainerWidget>());

    auto hBox = subcontainer->setLayout(std::make_unique<WVBoxLayout>());

    /// Toolbar setup
    auto toolbar = vBox->addWidget(std::make_unique<Toolbar>());

    /// Sidebar setup
    auto sidebar = hBox->addWidget(std::make_unique<Sidebar>());



    /// Content setup
    auto content = hBox->addWidget(std::make_unique<Content>());




}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<HelloApplication>(env);
    });
}