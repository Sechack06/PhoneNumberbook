#pragma once
#include "node.h"

PERSONLIST readfile(char FileName[60]);
void writefile(PERSONLIST data);
void loaddata(hWnd);
void revisefile(char oldFileName[60], PERSONLIST data);
void removedata(char FileName[]);