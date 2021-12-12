#include <iostream>
using namespace std;
#include <string>
#include "jolly_banker.h"

int main(int argc, char* argv[])
{
    JollyBanker bank;
    if (argc != 2)
    {
        cerr << "Missing Input File" << endl;
        return -1;
    }
    string filename = argv[1];
    bank.ReadInput(filename);
    bank.StoringAccounts();
    bank.Display();
}