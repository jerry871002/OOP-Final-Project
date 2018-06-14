#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(bool en = false, bool de = false);

    void encode();
    void decode();

protected:
    QString firstName;
    QString lastName;

    QString username;
    QString password;

    // Access right to encode() and decode()
    const bool canEncode;
    const bool canDecode;
};

#endif // USER_H
