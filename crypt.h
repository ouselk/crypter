#ifndef CRYPT_H
#define CRYPT_H

#include <string>
#include <map>
#include <vector>

enum class Encryption
{
	keyword,
	simpleTable,
	vidger,
	rsa
};

const std::vector<std::string> ENCRYPTIONS = {"Шифр со сдвигом по кодовому слову", "Простой табличный шифр",
											  "Шифр Виженера", "RSA"};

std::string encrypt(std::string text, Encryption crypt, std::string key="");
std::string decrypt(std::string crypted, Encryption crypt);
std::string cezarCrypt(std::string text);
std::string keyword_encrypted(std::string text, std::string key);
std::string keyword_decrypted(std::string encrypted, std::string key);
std::string simpleTableCrypt(std::string text, int n, int m);
std::string simpleTableDecrypt(std::string text, int n, int m);
std::string vidgerCrypt(std::string text, std::string key);
std::string vidgerDecrypt(std::string key, std::string text);
std::string rsaCrypt(std::string msg, int n, int e);
std::string rsaDecrypt(std::string msg, int n, int d);

#endif
