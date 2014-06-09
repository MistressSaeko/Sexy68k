#ifndef DIALOGS_H
#define DIALOGS_H
#include <windows.h>
#include "resource.h"
#include "main.h"

void DoROMLoad1(HWND hwnd)
{
	OPENFILENAME ofn;
	char szFileName[260];
	HANDLE di;

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "X68000 ROM (*.dim)\0*.dim\0";
	ofn.lpstrFile = szFileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFileName);
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrTitle = "Load X68000 ROM Image";
	ofn.lpstrDefExt = "dim";

	if(GetOpenFileName(&ofn))
	{
		di = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
		SendDlgItemMessage(hwnd, IDC_STATUS, SB_SETTEXT, 0, (LPARAM)szFileName);
    }
}

void DoROMLoad2(HWND hwnd)
{
	OPENFILENAME ofn;
	char szFileName[260];
	HANDLE di;

	ZeroMemory(&ofn, sizeof(ofn));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = hwnd;
	ofn.lpstrFilter = "X68000 ROM (*.dim)\0*.dim\0";
	ofn.lpstrFile = szFileName;
	ofn.lpstrFile[0] = '\0';
	ofn.nMaxFile = sizeof(szFileName);
	ofn.Flags = OFN_EXPLORER | OFN_FILEMUSTEXIST | OFN_HIDEREADONLY;
	ofn.lpstrTitle = "Load X68000 ROM Image";
	ofn.lpstrDefExt = "dim";

	if(GetOpenFileName(&ofn))
	{
		di = CreateFile(szFileName, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, (HANDLE) NULL);
		SendDlgItemMessage(hwnd, IDC_STATUS, SB_SETTEXT, 1, (LPARAM)szFileName);
    }
}

BOOL CALLBACK PathSetDlg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch(message)
    {
        case WM_INITDIALOG:

        return TRUE;
        case WM_COMMAND:
            switch(LOWORD(wParam))
            {
                case IDOK:
                    EndDialog(hwnd, IDOK);
                break;
                case IDCANCEL:
                    EndDialog(hwnd, IDCANCEL);
                break;
            }
        break;
        default:
            return FALSE;
    }
    return TRUE;
}

BOOL CALLBACK AboutDlg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:

		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
			break;
		}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK InputCfg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:

		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
		break;
		}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK VideoCfg(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case WM_INITDIALOG:

		return TRUE;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			EndDialog(hwnd, IDOK);
			break;
		case IDCANCEL:
			EndDialog(hwnd, IDCANCEL);
		break;
		}
		break;
		default:
			return FALSE;
	}
	return TRUE;
}

#endif // DIALOGS_H