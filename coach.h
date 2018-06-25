#ifndef COACH_H
#define COACH_H

#include "user.h"
#include "imageprocess.h"

class Coach : public User, public ImageProcess
{
public:
    Coach(QString fn, QString ln, QString rl, bool en, bool de);

    void encode(QString filename, QString messageToHide, QString messageKey);
    void decode(QString filename, QString messageKey);

protected:
    int generateKey(std::string messageKey);
};

#endif // COACH_H
