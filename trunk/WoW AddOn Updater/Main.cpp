/************************************************************************/
/* WoW AddOn Updater	                                                */
/************************************************************************/

#include "cBlizzard.h"

BOOL DlgProc(HWND, UINT, WPARAM, LPARAM);

int WINAPI WinMain(__in HINSTANCE hInstance, __in_opt HINSTANCE hPrevInstance, __in_opt LPSTR lpCmdLine, __in int nShowCmd)
{
	MSG Msg;
	InitCommonControls();
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, (DLGPROC)DlgProc);
	while (GetMessage(&Msg, NULL, 0, 0))
	{
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}
typedef struct tagTest
{
	char* one;
	char* two;
	char* three;
}Tester;

Tester rTest[ ] = {
	("One", "OneOne", "OneOneOne"),
	("Two", "TwoTwo", "TwoTwoTwo"),
	("Three", "ThreeThree", "ThreeThreeThree"),
};

BOOL DlgProc(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam)
{
	HICON hIcon, hIconSm;
	vector<string> vAddons;
	char* nCols[3] = {"AddOns", "Version", "Update"};
	switch(Msg)
	{
	case WM_INITDIALOG:
		hIcon = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 32, 32, 0);
		hIconSm = (HICON)LoadImage(GetModuleHandle(NULL), MAKEINTRESOURCE(IDI_ICON1), IMAGE_ICON, 16, 16, 0);
		SendMessage(hWnd, WM_SETICON, ICON_BIG, (LPARAM)hIcon);
		SendMessage(hWnd, WM_SETICON, ICON_SMALL, (LPARAM)hIconSm);
		//Setup Coloums
		LVCOLUMN lvColumn;
		lvColumn.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		for (int iCol = 0; iCol < 3; iCol++)
		{
			lvColumn.iSubItem = iCol;
			lvColumn.pszText = nCols[iCol];
			lvColumn.cx = 140;
			lvColumn.fmt = LVCFMT_LEFT;
			SendMessage(GetDlgItem(hWnd, IDC_LIST5), LVM_INSERTCOLUMN, (WPARAM)iCol, (LPARAM)&lvColumn);
		}

		gBlizz.GetAddOnDir();
		gBlizz.GetList(hWnd);
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case ID_FILE_CLOSE40001: // Close
				PostQuitMessage(0);
				break;
		case IDC_BUTTON3: // Close
				PostQuitMessage(0);
				break;
		}
		break;
	case WM_CLOSE:
		PostQuitMessage(0);
		break;
	default:
		return FALSE;
	}
	return FALSE;
}