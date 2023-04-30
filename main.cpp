#include <iostream>
#include <tuple>
#include <string>
#include "userInterface.h"
#include "files.h"
#include "crypt.h"

int main()
{
	const std::string DEFAULT_DECRYPTED_FILENAME = "decrypted.txt";
	const std::string DEFAULT_ENCRYPTED_FILENAME = "encrypted.txt";

	Action action = getAction();
	if (action == Action::crypt)
	{
		writeFile(getUserText("0"), DEFAULT_DECRYPTED_FILENAME);
		Encryption crypt = getEncryption(ENCRYPTIONS);
		std::string encryptedText = encrypt(readFile(DEFAULT_DECRYPTED_FILENAME), crypt);
		writeFile(encryptedText, DEFAULT_ENCRYPTED_FILENAME);
	}
	else if (action == Action::decrypt)
	{
	}

	else if (action == Action::error)
		return -1;
}

