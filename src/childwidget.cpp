#include "childwidget.h"

using namespace LBGui;

ChildWidget::ChildWidget(QString name, QIcon icon, QWidget *parent):
    QWidget(parent),
    m_name(name),
    m_icon(icon)
{
}

QString ChildWidget::name()
{
    return m_name;
}

QIcon ChildWidget::icon()
{
    return m_icon;
}
