#include <fstream>
#include <ios>
#include <iostream>
#include "files.h"



std::string writeFile(std::string text, std::string fileName, bool clearFile)
{
	//Функция записывает строку text в файл с именем fileName.
	//Если такого файла не существует - файл создается,
	//если файл существует - его содержимое перезаписывается.
	//Функция возвращает имя файла или ошибку.
	std::ofstream fout;
	if (!clearFile)
		fout.open(fileName, std::ios_base::app);
	else
		fout.open(fileName);
	if (!fout.is_open())
		return "Ошибка открытия файла";
	fout << text;
	fout.close();

	return fileName;
}

std::string readFile(std::string fileName)
{
	//Функция считывает текст из файла и возвращает его,
	//если файл не был прочитан, возвращает строку
	//Ошибка открытия файла.
	std::ifstream fin(fileName);
	std::string text;
	
	if (!fin.is_open())
		return "Ошибка открытия файла";

	while (fin)
	{
		std::string temp;
		fin >> temp;
		text+=temp + '\n';
	}
	text.pop_back();
	fin.close();
	return text;
}

std::string readString(std::string fileName, int index)
{
	std::ifstream fin(fileName);

	if (!fin.is_open())
		throw "Ошибка открытия файла";

	int i = 0;
	while (fin)
	{
		std::string string;
		fin >> string;
		if (index == i++)
			return string;
	}

	throw "Не найдина строка с индексом " + index;
}

bool fileExists(std::string fileName)
{
	std::ifstream fin(fileName);
	return fin.is_open();
}