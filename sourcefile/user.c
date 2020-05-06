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
        MessageBoxA(hWndlogin, "이미 존재하는 사용자 이름입니다.", "이름 존재", MB_OK | MB_ICONINFORMATION);
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
                MessageBoxA(hWndlogin, "계정이 정상적으로 생성되었습니다!!", "성공", MB_OK);
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
                        MessageBoxA(hWndlogin, "계정이 정상적으로 수정되었습니다!!", "성공!", MB_OK);
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
        MessageBoxA(hWndlogin, "계정 삭제 실패", "error", MB_OK | MB_ICONERROR);
        return;
    }
    else
    {
        MessageBoxA(hWndlogin, "계정이 정상적으로 삭제되었습니다!!", "성공", MB_OK);
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
        MessageBoxA(hWndlogin, "현재 사용자 계정이 존재하지 않습니다. 계정을 만들어주세요.\n비밀번호가 없는 계정을 만드려면 비밀번호 입력칸을 비워두시면 됩니다.", "계정 없음", MB_OK | MB_ICONWARNING);
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
    MessageBoxA(hWndlogin, "존재하지 않는 아이디이거나 비밀번호가 틀렸습니다.\n비밀번호가 없는 계정일경우 아이디만 입력하시고 비밀번호 입력란은 비워두세요.", "로그인 실패", MB_OK | MB_ICONWARNING);
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
    int msg = MessageBoxA(hWndMain, "정말 로그아웃하시겠습니까?", "로그아웃", MB_OKCANCEL | MB_ICONQUESTION);

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