#include <vector>
#include <string>
#include "crypt.h"

std::string encrypt(std::string text, Encryption crypt)
{
	std::string crypted = text;
	switch (crypt)
	{
		case Encryption::cezar:
			crypted = cezarCrypt(text);
			break;
	}

	return crypted;
}

std::string cezarCrypt(std::string text)
{
	std::string res = "CEZAR";
	return res;
}
