#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <QObject>
#include <QMutex>

#include <mainwindow.h>

class Controller : public QObject
{
    Q_OBJECT

    // CONTROLLER
public:
        void initialize();
        void showMainWindow();
private:
        void initializeMainWindow();
        void initializeDatabase();

        LBGui::MainWindow* m_mainWindow;
   // SINGLETON
public:
    static Controller* instance()
    {
        static QMutex mutex;
        if (!m_Instance)
        {
            mutex.lock();

            if (!m_Instance)
                m_Instance = new Controller;

            mutex.unlock();
        }

        return m_Instance;
    }

    static void drop()
    {
        static QMutex mutex;
        mutex.lock();
        delete m_Instance;
        m_Instance = 0;
        mutex.unlock();
    }

private:
    Controller() {}
    ~Controller();

    Controller(const Controller &); // hide copy constructor
    Controller& operator=(const Controller &); // hide assign op
                                 // we leave just the declarations, so the compiler will warn us
                                 // if we try to use those two functions by accident

    static Controller* m_Instance;
};

#endif // CONTROLLER_H
