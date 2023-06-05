#include <iostream>
#include <tuple>
#include <string>
#include <Windows.h>
#include <cstdio>
#include "userInterface.h"
#include "files.h"
#include "crypt.h"
#include "funcs.h"

int doAction(Action action, Encryption crypt, std::string decryptedFilename, std::string encryptedFilename)
{
	if (action == Action::crypt)
	{ 
		writeFile(getUserText("0"), decryptedFilename);
		std::string key = getKey(crypt);
		writeFile(readString(encryptedFilename, 0) + '\n' + key + '\n', encryptedFilename);
//		std::cout << readFile(decryptedFilename);
		try{
		std::string encryptedText = encrypt(readFile(decryptedFilename), crypt, key);
		writeFile(encryptedText, encryptedFilename, false);    
		} catch(const char* str)
		{
			std::cout << str << std::endl;
			std::cout << "Попробуйте выбрать другое действие."<<std::endl<<std::endl;;
			Action act = getAction();
			Encryption crypt = getEncryption(ENCRYPTIONS);
			doAction(act, crypt, decryptedFilename, encryptedFilename);
		}
	}
	else if (action == Action::decrypt)
	{
		std::string password = readString(encryptedFilename, 0);
		std::string encrypted = readFile(encryptedFilename);
		
		deleteSubStr(encrypted, password + '\n');

		try{
			std::string decryptedText = decrypt(encrypted, crypt);
			writeFile(decryptedText, decryptedFilename);
		} catch(const char* str)
		{
			std::cout << str << std::endl;
			std::cout << "Попробуйте другое действие." << std::endl<<std::endl;
			Action act = getAction();
			crypt = getEncryption(ENCRYPTIONS);
			doAction(act, crypt, decryptedFilename, encryptedFilename);
		}
	}

	else if (action == Action::error)
		return -1;
	
	return 0;
}

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
			if (i == 0)
			{
				std::cout << "Попытка перебора пароля. Программа удаляет файл и завершает работу." << std::endl;
				remove(encryptedFilename.c_str());
				return -1;
			}
			i--;
			std::cout << "Осталось " << i << " попытки." << std::endl;
			userPass = getPassword("Введите пароль для использования программы: ");	
		} while (userPass != truePass);


	}

	Action action = getAction();
	Encryption crypt = getEncryption(ENCRYPTIONS);

	if (doAction(action, crypt, decryptedFilename, encryptedFilename)==0)
		std::cout << "Успех!";
}