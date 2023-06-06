#include <string>
#include <map>
#include <iostream>
#include "funcs.h"
#include "userInterface.h"


void checkKey(std::string key, Encryption crypt)
{
    switch (crypt)
    {
        case Encryption::keyword :
            checkKeyKE(key);
            break;
        case Encryption::simpleTable:
            checkKeyST(key);
            break;
        case Encryption::rsa:
            checkKeyRSA(key);
            break;
    }
}

void deleteSubStr(std::string& string, const std::string& substr)
{
    std::string::size_type i = string.find(substr);
    if (i != std::string::npos)
        string.erase(i, substr.size());
}

/*5.14 Шифр с использованием кодового слова. Шифр с использованием кодового слова является одним из самых простых как в реализации,
так и в расшифровывании.Идея заключается в том, что выбирается кодовое слово, которое пишется впереди,
затем выписываются остальные буквы алфавита в своем порядке.*/

int getCountKE(std::string str, char sym)
{
    int count = 0;
    for (int i = 0; i < str.size(); i++)
        if (str[i] == sym)
            count++;
    return count;
}
std::string checkKeyKE(std::string key)
{
    for (int i = 0; i < key.size(); i++)
    {
        if (getCountKE(key, key[i]) > 1)
            throw "Неверно введен ключ.";
    }
    return key;
}


std::map<unsigned char, unsigned char> getBaseAndChangeKE(std::string key)
{
    std::string new_alph = "";
    std::string alphabet = "";
    std::map<unsigned char, unsigned char> base_n_change;
    for (int i = 33; i < 256; i++)
    {
        if (i == 127 || i == 152 || i == 160 || i == 173)
            continue;
        else
            alphabet += static_cast<unsigned char>(i);
    }
    new_alph += key;
    for (int j = 0; j < alphabet.size(); j++)
    {
        if (key.find(alphabet[j]) == -1)
            new_alph += alphabet[j];
    }
    for (int i = 0; i < alphabet.size(); i++) {
        base_n_change[alphabet[i]] = new_alph[i];
    }
    
    return base_n_change;
}

//Для шифра simpleTable

bool isNumber(std::string str)
{
    for (unsigned char c : str)
        if (!std::isdigit(c))
            return false;
    return true;
}

std::pair<int, int> checkKeyST(std::string key)
{
    int n = 0;
    int m = 0;
    size_t indOfX = key.find("x");
    if (indOfX == std::string::npos)
        throw "Неверно введен ключ.";
    std::string nstr = key.substr(0, indOfX);
    std::string mstr = key.substr(indOfX+1, key.size());
    if (!isNumber(nstr) || !isNumber(mstr))
        throw "Неверно введен ключ.";
    
    return std::pair<int, int>(std::stoi(nstr), std::stoi(mstr)); 
}

//RSA

int checkKeyRSA(std::string key)
{
    if (!isNumber(key))
        throw "Неправильно введен ключ.";
    int e = std::stoi(key);
    if (e>216)
        throw "Неправильно введен ключ.";
    for (int i = 2; i<216; i++)
        if (e%i == 0 && 216%i==0)
            throw "Неправильно введен ключ.";
    return e;
}

int modulePow(int a, int x, int p)
{
  // т.к.         c = (a * b) mod m
  // эквивалентно c = (a (mod m) * b (mod m)) mod m
  // Работает алгоритм следующий:
        // Пусть c = 1, n? = 0.
      // Увеличим n? на 1.
      // Установим c ? ( b ? c ) ( mod m ).
      // Если n? < n, возвращаемся к шагу 2. В противном случае, c содержит правильный ответ c ? b n ( mod m ).
  int h = 1;
  a = a % p;
  for (int i = 1; i <= x; i++) {
    h = (static_cast<int64_t>(h) * a) % p;
  }
  return h;
}

void genEuclidAlg(int a, int b, int res[3])
{
  // Обобщенный (расширенный) расширенный алгоритм евклида
  // получаем числа a и b, и массив res, в который запишем результат:
  // на первое место - наибольший общий делитель,
  // на второе место - коэффициент x при a
  // на третье место - коэффициент y при b
  // в выражении ax+by=gcd(a,b)
  int U[3] {a, 1, 0};
  int V[3] {b, 0, 1};
  int T[3] {0};
  
  while (V[0] != 0)
  {
    int q = U[0] / V[0];
    T[0] = U[0] % V[0];
    T[1] = U[1] - q*V[1];
    T[2] = U[2] - q*V[2];
    std::copy(std::begin(V), std::end(V), std::begin(U));
    std::copy(std::begin(T), std::end(T), std::begin(V));
  }
  res[0] = U[0];
  res[1] = U[1];
  res[2] = U[2];
}


int getD(int e, int fN)
{
    int res[3] = {0,0,0};
    genEuclidAlg(fN, e, res);
    int d = res[2];
    if (d<0)
        d+=fN;
    return d;
}

//гронсфельд
int checkKeyGF(std::string key)
{

    if (!isNumber(key))
    {
        throw "Неверно введен ключ (введите число).";
    }
    int nkey = stoi(key);
    if (nkey < 1)
        throw "Неверно введен ключ (должно быть натуральное число)";

    return nkey;
}

std::vector<int> cifGF(int key) {
    std::vector<int> keys_cif;
    int cif;
    for (int i = 0; key > 0; key /= 10) {
        cif = key % 10;
        keys_cif.push_back(cif);
    }
    std::reverse(keys_cif.begin(), keys_cif.end());
    return keys_cif;
}
