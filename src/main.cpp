#include <QApplication>

#include "controller.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_DontShowIconsInMenus, true);
    a.setApplicationName("projectoptinvest");
    a.setOrganizationName("lbproductions");

    Controller::instance()->initialize();
    Controller::instance()->showMainWindow();

    return a.exec();
}
