#ifndef CRYPT_H
#define CRYPT_H

#include <string>
#include <map>
#include <vector>

enum class Encryption
{
	cezar,
	keyword
};

const std::vector<std::string> ENCRYPTIONS = {"Шифр Цезаря", "Шифр с использованием кодового слова"};

std::string encrypt(std::string text, Encryption crypt, std::string key="");
std::string decrypt(std::string crypted, Encryption crypt);
std::string cezarCrypt(std::string text);
std::string keyword_encrypted(std::string text, std::string key);
std::string keyword_decrypted(std::string encrypted, std::string key);

#endif
