#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QToolButton>

using namespace LBGui;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_childWidgetIndex(0),
    m_currentChildWidgetIndex(0)
{
    ui->setupUi(this);

    m_buttonGroup = new QButtonGroup(this);

    connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this, SLOT(onButtonClicked(int)));
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

    m_childWidets.append(childWidget);
}

void MainWindow::setCurrentChildWidget(int index)
{
    m_buttonGroup->button(index)->click();
}

void MainWindow::onButtonClicked(int index)
{
    ui->centralStackedWidget->setCurrentIndex(index);

    if(index < 0 || index > m_childWidets.size()-1)
        return;

    // Delete old widgets from status bar
    ChildWidget* oldChild = m_childWidets.at(m_currentChildWidgetIndex);
    if(oldChild) {
        foreach(QWidget* widget, oldChild->statusBarButtons()) {
            widget->setVisible(false);
            ui->statusbar->removeWidget(widget);
        }
    }

    // Add new widgets to status bar
    ChildWidget* currentChild = m_childWidets.at(index);
    if(currentChild) {
        foreach(QWidget* widget, oldChild->statusBarButtons()) {
            widget->setVisible(true);
            ui->statusbar->addPermanentWidget(widget);
        }
    }

    m_currentChildWidgetIndex = index;
}

