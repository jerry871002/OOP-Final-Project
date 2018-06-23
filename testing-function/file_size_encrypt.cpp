#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

using namespace std;

int main(int argc, char const *argv[]) {
    fstream inFile(argv[1], ios::in);
    fstream outFile(argv[2], ios::out);

    string messageToHide;
    string publicMessage;

    cin >> publicMessage;
    getline(inFile, messageToHide);

    int key = 0;
    for(int i = 0; i < publicMessage.length(); i++)
        key += (int)publicMessage[i];
    key /= publicMessage.length();
    cout << key << endl;

    cout << "Before encode:" << endl;
    for(int i = 0; i < messageToHide.length(); i++) {
        cout << messageToHide[i] << " ";
        cout << (int)messageToHide[i] << endl;
    }

    //encode the message
    cout << "After encode:" << endl;
    for(int i = 0; i < messageToHide.length(); i++) {
        messageToHide[i] = messageToHide[i] ^ key;
        cout << messageToHide[i] << " ";
        cout << (int)messageToHide[i] << endl;
    }
    outFile << messageToHide;

    inFile.close();
    outFile.close();
    return 0;
}
