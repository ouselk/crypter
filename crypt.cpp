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
	std::string crypted = "Empty";
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
        case Encryption::rsa:
        {
            int e = checkKeyRSA(key);
            int n = 247;
            crypted = rsaCrypt(text, n, e);
            break;
        }
        case Encryption::gronsfeld:
        {
            int k = checkKeyGF(key);
            crypted = groncfeldCrypted(text, k);
            break;
        }
        case Encryption::atbash:
        {
            crypted = atbashEncrypted(text);
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
            std::string key =getKey(crypted, crypt);

            decrypted = vidgerDecrypt(crypted, key);
            break;
        }
        case Encryption::rsa:
        {
            std::string key = getKey(crypted, crypt);
            int e = checkKeyRSA(key);
            int n = 247;
            int res[3] = {0,0,0};
            genEuclidAlg(216, e, res);
            int d = res[2];
            decrypted = rsaDecrypt(crypted, n, d);
            break;
        }
        case Encryption::gronsfeld:
        {
            std::string key = getKey(crypted, crypt);
            decrypted = groncfeldDecrypted(crypted, checkKeyGF(key));
            break;
        }
        case Encryption::atbash:
        {
            decrypted = atbashEncrypted(crypted);
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
            {
                std::cout << text.size()  <<  " - ";
                throw "необходимый размер для таблицы";
            }
            table[i][j]=text.at(index++);
        }
    if (index < text.size() - 1)
    {
        std::cout << text.size() << " - ";
        throw "необходимый размер для таблицы";
    }

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

std::string vidgerCrypt(std::string text, std::string key) {
    int text_length = text.length();
    int key_length = key.length();
    std::string encrypted_text(text_length, ' ');

    for (int i = 0; i < text_length; i++) {
        unsigned char t = text[i];
        unsigned char k =key[i%key_length];
 //       unsigned char space = ' ';
        if (isspace(t))
            encrypted_text[i] = t;
        else
            encrypted_text[i] = ((t - ' ' + k - ' ') % 224) + ' ';
        
    }

    return encrypted_text;
}

std::string vidgerDecrypt(std::string text, std::string key) {
    int text_length = text.length();
    int key_length = key.length();
    std::string decrypted_text(text_length, ' ');

    for (int i = 0; i < text_length; i++) {
        unsigned char t = text[i];
        unsigned char k = key[i%key_length];
        if (isspace(t))
            decrypted_text[i] = t;
        else
            decrypted_text[i] = ((t - ' ' + 224 - (k - ' ')) % 224) + ' ';
    }

    return decrypted_text;
}
//RSA
std::string rsaCrypt(std::string msg, int n, int e)
{
    std::string crypt = msg;
    for (int i = 0; i<msg.size(); i++)
    {
        unsigned char sym = msg[i];
        unsigned char cryptsym = modulePow(static_cast<unsigned char>(msg[i]), e, n);
        if (sym > 245)
            crypt[i] = sym;

        else
            crypt[i] = cryptsym;
    }

    return crypt;
}

std::string rsaDecrypt(std::string msg, int n, int d)
{
    std::string crypt = msg;
    for (int i = 0; i < msg.size(); i++)
    {
        unsigned char sym = msg[i];
        unsigned char cryptsym = modulePow(static_cast<unsigned char>(msg[i]), d, n);
        if (sym > 245)
            crypt[i] = sym;
        else
            crypt[i] = cryptsym;
    }

    return crypt;
}

//Gronsfeld

std::string groncfeldCrypted(std::string text, int key) {
    //int key_c = checkKey(key);
    std::vector<int>key_cif = cifGF(key);
    int keyLen = key_cif.size();
    std::string result = "";

    for (int i = 0; i < text.length(); i++)
    {
        unsigned char letter = text[i];

        // Получаем соответствующий символ из ключа
        int keyIndex = i % keyLen;
        int keyValue = key_cif[keyIndex];

        // Шифруем букву
        unsigned char encryptedLetter = letter;
        if (!isspace(letter))
            encryptedLetter = ((letter - '!' + keyValue) % 223) + '!';

        // Добавляем зашифрованный символ в строку результата
        result += encryptedLetter;
    }

    return result;
}
std::string groncfeldDecrypted(std::string crypted_text, int key) {
    std::string result = "";
    std::vector<int> key_cif = cifGF(key);
    int keyLen = key_cif.size();

    for (int i = 0; i < crypted_text.length(); i++)
    {
        unsigned char letter = crypted_text[i];

        // Получаем соответствующий символ из ключа
        int keyIndex = i % keyLen;
        int keyValue = key_cif[keyIndex];

        // Расшифровываем букву
        unsigned char decryptedLetter = letter;
        if (!isspace(letter))
            decryptedLetter = ((letter - '!' - keyValue + 223) % 223) + '!';

        // Добавляем расшифрованный символ в строку результата
        result += decryptedLetter;
    }

    return result;
}

// атбаш

std::string atbashEncrypted(std::string text) {
    int size = text.size();
    int count = 0;
    bool flag_1 = true;
    std::string resultStr = "";
    for (int i = 0; i < size; i++)
    {
        unsigned char askii = text[i];
        if (text[i] == ' ')
            resultStr += ' ';
        else if (text[i] == '\n')
            resultStr += '\n';
        else
            resultStr += static_cast<unsigned char>(255 - (askii - 33));

    }
    return resultStr;
}