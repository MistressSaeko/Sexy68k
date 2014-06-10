// Strip out unnecessary crap
#define WIN32_LEAN_AND_MEAN

// Global includes.
#include <windows.h>
#include <commdlg.h>
#include <commctrl.h>

// Local includes.
#include "resource.h"
#include "dialogs.h"
#include "main.h"

void WINAPI InitCommonControlsEx(void);  // Have to do this. Or we don't get to use controls.

// Standard global variables. Limit the usage of these or experience a huge overhead.
char szClassName[ ] = "Sexy68k";
char ROM_Path[MAX_PATH];
char ini_path[MAX_PATH];
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

// Save emulator settings using an ini file.
//int save_settings(HINSTANCE hInst)
//{
//	{
//	char *p;
//	GetModuleFileName(hInst, ini_path, sizeof(ini_path));
//	p = strrchr(ini_path, '\\');
//	if(NULL == p)
//	{
//		p = (ini_path - 1);
//	}
//
//	strcpy((p + 1), "sexy68k.ini");
//	}
//
//	WritePrivateProfileString
//}



int APIENTRY WinMain(HINSTANCE hInst, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
    HWND hwnd; 
    MSG msg;           
    WNDCLASSEX wc;       

	// Register the Window. If it fails, all hell breaks loose.
    wc.hInstance     = hInst;
    wc.lpszClassName = szClassName;
    wc.style         = CS_DBLCLKS;                
    wc.cbSize        = sizeof (WNDCLASSEX);  
    wc.hIcon         = LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APPICO));
    wc.hIconSm       = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_APPICO), IMAGE_ICON, 16, 16, 0); // Have to use LoadImage() because LoadIcon() only supports 32x32 icons.
    wc.hCursor       = LoadCursor (NULL, IDC_ARROW);																// Default cursor.
    wc.lpszMenuName  = MAKEINTRESOURCE(IDM_MAINMENU);																// Yay! A menu! :D
    wc.cbClsExtra    = 0;                     
    wc.cbWndExtra    = 0;                     
    wc.hbrBackground = (HBRUSH) COLOR_BACKGROUND +1;
	wc.lpfnWndProc   = WndProc;																						// Pointer to the Window Procedure.

    if (!RegisterClassEx (&wc))
	{
		MessageBox(NULL, "Unable to register window.", "Sexy68k", MB_ICONEXCLAMATION | MB_OK);
        return 0;
	}

	// Succesfully registered. Now let's actually create the window!
    hwnd = CreateWindowEx (
           WS_EX_CLIENTEDGE,  
           szClassName,         
           "Sexy68k",           
           WS_BORDER | WS_MINIMIZEBOX | WS_CAPTION | WS_SYSMENU | WS_VISIBLE,
           CW_USEDEFAULT,     
           CW_USEDEFAULT,       
           800,                 
           600,                 
           HWND_DESKTOP,        
           NULL,
           hInst,
		   NULL
           );
	
	if(hwnd == NULL)
	{
		MessageBox(NULL, "Window creation failed.", "Sexy68k", MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}
   
	//Pretty standard stuff here.
    ShowWindow (hwnd, nCmdShow);
	UpdateWindow(hwnd);

  // Main message loop.
    while (GetMessage (&msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return msg.wParam;
}



LRESULT CALLBACK WndProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)              
    {
		case WM_CREATE: // Statusbars and shit.
        {
            int statwidths[] = {400, -1};
             
            HWND hStatus = CreateWindowEx(
                0,
                STATUSCLASSNAME,
                NULL,
				WS_CHILD | WS_VISIBLE,
                0,
                0,
                0,
                0,
				hwnd,
                (HMENU)IDC_STATUS,
                GetModuleHandle(NULL),
                NULL
                );
           
           SendMessage(hStatus, SB_SETPARTS, sizeof(statwidths)/sizeof(int), (LPARAM)statwidths);
           SendMessage(hStatus, SB_SETTEXT, 0, (LPARAM)"Disk drive 1 is empty.");
		   SendMessage(hStatus, SB_SETTEXT, 1, (LPARAM)"Disk drive 2 is empty.");
		}
        break;

        case WM_SIZE: // Let Windows size them automagically.
        {	
			SendMessage(GetDlgItem(hwnd, IDC_STATUS), WM_SIZE, 0, 0);
        }
        break;

        case WM_COMMAND: // Makes the menu items actually do crap. :o
        switch(LOWORD(wParam))
        {
            case ID_DISKDRIVE1_INSERTDISK:
            DoROMLoad1(hwnd);
            break;

            case ID_DISKDRIVE2_INSERTDISK:
            DoROMLoad2(hwnd);
            break;

			case ID_HELP_ABOUT:
			{
			int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_ABOUT), hwnd, AboutDlg);
			if(ret == IDOK)
            {	
               EndDialog(hwnd, IDOK);
            }
            else if(ret == -1)
            {
                MessageBox(hwnd, "Cannot display dialog.", "Sexy68k", MB_OK | MB_ICONINFORMATION);
            }
			}
			break;

            case ID_CONFIG_PATHS:
			{
            int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_PATHSCFG), hwnd, PathSetDlg);
            if(ret == IDOK)
            {
               EndDialog(hwnd, IDOK);
            }
            else if(ret == IDCANCEL)
            {
               EndDialog(hwnd, IDCANCEL);
            }
            else if(ret == -1)
            {
                MessageBox(hwnd, "Cannot display dialog.", "Sexy68k", MB_OK | MB_ICONINFORMATION);
            }
			}
			break;

			case ID_INPUT_INPUTOPTIONS:
			{
			int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_INPUTCFG), hwnd, InputCfg);
			if(ret == IDOK)
            {
               EndDialog(hwnd, IDOK);
            }
            else if(ret == IDCANCEL)
            {
               EndDialog(hwnd, IDCANCEL);
            }
            else if(ret == -1)
            {
                MessageBox(hwnd, "Cannot display dialog.", "Sexy68k", MB_OK | MB_ICONINFORMATION);
            }
			}
			break;

			case ID_VIDEO_VIDEOOPTIONS:
			{
			int ret = DialogBox(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_VIDCFG), hwnd, VideoCfg);
			if(ret == IDOK)
            {
               EndDialog(hwnd, IDOK);
            }
            else if(ret == IDCANCEL)
            {
               EndDialog(hwnd, IDCANCEL);
            }
            else if(ret == -1)
            {
                MessageBox(hwnd, "Cannot display dialog.", "Sexy68k", MB_OK | MB_ICONINFORMATION);
            }
			}
			break;

		case ID_FILE_EXIT:
			{
				DestroyWindow(hwnd);
			}
			break;		
        }
		break;

        case WM_DESTROY: // Click the little X icon in the window to see what happens.
            PostQuitMessage (0);       
            break;
        default:  // For messages we don't deal with.        
            return DefWindowProc (hwnd, message, wParam, lParam);
    }

    return 0;
}