#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char const *argv[]) {
    fstream inFile(argv[1], ios::in);
    fstream outFile(argv[2], ios::out);
    inFile.open();
    outFile.open();

    string messageToHide;
    string publicMessage;

    cin >> publicMessage;
    getline(inFile, messageToHide);

    int key = 0;
    for(int i = 0; i < publicMessage.length(); i++)
        key += (int)publicMessage[i];
    key /= publicMessage.length();
    cout << key << endl;

    //encode the message
    for(int i = 0; i < messageToHide.length(); i++)
        messageToHide[i] = messageToHide[i] ^ key;
    cout << messageToHide << endl;

    // decode the message
    for(int i = 0; i < messageToHide.length(); i++)
        messageToHide[i] = messageToHide[i] ^ key;
    cout << messageToHide << endl;

    inFile.close();
    outFile.close();
    return 0;
}
