#include <iostream>
#include <string>
#include <limits>
#include <vector>
#include "userInterface.h"
#include "crypt.h"


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

std::string getPassword()
{
	std::cout << "Введите пароль для шифрования";
	std::string pass;
	std::cin >> pass;
	return pass;
}

Action getAction()
{
	char act;
	do
	{
		std::cout << "Вы хотите расшифровать или зашифровать текст [D\\C]:";
		std::cin >> act;
	} while (act!='D' && act!='C');
	
	if (act=='D')
		return Action::decrypt;
	if (act=='C')
		return Action::crypt;

	return Action::error;

}
