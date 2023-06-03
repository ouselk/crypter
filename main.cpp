#include <iostream>
#include <tuple>
#include <string>
#include <Windows.h>
#include <cstdio>
#include "userInterface.h"
#include "files.h"
#include "crypt.h"
#include "funcs.h"

int main()
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	const std::string DEFAULT_DECRYPTED_FILENAME = "decrypted.txt";
	const std::string DEFAULT_ENCRYPTED_FILENAME = "encrypted.txt";

	std::string decryptedFilename = DEFAULT_DECRYPTED_FILENAME;
	std::string encryptedFilename = DEFAULT_ENCRYPTED_FILENAME;
	if (!fileExists(encryptedFilename))
	{
		std::cout << "Не существует файла с названием " << encryptedFilename << "." << std::endl;
		std::string password = getPassword("Задайте пароль для работы с программой, который будет помещен в начало файла: ");
		writeFile(password + '\n', encryptedFilename);
	}
	else
	{
		std::string userPass;
		std::string truePass = readString(encryptedFilename, 0);
		int i = 3;
		do
		{
			std::cout << "Осталось " << i-- << " попытки." << std::endl;
			userPass = getPassword("Введите пароль для использования программы: ");
		} while (userPass != truePass && i > 0);

		if (i == 0)
		{
			std::cout << "Попытка перебора пароля. Программа удаляет файл и завершает работу." << std::endl;
			remove(encryptedFilename.c_str());
			return -1;
		}
	}

	Action action = getAction();
	Encryption crypt = getEncryption(ENCRYPTIONS);
	if (action == Action::crypt)
	{ 
		writeFile(getUserText("0"), decryptedFilename);
		std::string key = "";
		if (crypt == Encryption::keyword)
		{
			key = getPassword("Введите ключ шифрования: ");
			
			writeFile(readString(encryptedFilename, 0) + '\n' + key + '\n', encryptedFilename);
		}

		std::string encryptedText = encrypt(readFile(decryptedFilename), crypt, key);
		writeFile(encryptedText, encryptedFilename, false);    
	}
	else if (action == Action::decrypt)
	{
		std::string password = readString(encryptedFilename, 0);
		std::string encrypted = readFile(encryptedFilename);
		
		deleteSubStr(encrypted, password + '\n');

		std::string decryptedText = decrypt(encrypted, crypt);
		writeFile(decryptedText, decryptedFilename);
	}

	else if (action == Action::error)
		return -1;
}

