// CDlgPasswd.cpp: 实现文件
//

#include "stdafx.h"
#include "RSyncCtrlTest.h"
#include "CDlgPasswd.h"
#include "afxdialogex.h"

#include "util.h"


// CDlgPasswd 对话框

IMPLEMENT_DYNAMIC(CDlgPasswd, CDialogEx)

CDlgPasswd::CDlgPasswd(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CDlgPasswd, pParent)
	, m_strPw(_T(""))
{

}

CDlgPasswd::~CDlgPasswd()
{
}

void CDlgPasswd::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_etPw);
	DDX_Text(pDX, IDC_EDIT1, m_strPw);
}


BEGIN_MESSAGE_MAP(CDlgPasswd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgPasswd::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgPasswd 消息处理程序


void CDlgPasswd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItemText(IDC_EDIT1, m_strPw);

	{
		//containerId
		std::vector < std::pair<std::wstring, std::wstring> > userLists;
		if (!getUserlist(userLists))
		{
			AfxMessageBox(L"获取用户列表失败");
			return;
		}
		else if (userLists.size() == 0)
		{
			AfxMessageBox(L"用户列表为空");
			return;
		}
		else
		{
			m_ContainerId = userLists[0].second.data();
		}
	}

	if (!login(m_strPw.GetBuffer()))
	{
		AfxMessageBox(L"登录失败，请检查key是否插入");
		return;
	}
	else
	{
		//密码
		m_PassWord = m_strPw;
		

		//authCode
		auto authCode = getParameter(L"authCode");
		if (!authCode.first)
		{
			AfxMessageBox(L"获取authCode失败");
			return;
		}
		else
		{
			m_AuthCode = authCode.second.data();
		}

		//certbase64
		auto certbase64 = getCertBase64(m_ContainerId.GetBuffer(), 1);
		if (!certbase64.first)
		{
			AfxMessageBox(L"获取certbase64失败");
			return;
		}
		else
		{
			m_CertSign = certbase64.second.data();
		}

		certbase64 = getCertBase64(m_ContainerId.GetBuffer(), 2);
		if (!certbase64.first)
		{
			AfxMessageBox(L"获取certbase64失败");
			return;
		}
		else
		{
			m_CertEncrypt = certbase64.second.data();
		}
	}
	CDialogEx::OnOK();
}

CString CDlgPasswd::getPw()
{
	return m_strPw;
}
