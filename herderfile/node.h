#pragma once
#define _CRT_SECURE_NO_WARNINGS

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <Windows.h>
#include <io.h>
#include <conio.h>
#include <stdbool.h>

#pragma pack(push, 1)
typedef struct _PERSONLIST
{
	char Path[260];
	char FileName[60];
	char name[50];
	char phonenumber[3][6];
	char email[50];
	char Mdomain[15];
	char homeadress[100];
	char etc[1000];
	struct _PERSONLIST* next;
}PERSONLIST;
#pragma pack(pop)

PERSONLIST* addnodedata(PERSONLIST* target, PERSONLIST add);
PERSONLIST* findnode(char name[50]);
int serchdata(char keyword[50]);
void freenodes();