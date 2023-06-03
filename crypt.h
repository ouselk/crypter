#ifndef CRYPT_H
#define CRYPT_H

enum class Encryption
{
	cezar,
	keyword
};

const std::vector<std::string> ENCRYPTIONS = {"Шифр Цезаря", "Шифр с использованием кодового слова"};

std::string encrypt(std::string text, Encryption crypt);
std::string cezarCrypt(std::string text);
std::string keyword_encrypted(std::string text, std::map<unsigned char, unsigned char>& base_n_change);
std::string keyword_decrypted(std::string encrypted, std::map<unsigned char, unsigned char> base_n_change);

#endif
