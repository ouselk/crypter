#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <vector>
#include "crypt.h"


enum class Action
{
	error = -1,
	crypt,
	decrypt
};

std::string getUserText(std::string endOfInput);
Encryption getEncryption(const std::vector<std::string> &encryptions);
std::string getPassword(std::string message);
Action getAction();
#endif
