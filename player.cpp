#include <QMessageBox>
#include "player.h"

Player::Player(QString fn, QString ln, QString rl, bool en, bool de) :
    User(fn, ln, rl, en, de)
{
    // Nothing to do here
}

void Player::encode(QString filename, QString messageToHide, QString messageKey)
{
    encrypt(messageToHide, messageKey);
    encodeImage(filename);
}

void Player::decode(QString filename, QString messageKey)
{
    decodeImage(filename);
    QString theSecret = decrypt(messageKey);
    QMessageBox::information(NULL, "", "What he or she really want to say is:\n" + theSecret);
}

int Player::generateKey(std::string messageKey)
{
    int key = 0;
    messageKey = "player" + messageKey;

    for (unsigned long i = 0; i < messageKey.length(); i++)
        key += (int)messageKey[i];
    key /= messageKey.length();

    return key;
}
