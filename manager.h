#ifndef MANAGER_H
#define MANAGER_H

#include "user.h"
#include "imageprocess.h"

class Manager : public User, public ImageProcess
{
public:
    Manager(QString fn, QString ln, QString rl, bool en, bool de);

    void encode(QString filename, QString messageToHide, QString messageKey);
    void decode(QString filename, QString messageKey);

protected:
    int generateKey(std::string messageKey);
};

#endif // MANAGER_H
