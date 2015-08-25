#include <Windows.h>
#include <string>
#include <vector>
#include <fstream>
#include <CommCtrl.h>
#pragma comment(lib, "ComCtl32")
#include "resource.h"
using namespace std;

class cBlizzard
{
public:
	void GetAddOnDir();
	void GetList(HWND);
protected:
private:
	char Directory[1024];
};

extern cBlizzard gBlizz;