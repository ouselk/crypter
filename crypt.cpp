#include <vector>
#include <string>
#include <cmath>
#include <iostream>
#include <Windows.h> 
#include <map>
#include "funcs.h"
#include "crypt.h"

std::string encrypt(std::string text, Encryption crypt)
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
            std::map<unsigned char, unsigned char> baseAndChange{};
            crypted = keyword_encrypted(text, baseAndChange);

        }

	}

	return crypted;
}

std::string cezarCrypt(std::string text)
{
	std::string res = "CEZAR";
	return res;
}



/*5.14 Шифр с использованием кодового слова. Шифр с использованием кодового слова является одним из самых простых как в реализации,
так и в расшифровывании. Идея заключается в том, что выбирается кодовое слово, которое пишется впереди,
затем выписываются остальные буквы алфавита в своем порядке. */

std::string keyword_encrypted(std::string text, std::map<unsigned char, unsigned char>& base_n_change) {
    std::string key;
    std::string new_alph = "";
    std::string alphabet = "";
    for (int i = 33; i < 256; i++)
    {
        if (i == 127 || i == 152 || i == 160 || i == 173)
            continue;
        else
            alphabet += static_cast<unsigned char>(i);
    }
    std::cout << "Введите текстовый ключ без повторения букв: ";
    getline(std::cin, key);
    try {
        getKeyKE(key);
    }
    catch (char sym)
    {
        std::cout << "В ключе повторилась буква " << sym << '.' << std::endl;
        keyword_encrypted(text, base_n_change);
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
std::string keyword_decrypted(std::string encrypted, std::map<unsigned char, unsigned char> base_n_change)
{
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