#pragma once
#include "node.h"

#pragma pack(push, 1)
typedef struct _USER
{
	char userpath[260];
	char userdatapath[260];
	char name[50];
	char id[35];
	char password[35];
	int key;
}USER;
#pragma pack(pop)

void adduser(USER data);
void removeuser(USER deluser);
void reviseuser(char oldusername[], USER data);
USER checklogin(char *id, char *password);
USER readuserdata(char filename[]);
void logout();