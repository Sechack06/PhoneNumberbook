#pragma once
#include "node.h"
#include "user.h"
PERSONLIST makecryptogram(PERSONLIST data);
char* encoding(char string[]);
PERSONLIST decryptpsl(PERSONLIST data);
USER usermakecryptogram(USER data);
char* userencoding(char string[], int key);
USER userdecryptpsl(USER data);
int makekey();