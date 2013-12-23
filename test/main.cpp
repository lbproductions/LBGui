#include <QApplication>
#include <QHBoxLayout>
#include <QLabel>

#include "../src/mainwindow.h"

int main(int argc, char *argv[]) \
{ \
    QApplication app(argc, argv); \

    LBGui::MainWindow* window = new LBGui::MainWindow();
    LBGui::ChildWidget* widget = new LBGui::ChildWidget("Test", QIcon(), window);
    QHBoxLayout* layout = new QHBoxLayout(window);
    layout->addWidget(new QLabel("TestLabel",widget));
    widget->setLayout(layout);
    LBGui::ChildWidget* widget1 = new LBGui::ChildWidget("AnotherTest", QIcon(), window);

    window->registerChildWidget(widget);
    window->registerChildWidget(widget1);

    window->show();

    return app.exec();
}
