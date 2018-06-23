#include <QDebug>
#include <fstream>
#include <opencv2/opencv.hpp>
#include "user.h"

using namespace std;
using namespace cv;

User::User(QString fn, QString ln, bool en, bool de) :
    firstName(fn),
    lastName(ln),
    canEncode(en),
    canDecode(de)
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

void User::encode(QString filename, QString messageToHide, QString messageKey)
{
    encrypt(messageToHide, messageKey);
    encodeImage(filename);
}

void User::decode(QString filename, QString messageKey)
{
    decodeImage(filename);
    QString theSecret = decrypt(messageKey);
}

void User::encrypt(QString QmessageToHide, QString QmessageKey)
{
    ofstream outFile("messageEncrypted.txt");

    string messageToHide = QmessageToHide.toStdString();
    string messageKey = QmessageKey.toStdString();

    // Make a key by messageKey
    int key = 0;
    for (unsigned long i = 0; i < messageKey.length(); i++)
        key += (int)messageKey[i];
    key /= messageKey.length();

    // Encrypt the message
    for (unsigned long i = 0; i < messageToHide.length(); i++)
        messageToHide[i] = messageToHide[i] ^ key;

    // Write into a file
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
    int key = 0;
    for (unsigned long i = 0; i < messageKey.length(); i++)
        key += (int)messageKey[i];
    key /= messageKey.length();

    // decode the message
    for(unsigned long i = 0; i < messageToFind.length(); i++)
        messageToFind[i] = messageToFind[i] ^ key;

    inFile.close();

    return QString::fromStdString(messageToFind);
}

bool isBitSet(char ch, int pos)
{
    // 7 6 5 4 3 2 1 0
    ch = ch >> pos;
    if (ch & 1)
        return true;
    return false;
}

int User::encodeImage(QString Qfilename)
{
    string filename = Qfilename.toStdString();

    qDebug() << Qfilename << endl;

    // Stores original image
    Mat image = imread(filename);
    if (image.empty())
    {
        qDebug() << "Image Error\n";
        return 1;
    }

    // Open file for text information
    ifstream file("messageEncrypted.txt");
    if (!file.is_open())
    {
        qDebug() << "File Error\n";
        return 1;
    }

    // char to work on
    char ch;
    // reads the first char from the file
    file.get(ch);
    // contains information about which bit of char to work on
    int bit_count = 0;
    // to check whether file has ended
    bool last_null_char = false;
    // to check if the whole message is encoded or not
    bool encoded = false;

    /*
    To hide text into images. We are taking one char (8 bits) and each of the 8 bits are stored
    in the Least Significant Bits (LSB) of the pixel values (Red,Green,Blue).
    We are manipulating bits in such way that changing LSB of the pixel values will not make a huge difference.
    The image will still look similiar to the naked eye.
    */
    qDebug() << image.rows << "\n";
    qDebug() << image.cols << "\n";

    for (int row = 0; row < image.rows; row++)
    {
        for (int col = 0; col < image.cols; col++)
        {
            for (int color = 0; color < 3; color++)
            {
                // stores the pixel details
                Vec3b pixel = image.at<Vec3b>(Point(row, col));//像素

                // if bit is 1 : change LSB of present color value to 1.
                // if bit is 0 : change LSB of present color value to 0.
                if (isBitSet(ch, 7 - bit_count))
                    pixel.val[color] |= 1; // pixel.val[color] or 1(強制設成1)
                else
                    pixel.val[color] &= ~1; //維持原狀

                // update the image with the changed pixel values
                image.at<Vec3b>(Point(row, col)) = pixel;

                // increment bit_count to work on next bit
                bit_count++;

                // 如果讀到文字檔的最後一個字元 則跳出三個迴圈輸出圖片
                if (last_null_char && bit_count == 8)
                {
                    encoded  = true;
                    goto OUT; // 直接跳出三層迴圈
                }

                // if bit_count is 8 we pick the next char from the file and work on it
                if (bit_count == 8)
                {
                    bit_count = 0;
                    file.get(ch);

                    // if EndOfFile(EOF) is encountered insert NULL char to the image
                    if (file.eof())
                    {
                        last_null_char = true;
                        ch = '\0';
                    }
                }
            }
        }
    }

    OUT:;


    // whole message was not encoded
    if (!encoded) {
        qDebug() << "Message too big. Try with larger image.\n";
        return 2;
    }

    qDebug() << "successfully encode";
    // Writes the stegnographic image
    filename.erase(filename.end()-4, filename.end());
    filename += "-encode.png";

    qDebug() << QString::fromStdString(filename);
    imwrite(filename, image);
    return 0;
}

void User::decodeImage(QString Qfilename)
{
    string filename = Qfilename.toStdString();

    // Stores original image
    Mat image = imread(filename);
    if (image.empty())
    {
        qDebug() << "Image Error\n";
        return;
    }

    // char to work on
    char ch = 0;
    // contains information about which bit of char to work on
    int bit_count = 0;
    //output textfile
    ofstream outFile("messageEncrypted.txt");

    /*
    To extract the message from the image, we will iterate through the pixels and extract the LSB of
    the pixel values (RGB) and this way we can get our message.
    */
    for (int row = 0; row < image.rows; row++)
    {
        for (int col = 0; col < image.cols; col++)
        {
            for (int color = 0; color < 3; color++)
            {
                // stores the pixel details
                Vec3b pixel = image.at<Vec3b>(Point(row, col));

                // manipulate char bits according to the LSB of pixel values
                if (isBitSet(pixel.val[color], 0))
                    ch |= 1;

                // increment bit_count to work on next bit
                bit_count++;

                // bit_count is 8, that means we got our char from the encoded image
                if (bit_count == 8)
                {
                    // NULL char is encountered
                    if (ch == '\0')
                        goto OUT; // 直接跳出三層迴圈

                    bit_count = 0;
                    outFile << ch;
                    ch = 0;
                }
                else
                {
                    ch = ch << 1;
                }
            }
        }
    }
    OUT:;
}
