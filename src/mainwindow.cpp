#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolButton>

using namespace LBGui;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_childWidgetIndex(0)
{
    ui->setupUi(this);

    m_buttonGroup = new QButtonGroup(this);

    connect(m_buttonGroup, SIGNAL(buttonClicked(int)), ui->centralStackedWidget, SLOT(setCurrentIndex (int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::registerChildWidget(ChildWidget *childWidget)
{
    QToolButton* button = new QToolButton(this);
    button->setText(childWidget->name());
    button->setFixedSize(70,70);
    button->setCheckable(true);

    m_buttonGroup->addButton(button, m_childWidgetIndex);
    m_childWidgetIndex++;

    ui->buttonLayout->addWidget(button);

    ui->centralStackedWidget->addWidget(childWidget);
}

