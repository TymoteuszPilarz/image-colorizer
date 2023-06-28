#include <memory>

#include <Wt/WApplication.h>
#include <Wt/WContainerWidget.h>
#include <Wt/WToolBar.h>
#include <Wt/WLink.h>
#include <Wt/WLinkedCssStyleSheet.h>
#include <Wt/WVBoxLayout.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WPushButton.h>
#include <Wt/WTable.h>

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

    useStyleSheet(Wt::WLink("css/styles.css"));

    auto container = root()->addWidget(std::make_unique<WContainerWidget>());
    container->setStyleClass("background");

    auto vBox = container->setLayout(std::make_unique<WVBoxLayout>());
    vBox->setContentsMargins(0, 0, 0, 0);
    vBox->setSpacing(0);

    /// Content needs to be created earlier, because it is used as a parameter in Toolbar and Sidebar contructors, but appears in vbox after the Toolbar
    auto contentPtr = std::make_unique<Content>();

    /// Toolbar setup
    auto toolbar = vBox->addWidget(std::make_unique<Toolbar>(contentPtr.get()));

    /// Sidebar and content container setup
    auto subcontainer = vBox->addWidget(std::make_unique<WContainerWidget>());

    auto hBox = subcontainer->setLayout(std::make_unique<WHBoxLayout>());
    hBox->setContentsMargins(0, 0, 0, 0);
    hBox->setSpacing(0);

    /// Sidebar setup
    auto sidebar = hBox->addWidget(std::make_unique<Sidebar>(contentPtr.get()));

    /// Content setup
    auto content = hBox->addWidget(std::move(contentPtr));
}

int main(int argc, char **argv)
{
    return Wt::WRun(argc, argv, [](const Wt::WEnvironment& env) {
        return std::make_unique<HelloApplication>(env);
    });
}