#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <unordered_map>

#define maxvalue(a, b) (a > b ? a : b)

std::vector<int> encoding(std::string s1)
{
    std::unordered_map<std::string, int> dict;
    std::vector<int> codes;
    std::vector<std::string> table; // Таблица для вывода всех использованных элементов словаря
    std::vector<std::string> table2; // Таблица для вывода новых элементов словаря
    int count = 0;
    size_t maxout = 1;
    for (char i : s1)
    {
        dict[std::string(1, i)] = int(i);
    }
    std::string current;
    size_t i = 0;
    while (i < s1.length())
    {
        int move = 1;
        std::string candidate;
        current = s1[i];
        while (dict.count(current) != 0)
        {
            candidate = current;
            if (i + move < s1.length())
            {
                current += s1[i + move];
                move++;
            }
            else
            {
                break;
            }
        }
        count++;
        if (dict.count(current) == 0)
        {
            dict[current] = 255 + count;
            table2.push_back(current);
            maxout = maxvalue(maxout, current.length());
        }
        codes.push_back(dict[candidate]);
        table.push_back(candidate);
        
        i += candidate.length();
    }

    // Вывод таблицы
    {
        std::cout<<std::setw((maxout > 6) ? maxout : 6)<<"String"<<"      "<<"Output_Code"<<"      "<<"Addition"<<"\n"<<std::endl;
        for (size_t i = 0; i < table.size(); i++)
        {
            std::cout<<std::setw((maxout > 6) ? maxout : 6)<<table[i]<<"             "<<std::setw(4)<<dict[table[i]];
            if (i < table2.size())
            {
                std::cout<<"   "<<std::setw((maxout > 6) ? maxout : 6)<<table2[i]<<"   "<<std::setw(4)<<dict[table2[i]]<<"\n"<<std::endl;
            }
            else
            {
                std::cout<<"\n"<<std::endl;
            }
        }
    }
    return codes;
}

void decoding(std::vector<int> op)
{
    std::unordered_map<int, std::string> dict;
    for (int i = 0; i < 256; i++)
    {
        dict[i] = std::string(1, char(i));
    }
    std::string result = "";
    std::string resultcopy = "";
    std::string lastelement;
    int count = 1;
    for (int i : op)
    {
        if ((i > 4095) || (i < 0) || (count == 1 && i > 255))
        {
            std::cout<<"Неверный код"<<std::endl;
            exit(1);
        }
        result += dict[i];
        if (count > 1)
        {
            dict[255 + count - 1] = lastelement + dict[i][0];
            result = resultcopy + dict[i];
        }
        lastelement = dict[i];
        dict[255 + count] = dict[i];
        count++;
        resultcopy = result;
    }
    std::cout<<"Decoding:"<<"\n"<<result<<std::endl;
}