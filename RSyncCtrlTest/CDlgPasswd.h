#pragma once


// CDlgPasswd 对话框
#include "util.h"//GDoc

class CDlgPasswd : public CDialogEx
{
	DECLARE_DYNAMIC(CDlgPasswd)

public:
	CDlgPasswd(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CDlgPasswd();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CDlgPasswd };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	
	afx_msg void OnBnClickedOk();
private:
	CEdit m_etPw;
	CEdit m_etAuthCode;
	CEdit m_etCloudUrl;
	CEdit m_etTokenLogin;
	CEdit m_etTokenEncrypt;
	CEdit m_etTokenDecrypt;
	CEdit m_etTokenSeal;
	CEdit m_etTokenCert;
	CEdit m_etTimePerTest;

	CString m_strPw;
	CString m_strAuthCode;
	CString m_strCloudUrl;
	CString m_strTokenLogin;
	CString m_strTokenEncrypt;
	CString m_strTokenDecrypt;
	CString m_strTokenSeal;
	CString m_strTokenCert;
	CString m_strTimePerTest;

private:
	GDoc jsonDoc;//配置文件

public:
	CString getPw();
	virtual BOOL OnInitDialog();
};
