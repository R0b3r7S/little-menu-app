#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "data-type.h"

int Menu(char* const);
void CreateFile(const char* const);
void AddStudent(const char* const);
void* ReadStudents(const char* const);
void PrintStudents(const STUDENT* const);
void* SearchForStudent(STUDENT* const);
void DeleteStudent(STUDENT** const, STUDENT* const, const char* const);
void RenameFile(char*);
int DeleteFile(const char*);
int ExitProgram(STUDENT*);

#endif //FUNCTIONS_H