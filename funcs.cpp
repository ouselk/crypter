#include <string>
#include "funcs.h"

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
std::string getKeyKE(std::string key)
{
    for (int i = 0; i < key.size(); i++)
    {
        if (getCount(key, key[i]) > 1)
            throw key[i];
    }
    return key;
}