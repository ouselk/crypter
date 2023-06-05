#ifndef FUNCS_H
#define FUNCS_H

#include <string>
#include <map>
#include "crypt.h"

void checkKey(std::string key, Encryption crypt);

/*5.14 Шифр с использованием кодового слова. Шифр с использованием кодового слова является одним из самых простых как в реализации,
так и в расшифровывании.Идея заключается в том, что выбирается кодовое слово, которое пишется впереди,
затем выписываются остальные буквы алфавита в своем порядке.*/
int getCountKE(std::string str, char sym);
std::string checkKeyKE(std::string key);
std::map<unsigned char, unsigned char> getBaseAndChangeKE(std::string key);
void deleteSubStr(std::string& string, const std::string& substr);

bool isNumber(std::string str);
std::pair<int, int> checkKeyST(std::string key);
#endif