#include "customer.h"

Customer::Customer(QObject *parent) :
    QObject(parent)
{
}

QString Customer::firstName() const
{
    return m_firstName;
}

void Customer::setFirstName(const QString &_name)
{
    m_firstName = _name;
}

QString Customer::lastName() const
{
    return m_lastName;
}

void Customer::setLastName(const QString &_lastName)
{
    m_lastName = _lastName;
}

Customer::Gender Customer::gender() const
{
    return m_gender;
}

void Customer::setGender(const Gender &_gender)
{
    m_gender = _gender;
}

QString Customer::genderString() const
{
    if(m_gender == Male) {
        return "Herr";
    }
    if(m_gender == Female) {
        return "Frau";
    }

    return "";
}
