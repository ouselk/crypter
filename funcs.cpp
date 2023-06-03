#include <string>
#include <map>
#include <iostream>
#include "funcs.h"
#include "userInterface.h"


void deleteSubStr(std::string& string, const std::string& substr)
{
    std::string::size_type i = string.find(substr);
    if (i != std::string::npos)
        string.erase(i, substr.size());
}

/*5.14 Шифр с использованием кодового слова. Шифр с использованием кодового слова является одним из самых простых как в реализации,
так и в расшифровывании.Идея заключается в том, что выбирается кодовое слово, которое пишется впереди,
затем выписываются остальные буквы алфавита в своем порядке.*/

int getCountKE(std::string str, char sym)
{
    int count = 0;
    for (int i = 0; i < str.size(); i++)
        if (str[i] == sym)
            count++;
    return count;
}
std::string checkKeyKE(std::string key)
{
    for (int i = 0; i < key.size(); i++)
    {
        if (getCountKE(key, key[i]) > 1)
            throw key[i];
    }
    return key;
}

std::map<unsigned char, unsigned char> getBaseAndChangeKE(std::string key)
{
    std::string new_alph = "";
    std::string alphabet = "";
    std::map<unsigned char, unsigned char> base_n_change;
    for (int i = 33; i < 256; i++)
    {
        if (i == 127 || i == 152 || i == 160 || i == 173)
            continue;
        else
            alphabet += static_cast<unsigned char>(i);
    }

    try {
        checkKeyKE(key);
    }
    catch (char sym)
    {
        std::cout << key << std::endl;
        key = getPassword("В ключе повторилась буква. Повторите ввод: ");
        getBaseAndChangeKE(key);
    }
    new_alph += key;
    for (int j = 0; j < alphabet.size(); j++)
    {
        if (key.find(alphabet[j]) == -1)
            new_alph += alphabet[j];
    }
    for (int i = 0; i < alphabet.size(); i++) {
        base_n_change[alphabet[i]] = new_alph[i];
    }
    
    return base_n_change;
}