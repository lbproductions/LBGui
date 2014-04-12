#ifndef DIALOGCONTROLLER_H
#define DIALOGCONTROLLER_H

#include <QObject>

class GameWindow;

class DialogController : public QObject
{
        Q_OBJECT
    public:
        enum SlideInMode {
            Left,
            Right,
            Bottom,
            Top
        };
        explicit DialogController(QWidget *parent = 0);

        int dialogHeight() const;
        void setDialogHeight(int dialogHeight);

        int dialogWidth() const;
        void setDialogWidth(int dialogWidth);

        int dialogOffsetTop() const;
        void setDialogOffsetTop(int dialogOffsetTop);

        int dialogOffsetLeft() const;
        void setDialogOffsetLeft(int dialogOffsetLeft);

        int dialogOffsetBottom() const;
        void setDialogOffsetBottom(int dialogOffsetBottom);

        int dialogOffsetRight() const;
        void setDialogOffsetRight(int dialogOffsetRight);

        void showDialog(QWidget *widget);
        void closeDialogOnMousePress(const QPoint &mousePos);

        void setSlideInMode(SlideInMode mode);

    signals:
        void dialogClosed();

    public slots:
        void closeDialog();

    private:
        QWidget *m_parent;
        QWidget *m_dialog;
        QWidget *m_widget;

        int m_dialogHeight;
        int m_dialogWidth;

        int m_dialogOffsetTop;
        int m_dialogOffsetLeft;
        int m_dialogOffsetBottom;
        int m_dialogOffsetRight;

        void closeDialogWhenDestroyed();

        QWidget *frameWidget(QWidget *widget);
        QRect visibleGeometry(QWidget *widget) const;
        QRect hiddenGeometry(QWidget *widget) const;

        SlideInMode m_mode;
};

#endif // DIALOGCONTROLLER_H
