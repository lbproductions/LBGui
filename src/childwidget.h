#ifndef LBGUI_CHILDWIDGET_H
#define LBGUI_CHILDWIDGET_H

#include <QWidget>
#include <QIcon>

namespace LBGui {

class ChildWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ChildWidget(QString name, QIcon icon = QIcon(), QWidget *parent = 0);

    QString name();

    QIcon icon();

signals:

public slots:

private:
    QString m_name;
    QIcon m_icon;

};

} // namespace LBGui

#endif // LBGUI_CHILDWIDGET_H
