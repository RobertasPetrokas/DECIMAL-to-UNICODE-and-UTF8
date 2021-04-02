#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <math.h>
#include <cstdlib>
#include <Windows.h>
#include <fstream>
#include <sstream>

using namespace std;

string decToHexa(unsigned long long int num)
{
    stringstream stream;
    stream << uppercase << hex << num;
    string hexa = stream.str();
    while (hexa.size() < 4) hexa.insert(0, "0");
    
    return hexa;
}

string decToBin(int input)
{
    string bin;
    while (input != 0)
    {
        if (input / 2 == 0)
        {
            bin.insert(0, to_string(input % 2));
            break;
        }
        else
        {
            bin.insert(0, to_string(input % 2));
            input = input / 2;
        }
    }
    return bin;
}

string binToUTF8(string bin, int input)
{
    string utfBin;
    if (input <= 127)
    {
        while (bin.size() < 7) bin.insert(0, "0");

        reverse(bin.begin(), bin.end());
        for (int i(0); i < 7; i++) utfBin.push_back(bin[i]);
        utfBin.push_back('0');
    }
    else if (input >= 128 && input <= 2047)
    {
        while (bin.size() < 11) bin.insert(0, "0");

        reverse(bin.begin(), bin.end());
        for (int i(0); i < 6;i++) utfBin.push_back(bin[i]);
        utfBin.push_back('0');
        utfBin.push_back('1');
        for (int i(6); i < 11; i++) utfBin.push_back(bin[i]);
        utfBin.push_back('0');
        utfBin.push_back('1');
        utfBin.push_back('1');
    }
    else if (input >= 2048 && input <= 65535)
    {
        while (bin.size() < 16) bin.insert(0, "0");

        reverse(bin.begin(), bin.end());
        for (int i(0); i < 6;i++) utfBin.push_back(bin[i]);
        utfBin.push_back('0');
        utfBin.push_back('1');
        for (int i(6); i < 12; i++) utfBin.push_back(bin[i]);
        utfBin.push_back('0');
        utfBin.push_back('1');
        for (int i(12); i < 16; i++) utfBin.push_back(bin[i]);
        utfBin.push_back('0');
        utfBin.push_back('1');
        utfBin.push_back('1');
        utfBin.push_back('1');
    }
    else if (input >= 65536 && input <= 1114111)
    {
        while (bin.size() < 21) bin.insert(0, "0");

        reverse(bin.begin(), bin.end());
        for (int i(0); i < 6;i++) utfBin.push_back(bin[i]);
        utfBin.push_back('0');
        utfBin.push_back('1');
        for (int i(6); i < 12; i++) utfBin.push_back(bin[i]);
        utfBin.push_back('0');
        utfBin.push_back('1');
        for (int i(12); i < 18; i++) utfBin.push_back(bin[i]);
        utfBin.push_back('0');
        utfBin.push_back('1');
        for (int i(18); i < 21; i++) utfBin.push_back(bin[i]);   
        utfBin.push_back('0');
        utfBin.push_back('1');
        utfBin.push_back('1');
        utfBin.push_back('1');
        utfBin.push_back('1');
    }
    return utfBin;
}

unsigned long long int binToDec(string utfBin)
{
    unsigned long long int dec(0);
    for (int i(0); i < utfBin.size(); i++)
    {
        dec += (utfBin[i]-48) * pow(2, i);
    }
    return dec;
}

int hexToDec(char hex)
{
    int utf(0);
        if (hex == '0') utf = 0;
        else if (hex == '1') utf = 1;
        else if (hex == '2') utf = 2;
        else if (hex == '3') utf = 3;
        else if (hex == '4') utf = 4;
        else if (hex == '5') utf = 5;
        else if (hex == '6') utf = 6;
        else if (hex == '7') utf = 7;
        else if (hex == '8') utf = 8;
        else if (hex == '9') utf = 9;
        else if (hex == 'A') utf = 10;
        else if (hex == 'B') utf = 11;
        else if (hex == 'C') utf = 12;
        else if (hex == 'D') utf = 13;
        else if (hex == 'E') utf = 14;
        else if (hex == 'F') utf = 15;
  
    return utf;
}



int main(){

    SetConsoleOutputCP(CP_UTF8);
    string hexa, bin, utfBin, utfHexa;
    int input;
    unsigned long long int dec;
    ofstream fd("output.txt");
    bool go = true;
    int choice;

    while (go)
    {
        cout << "----------------------------------DECIMAL to UNICODE and UTF8 converter----------------------------------" << endl << endl
            << " --------------MENU---------------" << endl << endl
            << " 1 - Convert" << endl
            << " 2 - Exit" << endl
            << "Enter your selection and press ENTER: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            system("cls");
            cout << "Enter decimal number: ";
            cin >> input;

            hexa = decToHexa(input);
            bin = decToBin(input);
            utfBin = binToUTF8(bin, input);
            dec = binToDec(utfBin);
            utfHexa = decToHexa(dec);


            cout << "Unicode: U+" << hexa << endl;
            cout << "UTF8: " << utfHexa << endl;
            cout << "CHAR: ";
            for (int i = 0; i < utfHexa.size(); i += 2) {
                int a = hexToDec(utfHexa[i]) * 16;
                int b = hexToDec(utfHexa[i + 1]);
                cout << (char)(a + b);
                fd << (char)(a + b);
            }
            cout << endl << endl;
            break;
        }
        case 2:
        {
            system("cls");
            cout << "Done." << endl;
            go = false;
            break;
        }
        default:
            system("cls");
            cout << "wrong choice." << endl
                << "Try again." << endl;
            break;
        }
    }
}