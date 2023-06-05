#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "userInterface.h"
#include "crypt.h"
#include "funcs.h"



std::string getUserText(std::string endOfInput)
{
	//Функция получает от пользователя и возвращает многострочный текст,
	//ввод завершается, когда пользователь вводит строку, равную
	//параметру endOfInput

	std::cout << "Введите текст для шифрования (для завершения введите строку, следующего содержания \"" << endOfInput << "\"):" << std::endl;
	std::string text = "";

	while (std::cin)
	{
		std::string t ="";
		getline(std::cin, t);
		if (t==endOfInput)
			break;
		text+=t+'\n';
	}
	text.erase(text.begin());

	return text;
}

Encryption getEncryption(const std::vector<std::string> &encryptions)
{
	//Функции передается вектор строк запрашиваемых шифров,
	//она запрашивает у пользователя шифр до тех пор, пока
	//не получит допустимое число, означающее шифр.
	//Возвращает идентификатор шифра.
	std::cin.clear();
	int encryption_code = -1;
	do
	{
		std::cout << "Выберите один из шифров:" << std::endl;
		for (int i = 0; i < encryptions.size(); i++)
			std::cout << i << ") " << encryptions[i] << std::endl;
		std::cout << "Введите номер шифра: ";
		std::cin >> encryption_code;
	} while (encryption_code < 0 || encryption_code >= encryptions.size());
	
	return static_cast<Encryption>(encryption_code);
}

std::string getPassword(std::string message)
{
	std::cout << message;
	std::string pass;
	std::cin >> pass;
	std::cin.ignore(32222, '\n');
	return pass;
}

std::string getPassword(std::string message, bool keyValid(std::string))
{
	std::string key = getPassword(message);
	if (!keyValid(key))
		throw "Введен неверный ключ.";
	return key;
}

std::string getKey(Encryption encrypt)
{
	std::string key = "";
	try
	{
		if (encrypt == Encryption::keyword)
		{
			key = getPassword("Введите ключ шифрования, не содержащий одинаковых символов: ");
			checkKeyKE(key);
		}
		else if (encrypt == Encryption::simpleTable)
		{
			key = getPassword("Введите размер таблицы в формате NxM: ");
			checkKeyST(key);
		}
	}
	catch (const char* str)
	{
		std::cout << str << std::endl;
		key = getKey(encrypt);
	}

	return key;
}

Action getAction()
{
	char act;
	do
	{
		std::cout << "Вы хотите расшифровать или зашифровать текст [D\\C]: ";
		std::cin >> act;
	} while (act!='D' && act!='C');
	
	if (act=='D' || act=='d')
		return Action::decrypt;
	if (act=='C' || act=='c')
		return Action::crypt;

	return Action::error;

}

std::string getKey(std::string &crypted, Encryption crypt)
{
	std::string key = "";
	for (auto s : crypted)
	{
		if (s == '\n')
			break;
		key += s;
	}

	try{ checkKey(key, crypt);}
	catch (...) {throw "Неверно указан шифр.";}
	
	deleteSubStr(crypted, key + '\n');
	return key;
}