#include<fstream>
#include<iostream>
#include<cstdlib>
#include<string>

using namespace std;

int main()
{
    char filename[] = "test.txt";
    fstream fp;
    fp.open(filename, ios::out);

    string input, output;
    string key;
    int intkey = 0;

    cout << "Input your sentence: ";
    getline(cin, input);

    int *code = new int[input.length()];

    cout << "Input your key: ";
    getline(cin, key);

    for(int i = 0; i < key.length(); i++)
        intkey += (int)key[i];

    intkey /= key.length();

    for(int i = 0; i < input.length(); i++)
    {
        code[i] = (int)(input[i] ^ intkey);
        fp << code[i] << " ";
    }

    delete(code);
    fp.close();//�����ɮ�
    return 0;
}
