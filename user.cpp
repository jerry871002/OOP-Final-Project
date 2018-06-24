#include <fstream>
#include "user.h"

using namespace std;

User::User(QString fn, QString ln, QString rl, bool en, bool de) :
    firstName(fn),
    lastName(ln),
    role(rl),
    canEncode(en),
    canDecode(de)
{
    // Nothing to do here
}

User::~User()
{
    // Nothing to do here
}

bool User::checkEncode() const
{
    return canEncode;
}

bool User::checkDecode() const
{
    return canDecode;
}

void User::encrypt(QString QmessageToHide, QString QmessageKey)
{
    ofstream outFile("messageEncrypted.txt");

    string messageToHide = QmessageToHide.toStdString();
    string messageKey = QmessageKey.toStdString();

    // Make a key by messageKey
    int key = generateKey(messageKey);

    // Encrypt the message
    for (unsigned long i = 0; i < messageToHide.length(); i++)
        messageToHide[i] = messageToHide[i] ^ key;

    // Write into the file
    outFile << messageToHide;

    outFile.close();
}

QString User::decrypt(QString QmessageKey)
{
    string messageToFind;
    ifstream inFile("messageEncrypted.txt");
    getline(inFile, messageToFind);

    string messageKey = QmessageKey.toStdString();

    // Make a key by messageKey
    int key = generateKey(messageKey);

    // Decode the message
    for (unsigned long i = 0; i < messageToFind.length(); i++)
        messageToFind[i] = messageToFind[i] ^ key;

    inFile.close();

    return QString::fromStdString(messageToFind);
}


