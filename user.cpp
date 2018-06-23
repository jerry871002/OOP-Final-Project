#include "user.h"

User::User(QString fn, QString ln, bool en, bool de) :
    firstName(fn),
    lastName(ln),
    canEncode(en),
    canDecode(de)
{

}

bool User::checkEncode()
{
    return canEncode;
}

bool User::checkDecode()
{
    return canDecode;
}

void User::encode()
{

}

void User::decode()
{

}
