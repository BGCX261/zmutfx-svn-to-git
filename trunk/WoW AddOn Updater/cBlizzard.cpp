#include "cBlizzard.h"

cBlizzard gBlizz;

void cBlizzard::GetAddOnDir()
{
	char Buffer[1024];
	HKEY hKey;
	DWORD dwSize[1024];
	DWORD dwRet = RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Blizzard Entertainment\\World of Warcraft", 0, KEY_QUERY_VALUE, &hKey);
	if (dwRet != ERROR_SUCCESS)
		return;
	dwRet = RegQueryValueEx(hKey, "InstallPath", NULL, NULL, (LPBYTE)Buffer, dwSize);
	if (dwRet != ERROR_SUCCESS)
		return;
	strcat(Buffer, "\Interface\\AddOns");
	strcat(Directory, Buffer);
	RegCloseKey(hKey);
}

void cBlizzard::GetList(HWND hWnd)
{
	WIN32_FIND_DATA fInfo;
	vector<string> vAddons;
	LVITEM lvItem;
	lvItem.mask = LVIF_TEXT;
	strcat(Directory, "\\*");
	HANDLE hFile = FindFirstFile(Directory, &fInfo);
	do 
	{
		if (strncmp(fInfo.cFileName, "Blizzard_", 9) != 0 && strncmp(fInfo.cFileName, ".", 1) != 0)
			vAddons.push_back(fInfo.cFileName);
	} while (FindNextFile(hFile, &fInfo));

	Directory[strlen(Directory)-1] = '\0';
	char tmpDir[1024];
	
	for (int b = 0; b < 2; b++)
	{
		for (int i = 0; i < vAddons.size(); i++)
		{
			ZeroMemory(&tmpDir, sizeof(tmpDir));
			sprintf(tmpDir, "%s%s\\%s.toc", Directory, vAddons[i].c_str(), vAddons[i].c_str());

			lvItem.iItem = i; 
			lvItem.iSubItem = b; 
			lvItem.pszText = (LPSTR)vAddons[i].c_str(); 
			if (b == 0)
			{
				SendMessage(GetDlgItem(hWnd, IDC_LIST5), LVM_INSERTITEM, 0, (LPARAM)&lvItem); 
			}
			else if (b == 1)
			{
				//Get Toc Version
				fstream fFile(tmpDir);
				string line;
				if (fFile.is_open())
				{
					while (!fFile.eof())
					{
						getline(fFile, line);
						if (strncmp(line.c_str(), "## Version", 10) == 0)
						{
							line.erase(0, 12);
							lvItem.pszText = (LPSTR)line.c_str();
							SendMessage(GetDlgItem(hWnd, IDC_LIST5), LVM_SETITEM, 0, (LPARAM)&lvItem);
						}
					}
				} 
			}
		}
	}
	//MessageBox(NULL, tmpDir, "", MB_OK);
}