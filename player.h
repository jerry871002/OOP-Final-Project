#ifndef PLAYER_H
#define PLAYER_H

#include "user.h"
#include "imageprocess.h"

class Player : public User, public ImageProcess
{
public:
    Player(QString fn, QString ln, QString rl, bool en, bool de);

    void encode(QString filename, QString messageToHide, QString messageKey);
    void decode(QString filename, QString messageKey);

protected:
    int generateKey(std::string messageKey);
};

#endif // PLAYER_H
