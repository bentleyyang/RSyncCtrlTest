// CDRS_CertSafe.h : 由 Microsoft Visual C++ 创建的 ActiveX 控件包装器类的声明

#pragma once

/////////////////////////////////////////////////////////////////////////////
// CDRS_CertSafe

class CDRS_CertSafe : public CWnd
{
protected:
	DECLARE_DYNCREATE(CDRS_CertSafe)
public:
	CLSID const& GetClsid()
	{
		static CLSID const clsid
			= { 0xF84C8F57, 0x5A05, 0x4D8C, { 0x82, 0x6D, 0x29, 0x58, 0x9C, 0x7A, 0x12, 0x1C } };
		return clsid;
	}
	virtual BOOL Create(LPCTSTR lpszClassName, LPCTSTR lpszWindowName, DWORD dwStyle,
						const RECT& rect, CWnd* pParentWnd, UINT nID,
						CCreateContext* pContext = nullptr)
	{
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID);
	}

	BOOL Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, CWnd* pParentWnd,
				UINT nID, CFile* pPersist = nullptr, BOOL bStorage = FALSE,
				BSTR bstrLicKey = nullptr)
	{
		return CreateControl(GetClsid(), lpszWindowName, dwStyle, rect, pParentWnd, nID,
		pPersist, bStorage, bstrLicKey);
	}

// 特性
public:

// 操作
public:

	void AboutBox()
	{
		InvokeHelper(DISPID_ABOUTBOX, DISPATCH_METHOD, VT_EMPTY, nullptr, nullptr);
	}
	CString RS_KeyGetKeySn()
	{
		CString result;
		InvokeHelper(0x14, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	CString RS_KeyGetKeySnExt(LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x15, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId);
		return result;
	}
	CString RS_GetUserList()
	{
		CString result;
		InvokeHelper(0x16, DISPATCH_METHOD, VT_BSTR, (void*)&result, nullptr);
		return result;
	}
	CString RS_GetCertBase64String(LPCTSTR containerId, short certType)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_I2 ;
		InvokeHelper(0x17, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId, certType);
		return result;
	}
	CString RS_CertLogin(LPCTSTR containerId, LPCTSTR password)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x18, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId, password);
		return result;
	}
	CString RS_GetPinRetryCount(LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x19, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId);
		return result;
	}
	CString RS_ChangePassWd(LPCTSTR containerId, LPCTSTR oldCdoe, LPCTSTR newCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId, oldCdoe, newCode);
		return result;
	}
	CString RS_KeySignByP1(LPCTSTR msg, LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, msg, containerId);
		return result;
	}
	CString RS_VerifySignByP1(LPCTSTR certBase64, LPCTSTR msg, LPCTSTR signdMsg)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, certBase64, msg, signdMsg);
		return result;
	}
	CString RS_KeyEncryptData(LPCTSTR rsKey, LPCTSTR certBase64)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, rsKey, certBase64);
		return result;
	}
	CString RS_KeyDecryptData(LPCTSTR encRsKey, LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, encRsKey, containerId);
		return result;
	}
	CString RS_GetCertInfo(LPCTSTR certBase64, LPCTSTR type)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x1f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, certBase64, type);
		return result;
	}
	CString RS_KeySignByP7(LPCTSTR msg, LPCTSTR flag, LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x20, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, msg, flag, containerId);
		return result;
	}
	CString RS_VerifySignByP7(LPCTSTR msg, LPCTSTR signdMsg, LPCTSTR flag)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x21, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, msg, signdMsg, flag);
		return result;
	}
	CString RS_CloudLoginAuth(LPCTSTR transid)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x22, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, transid);
		return result;
	}
	CString RS_CloudSealAuth(LPCTSTR transid)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x23, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, transid);
		return result;
	}
	CString RS_CloudGetAuth(LPCTSTR transid)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x24, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, transid);
		return result;
	}
	CString RS_CloudGetSealList(LPCTSTR token)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x25, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, token);
		return result;
	}
	CString RS_CloudSignByP7(LPCTSTR msg, LPCTSTR keySn, LPCTSTR transid, LPCTSTR token)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x26, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, msg, keySn, transid, token);
		return result;
	}
	CString RS_CloudGetSignResult(LPCTSTR transid)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x27, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, transid);
		return result;
	}
	CString RS_CloudLogoutAuth(LPCTSTR token)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x28, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, token);
		return result;
	}
	CString RS_CloudEncryptAuth(LPCTSTR transid)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x29, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, transid);
		return result;
	}
	CString RS_CloudEncryptData(LPCTSTR reachKey, LPCTSTR transid, LPCTSTR token)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, reachKey, transid, token);
		return result;
	}
	CString RS_CloudEncryptFile(LPCTSTR souceFilePath, LPCTSTR encFilePath, LPCTSTR transid, LPCTSTR token)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, souceFilePath, encFilePath, transid, token);
		return result;
	}
	CString RS_CloudDevryptAuth(LPCTSTR transid)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x2c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, transid);
		return result;
	}
	CString RS_CloudDevryptData(LPCTSTR encReachKey, LPCTSTR url, LPCTSTR transid, LPCTSTR token)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, encReachKey, url, transid, token);
		return result;
	}
	CString RS_CloudDevryptFile(LPCTSTR encFilePath, LPCTSTR dncFilePath, LPCTSTR url, LPCTSTR transid, LPCTSTR token)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, encFilePath, dncFilePath, url, transid, token);
		return result;
	}
	CString RS_CloudReceiveDevryptResult(LPCTSTR transid, LPCTSTR token, LPCTSTR devResult)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x2f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, transid, token, devResult);
		return result;
	}
	CString RS_CloudGetCompanyCert(LPCTSTR transid, LPCTSTR token)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x30, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, transid, token);
		return result;
	}
	CString RS_CloudGetCertAuth(LPCTSTR transid)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x31, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, transid);
		return result;
	}
	CString RS_CloudGetCertBase64(LPCTSTR transid, LPCTSTR token)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x32, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, transid, token);
		return result;
	}
	CString RS_CloudLogout(LPCTSTR userId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x33, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, userId);
		return result;
	}
	CString RS_KeyStatus(LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x34, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId);
		return result;
	}
	CString RS_ConfigParameters(LPCTSTR cmd, LPCTSTR val)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x35, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, cmd, val);
		return result;
	}
	CString RS_GetParameters(LPCTSTR cmd)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x36, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, cmd);
		return result;
	}
	CString RS_GreateQRCode(LPCTSTR qrcode, LPCTSTR path)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x37, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, qrcode, path);
		return result;
	}
	CString RS_GetTransid(LPCTSTR joinCode)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x38, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, joinCode);
		return result;
	}
	CString RS_EncryptFile(LPCTSTR souceFilePath, LPCTSTR encFilePath)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x39, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, souceFilePath, encFilePath);
		return result;
	}
	CString RS_DevryptFile(LPCTSTR symKey, LPCTSTR encFilePath, LPCTSTR dncDirectoryPath)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3a, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, symKey, encFilePath, dncDirectoryPath);
		return result;
	}
	CString RS_VerifyIdentity(LPCTSTR certBase64, LPCTSTR authNo)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3b, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, certBase64, authNo);
		return result;
	}
	CString RS_KeyEncryptFile(LPCTSTR souceFilePath, LPCTSTR encFilePath, LPCTSTR certBase64)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3c, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, souceFilePath, encFilePath, certBase64);
		return result;
	}
	CString RS_KeyDecryptFile(LPCTSTR encFilePath, LPCTSTR dncFilePath, LPCTSTR containerId)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3d, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, encFilePath, dncFilePath, containerId);
		return result;
	}
	CString RS_EncryptDataBase64(LPCTSTR symKey, LPCTSTR certBase64)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3e, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, symKey, certBase64);
		return result;
	}
	CString RS_EncryptFileBase64(LPCTSTR souceFilePath, LPCTSTR encFilePath, LPCTSTR certBase64)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x3f, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, souceFilePath, encFilePath, certBase64);
		return result;
	}
	CString RS_ConfigParamsByBussSys(LPCTSTR cmd, LPCTSTR val)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x40, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, cmd, val);
		return result;
	}
	CString RS_EncryptData(LPCTSTR dataStr)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR ;
		InvokeHelper(0x41, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, dataStr);
		return result;
	}
	CString RS_DevryptData(LPCTSTR symKey, LPCTSTR encDataStr)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x42, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, symKey, encDataStr);
		return result;
	}
	CString RS_KeyGetDeviceInfo(LPCTSTR containerId, LPCTSTR type)
	{
		CString result;
		static BYTE parms[] = VTS_BSTR VTS_BSTR ;
		InvokeHelper(0x43, DISPATCH_METHOD, VT_BSTR, (void*)&result, parms, containerId, type);
		return result;
	}


};
