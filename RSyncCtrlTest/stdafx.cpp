
// stdafx.cpp : 只包括标准包含文件的源文件
// RSyncCtrlTest.pch 将作为预编译标头
// stdafx.obj 将包含预编译类型信息

#include "stdafx.h"


Poco::FileOutputStream assertLogOfs(Poco::Path::current()+(u8"测试结果.txt"), std::ios::binary);

CDRS_CertSafe* s_pDRS_CertSafeCtrl = NULL;
HWND s_hMainWnd = NULL;
CWnd* s_pMainWnd = NULL;

CString m_PassWord= L"12345678";
CString m_ContainerId= L"F5BA5CE5-BC9A-49C8-AE47-1825115058D7";
CString m_AuthCode= L"";
CString m_CertEncrypt= L"MIID8jCCA5igAwIBAgILIPOoHk2h3atHMfEwCgYIKoEcz1UBg3UwYjELMAkGA1UEBhMCQ04xJDAiBgNVBAoMG05FVENBIENlcnRpZmljYXRlIEF1dGhvcml0eTEtMCsGA1UEAwwkTkVUQ0EgU00yIFRFU1QwMSBhbmQgRXZhbHVhdGlvbiBDQTAxMB4XDTE5MTEwMTA0NTgyNloXDTI0MTEwMTA0NTgyNlowgdExCzAJBgNVBAYTAkNOMQ8wDQYDVQQIDAZGdWppYW4xMzAxBgNVBAcMKuemj+W7uuecgeemj+W3nuW4gum8k+alvOWMuua5luS4nOi3rzE4OOWPtzE9MDsGA1UECgw056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTE9MDsGA1UEAww056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTBZMBMGByqGSM49AgEGCCqBHM9VAYItA0IABJ1jTugwIT4TlNF2IxsxVxv\/exGmo+Io3Upj\/SJv+epJQgo5ehOjD\/jAMZq413KCqF41gIaS7Ec3BSVNXJsWjvOjggHDMIIBvzAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBT8CyNZp3dl6nPw8AoQTyAVLBKlGDAfBgNVHSMEGDAWgBQMe+ticwN1+oxKJAz2jzshZX4X6TBrBgNVHSAEZDBiMGAGCisGAQQBgZJIDQowUjBQBggrBgEFBQcCARZEaHR0cDovL3d3dy5jbmNhLm5ldC9jcy9rbm93bGVkZ2Uvd2hpdGVwYXBlci9jcHMvbmV0Q0F0ZXN0Y2VydGNwcy5wZGYwMwYDVR0fBCwwKjAooCagJIYiaHR0cDovL3Rlc3QuY25jYS5uZXQvY3JsL1NNMkNBLmNybDAOBgNVHQ8BAf8EBAMCAzgwNAYKKwYBBAGBkkgBDgQmDCQ1MjE2MDc4NmMwYTM3MmZjOGMzMzBhMDJiMTZjYmE2M0BTMDIwgYYGCCsGAQUFBwEBBHoweDBNBggrBgEFBQcwAYZBaHR0cDovLzE5Mi4xNjguMC43OS9vY3NwY29uc29sZS9vY3NwL29jc3BfY2hlY2tfdXNlcmNlcnRfc3RhdGUuZG8wJwYIKwYBBQUHMAGGG2h0dHA6Ly8xNzIuMC4wLjE6ODAvdGVzdHVybDAKBggqgRzPVQGDdQNIADBFAiBUQE+fdAD1eH6OyCuSURjv\/vp+x0MYv8Hkh8S4Ks\/svQIhANdkoJyTiNlij5wckuzhWDJLokcGIyup+y5JYS4xmt7D";
CString m_CertSign= L"MIID8jCCA5igAwIBAgILENzv3NBdilQmXGUwCgYIKoEcz1UBg3UwYjELMAkGA1UEBhMCQ04xJDAiBgNVBAoMG05FVENBIENlcnRpZmljYXRlIEF1dGhvcml0eTEtMCsGA1UEAwwkTkVUQ0EgU00yIFRFU1QwMSBhbmQgRXZhbHVhdGlvbiBDQTAxMB4XDTE5MTEwMTA0NTgyNloXDTI0MTEwMTA0NTgyNlowgdExCzAJBgNVBAYTAkNOMQ8wDQYDVQQIDAZGdWppYW4xMzAxBgNVBAcMKuemj+W7uuecgeemj+W3nuW4gum8k+alvOWMuua5luS4nOi3rzE4OOWPtzE9MDsGA1UECgw056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTE9MDsGA1UEAww056aP5bu655Ge5pyv5L+h5oGv56eR5oqA5pyJ6ZmQ5YWs5Y+477yIU00y5rWL6K+VMu+8iTBZMBMGByqGSM49AgEGCCqBHM9VAYItA0IABJPDjH4qPGIXcKopl6CYXTOqOAE2dmRchTE3TTlDtg7zTPFbe\/fOUFj+zlkUfrLWwopPAJOCA0cG\/ufkffHbhjejggHDMIIBvzAMBgNVHRMBAf8EAjAAMB0GA1UdDgQWBBQJVOszT+dSIPLoT8mIVl01gK37OTAfBgNVHSMEGDAWgBQMe+ticwN1+oxKJAz2jzshZX4X6TBrBgNVHSAEZDBiMGAGCisGAQQBgZJIDQowUjBQBggrBgEFBQcCARZEaHR0cDovL3d3dy5jbmNhLm5ldC9jcy9rbm93bGVkZ2Uvd2hpdGVwYXBlci9jcHMvbmV0Q0F0ZXN0Y2VydGNwcy5wZGYwMwYDVR0fBCwwKjAooCagJIYiaHR0cDovL3Rlc3QuY25jYS5uZXQvY3JsL1NNMkNBLmNybDAOBgNVHQ8BAf8EBAMCBsAwNAYKKwYBBAGBkkgBDgQmDCQ1MjE2MDc4NmMwYTM3MmZjOGMzMzBhMDJiMTZjYmE2M0BTMDIwgYYGCCsGAQUFBwEBBHoweDBNBggrBgEFBQcwAYZBaHR0cDovLzE5Mi4xNjguMC43OS9vY3NwY29uc29sZS9vY3NwL29jc3BfY2hlY2tfdXNlcmNlcnRfc3RhdGUuZG8wJwYIKwYBBQUHMAGGG2h0dHA6Ly8xNzIuMC4wLjE6ODAvdGVzdHVybDAKBggqgRzPVQGDdQNIADBFAiEA8njyShJt4\/DvEvFRIwusHppJT8pjm0Gu3234oVF6ovACIEKVRMxL5F\/FfyaBJOJd8T4aEWdMIrOTwrX0r+NSftx1";

CString m_RsignCloud;
CString m_TokenLogin;
CString m_TokenEncrypt;
CString m_TokenDecrypt;
CString m_TokenSeal;
CString m_TokenCert;

std::vector<seal> m_SealList;

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
		//OutputDebugString(L"KG_HARD_API  RegisterClassEx(&wcx) == FALSE ");
		dwError = GetLastError();
		if (ERROR_CLASS_ALREADY_EXISTS != dwError)
		{
			return FALSE;
		}
	}

	//OutputDebugString(L"KG_HARD_API  开始调用(&wcx) CreateWindow ");

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

	//OutputDebugString(L"KG_HARD_API 结束调用 CreateWindow ");
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