#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include "functions.h"

int Menu(char* const fileName) {

	printf("====================");
	printf("Odaberite jednu od ponudenih opcija:");
	printf("====================\n");
	printf("\t\t\tOpcija 1: dodavanje studenta!\n");
	printf("\t\t\tOpcija 2: citavanje studenata!\n");
	printf("\t\t\tOpcija 3: ispisivanje studenata!\n");
	printf("\t\t\tOpcija 4: pretrazivanje studenta!\n");
	printf("\t\t\tOpcija 5: brisanje studenta!\n");
	printf("\t\t\tOpcija 6: promjena imena datoteci!\n");
	printf("\t\t\tOpcija 7: brisanje datoteke!\n");
	printf("\t\t\tOpcija 8: izlaz iz programa!\n");
	printf("============================================================================\n");

	int condition = 0;
	static STUDENT* studentArray = NULL;
	static STUDENT* foundStudent = NULL;

	scanf("%d", &condition);

	switch (condition) {
	case 1:
		AddStudent(fileName);
		break;
	case 2:
		if (studentArray != NULL) {
			free(studentArray);
			studentArray = NULL;
		}
		studentArray = (STUDENT*)ReadStudents(fileName);
		//if (studentArray == NULL) {
		//	exit(EXIT_FAILURE);
		//}
		break;
	case 3:
		PrintStudents(studentArray);
		break;
	case 4:
		foundStudent = (STUDENT*)SearchForStudent(studentArray);
		break;
	case 5:
		DeleteStudent(&foundStudent, studentArray, fileName);
		if (studentArray != NULL) {
			free(studentArray);
			studentArray = NULL;
		}
		break;
	case 6:
		RenameFile(fileName);
		break;
	case 7:
		condition = DeleteFile(fileName);
		break;
	case 8:
		condition = ExitProgram(studentArray);
		break;
	default:
		condition = 0;
	}
	return condition;
}