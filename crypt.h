#ifndef CRYPT_H
#define CRYPT_H

enum class Encryption
{
	cezar
};

const std::vector<std::string> ENCRYPTIONS = {"Шифр Цезаря"};

std::string encrypt(std::string text, Encryption crypt);
std::string cezarCrypt(std::string text);

#endif
