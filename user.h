#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(QString fn = 0, QString ln = 0, bool en = false, bool de = false);

    void encode();
    void decode();

protected:
    QString firstName;
    QString lastName;

    // Access right to encode() and decode()
    const bool canEncode;
    const bool canDecode;
};

#endif // USER_H
