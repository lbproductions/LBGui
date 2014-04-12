#include "dialogcontroller.h"

#include <QPropertyAnimation>
#include <QFrame>
#include <QHBoxLayout>

DialogController::DialogController(QWidget *parent) :
    QObject(parent),
    m_parent(parent),
    m_dialog(nullptr),
    m_widget(nullptr),
    m_dialogHeight(-1),
    m_dialogWidth(-1),
    m_dialogOffsetTop(0),
    m_dialogOffsetLeft(29),
    m_mode(Bottom)
{
}

int DialogController::dialogHeight() const
{
    return m_dialogHeight;
}

void DialogController::setDialogHeight(int dialogHeight)
{
    m_dialogHeight = dialogHeight;
}

int DialogController::dialogOffsetTop() const
{
    return m_dialogOffsetTop;
}

void DialogController::setDialogOffsetTop(int dialogOffsetTop)
{
    m_dialogOffsetTop = dialogOffsetTop;
}

int DialogController::dialogOffsetLeft() const
{
    return m_dialogOffsetLeft;
}

void DialogController::setDialogOffsetLeft(int dialogOffsetLeft)
{
    m_dialogOffsetLeft = dialogOffsetLeft;
}

void DialogController::setSlideInMode(DialogController::SlideInMode mode)
{
    m_mode = mode;
}

void DialogController::closeDialogOnMousePress(const QPoint &mousePos)
{
    if(!m_dialog)
        return;

    if(m_dialog->geometry().contains(mousePos))
        return;

    closeDialog();
}

void DialogController::showDialog(QWidget *widget)
{
    QWidget *frame = frameWidget(widget);
    if(m_dialogHeight > 0) {
        frame->setFixedHeight(m_dialogHeight);
    }
    if(m_dialogWidth > 0) {
        frame->setFixedWidth(m_dialogWidth);
    }
    frame->setFocus();
    frame->show();
    connect(widget, &QWidget::destroyed, this, &DialogController::closeDialogWhenDestroyed);

    if(m_dialog) { // previous dialog
        if(m_widget)
            disconnect(m_widget, 0, this, 0);

        m_dialog->close();
        m_dialog->deleteLater();
        m_widget = widget;
        m_dialog = frame;
        frame->setGeometry(visibleGeometry(frame));
        return; // only animate, if there was no dialog before.
    }

    m_widget = widget;
    m_dialog = frame;

    QPropertyAnimation *animation  = new QPropertyAnimation(m_dialog, "geometry");
    animation->setStartValue(hiddenGeometry(frame));
    animation->setEndValue(visibleGeometry(frame));
    animation->setDuration(300);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    animation->start();

    connect(animation, &QPropertyAnimation::finished,
            animation, &QPropertyAnimation::deleteLater);
}

void DialogController::closeDialog()
{
    QWidget *dialog = m_dialog;
    m_dialog = nullptr;
    m_widget = nullptr;

    if(!dialog)
        return;

    QRect geom = dialog->geometry();
    int w = geom.width() + m_dialogOffsetLeft;
    QPropertyAnimation *animation  = new QPropertyAnimation(dialog, "geometry");
    animation->setStartValue(visibleGeometry(dialog));
    animation->setEndValue(hiddenGeometry(dialog));
    animation->setDuration(300);
    animation->setEasingCurve(QEasingCurve::OutExpo);
    animation->start();

    connect(animation, &QPropertyAnimation::finished, [=]{
        animation->deleteLater();
        dialog->close();
        dialog->deleteLater();
    });

    emit dialogClosed();
}
int DialogController::dialogWidth() const
{
    return m_dialogWidth;
}

void DialogController::setDialogWidth(int dialogWidth)
{
    m_dialogWidth = dialogWidth;
}

int DialogController::dialogOffsetRight() const
{
    return m_dialogOffsetRight;
}

void DialogController::setDialogOffsetRight(int dialogOffsetRight)
{
    m_dialogOffsetRight = dialogOffsetRight;
}

int DialogController::dialogOffsetBottom() const
{
    return m_dialogOffsetBottom;
}

void DialogController::setDialogOffsetBottom(int dialogOffsetBottom)
{
    m_dialogOffsetBottom = dialogOffsetBottom;
}


void DialogController::closeDialogWhenDestroyed()
{
    QWidget *w = static_cast<QWidget*>(sender());
    if(w != m_widget)
        return;

    closeDialog();
}

QWidget *DialogController::frameWidget(QWidget *widget)
{
    QFrame *frame = new QFrame(m_parent);
    frame->setLayout(new QHBoxLayout);
    frame->setObjectName("actionFrame");
    frame->setMinimumWidth(widget->width());
    frame->layout()->addWidget(widget);
    frame->layout()->setContentsMargins(0,0,0,0);
    if(m_mode == Bottom) {
        frame->setStyleSheet("QFrame#actionFrame { background: rgb(35,35,35); border:none; border-top:2px solid rgb(108,108,108);}");
    }
    return frame;
}

QRect DialogController::visibleGeometry(QWidget *widget) const
{
    if(m_mode == Bottom) {
        return QRect(0, m_parent->height() - widget->height(), m_parent->width(), widget->height());
    }

    return QRect(0,0,0,0);
}

QRect DialogController::hiddenGeometry(QWidget *widget) const
{
    if(m_mode == Bottom) {
        return QRect(0, m_parent->height(), m_parent->width(), widget->height());
    }

    return QRect(0,0,0,0);
}
