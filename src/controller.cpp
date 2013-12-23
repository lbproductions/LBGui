#include "controller.h"

#include <QDebug>
#include <QDir>
#include <QCoreApplication>

#include <QSqlDatabase>
#include <QPersistence.h>

#include <data/customer.h>

Controller* Controller::m_Instance = 0;

using namespace LBGui;

Controller::~Controller()
{
    if(m_mainWindow) {
        m_mainWindow = 0;
        delete m_mainWindow;
    }
}

void Controller::initialize()
{
    initializeDatabase();
    initializeMainWindow();
}

void Controller::showMainWindow()
{
    if(!m_mainWindow)
        return;

    m_mainWindow->show();
}

void Controller::initializeMainWindow()
{
    m_mainWindow = new MainWindow();
    m_mainWindow->setWindowTitle("Optinvest");
}

void Controller::initializeDatabase()
{
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/database.db");
    if(!db.open()) {
        qDebug("Could not open database: " + QCoreApplication::applicationDirPath() + "/database.db");
    }

    Qp::registerMappableTypes<int, int>();
    Qp::setDatabase(db);
    Qp::registerClass<Customer>();
    Qp::adjustDatabaseSchema();
}
