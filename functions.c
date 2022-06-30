#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "data-type.h"

static int numberOfStudents = 0;

void CreateFile(const char* const fileName) {

	FILE* pF = fopen(fileName, "rb");
	if (pF == NULL) {

		pF = fopen(fileName, "wb");
		if (pF == NULL) {
			perror("Creating file");
			exit(EXIT_FAILURE);
		}

		fwrite(&numberOfStudents, sizeof(int), 1, pF);
	}
	else {
		printf("Datoteka %s postoji na disku\n", fileName);
	}

	fclose(pF);
}

void AddStudent(const char* const fileName) {

	FILE* pF = fopen(fileName, "rb+");
	if (pF == NULL) {
		perror("Reading and writing to file");
		exit(EXIT_FAILURE);
	}

	fread(&numberOfStudents, sizeof(int), 1, pF);
	//printf("brojStudenata: %d\n", numberOfStudents);

	STUDENT temp = { 0 };

	temp.id = numberOfStudents;

	getchar();
	printf("Unesite ime studenta!\n");
	scanf("%19[^\n]", temp.firtsName);
	printf("Unesite prezime studenta!\n");
	getchar();
	scanf("%19[^\n]", temp.lastName);
	fseek(pF, sizeof(STUDENT) * numberOfStudents, SEEK_CUR);
	fwrite(&temp, sizeof(STUDENT), 1, pF);
	rewind(pF);

	numberOfStudents++;

	fwrite(&numberOfStudents, sizeof(int), 1, pF);
	fclose(pF);
}

void* ReadStudents(const char* const fileName) {

	FILE* pF = fopen(fileName, "rb");
	if (pF == NULL) {
		perror("Reading file");
		return NULL;
		//exit(EXIT_FAILURE);
	}

	fread(&numberOfStudents, sizeof(int), 1, pF);
	printf("Broj studenata: %d\n", numberOfStudents);

	STUDENT* studentArray = NULL;

	if (numberOfStudents != 0) {

		studentArray = (STUDENT*)calloc(numberOfStudents, sizeof(STUDENT));
		if (studentArray == NULL) {
			perror("Allocating student array");
			return NULL;
			//exit(EXIT_FAILURE);
		}

		fread(studentArray, sizeof(STUDENT), numberOfStudents, pF);
	}
	else {
		fprintf(stderr, "Nema studenata u datoteci!\n");

		return NULL;
	}

	fclose(pF);

	return studentArray;
}

void PrintStudents(const STUDENT* const studentArray) {

	if (studentArray == NULL || numberOfStudents == 0) {
		fprintf(stderr, "Polje studenata je prazno!\n");

		return;
	}

	static int localStuNumb = 0;
	int i;

	if (localStuNumb == 0) {
		memcpy(&localStuNumb, &numberOfStudents, sizeof(int));
	}

	if (localStuNumb < numberOfStudents) {

		fprintf(stderr, "Azurirati sve studente!\n");
		memcpy(&localStuNumb, &numberOfStudents, sizeof(int));
	}
	else {
		for (i = 0; i < numberOfStudents; i++)
		{
			printf("Student broj %d\tID: %d\time: %s\tprezime: %s\n",
				i + 1,
				(studentArray + i)->id,
				(studentArray + i)->firtsName,
				(studentArray + i)->lastName);
		}
	}
}

void* SearchForStudent(STUDENT* const studentArray) {

	if (studentArray == NULL) {
		fprintf(stderr, "Polje studenata je prazno!\n");

		return NULL;
	}

	int i;
	char requiredName[20] = { '\0' };

	printf("Unesite trazeni kriterij za pronalazak studenta.\n");
	getchar();
	scanf("%19[^\n]", requiredName);

	for (i = 0; i < numberOfStudents; i++)
	{
		if (!strcmp(requiredName, (studentArray + i)->firtsName)) {

			printf("Student je pronaden!\n");

			return (studentArray + i);
		}
	}

	return NULL;
}

void RenameFile(char* oldFileName) {

	char newFileName[20] = { '\0' };

	printf("Unesite novi naziv datoteke!\n");
	getchar();
	scanf("%19[^\n]", newFileName);
	printf("Zelite li uistinu promijeniti ime datoteci?\n");
	printf("Utipkajte \"da\" ako uistinu zelite promijeniti ime datoteke u suprotno utipkajte\
\"ne\"!\n");

	char confirm[3] = { '\0' };

	scanf("%2s", confirm);

	if (!strcmp("da", confirm)) {

		int status = rename(oldFileName, newFileName);

		status == 0 ? printf("Uspjesno promijenjeno ime datoteci!\n") :
			fprintf(stderr, "Nemogucnost promjene imena datoteci zbog: %s!\n", strerror(errno));

		if (status == 0) {
			strcpy(oldFileName, newFileName);
		}
	}
}

void DeleteStudent(STUDENT** const foundStudent, STUDENT* const studentArray, const char* const fileName) {

	if (studentArray == NULL) {
		fprintf(stderr, "Polje studenata je prazno!\n");

		return;
	}

	if (*foundStudent == NULL) {
		fprintf(stderr, "Nema studenta za obrisati!\n");

		return;
	}

	FILE* pF = fopen(fileName, "wb");
	if (pF == NULL) {
		perror("Creating file");
		exit(EXIT_FAILURE);
	}

	fseek(pF, sizeof(int), SEEK_SET);

	int i;
	int newStudentCounter = 0;

	for (i = 0; i < numberOfStudents; i++)
	{
		if (*foundStudent != (studentArray + i)) {
			(studentArray + i)->id = newStudentCounter;
			fwrite((studentArray + i), sizeof(STUDENT), 1, pF);
			newStudentCounter++;
		}
	}

	rewind(pF);
	fwrite(&newStudentCounter, sizeof(int), 1, pF);
	fclose(pF);
	printf("Student je uspjesno obrisan!\n");

	*foundStudent = NULL;
}

int DeleteFile(const char* fileName) {

	printf("Zelite li uistinu obrisati datoteku %s?\n", fileName);
	printf("Utipkajte \"da\" ako uistinu zelite obrisati datoteku u suprotno utipkajte\
\"ne\"!\n");

	char confirm[3] = { '\0' };

	scanf("%2s", confirm);

	if (!strcmp("da", confirm)) {

		int status = remove(fileName);

		status == 0 ? printf("Uspjesno obrisana datoteka %s!\n", fileName) :
			fprintf(stderr, "Neuspjesno brisanje datoteke %s zbog: %s!\n", fileName, strerror(errno));

		if (status == 0) {
			numberOfStudents = 0;

			return 7;
		}
	}

	return 1;
}

int ExitProgram(STUDENT* studentArray) {

	free(studentArray);

	return 0;
}