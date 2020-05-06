#include "node.h"

PERSONLIST* head;
PERSONLIST* tail;
PERSONLIST* find;
PERSONLIST* Temp;
extern HWND hlist;
extern HWND hWndMain;

PERSONLIST* addnodedata(PERSONLIST *target, PERSONLIST add)
{
	PERSONLIST* newNode = (PERSONLIST*)malloc(sizeof(PERSONLIST));
	strcpy(newNode->Path, add.Path);
	strcpy(newNode->FileName, add.FileName);
	strcpy(newNode->name, add.name);
	memcpy(newNode->phonenumber, add.phonenumber, sizeof(char[3][6]));
	strcpy(newNode->email, add.email);
	strcpy(newNode->Mdomain, add.Mdomain);
	strcpy(newNode->homeadress, add.homeadress);
	strcpy(newNode->etc, add.etc);
	if (target == NULL)
	{
		head = newNode;
		newNode->next = NULL;
		return newNode;
	}
	else if (target->next == NULL)
	{
		tail = newNode;
		target->next = newNode;
		newNode->next = NULL;
		return newNode;
	}
	else
	{
		newNode->next = target->next;
		target->next = newNode;
		return newNode;
	}
}
PERSONLIST* findnode(char name[50])
{
	Temp = head;
	while (Temp != NULL)
	{
		if (!strcmp(Temp->name, name))
		{
			find = Temp;
			Temp = head;

			return find;
		}
		else
		{
			Temp = Temp->next;
		}
	}
	Temp = head;
	return NULL;
}
int serchdata(char keyword[50])
{
	Temp = head;
	int i = 0;
	while (Temp != NULL)
	{
		if (strstr(Temp->name, keyword))
		{
			SendMessageA(hlist, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)Temp->name);
			i++;
		}
		Temp = Temp->next;
	}
	Temp = NULL;
	return i;
}
void freenodes()
{
	Temp = head;      // 연결 리스트 순회용 포인터에 첫 번째 노드의 주소 저장
	while (Temp != NULL)    // 포인터가 NULL이 아닐 때 계속 반복
	{
		PERSONLIST* next = Temp->next; // 현재 노드의 다음 노드 주소를 임시로 저장
		free(Temp);        // 현재 노드 메모리 해제
		Temp = next;       // 포인터에 다음 노드의 주소 저장
	}
}