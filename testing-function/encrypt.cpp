#include <iostream>

using namespace std;

int main() {
    //string messageToHide = "NCTU";
    //string publicMessage = "My mom miss you a lot.";
    string messageToHide = "今晚九點任務A，B計畫";
    string publicMessage = "我今天去超市買了一條香腸";

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

    return 0;
}
