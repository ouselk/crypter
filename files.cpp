#include <fstream>
#include <iostream>
#include "files.h"



std::string writeFile(std::string text, std::string fileName)
{
	//Функция записывает строку text в файл с именем fileName.
	//Если такого файла не существует - файл создается,
	//если файл существует - его содержимое перезаписывается.
	//Функция возвращает имя файла или ошибку.
	std::ofstream fout;
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
