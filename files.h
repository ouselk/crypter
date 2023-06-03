#ifndef FILES_H
#define FILES_H

std::string writeFile(std::string text, std::string fileName, bool clearFile = true);
std::string readFile(std::string fileName);
std::string readString(std::string fileName, int index);
bool fileExists(std::string fileName);

#endif
