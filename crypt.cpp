#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <map>
#include "funcs.h"
#include "userInterface.h"
#include "crypt.h"

std::string encrypt(std::string text, Encryption crypt, std::string key)
{
	std::string crypted = text;
	switch (crypt)
	{
		case Encryption::cezar:
        {
            crypted = cezarCrypt(text);
            break;
        }
        case Encryption::keyword:
        {
            crypted = keyword_encrypted(text, key);
        }

	}

	return crypted;
}

std::string decrypt(std::string crypted, Encryption crypt)
{
    std::string decrypted = crypted;
    switch (crypt)
    {
        case Encryption::keyword:
        {
            std::string key = "";
            for (auto s : crypted)
            {
                if (s == '\n')
                    break;
                key += s;
            }
            deleteSubStr(crypted, key + '\n');
            decrypted = keyword_decrypted(crypted, key);
        }
    }

    return decrypted;
}

std::string cezarCrypt(std::string text)
{
	std::string res = "CEZAR";
	return res;
}



/*5.14 Шифр с использованием кодового слова. Шифр с использованием кодового слова является одним из самых простых как в реализации,
так и в расшифровывании. Идея заключается в том, что выбирается кодовое слово, которое пишется впереди,
затем выписываются остальные буквы алфавита в своем порядке. */

std::string keyword_encrypted(std::string text, std::string key) {

    std::map<unsigned char, unsigned char> base_n_change = getBaseAndChangeKE(key);

    std::string resultStr = text;
    for (int i = 0; i < text.size(); i++)
    {
        if (text[i] == ' ')
        {
            resultStr += ' ';
            continue;
        }

        for (auto pair : base_n_change)
        {
            if (pair.first == static_cast<unsigned char>(text[i]))
                resultStr[i] = pair.second;
        }
    }
    return resultStr;

}
std::string keyword_decrypted(std::string encrypted, std::string key)
{
    std::map<unsigned char, unsigned char> base_n_change = getBaseAndChangeKE(key);
    std::string resultStr = encrypted;
    for (int i = 0; i < encrypted.size(); i++)
    {
        if (encrypted[i] == ' ')
        {
            resultStr += ' ';
            continue;
        }
        for (auto pair : base_n_change)
        {
            if (pair.second == static_cast<unsigned char>(encrypted[i]))
                resultStr[i] = pair.first;
        }
    }
    return resultStr;
}