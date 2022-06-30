#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include "functions.h"

static void InputFileName(char* const fileName) {

	printf("Unesite ime datoteke s kojom se treba raditi!\n");
	getchar();
	scanf("%19[^\n]", fileName);
}

int main(void) {

	int condition = 1;
	char fileName[20] = { '\0' };
	
	InputFileName(fileName);
	CreateFile(fileName);

	while (condition) {
		condition = Menu(fileName);
		if (condition == 7) {
			InputFileName(fileName);
			CreateFile(fileName);
		}
	}

	printf("Zavrsetak programa!\n");

	return 0;
}