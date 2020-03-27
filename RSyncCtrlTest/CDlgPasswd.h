#pragma once


// CDlgPasswd 对话框

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
	CString m_strPw;

public:
	CString getPw();
};
