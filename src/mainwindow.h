#ifndef LBGUI_MAINWINDOW_H
#define LBGUI_MAINWINDOW_H

#include <QMainWindow>
#include <QButtonGroup>

#include <childwidget.h>

namespace LBGui {

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void registerChildWidget(ChildWidget* childWidget);

private:
    Ui::MainWindow *ui;

    int m_childWidgetIndex;
    QButtonGroup* m_buttonGroup;

};


} // namespace LBGui
#endif // LBGUI_MAINWINDOW_H
