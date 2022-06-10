#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#define MAX 256
#define NAME 1
#define DECIMAL 10
#define StructNameSize 35

typedef struct StudentCourseGrade
{
	char courseName[35];
	int grade;
}StudentCourseGrade;

typedef struct Student
{
	char name[35];
	StudentCourseGrade* grades; //dynamic array of courses
	int numberOfCourses;
}Student;

//Part A
void countStudentsAndCourses(const char* fileName, int** coursesPerStudent, int* numberOfStudents);
int countPipes(const char* lineBuffer, int maxCount);
char*** makeStudentArrayFromFile(const char* fileName, int** coursesPerStudent, int* numberOfStudents);
void printStudentArray(const char* const* const* students, const int* coursesPerStudent, int numberOfStudents);
void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor);
void studentsToFile(char*** students, int* coursesPerStudent, int numberOfStudents);
void printStudentStruct(Student* studentsStruct, int numberOfStudents);

//Part B
Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents);
void writeToBinFile(const char* fileName, Student* students, int numberOfStudents);
Student* readFromBinFile(const char* fileName);

int main()
{
	//Part A
	int* coursesPerStudent = NULL;
	int numberOfStudents = 0;

	//print countPipes
	/*printf(" %d\n", countPipes("ab|cd|ef", 8));
	printf(" %d\n", countPipes("abcde", 5));
	printf(" %d\n", countPipes("abcdef", -2));*/

	// print countStudentsAndCourses
	/*countStudentsAndCourses("studentList.txt", &coursesPerStudent, &numberOfStudents);
	printf("number of students is: %d\n", numberOfStudents);
	printf("the courses per students is:\n");
	for (int i = 0; i < numberOfStudents; i++)
	{
		printf(" %d, ", coursesPerStudent[i]);
	}*/

	char*** students = makeStudentArrayFromFile("studentList.txt", &coursesPerStudent, &numberOfStudents);
	printStudentArray(students, coursesPerStudent, numberOfStudents);
	factorGivenCourse(students, coursesPerStudent, numberOfStudents, "Advanced Topics in C", +5);
	printStudentArray(students, coursesPerStudent, numberOfStudents);
	//studentsToFile(students, coursesPerStudent, numberOfStudents); //this frees all memory. Part B fails if this line runs. uncomment for testing (and comment out Part B)

	//Part B
	Student* transformedStudents = transformStudentArray(students, coursesPerStudent, numberOfStudents);
	printStudentStruct(transformedStudents, numberOfStudents);
	writeToBinFile("students.bin", transformedStudents, numberOfStudents);
	Student* testReadStudents = readFromBinFile("students.bin");
	printStudentStruct(testReadStudents, numberOfStudents);

	//add code to free all arrays of struct Student


	/*_CrtDumpMemoryLeaks();*/ //uncomment this block to check for heap memory allocation leaks.
	// Read https://docs.microsoft.com/en-us/visualstudio/debugger/finding-memory-leaks-using-the-crt-library?view=vs-2019

	return 0;
}

void countStudentsAndCourses(const char* fileName, int** coursesPerStudent, int* numberOfStudents)
{
	char buffer[MAX];
	FILE* fp = fopen(fileName, "r");
	if (fp == NULL)
	{
		printf("can't open file1\n");
		exit(1);
	}
	while (fgets(buffer, MAX, fp) != NULL)// count number of students
		(*numberOfStudents) += 1;
	rewind(fp);
	*coursesPerStudent = (int*)malloc(sizeof(int));
	if (*coursesPerStudent == NULL)
	{
		printf("allocation failed\n");
		exit(1);
	}
	for (int i = 0; i < (*numberOfStudents); i++)
	{
		fgets(buffer, MAX, fp);
		(*coursesPerStudent)[i] = countPipes(buffer, MAX);
	}
	int closeFile = fclose(fp);
	if (closeFile == EOF)
	{
		printf("problem closing file\n");
		exit(1);
	}
}

int countPipes(const char* lineBuffer, int maxCount)
{
	int res = 0;
	if (*(lineBuffer) == NULL)
		return -1;
	if (maxCount <= 0)
		return 0;
	for (int i = 0; i < maxCount; i++)
	{
		if (lineBuffer[i] == '\0')
			return res;
		if (lineBuffer[i] == '|')
			res++;
	}
	return res;
}

char*** makeStudentArrayFromFile(const char* fileName, int** coursesPerStudent, int* numberOfStudents)
{
	countStudentsAndCourses(fileName, coursesPerStudent, numberOfStudents);
	char c;
	char buffer[MAX];
	int j = 0, bufferSize = 0;
	FILE* fp = fopen(fileName, "rt");
	if (fp == NULL)
	{
		printf("can't open file2\n");
		exit(1);
	}
	//check file size
	fseek(fp, 0, SEEK_END);
	int end = ftell(fp);
	rewind(fp);
	char*** students = (char***)malloc(sizeof(char**) * (*numberOfStudents + 1));
	if (!students) { printf("memory allocation error"); exit(1); }
	for (int i = 0; i < (*numberOfStudents); i++)// for evrey student
	{
		int sizeOfStudent = (*coursesPerStudent)[i] * 2 + NAME;
		*(students + i) = (char**)malloc(sizeof(char*) * (sizeOfStudent + 1));//allocatin of array for a student
		if (!*(students + i)) { printf("memory allocation error"); exit(1); }
		for (int k = 0; k < sizeOfStudent; k++)//for every string of a student
		{
			c = fgetc(fp);
			while (c != '|' && c != ',')
			{
				buffer[j++] = c;
				bufferSize++;
				if (ftell(fp) == end)
					break;
				c = fgetc(fp);
				if (c == '\n')
					break;
			}
			buffer[j] = '\0';
			students[i][k] = (char*)malloc(sizeof(char) * bufferSize + 1);
			if (!students[i][k]) { printf("memory allocation error"); exit(1); }
			strcpy(students[i][k], buffer);
			j = 0;
			*buffer = '\0';
			bufferSize = 0;
		}
	}
	return students;
}

void factorGivenCourse(char** const* students, const int* coursesPerStudent, int numberOfStudents, const char* courseName, int factor)
{
	if (factor > 20 || factor < -20)
	{
		printf("factor is not in range");
		return;
	}
	for (int i = 0; i < numberOfStudents; i++)//for every student
	{
		int studentSize = (coursesPerStudent[i] * 2) + NAME;
		for (int j = 1; j < studentSize - 1; j++)//for every cours
		{
			if (strcmp(students[i][j], courseName) == 0)
			{
				int grade = atoi(students[i][j + 1]);
				grade += factor;
				if (grade > 100)
					grade = 100;
				_itoa(grade, students[i][j], DECIMAL);
			}
		}
	}
}

void printStudentArray(const char* const* const* students, const int* coursesPerStudent, int numberOfStudents)
{
	for (int i = 0; i < numberOfStudents; i++)
	{
		printf("name: %s\n*********\n", students[i][0]);
		for (int j = 1; j <= 2 * coursesPerStudent[i]; j += 2)
		{
			printf("course: %s\n", students[i][j]);
			printf("grade: %s\n", students[i][j + 1]);
		}
		printf("\n");
	}
}

void freeArr(char*** students, int* coursesPerStudent, int numberOfStudents)
{
	for (int i = 0; i < numberOfStudents; i++)
	{
		int studentSize = (coursesPerStudent[i] * 2) + NAME;
		for (int j = 0; j < studentSize; j++)
		{
			free(students[i][j]);
		}
		free(students[i]);
	}
	free(students);
}

void studentsToFile(char*** students, int* coursesPerStudent, int numberOfStudents)
{
	FILE* fp = fopen("studentList.txt", "w+");
	assert(fp);
	for (int i = 0; i < numberOfStudents; i++)//for every student
	{
		fputs(*(students[i]), fp);
		int studentSize = (coursesPerStudent[i] * 2) + NAME;
		for (int j = 1; j < studentSize; j += 2)
		{
			fputc('|', fp);
			fputs(students[i][j], fp);
			fputc(',', fp);
			fputs(students[i][j + 1], fp);
		}
		fputc('\n', fp);
	}
	if (fclose(fp) == EOF) { printf("problem closing file\n"); exit(1); }
	freeArr(students, coursesPerStudent, numberOfStudents);
}

void writeToBinFile(const char* fileName, Student* students, int numberOfStudents)
{
	FILE* fileptr = fopen(fileName, "wb");
	if (!fileptr) { printf("can't open file\n"); exit(1); }
	fwrite(&numberOfStudents, sizeof(int), 1, fileptr);
	for (int i = 0; i < numberOfStudents; i++)
	{
		fwrite(students[i].name, sizeof(char) * StructNameSize, 1, fileptr);
		fwrite(&students[i].numberOfCourses, sizeof(int), 1, fileptr);
		for (int j = 0; j < students[i].numberOfCourses; j++)
		{
			fwrite(students[i].grades[j].courseName, sizeof(char) * StructNameSize, 1, fileptr);
			fwrite(&students[i].grades[j].grade, sizeof(int), 1, fileptr);
		}
	}
	assert(fclose(fileptr) == 0);
}

Student* readFromBinFile(const char* fileName)
{
	FILE* fileptr = fopen(fileName, "rb");
	if (!fileptr) { printf("can't open file\n"); exit(1); }
	int numberOfStudents;
	fread(&numberOfStudents, sizeof(int), 1, fileptr);
	Student* studentarr = (Student*)malloc(sizeof(Student) * numberOfStudents);
	if (!studentarr) { printf("allocation failed\n"); exit(1); }
	for (int i = 0; i < numberOfStudents; i++)
	{
		fread(studentarr[i].name, sizeof(char) * StructNameSize, 1, fileptr);
		fread(&studentarr[i].numberOfCourses, sizeof(int), 1, fileptr);
		studentarr[i].grades = (StudentCourseGrade*)malloc(studentarr[i].numberOfCourses * sizeof(StudentCourseGrade));
		if (!studentarr[i].grades) { printf("allocation failed\n"); exit(1); }
		for (int j = 0; j < studentarr[i].numberOfCourses; j++)
		{
			fread(studentarr[i].grades[j].courseName, sizeof(char) * StructNameSize, 1, fileptr);
			fread(&studentarr[i].grades[j].grade, sizeof(int), 1, fileptr);
		}
	}
	if (fclose(fileptr) == EOF) { printf("problem closing file\n"); exit(1); }
	return studentarr;
}

Student* transformStudentArray(char*** students, const int* coursesPerStudent, int numberOfStudents)
{
	Student* arrStudent = (Student*)malloc(numberOfStudents * sizeof(Student));
	if (!arrStudent) { printf("allocation failed\n"); exit(1); }
	for (int i = 0; i < numberOfStudents; i++)// for every student
	{
		int k = 0;
		int studentSize = (coursesPerStudent[i] * 2) + NAME;
		arrStudent[i].numberOfCourses = coursesPerStudent[i];
		strcpy(arrStudent[i].name, students[i][0]);
		arrStudent[i].grades = (StudentCourseGrade*)malloc(coursesPerStudent[i] * sizeof(StudentCourseGrade));
		if (!arrStudent[i].grades) { printf("allocation failed\n"); exit(1); }
		for (int j = 1; j < studentSize; j += 2)// for every cours
		{
			int grade = atoi(students[i][j + 1]);
			arrStudent[i].grades[k].grade = grade;
			strcpy(arrStudent[i].grades[k].courseName, students[i][j]);
			k++;
		}
	}
	return arrStudent;
}

void printStudentStruct(Student* studentsStruct, int numberOfStudents)
{
	printf("the student struct is:\n********\n");
	for (int i = 0; i < numberOfStudents; i++)
	{
		printf("name of student: %s\n", studentsStruct[i].name);
		for (int j = 0; j < studentsStruct[i].numberOfCourses; j++)
		{
			printf("cours name: %s\n", studentsStruct[i].grades[j].courseName);
			printf("grade: %d\n", studentsStruct[i].grades[j].grade);
		}
		printf("**********\n\n");
	}
}