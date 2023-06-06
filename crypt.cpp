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
    std::cout << "encrypt" << std::endl;
	std::string crypted = text;
    if (text.empty())
        throw "Нечего зашифровывать";
	switch (crypt)
	{
        case Encryption::keyword:
        {
            crypted = keyword_encrypted(text, key);
            break;
        }
        case Encryption::simpleTable:
        {
            std::pair<int, int> pr = checkKeyST(key);
            crypted = simpleTableCrypt(text, pr.first, pr.second);
            break;
        }
        case Encryption::vidger:
        {
            crypted = vidgerCrypt(text,key);
            break;
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
            std::string key = getKey(crypted, crypt);
            decrypted = keyword_decrypted(crypted, key);
            break;
        }
        case Encryption::simpleTable:
        {
            std::string key = getKey(crypted, crypt);
            std::pair <int, int> p = checkKeyST(key);
            decrypted = simpleTableDecrypt(crypted, p.first, p.second);
            break;
        }
        case Encryption::vidger:
        {
            decrypted = vidgerDecrypt(crypted, getKey(crypted, crypt));
            break;
        }
    }
        

    return decrypted;
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

//5.16 Простая табличная перестановка.
std::string simpleTableCrypt(std::string text, int n, int m)
//n количество строк
//m количество столбцов
{
    text.erase(std::remove_if(text.begin(), text.end(), [](char c){ 
                  return std::isspace(static_cast<unsigned char>(c));
               }), text.end());
    //std::cout << text << std::endl;
    std::vector<std::vector<unsigned char>> table(n);
    for (auto &col : table)
        col=std::vector<unsigned char>(m);
//    std::cout << text << std::endl;

    int index = 0;
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
        {
            if (index>=text.size())
                throw "Таблица слишком большая для сообщения";
            table[i][j]=text.at(index++);
        }
    if (index<text.size()-1)
        throw "Таблица слишком маленькая для сообщения";

    std::string crypted = "";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            crypted += table[i][j];
    
    return crypted;
}

std::string simpleTableDecrypt(std::string text, int n, int m)
//n количество строк
//m количество столбцов
{
    text.erase(std::remove_if(text.begin(), text.end(), [](char c){ 
                  return std::isspace(static_cast<unsigned char>(c));
               }), text.end());
    //std::cout << text << std::endl;
    std::vector<std::vector<unsigned char>> table(n);
    for (auto &col : table)
        col=std::vector<unsigned char>(m);
    std::cout << text << std::endl;

    int index = 0;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
        {
            if (index>=text.size())
                throw "Таблица слишком большая для сообщения";
            table[i][j]=text.at(index++);
        }
    if (index<text.size()-1)
        throw "Таблица слишком маленькая для сообщения";

    std::string crypted = "";
    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            crypted += table[i][j];
    
    return crypted;
}

// Шифр виженера

std::string vidgerCrypt(std::string text, std::string key)
{
    std::string crypted = "";
    size_t d = key.size();
    int n = 256;
    for (int i = 0; i < text.size(); i++)
    {
        unsigned char indT = text[i];
        unsigned char indK = key[i%d];
        unsigned char sym = (indT+indK)%n;
        crypted+=sym;
    }

    return crypted;
}

std::string vidgerDecrypt(std::string text, std::string key)
{
    std::string crypted = "";
    
    int n = 256;
    size_t d = key.size();
    for (int i = 0; i < text.size(); i++)
    {
        unsigned char indT = text[i];
        unsigned char indK = key[i%d];
        unsigned char sym = (indT-indK)%n;
        crypted+=sym;
    //    std::cout << "Text: " << indT << " Key: " << indK << " Shifr: " << (indT+indK)%alphabet.size()+1 << std::endl;
    }

    return crypted;
}