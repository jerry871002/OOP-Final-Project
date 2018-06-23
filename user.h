#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(QString fn = 0, QString ln = 0, bool en = false, bool de = false);

    void encode(QString filename, QString messageToHide, QString messageKey);
    void decode(QString filename, QString messageKey);

    bool checkEncode() const;
    bool checkDecode() const;

protected:
    QString firstName;
    QString lastName;

    // Utility functions
    void encrypt(QString QmessageToHide, QString QmessageKey);
    QString decrypt(QString QmessageKey);
    int encodeImage(QString Qfilename);
    void decodeImage(QString Qfilename);

    // Access right to encode() and decode()
    const bool canEncode;
    const bool canDecode;
};

#endif // USER_H
