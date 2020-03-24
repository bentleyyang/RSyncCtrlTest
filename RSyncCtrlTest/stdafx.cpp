
// stdafx.cpp : 只包括标准包含文件的源文件
// RSyncCtrlTest.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"



CDRS_CertSafe* s_pDRS_CertSafeCtrl = NULL;
HWND s_hMainWnd = NULL;
CWnd* s_pMainWnd = NULL;

LRESULT CALLBACK MyWndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, message, wParam, lParam);
}

void MyDestroyWindow()
{
	if (s_pDRS_CertSafeCtrl != NULL)
	{
		s_pDRS_CertSafeCtrl->DestroyWindow();
		delete s_pDRS_CertSafeCtrl;
		s_pDRS_CertSafeCtrl = NULL;
	}
	if (s_pMainWnd != NULL)
	{
		s_pMainWnd->Detach();
		delete s_pMainWnd;
		s_pMainWnd = NULL;
	}
}

BOOL MyCreateWindow(WndProc _wndProc, HWND* _pHWND)
{
	WNDCLASSEX wcx;

	// Fill in the window class structure with parameters 
	// that describe the main window. 

	wcx.cbSize = sizeof(wcx);          // size of structure 
	wcx.style = CS_HREDRAW | CS_VREDRAW;                    // redraw if size changes 
	wcx.lpfnWndProc = _wndProc;     // points to window procedure 
	wcx.cbClsExtra = 0;                // no extra class memory 
	wcx.cbWndExtra = 0;                // no extra window memory 
	wcx.hInstance = GetModuleHandle(NULL);         // handle to instance 
	wcx.hIcon = LoadIcon(NULL,
		IDI_APPLICATION);              // predefined app. icon 
	wcx.hCursor = LoadCursor(NULL,
		IDC_ARROW);                    // predefined arrow 
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);                  // white background brush 
	wcx.lpszMenuName = L"MainMenu";    // name of menu resource 

	//CTime time = CTime::GetCurrentTime();  
	CString sAnnotName;
	//sAnnotName.Format(_T("Image_%d_%d_%d_%d:%d:%d"),time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());

	//OutputDebugString("KG_HARD_API  sAnnotName = " + sAnnotName);
	DWORD w = GetTickCount();
	sAnnotName.Format(L"%d", w);

	wcx.lpszClassName = sAnnotName;//"MainWClass";  // name of window class 
	wcx.hIconSm = NULL;
	DWORD dwError = 0;
	// Register the window class. 
	if (RegisterClassEx(&wcx) == FALSE)
	{
		OutputDebugString(L"KG_HARD_API  RegisterClassEx(&wcx) == FALSE ");
		dwError = GetLastError();
		if (ERROR_CLASS_ALREADY_EXISTS != dwError)
		{
			return FALSE;
		}
	}

	OutputDebugString(L"KG_HARD_API  开始调用(&wcx) CreateWindow ");

	*_pHWND = CreateWindow(
		sAnnotName,        // name of window class 
		L"Sample",            // title-bar string 
		WS_OVERLAPPEDWINDOW, // top-level window 
		CW_USEDEFAULT,       // default horizontal position 
		CW_USEDEFAULT,       // default vertical position 
		CW_USEDEFAULT,       // default width 
		CW_USEDEFAULT,       // default height 
		(HWND)NULL,         // no owner window 
		(HMENU)NULL,        // use class menu 
		wcx.hInstance,           // handle to application instance 
		(LPVOID)NULL);      // no window-creation data 

	if (!*_pHWND)
		return FALSE;

	// Show the window and send a WM_PAINT message to the window 
	// procedure. 

	OutputDebugString(L"KG_HARD_API 结束调用 CreateWindow ");
	ShowWindow(*_pHWND, SW_HIDE);
	UpdateWindow(*_pHWND);







	if (s_pMainWnd == NULL)
	{

		s_pMainWnd = new CWnd();
		s_pMainWnd->Attach(s_hMainWnd);
	}

	if (s_pDRS_CertSafeCtrl == NULL)
	{
		s_pDRS_CertSafeCtrl = new CDRS_CertSafe();
		s_pDRS_CertSafeCtrl->Create(_T("DRS_CertSafe"), WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS, CRect(0, 0, 200, 200), s_pMainWnd, 1000);
		if (IsWindow(s_pDRS_CertSafeCtrl->m_hWnd) != TRUE)
		{
			return FALSE;
		}
	}
	return TRUE;
}