#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <QObject>

class Customer : public QObject
{
    Q_OBJECT
    Q_ENUMS(Gender)
    Q_PROPERTY(QString firstName READ firstName WRITE setFirstName)
    Q_PROPERTY(QString lastName READ lastName WRITE setLastName)
public:
    enum Gender {
        Male,
        Female
    };
    explicit Customer(QObject *parent = 0);

    QString firstName() const;
    void setFirstName(const QString &_name);

    QString lastName() const;
    void setLastName(const QString &_lastName);

    Gender gender() const;
    void setGender(const Gender &_gender);
    QString genderString() const;

signals:

public slots:

private:
    QString m_firstName;
    QString m_lastName;

    Gender m_gender;

};

#endif // CUSTOMER_H
