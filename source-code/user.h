#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User(QString fn = 0, QString ln = 0, QString rl = 0, bool en = false, bool de = false);
    virtual ~User();

    virtual void encode(QString filename, QString messageToHide, QString messageKey) = 0;
    virtual void decode(QString filename, QString messageKey) = 0;

    bool checkEncode() const;
    bool checkDecode() const;

protected:
    // Access right to encode() and decode()
    const bool canEncode;
    const bool canDecode;

    // Utility functions
    void encrypt(QString QmessageToHide, QString QmessageKey);
    QString decrypt(QString QmessageKey);
    virtual int generateKey(std::string messageKey) = 0;

private:
    QString firstName;
    QString lastName;
    QString role;

};

#endif // USER_H
