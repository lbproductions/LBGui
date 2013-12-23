#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setAttribute(Qt::AA_DontShowIconsInMenus, true);
    a.setApplicationName("projectoptinvest");
    a.setOrganizationName("lbproductions");

    return a.exec();
}
