#include "node.h"
#include "file.h"
#include "main.h"
#include "cryptogram.h"
#include "nowtime.h"
#include <time.h>
#include <stdlib.h>
#include <Shlobj.h>
#pragma comment(lib, "Shell32.lib")

extern HWND hlist;
extern HWND hWndMain;
extern PERSONLIST* head;
extern PERSONLIST* tail;
extern PERSONLIST data;
extern USER thisuserifm;
PERSONLIST* temp;

void loaddata()
{
    //데이터 파일 이름을 추출하고 파일을 읽는다.
    typedef struct _finddata_t FILELIST;
    FILELIST fd;
    intptr_t handle;
    int result = 1;
    char datapath[260] = "";
    strcpy(datapath, thisuserifm.userpath);
    strcat(datapath, "\\");
    strcat(datapath, "*.pdt");
    handle = _findfirst(datapath, &fd);
    listboxremove();
    temp = NULL;

    if (handle == -1)
    {
        return;
    }
    while (result != -1)
    {
            data = readfile(fd.name);
            temp = addnodedata(temp, data);
            SendMessageA(hlist, LB_ADDSTRING, (WPARAM)NULL, (LPARAM)data.name);
            result = _findnext(handle, &fd);
    }
    _findclose(handle);
}
void writefile(PERSONLIST data)
{
    char Path[MAX_PATH];
    strcpy(Path, thisuserifm.userpath);
    strcat(Path, "\\");
    strcat(Path, data.FileName);
    strcpy(data.Path, Path);

    //구조체를 파일에 쓴다.
    FILE* fp = fopen(Path, "wb");
    if (fp == NULL)
    {
        MessageBoxA(hWndMain, "Can`t write data", "error", MB_OK | MB_ICONSTOP);
        return;
    }
    else
    {
        data = makecryptogram(data);
        int count = 0;
        count = fwrite(&data, sizeof(data), 1, fp);
        if (count < 1)
        {
            data = decryptpsl(data);
            MessageBoxA(hWndMain, "The data cannot be saved.\nThe data is stored blank.", "readerror", MB_OK | MB_ICONERROR);
            freenodes();
            fclose(fp);
            return;
        }
        else
        {
            MessageBoxA(hWndMain, "정상적으로 저장되었습니다!!", "성공!", MB_OK);
            fclose(fp);
            data = decryptpsl(data);
        }

        srand((unsigned int)time(NULL));

        char temp[MAX_PATH] = "";
        char temp2[300] = "";
        char temp3[10] = "";
        strcpy(temp, ".\\log\\add\\data\\");
        strcat(temp, _itoa(rand(), temp3, 10));
        strcat(temp, ".log");
        FILE* fplog = fopen(temp, "w");
        if (fplog == NULL)
        {
            freenodes();
            loaddata();
            return;
        }
        else
        {
            strcpy(temp2, "name=");
            strcat(temp2, data.name);
            strcat(temp2, " - ");
            strcat(temp2, "time=");
            strcat(temp2, timeretn());
            strcat(temp2, " - action=");
            strcat(temp2, "add persondata");
            fwrite(temp2, strlen(temp2), 1, fplog);
            fclose(fplog);
        }
        freenodes();
        loaddata();
    }
}
PERSONLIST readfile(char FileName[60])
{
    char Path[MAX_PATH];
    strcpy(Path, thisuserifm.userpath);
    strcat(Path, "\\");
    strcat(Path, FileName);
    //구조체를 파일에서 읽는다.
    FILE* fp = fopen(Path, "rb");
    if (fp == NULL)
    {
        MessageBoxA(hWndMain, "Can`t read data", "error", MB_OK | MB_ICONSTOP);
        freenodes();
        exit(-1);
        return data;
    }
    else
    {
        int count = 0;
        count = fread(&data, sizeof(data), 1, fp);
        if (count < 1)
        {
            MessageBoxA(hWndMain, "There is corrupt data or data in an unsupported format.\nexit program.", "readerror", MB_OK | MB_ICONERROR);
            freenodes();
            fclose(fp);
            exit(-1);
            return data;
        }
        else
        {
            data = decryptpsl(data);
            fclose(fp);
        }

        return data;
    }
}
void revisefile(char oldFileName[60], PERSONLIST data)
{
    char oldPath[MAX_PATH] = { 0 };
    char newPath[MAX_PATH] = { 0 };
    strcpy(oldPath, thisuserifm.userpath);
    strcat(oldPath, "\\");
    strcat(oldPath, oldFileName);
    strcpy(newPath, thisuserifm.userpath);
    strcat(newPath, "\\");
    strcat(newPath, data.FileName);

    FILE* fp = fopen(oldPath, "wb");
    if (fp == NULL)
    {
        MessageBoxA(hWndMain, "Can`t revise data", "error", MB_OK | MB_ICONSTOP);
        return;
    }
    else
    {
        data = makecryptogram(data);
        int count = 0;
        count = fwrite(&data, sizeof(data), 1, fp);
        if (count < 1)
        {
            MessageBoxA(hWndMain, "The data cannot be saved.\nThe data is stored blank.", "readerror", MB_OK | MB_ICONERROR);
            fclose(fp);
            freenodes();
            loaddata();
            return;
        }
        else
        {
            fclose(fp);
            if (rename(oldPath, newPath) != 0)
            {
                MessageBoxA(hWndMain, "Can`t revise name", "error", MB_OK | MB_ICONSTOP);
                return;
            }
            MessageBoxA(hWndMain, "정상적으로 수정되었습니다!!", "성공!", MB_OK);
            data = decryptpsl(data);
        }

        srand((unsigned int)time(NULL));

        char temp[MAX_PATH] = "";
        char temp2[300] = "";
        char temp3[10] = "";
        strcpy(temp, ".\\log\\revise\\data\\");
        strcat(temp, _itoa(rand(), temp3, 10));
        strcat(temp, ".log");
        FILE* fplog = fopen(temp, "w");
        if (fplog == NULL)
        {
            return;
        }
        else
        {
            strcpy(temp2, "oldFilename=");
            strcat(temp2, oldFileName);
            strcat(temp2, " - ");
            strcat(temp2, "name=");
            strcat(temp2, data.name);
            strcat(temp2, " - ");
            strcat(temp2, "time=");
            strcat(temp2, timeretn());
            strcat(temp2, " - action=");
            strcat(temp2, "revise persondata");
            fwrite(temp2, strlen(temp2), 1, fplog);
            fclose(fplog);
        }
        freenodes();
        loaddata();
    }
}
void removedata(char FileName[])
{
    char Path[260];
    strcpy(Path, thisuserifm.userpath);
    strcat(Path, "\\");
    strcat(Path, FileName);
    if (DeleteFileA(Path) == 0)
    {
        MessageBoxA(hWndMain, "연락처를 삭제하는데 실패했습니다.", "error", MB_OK | MB_ICONERROR);
        return;
    }
    else
    {
        MessageBoxA(hWndMain, "연락처를 삭제하는데 성공했습니다!!", "성공", MB_OK);
        srand((unsigned int)time(NULL));

        char temp[260] = "";
        char temp2[300] = "";
        char temp3[10] = "";
        strcpy(temp, ".\\log\\del\\data\\");
        strcat(temp, _itoa(rand(), temp3, 10));
        strcat(temp, ".log");
        FILE* fplog = fopen(temp, "w");
        if (fplog == NULL)
        {
            return;
        }
        else
        {
            strcpy(temp2, "delfilename=");
            strcat(temp2, FileName);
            strcat(temp2, " - ");
            strcat(temp2, "time=");
            strcat(temp2, timeretn());
            strcat(temp2, " - action=");
            strcat(temp2, "delete persondata");
            fwrite(temp2, strlen(temp2), 1, fplog);
            fclose(fplog);
        }
    }
}