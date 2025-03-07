#include <iostream>
#include <vector>
#include <string>
#include "lzw.h"

using namespace std;

int main()
{
    string test;
    getline(cin, test);
    vector<int> code = encoding(test);
    cout<<"Output Codes are: ";
    for (auto i : code)
    {
        cout<<i<<" ";
    }
    cout<<endl;
    decoding(code);
    return 0;
}
