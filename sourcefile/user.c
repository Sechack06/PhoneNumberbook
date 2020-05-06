#include "user.h"
#include "file.h"
#include "node.h"
#include "cryptogram.h"
#include "nowtime.h"
#include <time.h>
#include <direct.h>
#include <Windows.h>
#include <Shlwapi.h>
#pragma comment(lib, "Shlwapi.lib")

extern HWND hWndlogin;
extern HWND hWndMain;
extern USER thisuserifm;
extern HINSTANCE g_hInst;

void adduser(USER data)
{
    char trscnuspath[260] = ".\\trscn\\";
    strcat(trscnuspath, data.name);
    data.key = makekey();
    if (PathFileExistsA(data.userdatapath))
    {
        MessageBoxA(hWndlogin, "�̹� �����ϴ� ����� �̸��Դϴ�.", "�̸� ����", MB_OK | MB_ICONINFORMATION);
        return;
    }
    FILE* fp = fopen(data.userdatapath, "wb");
    if (fp == NULL)
    {
        MessageBoxA(hWndlogin, "The user cannot be add", "adderror", MB_OK | MB_ICONERROR);
        return;
    }
    else
    {
        if (!_mkdir(data.userpath) && !_mkdir(trscnuspath))
        {
            data = usermakecryptogram(data);
            int count = 0;
            count = fwrite(&data, sizeof(data), 1, fp);
            if (count < 1)
            {
                MessageBoxA(hWndlogin, "The user cannot be add", "adderror", MB_OK | MB_ICONERROR);
                fclose(fp);
                return;
            }
            else
            {
                MessageBoxA(hWndlogin, "������ ���������� �����Ǿ����ϴ�!!", "����", MB_OK);
                data = userdecryptpsl(data);
                fclose(fp);
            }
        }
        else
        {
            MessageBoxA(hWndlogin, "The user cannot be add", "adderror", MB_OK | MB_ICONERROR);
            fclose(fp);
            return;
        }

        srand((unsigned int)time(NULL));

        char temp[MAX_PATH] = "";
        char temp2[70] = "";
        char temp3[10] = "";
        strcpy(temp, ".\\log\\add\\user\\");
        strcat(temp, _itoa(rand(), temp3, 10));
        strcat(temp, ".log");
        FILE* fplog = fopen(temp, "w");
        if (fplog == NULL)
        {
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
            strcat(temp2, "add userdata");
            fwrite(temp2, strlen(temp2), 1, fplog);
            fclose(fplog);
        }
    }
}
void reviseuser(char oldusername[], USER data)
{
    char temppath[MAX_PATH];
    strcpy(temppath, ".\\data\\user\\userdata\\");
    strcat(temppath, oldusername);
    strcat(temppath, ".usd");
    FILE* fp = fopen(temppath, "wb");
    if (fp == NULL)
    {
        MessageBoxA(hWndlogin, "The user cannot be revise", "readerror", MB_OK | MB_ICONERROR);
        return;
    }
    else
    {
        data = usermakecryptogram(data);
        int count = 0;
        count = fwrite(&data, sizeof(data), 1, fp);
        if (count < 1)
        {
            data = userdecryptpsl(data);
            MessageBoxA(hWndlogin, "The user cannot be revise", "readerror", MB_OK | MB_ICONERROR);
            fclose(fp);
            return;
        }
        else
        {
            if (!_mkdir(data.userpath))
            {
                if (!rename(temppath, data.userdatapath))
                {
                    MessageBoxA(hWndlogin, "The user cannot be revise", "readerror", MB_OK | MB_ICONERROR);
                    fclose(fp);
                    return;
                }
                else
                {
                    char tempuserpath[260] = "";
                    strcpy(tempuserpath, ".\\data\\user\\");
                    strcat(tempuserpath, oldusername);
                    if (!rename(tempuserpath, data.userpath))
                    {
                        MessageBoxA(hWndlogin, "The user cannot be revise", "readerror", MB_OK | MB_ICONERROR);
                        fclose(fp);
                        return;
                    }
                    else
                    {
                        MessageBoxA(hWndlogin, "������ ���������� �����Ǿ����ϴ�!!", "����!", MB_OK);
                        fclose(fp);
                        data = userdecryptpsl(data);
                    }
                }
            }
            else
            {
                MessageBoxA(hWndlogin, "The user cannot be revise", "readerror", MB_OK | MB_ICONERROR);
                fclose(fp);
                return;
            }
        }

        srand((unsigned int)time(NULL));

        char temp[MAX_PATH] = "";
        char temp2[70] = "";
        char temp3[10] = "";
        strcpy(temp, ".\\log\\revise\\user\\");
        strcat(temp, _itoa(rand(), temp3, 10));
        strcat(temp, ".log");
        FILE* fplog = fopen(temp, "w");
        if (fplog == NULL)
        {
            return;
        }
        else
        {
            strcpy(temp2, "oldname=");
            strcat(temp2, oldusername);
            strcat(temp2, " - ");
            strcat(temp2, "name=");
            strcat(temp2, data.name);
            strcat(temp2, " - ");
            strcat(temp2, "time=");
            strcat(temp2, timeretn());
            strcat(temp2, " - action=");
            strcat(temp2, "revise userdata");
            fwrite(temp2, strlen(temp2), 1, fplog);
            fclose(fplog);
        }
    }
}
void removeuser(USER deluser)
{
    char trscnpath[MAX_PATH] = ".\\data\\trscn\\";
    strcat(trscnpath, deluser.name);
    strcat(trscnpath, "\\");

    if (!DeleteFileA(deluser.userdatapath))
    {
        MessageBoxA(hWndlogin, "���� ���� ����", "error", MB_OK | MB_ICONERROR);
        return;
    }
    else
    {
        MessageBoxA(hWndlogin, "������ ���������� �����Ǿ����ϴ�!!", "����", MB_OK);
        srand((unsigned int)time(NULL));

        char temp[MAX_PATH] = "";
        char temp2[70] = "";
        char temp3[10] = "";
        strcpy(temp, ".\\log\\del\\user\\");
        strcat(temp, _itoa(rand(), temp3, 10));
        strcat(temp, ".log");
        FILE* fplog = fopen(temp, "w");
        if (fplog == NULL)
        {
            return;
        }
        else
        {
            strcpy(temp2, "name=");
            strcat(temp2, deluser.name);
            strcat(temp2, " - ");
            strcat(temp2, "time=");
            strcat(temp2, timeretn());
            strcat(temp2, " - action=");
            strcat(temp2, "delete userdata");
            fwrite(temp2, strlen(temp2), 1, fplog);
            fclose(fplog);
        }
    }
}
USER readuserdata(char filename[])
{
    USER data;
    char Path[MAX_PATH];
    strcpy(Path, ".\\data\\user\\userdata\\");
    strcat(Path, filename);

    FILE* fp = fopen(Path, "rb");
    if (fp == NULL)
    {
        MessageBoxA(hWndlogin, "Can`t read userdata", "error", MB_OK | MB_ICONSTOP);
        exit(-1);
        return data;
    }
    else
    {
        int count = 0;
        count = fread(&data, sizeof(data), 1, fp);
        if (count < 1)
        {
            MessageBoxA(hWndlogin, "There is corrupt userdata or userdata in an unsupported format.\nexit program.", "readerror", MB_OK | MB_ICONERROR);
            fclose(fp);
            exit(-1);
            return data;
        }
        else
        {
            data = userdecryptpsl(data);
            fclose(fp);
        }

        return data;
    }
}
USER checklogin(char *id, char *password)
{
    typedef struct _finddata_t FILELIST;
    FILELIST fd;
    intptr_t handle;
    int result = 1;
    USER chkuser;
    memset(&chkuser, 0, sizeof(chkuser));
    srand(time(NULL));
    handle = _findfirst(".\\data\\user\\userdata\\*.usd", &fd);

    if (handle == -1)
    {
        MessageBoxA(hWndlogin, "���� ����� ������ �������� �ʽ��ϴ�. ������ ������ּ���.\n��й�ȣ�� ���� ������ ������� ��й�ȣ �Է�ĭ�� ����νø� �˴ϴ�.", "���� ����", MB_OK | MB_ICONWARNING);
        return chkuser;
    }
    while (result != -1)
    {
        chkuser = readuserdata(fd.name);
        if (!strcmp(chkuser.id, id))
        {
            if (!strcmp(chkuser.password, password))
            {
                char temp[MAX_PATH] = "";
                char temp2[70] = "";
                char temp3[10] = "";
                strcpy(temp, ".\\log\\login\\success\\");
                strcat(temp, _itoa(rand(), temp3, 10));
                strcat(temp, ".log");
                FILE* fplog = fopen(temp, "w");
                if (fplog == NULL)
                {
                    return chkuser;
                }
                else
                {
                    strcat(temp2, "ID=");
                    strcat(temp2, id);
                    strcat(temp2, " - ");
                    strcat(temp2, "time=");
                    strcat(temp2, timeretn());
                    strcat(temp2, " - action=");
                    strcat(temp2, "login");
                    fwrite(temp2, strlen(temp2), 1, fplog);
                    fclose(fplog);
                }
                return chkuser;
            }
        }
        result = _findnext(handle, &fd);
    }
    _findclose(handle);
    MessageBoxA(hWndlogin, "�������� �ʴ� ���̵��̰ų� ��й�ȣ�� Ʋ�Ƚ��ϴ�.\n��й�ȣ�� ���� �����ϰ�� ���̵� �Է��Ͻð� ��й�ȣ �Է¶��� ����μ���.", "�α��� ����", MB_OK | MB_ICONWARNING);
    char temp[MAX_PATH] = "";
    char temp2[70] = "";
    char temp3[10] = "";
    strcpy(temp, ".\\log\\login\\fail\\");
    strcat(temp, _itoa(rand(), temp3, 10));
    strcat(temp, ".log");
    FILE* fplog = fopen(temp, "w");
    if (fplog == NULL)
    {
        return chkuser;
    }
    else
    {
        strcat(temp2, "ID=");
        strcat(temp2, id);
        strcat(temp2, " - ");
        strcat(temp2, "time=");
        strcat(temp2, timeretn());
        strcat(temp2, " - action=");
        strcat(temp2, "login");
        fwrite(temp2, strlen(temp2), 1, fplog);
        fclose(fplog);
    }
    return chkuser;
}
void logout()
{
    int msg = MessageBoxA(hWndMain, "���� �α׾ƿ��Ͻðڽ��ϱ�?", "�α׾ƿ�", MB_OKCANCEL | MB_ICONQUESTION);

    switch (msg)
    {
    case IDOK:
        ZeroMemory(&thisuserifm, sizeof(thisuserifm));
        DestroyWindow(hWndMain);
        hWndlogin = CreateWindowA("PhoneNumberbooklogin", "PhoneNumberbook - 2.0 - login", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 300, 200, 1000, 700, NULL, NULL, g_hInst, NULL);
        break;
    default:
        return;
        break;
    }
}