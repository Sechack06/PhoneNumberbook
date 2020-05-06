#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <Windows.h>
#include <stdbool.h>
#include <strsafe.h>
#include "resource.h"
#include "node.h"
#include "windowhandle.h"
#include "file.h"
#include "main.h"
#include "user.h"
#include "cryptogram.h"

HWND hWndMain;
HWND hWndlogin;
HINSTANCE g_hInst;
MSG msg;
WNDCLASSA WndClass;
WNDCLASSA WndClassadd;
WNDCLASSA WndClassRevise;
WNDCLASSA WndClassSee;
WNDCLASSA WndClassLogin;
WNDCLASSA WndClassAdduser;
HWND hedit;
HWND hlist;
PAINTSTRUCT ps;
HWND hPhoneNumber[3];
HWND hMail;
HWND hName;
HWND hMdomain;
HWND HhomeAdress;
HWND hetc;
HWND hidedit;
HWND hpasswordedit;
HWND haddName;
HWND hID;
HWND hPassword;
HWND hCheckPassword;
HWND hTrscnlist;
char str[128];
char MailDomain[8][15] = { "gmail.com","naver.com","daum.net","yahoo.com","msn.com", "icloud.com", "outlook.com", "live.com" };
char findbuffer[50];
int msgboxreturn;
PERSONLIST data;
PERSONLIST* datalink;
USER thisuserifm;
USER adduserifm;


int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
    memset(findbuffer, 0, sizeof(findbuffer)); //�˻� ���� �ʱ�ȭ
    memset(&data, 0, sizeof(data)); //����ó ���� ����ü �ʱ�ȭ
    HBRUSH Brush = CreateSolidBrush(RGB(0, 150, 230)); //���� ����

    //â ���� �Ҵ�
    WndClass.lpszClassName = "PhoneNumberbookwindow";
    WndClass.hInstance = hInstance;
    WndClass.lpfnWndProc = WinProc;
    WndClass.hbrBackground = Brush;
    WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    WndClass.cbClsExtra = 0;
    WndClass.cbWndExtra = 0;
    WndClass.lpszMenuName = NULL;
    WndClassadd.lpszClassName = "PhoneNumberbookadd";
    WndClassadd.hInstance = hInstance;
    WndClassadd.lpfnWndProc = addProc;
    WndClassadd.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    WndClassadd.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClassadd.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    WndClassadd.cbClsExtra = 0;
    WndClassadd.cbWndExtra = 0;
    WndClassadd.lpszMenuName = NULL;
    WndClassRevise.lpszClassName = "PhoneNumberbookrevise";
    WndClassRevise.hInstance = hInstance;
    WndClassRevise.lpfnWndProc = reviseProc;
    WndClassRevise.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    WndClassRevise.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClassRevise.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    WndClassRevise.cbClsExtra = 0;
    WndClassRevise.cbWndExtra = 0;
    WndClassRevise.lpszMenuName = NULL;
    WndClassSee.lpszClassName = "PhoneNumberbookSee";
    WndClassSee.hInstance = hInstance;
    WndClassSee.lpfnWndProc = SeeProc;
    WndClassSee.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    WndClassSee.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClassSee.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    WndClassSee.cbClsExtra = 0;
    WndClassSee.cbWndExtra = 0;
    WndClassSee.lpszMenuName = NULL;
    WndClassLogin.lpszClassName = "PhoneNumberbooklogin";
    WndClassLogin.hInstance = hInstance;
    WndClassLogin.lpfnWndProc = LoginProc;
    WndClassLogin.hbrBackground = Brush;
    WndClassLogin.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClassLogin.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    WndClassLogin.cbClsExtra = 0;
    WndClassLogin.cbWndExtra = 0;
    WndClassLogin.lpszMenuName = NULL;
    WndClassAdduser.lpszClassName = "PhoneNumberbookadduser";
    WndClassAdduser.hInstance = hInstance;
    WndClassAdduser.lpfnWndProc = UseraddProc;
    WndClassAdduser.hbrBackground = (HBRUSH)GetStockObject(LTGRAY_BRUSH);
    WndClassAdduser.hCursor = LoadCursor(NULL, IDC_ARROW);
    WndClassAdduser.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
    WndClassAdduser.cbClsExtra = 0;
    WndClassAdduser.cbWndExtra = 0;
    WndClassAdduser.lpszMenuName = NULL;

    //â ������ ���
    RegisterClassA(&WndClass);
    RegisterClassA(&WndClassadd);
    RegisterClassA(&WndClassRevise);
    RegisterClassA(&WndClassSee);
    RegisterClassA(&WndClassLogin);
    RegisterClassA(&WndClassAdduser);

    hWndlogin = CreateWindowA("PhoneNumberbooklogin", "PhoneNumberbook - 2.0 - login", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 300, 200, 1000, 700, NULL, NULL, g_hInst, NULL);

    while (GetMessageA(&msg, 0, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }

    return 0;
}
LRESULT CALLBACK LoginProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    LPMINMAXINFO pmmi;
    char id[35] = "";
    char password[35] = "";
    switch (Msg)
    {
    case WM_GETMINMAXINFO:
        pmmi = (LPMINMAXINFO)lParam;
        pmmi->ptMinTrackSize.x = 1000;
        pmmi->ptMinTrackSize.y = 700;
        pmmi->ptMaxTrackSize.x = 1000;
        pmmi->ptMaxTrackSize.y = 700;
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        HFONT myFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, NULL);
        HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
        SetBkColor(hdc, RGB(0, 150, 230));
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOutA(hdc, 310, 245, "���̵�", 6);
        TextOutA(hdc, 310, 295, "��й�ȣ", 8);
        EndPaint(hWnd, &ps);
        break;
    case WM_CREATE:
    {
        int x, y, width, height;
        RECT rtDesk, rtWindow;
        GetWindowRect(GetDesktopWindow(), &rtDesk);
        GetWindowRect(hWnd, &rtWindow);

        width = rtWindow.right - rtWindow.left;
        height = rtWindow.bottom - rtWindow.top;

        x = (rtDesk.right - width) / 2;
        y = (rtDesk.bottom - height) / 2;

        MoveWindow(hWnd, x, y, width, height, TRUE);
        CreateWindowA("button", "�α���", WS_VISIBLE | WS_CHILD, 630, 300, 100, 30, hWnd, (HMENU)LOGINBTN, g_hInst, NULL);
        hidedit = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LOWERCASE, 410, 250, 200, 25, hWnd, NULL, g_hInst, NULL);
        hpasswordedit = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LOWERCASE | ES_PASSWORD, 410, 300, 200, 25, hWnd, NULL, g_hInst, NULL);
        CreateWindowA("button", "���� �����", WS_VISIBLE | WS_CHILD, 510, 350, 100, 25, hWnd, (HMENU)MKUSRBTN, g_hInst, NULL);
    }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case LOGINBTN:
            if (!GetWindowTextA(hidedit, id, 35))
            {
                MessageBoxA(hWnd, "���̵� �Է��ϼ���.", "���̵� �Է�", MB_OKCANCEL | MB_ICONWARNING);
                return 0;
            }
            GetWindowTextA(hpasswordedit, password, 35);
            thisuserifm = checklogin(id, password);
            if (!strcmp(thisuserifm.id, id) && !strcmp(thisuserifm.password, password))
            {
                DestroyWindow(hWnd);
                hWndMain = CreateWindowA("PhoneNumberbookwindow", "PhoneNumberbook - 2.0", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 300, 200, 1000, 700, NULL, NULL, g_hInst, NULL); //���� â ����
                ShowWindow(hWndMain, SW_SHOWNORMAL);
                //������ �ε� �Լ� ȣ��
                loaddata();
            }
            break;
        case MKUSRBTN:
            CreateWindowA("PhoneNumberbookadduser", "PhoneNumberbook - Adduser", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 500, 300, 600, 500, hWndlogin, NULL, g_hInst, NULL);
            break;
        }
        break;
    case WM_CLOSE:
        msgboxreturn = MessageBoxA(hWnd, "���� ����ó�� �����ұ��?", "����", MB_OKCANCEL | MB_ICONQUESTION);
        switch (msgboxreturn)
        {
        case IDCANCEL:
            return 0;
        default:
            freenodes();
            PostQuitMessage(0);
            break;
        }
        break;
    }
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}
LRESULT CALLBACK UseraddProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    LPMINMAXINFO pmmi;
    char checkpassword[35] = "";
    switch (Msg)
    {
    case WM_GETMINMAXINFO:
        pmmi = (LPMINMAXINFO)lParam;
        pmmi->ptMinTrackSize.x = 600;
        pmmi->ptMinTrackSize.y = 500;
        pmmi->ptMaxTrackSize.x = 600;
        pmmi->ptMaxTrackSize.y = 500;
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        HFONT myFont = CreateFont(30, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, NULL);
        HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
        SetBkColor(hdc, RGB(190, 190, 190));
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOutA(hdc, 80, 95, "�̸�", 4);
        TextOutA(hdc, 80, 145, "���̵�", 6);
        TextOutA(hdc, 80, 195, "��й�ȣ", 8);
        TextOutA(hdc, 80, 245, "��й�ȣ Ȯ��", 13);
        EndPaint(hWnd, &ps);
        break;
    case WM_CREATE:
    {
        int x, y, width, height;
        RECT rtDesk, rtWindow;
        GetWindowRect(GetDesktopWindow(), &rtDesk);
        GetWindowRect(hWnd, &rtWindow);

        width = rtWindow.right - rtWindow.left;
        height = rtWindow.bottom - rtWindow.top;

        x = (rtDesk.right - width) / 2;
        y = (rtDesk.bottom - height) / 2;

        MoveWindow(hWnd, x, y, width, height, TRUE);
        haddName = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LOWERCASE, 230, 100, 200, 25, hWnd, NULL, g_hInst, NULL);
        hID = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LOWERCASE, 230, 150, 200, 25, hWnd, NULL, g_hInst, NULL);
        hPassword = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LOWERCASE | ES_PASSWORD, 230, 200, 200, 25, hWnd, NULL, g_hInst, NULL);
        hCheckPassword = CreateWindowA("edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_LOWERCASE | ES_PASSWORD, 230, 250, 200, 25, hWnd, NULL, g_hInst, NULL);
        CreateWindowA("button", "�����", WS_VISIBLE | WS_CHILD, 450, 390, 100, 30, hWnd, (HMENU)ADDUSERBTN, g_hInst, NULL);
        CreateWindowA("button", "���", WS_VISIBLE | WS_CHILD, 320, 390, 100, 30, hWnd, (HMENU)CNCLBTN, g_hInst, NULL);
    }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ADDUSERBTN:
            if (!GetWindowTextA(haddName, adduserifm.name, 50))
            {
                MessageBoxA(hWnd, "�̸��� �Է��ϼ���.", "�Է�", MB_OK | MB_ICONINFORMATION);
            }
            else if (!GetWindowTextA(hID, adduserifm.id, 35))
            {
                MessageBoxA(hWnd, "���̵� �Է��ϼ���.", "�Է�", MB_OK | MB_ICONINFORMATION);
            }
            else if (!GetWindowTextA(hPassword, adduserifm.password, 35))
            {
                strcpy(adduserifm.userdatapath, ".\\data\\user\\userdata\\");
                strcat(adduserifm.userdatapath, adduserifm.name);
                strcat(adduserifm.userdatapath, ".usd");
                strcpy(adduserifm.userpath, ".\\data\\user\\");
                strcat(adduserifm.userpath, adduserifm.name);
                adduser(adduserifm);
                DestroyWindow(hWnd);
            }
            else if (!GetWindowTextA(hCheckPassword, checkpassword, 35))
            {
                MessageBoxA(hWnd, "��й�ȣ�� Ȯ�����ּ���.", "��й�ȣ Ȯ��", MB_OK | MB_ICONWARNING);
            }
            else
            {
                if (strcmp(checkpassword, adduserifm.password))
                {
                    MessageBoxA(hWnd, "��й�ȣ�� �ٸ��ϴ�.", "��й�ȣ �ٸ�", MB_OK | MB_ICONWARNING);
                }
                else
                {
                    strcpy(adduserifm.userdatapath, ".\\data\\user\\userdata\\");
                    strcat(adduserifm.userdatapath, adduserifm.name);
                    strcat(adduserifm.userdatapath, ".usd");
                    strcpy(adduserifm.userpath, ".\\data\\user\\");
                    strcat(adduserifm.userpath, adduserifm.name);
                    adduser(adduserifm);
                    DestroyWindow(hWnd);
                }
            }
            break;
        case CNCLBTN:
            msgboxreturn = MessageBoxA(hWnd, "���� ���� ����⸦ ����ұ��?", "���", MB_OKCANCEL | MB_ICONQUESTION);
            switch (msgboxreturn)
            {
            case IDCANCEL:
                return 0;
            default:
                DestroyWindow(hWnd);
                break;
            }
            break;
        }
        break;
    case WM_CLOSE:
        msgboxreturn = MessageBoxA(hWnd, "���� ���� ����⸦ ����ұ��?", "���", MB_OKCANCEL | MB_ICONQUESTION);
        switch (msgboxreturn)
        {
        case IDCANCEL:
            return 0;
        default:
            DestroyWindow(hWnd);
            break;
        }
        break;
    }
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}
//������ ���ν��� �Լ�
LRESULT CALLBACK WinProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    LPMINMAXINFO pmmi;
    char welcome[50] = "";
    strcpy(welcome, thisuserifm.name);
    strcat(welcome, "�� ȯ���մϴ�!!");
    switch (Msg)
    {
    case WM_GETMINMAXINFO:
        pmmi = (LPMINMAXINFO)lParam;
        pmmi->ptMinTrackSize.x = 1000;
        pmmi->ptMinTrackSize.y = 700;
        pmmi->ptMaxTrackSize.x = 1000;
        pmmi->ptMaxTrackSize.y = 700;
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        HFONT myFont = CreateFont(50, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, NULL);
        HFONT oldFont = (HFONT)SelectObject(hdc, myFont);
        SetBkColor(hdc, RGB(0, 150, 230));
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOutA(hdc, 80, 50, "�޴�", 4);
        myFont = CreateFont(25, 0, 0, 0, 1000, 0, 0, 0, DEFAULT_CHARSET, 0, 0, 0, 0, NULL);
        oldFont = (HFONT)SelectObject(hdc, myFont);
        TextOutA(hdc, 280, 97, "����ó �˻�", 12);
        TextOutA(hdc, 600, 600, welcome, strlen(welcome));
        EndPaint(hWnd, &ps);
        break;
    case WM_CREATE:
    {
        int x, y, width, height;
        RECT rtDesk, rtWindow;
        GetWindowRect(GetDesktopWindow(), &rtDesk);
        GetWindowRect(hWnd, &rtWindow);

        width = rtWindow.right - rtWindow.left;
        height = rtWindow.bottom - rtWindow.top;

        x = (rtDesk.right - width) / 2;
        y = (rtDesk.bottom - height) / 2;

        MoveWindow(hWnd, x, y, width, height, TRUE);

        CreateWindowA("button", "����ó �߰�", WS_CHILD | WS_VISIBLE, 20, 120, 200, 50, hWnd, (HMENU)ADD, g_hInst, NULL);
        CreateWindowA("button", "����ó ����", WS_CHILD | WS_VISIBLE, 20, 200, 200, 50, hWnd, (HMENU)REVISE, g_hInst, NULL);
        CreateWindowA("button", "����ó ����", WS_CHILD | WS_VISIBLE, 20, 280, 200, 50, hWnd, (HMENU)REMOVE, g_hInst, NULL);
        CreateWindowA("button", "����", WS_CHILD | WS_VISIBLE, 20, 360, 200, 50, hWnd, (HMENU)UPDATE, g_hInst, NULL);
        hedit = CreateWindowA("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 390, 100, 400, 25, hWnd, NULL, g_hInst, NULL);
        hlist = CreateWindowA("listbox", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | LBS_STANDARD | LBS_DISABLENOSCROLL | LBS_EXTENDEDSEL, 390, 200, 400, 300, hWnd, (HMENU)LIST, g_hInst, NULL);
        CreateWindowA("button", "�˻�", WS_CHILD | WS_VISIBLE | WS_BORDER, 800, 100, 70, 25, hWnd, (HMENU)SEARCH, g_hInst, NULL);
        CreateWindowA("button", "����ó ����", WS_CHILD | WS_VISIBLE, 690, 510, 100, 30, hWnd, (HMENU)SEE, g_hInst, NULL);
    }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case ADD:
            CreateWindowA("PhoneNumberbookadd", "����ó �߰�", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 500, 250, 700, 600, hWnd, NULL, g_hInst, NULL);
            break;
        case REVISE:
			if (SendMessageA(hlist, LB_GETSELCOUNT, 0, 0) == 0)
			{
				MessageBoxA(hWnd, "������ �׸��� �����Ͽ� �ּ���.", "�׸� ����", MB_OK | MB_ICONEXCLAMATION);
			}
			else if (SendMessageA(hlist, LB_GETSELCOUNT, 0, 0) > 1)
			{
				MessageBoxA(hWnd, "1���� �׸� �����Ͽ� �ּ���.", "�׸� ����", MB_OK | MB_ICONEXCLAMATION);
			}
			else
			{
				char temp[50] = { 0, };
				SendMessageA(hlist, LB_GETTEXT, (WPARAM)SendMessageA(hlist, LB_GETCURSEL, 0, 0), (LPARAM)temp);
				datalink = findnode(temp);
				CreateWindowA("PhoneNumberbookrevise", "����ó ����", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 500, 250, 700, 600, hWnd, NULL, g_hInst, NULL);
			}
			break;
        case REMOVE:
            if (SendMessageA(hlist, LB_GETSELCOUNT, 0, 0) == 0)
            {
                MessageBoxA(hWnd, "������ �׸��� �����Ͽ� �ּ���.", "�׸� ����", MB_OK | MB_ICONEXCLAMATION);
            }
            else
            {
				int count = SendMessageA(hlist, LB_GETSELCOUNT, 0, 0);
				char temp[50] = "";
				int *tempindex = malloc(sizeof(int) * 10000);
				SendMessageA(hlist, LB_GETSELITEMS, 10000, (LPARAM)tempindex);
				for (int i = count - 1; i > -1; i--)
				{
					SendMessageA(hlist, LB_GETTEXT, (WPARAM)tempindex[i], (LPARAM)temp);
					removedata(findnode(temp)->FileName);
					SendMessageA(hlist, LB_DELETESTRING, tempindex[i], 0);
				}
				loaddata();
                free(tempindex);
            }
            break;
        case UPDATE:
            MessageBoxA(hWnd, "Version: 2.0.0(GUI)\n\n���α׷� ������ ������ ���Ƿ� �����Ұ��\n���α׷��� ���������� �������� ���� �� �ֽ��ϴ�.\n\n���� ����ȭ�� ���� �ʾ� ������ �߻��� �� �ֽ��ϴ�.", "����", MB_OK | MB_ICONINFORMATION);
            break;
        case SEARCH:
            if (!GetWindowTextA(hedit, findbuffer, 50))
            {
                freenodes();
                loaddata();
            }
            else
            {
                if (serchdata(findbuffer) == 0)
                {
                    MessageBoxA(hWnd, "�˻��Ͻ� �̸��� ����ó�� ã�� �� �����ϴ�.", "����ó ����", MB_OK | MB_ICONEXCLAMATION);
                    return 0;
                }
                else
                {
                    listboxremove();
                    serchdata(findbuffer);
                }
            }
            break;
        case SEE:
            if (SendMessageA(hlist, LB_GETSELCOUNT, 0, 0) == 0)
            {
                MessageBoxA(hWnd, "��ȸ�� �׸��� �����Ͽ� �ּ���.", "�׸� ����", MB_OK | MB_ICONEXCLAMATION);
            }
            else if (SendMessageA(hlist, LB_GETSELCOUNT, 0, 0) > 1)
            {
                MessageBoxA(hWnd, "1���� �׸� �����Ͽ� �ּ���.", "�׸� ����", MB_OK | MB_ICONEXCLAMATION);
            }
            else
            {
                char temp[50] = { 0, };
                SendMessageA(hlist, LB_GETTEXT, (WPARAM)SendMessageA(hlist, LB_GETCURSEL, 0, 0), (LPARAM)temp);
                datalink = findnode(temp);
                CreateWindowA("PhoneNumberbookSee", "����ó ����", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 500, 250, 700, 600, hWnd, NULL, g_hInst, NULL);
            }
            break;
        case LIST:
            switch (HIWORD(wParam))
            {
            case LBN_DBLCLK:
                {
                    char temp[50] = { 0, };
                    SendMessageA(hlist, LB_GETTEXT, (WPARAM)SendMessageA(hlist, LB_GETCURSEL, 0, 0), (LPARAM)temp);
                    datalink = findnode(temp);
                    CreateWindowA("PhoneNumberbookSee", "����ó ����", WS_VISIBLE | WS_OVERLAPPEDWINDOW | WS_BORDER, 500, 250, 700, 600, hWnd, NULL, g_hInst, NULL);
                }
                break;
            }
            break;
        }
        break;
    case WM_CLOSE:
        msgboxreturn = MessageBoxA(hWnd, "���� ����ó�� �����ұ��?", "����", MB_OKCANCEL | MB_ICONQUESTION);
        switch (msgboxreturn)
        {
        case IDCANCEL:
            return 0;
        default:
            freenodes();
            PostQuitMessage(0);
        }
        break;
    }
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}
LRESULT CALLBACK addProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    LPMINMAXINFO pmmi;
    switch (Msg)
    {
    case WM_GETMINMAXINFO:
        pmmi = (LPMINMAXINFO)lParam;
        pmmi->ptMinTrackSize.x = 700;
        pmmi->ptMinTrackSize.y = 600;
        pmmi->ptMaxTrackSize.x = 700;
        pmmi->ptMaxTrackSize.y = 600;
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        SetBkColor(hdc, RGB(190, 190, 190));
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOutA(hdc, 100, 104, "�̸�", 4);
        TextOutA(hdc, 100, 154, "��ȭ��ȣ", 8);
        TextOutA(hdc, 230, 154, "  ---", 5);
        TextOutA(hdc, 310, 154, "  ---", 5);
        TextOutA(hdc, 100, 204, "�����ּ�", 8);
        TextOutA(hdc, 300, 204, " @ ", 3);
        TextOutA(hdc, 100, 254, "���ּ�", 6);
        TextOutA(hdc, 100, 304, "��Ÿ����", 8);
        EndPaint(hWnd, &ps);
        break;
    case WM_CREATE:
    {
        int x, y, width, height;
        RECT rtDesk, rtWindow;
        GetWindowRect(GetDesktopWindow(), &rtDesk);
        GetWindowRect(hWnd, &rtWindow);

        width = rtWindow.right - rtWindow.left;
        height = rtWindow.bottom - rtWindow.top;

        x = (rtDesk.right - width) / 2;
        y = (rtDesk.bottom - height) / 2;

        MoveWindow(hWnd, x, y, width, height, TRUE);
        hName = CreateWindowA("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 100, 200, 25, hWnd, (HMENU)NAMEDT, g_hInst, NULL);
        hPhoneNumber[0] = CreateWindowA("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 180, 150, 50, 25, hWnd, (HMENU)PNUMEDT1, g_hInst, NULL);
        hPhoneNumber[1] = CreateWindowA("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 260, 150, 50, 25, hWnd, (HMENU)PNUMEDT2, g_hInst, NULL);
        hPhoneNumber[2] = CreateWindowA("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 340, 150, 50, 25, hWnd, (HMENU)PNUMEDT3, g_hInst, NULL);
        hMail = CreateWindowA("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 200, 120, 25, hWnd, (HMENU)MAILEDT, g_hInst, NULL);
        hMdomain = CreateWindowA("combobox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN, 325, 200, 120, 200, hWnd, (HMENU)MAILDOMAIN, g_hInst, NULL);
        HhomeAdress = CreateWindowA("edit", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 250, 450, 25, hWnd, (HMENU)HOMEADDR, g_hInst, NULL);
        hetc = CreateWindowA("edit", NULL, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_MULTILINE, 180, 300, 450, 150, hWnd, (HMENU)ETCEDT, g_hInst, NULL);
        CreateWindowA("button", "����", WS_CHILD | WS_VISIBLE, 550, 500, 100, 30, hWnd, (HMENU)SAVEBTN, g_hInst, NULL);
        CreateWindowA("button", "���", WS_CHILD | WS_VISIBLE, 430, 500, 100, 30, hWnd, (HMENU)CNCLBTN, g_hInst, NULL);

        for (int i = 0; i < 8; i++)
            SendMessageA(hMdomain, CB_ADDSTRING, 0, (LPARAM)MailDomain[i]);
    }
        break;
    case WM_CLOSE:
        msgboxreturn = MessageBoxA(hWnd, "���� ����ó �߰��� ����Ͻðڽ��ϱ�?", "����ó �߰� ���", MB_YESNO | MB_ICONQUESTION);
        switch (msgboxreturn)
        {
        case IDYES:
            DestroyWindow(hWnd);
            break;
        default:
            return 0;
            break;
        }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case CNCLBTN:
            msgboxreturn = MessageBoxA(hWnd, "���� ����ó �߰��� ����Ͻðڽ��ϱ�?", "����ó �߰� ���", MB_YESNO | MB_ICONQUESTION);
            switch (msgboxreturn)
            {
            case IDYES:
                DestroyWindow(hWnd);
                break;
            }
            break;
        case SAVEBTN:
            if (!GetWindowTextA(hName, data.name, 50))
            {
                MessageBoxA(hWnd, "�̸�, ��ȭ��ȣ�� �ʼ� �Է»����Դϴ�.", "�ʼ� �Է»���", MB_OK | MB_ICONINFORMATION);
            }
            else if (!GetWindowTextA(hPhoneNumber[0], data.phonenumber[0], 6) || !GetWindowTextA(hPhoneNumber[1], data.phonenumber[1], 6) || !GetWindowTextA(hPhoneNumber[2], data.phonenumber[2], 6))
            {
                MessageBoxA(hWnd, "�̸�, ��ȭ��ȣ�� �ʼ� �Է»����Դϴ�.", "�ʼ� �Է»���", MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                char temp[50] = { (char)NULL };
                strcpy(temp, data.name);
                strcat(temp, ".pdt");
                strcpy(data.FileName, temp);
                GetWindowTextA(hMail, data.email, 50);
                GetWindowTextA(hMdomain, data.Mdomain, 15);
                GetWindowTextA(HhomeAdress, data.homeadress, 100);
                GetWindowTextA(hetc, data.etc, 1000);
                writefile(data);
                DestroyWindow(hWnd);
            }
            break;
        }
        break;
    }
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}
LRESULT CALLBACK reviseProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    LPMINMAXINFO pmmi;
    switch (Msg)
    {
    case WM_GETMINMAXINFO:
        pmmi = (LPMINMAXINFO)lParam;
        pmmi->ptMinTrackSize.x = 700;
        pmmi->ptMinTrackSize.y = 600;
        pmmi->ptMaxTrackSize.x = 700;
        pmmi->ptMaxTrackSize.y = 600;
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        SetBkColor(hdc, RGB(190, 190, 190));
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOutA(hdc, 100, 104, "�̸�", 4);
        TextOutA(hdc, 100, 154, "��ȭ��ȣ", 8);
        TextOutA(hdc, 230, 154, "  ---", 5);
        TextOutA(hdc, 310, 154, "  ---", 5);
        TextOutA(hdc, 100, 204, "�����ּ�", 8);
        TextOutA(hdc, 300, 204, " @ ", 3);
        TextOutA(hdc, 100, 254, "���ּ�", 6);
        TextOutA(hdc, 100, 304, "��Ÿ����", 8);
        EndPaint(hWnd, &ps);
        break;
    case WM_CREATE:
    {
        int x, y, width, height;
        RECT rtDesk, rtWindow;
        GetWindowRect(GetDesktopWindow(), &rtDesk);
        GetWindowRect(hWnd, &rtWindow);

        width = rtWindow.right - rtWindow.left;
        height = rtWindow.bottom - rtWindow.top;

        x = (rtDesk.right - width) / 2;
        y = (rtDesk.bottom - height) / 2;

        MoveWindow(hWnd, x, y, width, height, TRUE);
        hName = CreateWindowA("edit", datalink->name, WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 100, 200, 25, hWnd, (HMENU)NAMEDT, g_hInst, NULL);
        hPhoneNumber[0] = CreateWindowA("edit", datalink->phonenumber[0], WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 180, 150, 50, 25, hWnd, (HMENU)PNUMEDT1, g_hInst, NULL);
        hPhoneNumber[1] = CreateWindowA("edit", datalink->phonenumber[1], WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 260, 150, 50, 25, hWnd, (HMENU)PNUMEDT2, g_hInst, NULL);
        hPhoneNumber[2] = CreateWindowA("edit", datalink->phonenumber[2], WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER, 340, 150, 50, 25, hWnd, (HMENU)PNUMEDT3, g_hInst, NULL);
        hMail = CreateWindowA("edit", datalink->email, WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 200, 120, 25, hWnd, (HMENU)MAILEDT, g_hInst, NULL);
        hMdomain = CreateWindowA("combobox", NULL, WS_CHILD | WS_VISIBLE | WS_BORDER | CBS_DROPDOWN, 325, 200, 120, 200, hWnd, (HMENU)MAILDOMAIN, g_hInst, NULL);
        HhomeAdress = CreateWindowA("edit", datalink->homeadress, WS_CHILD | WS_VISIBLE | WS_BORDER, 180, 250, 450, 25, hWnd, (HMENU)HOMEADDR, g_hInst, NULL);
        hetc = CreateWindowA("edit", datalink->etc, WS_CHILD | WS_VISIBLE | WS_VSCROLL, 180, 300, 450, 150, hWnd, (HMENU)ETCEDT, g_hInst, NULL);
        CreateWindowA("button", "����", WS_CHILD | WS_VISIBLE, 550, 500, 100, 30, hWnd, (HMENU)RSVEBTN, g_hInst, NULL);
        CreateWindowA("button", "���", WS_CHILD | WS_VISIBLE, 430, 500, 100, 30, hWnd, (HMENU)CNCLBTN, g_hInst, NULL);

        for (int i = 0; i < 8; i++)
        {
            SendMessageA(hMdomain, CB_ADDSTRING, 0, (LPARAM)MailDomain[i]);
        }
        SendMessageA(hMdomain, WM_SETTEXT, 0, (LPARAM)datalink->Mdomain);
    }
        break;
    case WM_CLOSE:
        msgboxreturn = MessageBoxA(hWnd, "���� ����ó ������ ����Ͻðڽ��ϱ�?", "����ó ���� ���", MB_YESNO | MB_ICONQUESTION);
        switch (msgboxreturn)
        {
        case IDYES:
            DestroyWindow(hWnd);
            break;
        default:
            return 0;
            break;
        }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case CNCLBTN:
            msgboxreturn = MessageBoxA(hWnd, "���� ����ó ������ ����Ͻðڽ��ϱ�?", "����ó ���� ���", MB_YESNO | MB_ICONQUESTION);
            switch (msgboxreturn)
            {
            case IDYES:
                DestroyWindow(hWnd);
                break;
            }
            break;
        case RSVEBTN:
            if (!GetWindowTextA(hName, data.name, 50))
            {
                MessageBoxA(hWnd, "�̸�, ��ȭ��ȣ�� �ʼ� �Է»����Դϴ�.", "�ʼ� �Է»���", MB_OK | MB_ICONINFORMATION);
            }
            else if (!GetWindowTextA(hPhoneNumber[0], data.phonenumber[0], 6) || !GetWindowTextA(hPhoneNumber[1], data.phonenumber[1], 6) || !GetWindowTextA(hPhoneNumber[2], data.phonenumber[2], 6))
            {
                MessageBoxA(hWnd, "�̸�, ��ȭ��ȣ�� �ʼ� �Է»����Դϴ�.", "�ʼ� �Է»���", MB_OK | MB_ICONINFORMATION);
            }
            else
            {
                char temp[60] = { (char)NULL };
                strcpy(temp, data.name);
                strcat(temp, ".pdt");
                strcpy(data.FileName, temp);
                GetWindowTextA(hMail, data.email, 50);
                GetWindowTextA(hMdomain, data.Mdomain, 15);
                GetWindowTextA(HhomeAdress, data.homeadress, 100);
                GetWindowTextA(hetc, data.etc, 1000);
                revisefile(datalink->FileName, data);
                DestroyWindow(hWnd);
            }
            break;
        }
        break;
    }
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}
LRESULT CALLBACK SeeProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
    HDC hdc;
    LPMINMAXINFO pmmi;
    switch (Msg)
    {
    case WM_GETMINMAXINFO:
        pmmi = (LPMINMAXINFO)lParam;
        pmmi->ptMinTrackSize.x = 700;
        pmmi->ptMinTrackSize.y = 600;
        pmmi->ptMaxTrackSize.x = 700;
        pmmi->ptMaxTrackSize.y = 600;
        break;
    case WM_PAINT:
        hdc = BeginPaint(hWnd, &ps);
        SetBkColor(hdc, RGB(190, 190, 190));
        SetTextColor(hdc, RGB(0, 0, 0));
        TextOutA(hdc, 100, 104, "�̸�", 4);
        TextOutA(hdc, 100, 154, "��ȭ��ȣ", 8);
        TextOutA(hdc, 230, 154, "  ---", 5);
        TextOutA(hdc, 310, 154, "  ---", 5);
        TextOutA(hdc, 100, 204, "�����ּ�", 8);
        TextOutA(hdc, 300, 204, " @ ", 3);
        TextOutA(hdc, 100, 254, "���ּ�", 6);
        TextOutA(hdc, 100, 304, "��Ÿ����", 8);
        EndPaint(hWnd, &ps);
        break;
    case WM_CREATE:
    {
        int x, y, width, height;
        RECT rtDesk, rtWindow;
        GetWindowRect(GetDesktopWindow(), &rtDesk);
        GetWindowRect(hWnd, &rtWindow);

        width = rtWindow.right - rtWindow.left;
        height = rtWindow.bottom - rtWindow.top;

        x = (rtDesk.right - width) / 2;
        y = (rtDesk.bottom - height) / 2;

        MoveWindow(hWnd, x, y, width, height, TRUE);
        hName = CreateWindowA("edit", datalink->name, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY | ES_READONLY, 180, 100, 200, 25, hWnd, (HMENU)NAMEDT, g_hInst, NULL);
        hPhoneNumber[0] = CreateWindowA("edit", datalink->phonenumber[0], WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_READONLY, 180, 150, 50, 25, hWnd, (HMENU)PNUMEDT1, g_hInst, NULL);
        hPhoneNumber[1] = CreateWindowA("edit", datalink->phonenumber[1], WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_READONLY, 260, 150, 50, 25, hWnd, (HMENU)PNUMEDT2, g_hInst, NULL);
        hPhoneNumber[2] = CreateWindowA("edit", datalink->phonenumber[2], WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER | ES_READONLY, 340, 150, 50, 25, hWnd, (HMENU)PNUMEDT3, g_hInst, NULL);
        hMail = CreateWindowA("edit", datalink->email, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 180, 200, 120, 25, hWnd, (HMENU)MAILEDT, g_hInst, NULL);
        hMdomain = CreateWindowA("edit", datalink->Mdomain, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 325, 200, 120, 25, hWnd, (HMENU)MAILDOMAIN, g_hInst, NULL);
        HhomeAdress = CreateWindowA("edit", datalink->homeadress, WS_CHILD | WS_VISIBLE | WS_BORDER | ES_READONLY, 180, 250, 450, 25, hWnd, (HMENU)HOMEADDR, g_hInst, NULL);
        hetc = CreateWindowA("edit", datalink->etc, WS_CHILD | WS_VISIBLE | WS_VSCROLL | ES_READONLY, 180, 300, 450, 150, hWnd, (HMENU)ETCEDT, g_hInst, NULL);
        CreateWindowA("button", "Ȯ��", WS_CHILD | WS_VISIBLE, 300, 500, 100, 30, hWnd, (HMENU)OK, g_hInst, NULL);
    }
        break;
    case WM_COMMAND:
        switch (LOWORD(wParam))
        {
        case OK:
            DestroyWindow(hWnd);
            break;
        }
        break;
    }
    return DefWindowProcA(hWnd, Msg, wParam, lParam);
}
inline void listboxremove()
{
    SendMessageA(hlist, LB_RESETCONTENT, 0, 0);
}