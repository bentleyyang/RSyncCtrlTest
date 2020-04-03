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

	using namespace rapidjson;
	GDoc jsonDoc;//配置文件
	fs::path path_conf = fs::path(fs::current_path().append("/config.json"));

	
	{
		//手机云证等参数读取
		std::error_code ec;
		uint64_t len=fs::file_size(path_conf, ec);
		if (ec) { AfxMessageBox(L"config.json不存在"); return; }
		std::vector<char> u8(len+1, '\0');
		fs::ifstream ifs(path_conf, std::ios::binary);
		ifs.read(u8.data(), len);
		if (ifs.fail()) { AfxMessageBox(L"config.json读取错误"); return; }
		
		jsonDoc.Parse(u8.data());
		if (jsonDoc.HasParseError()) { AfxMessageBox(L"config.json读取错误"); return; }
		const Value* token_login = GetValueByPointer(jsonDoc, "/token/登录token");
		const Value* token_encrypt = GetValueByPointer(jsonDoc, "/token/加密token");
		const Value* token_decrypt = GetValueByPointer(jsonDoc, "/token/解密token");
		const Value* token_seal = GetValueByPointer(jsonDoc, "/token/签章token");
		const Value* token_cert = GetValueByPointer(jsonDoc, "/token/证书token");
		const Value* password = GetValueByPointer(jsonDoc, "/密码");
		const Value* authCode = GetValueByPointer(jsonDoc, "/授权码");
		const Value* rsigncloud = GetValueByPointer(jsonDoc, "/服务器地址");
		if (!token_login||!token_encrypt || !token_decrypt||!token_seal||!token_cert||!password
			||!authCode||!rsigncloud) { AfxMessageBox(L"config.json读取错误"); return; }

		m_TokenLogin = to_wstr(token_login->GetString()).data();
		m_TokenEncrypt = to_wstr(token_encrypt->GetString()).data();
		m_TokenDecrypt = to_wstr(token_decrypt->GetString()).data();
		m_TokenSeal = to_wstr(token_seal->GetString()).data();
		m_TokenCert = to_wstr(token_cert->GetString()).data();
		m_PassWord = to_wstr(password->GetString()).data();
		m_AuthCode = to_wstr(authCode->GetString()).data();
		m_RsignCloud = to_wstr(rsigncloud->GetString()).data();

	}

	{
		//获取证书列表
		auto seallist = getSealList();
		if (!seallist.first) { AfxMessageBox(L"获取签章列表失败"); return; }
		else if (seallist.second.empty()) { AfxMessageBox(L"签章列表为空"); return; }
		else { m_SealList = seallist.second; }
	}

#if 1
	{
		//获取ukey的containerId
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


	if (!m_strPw.IsEmpty())
	{
		m_PassWord = m_strPw;
	}

	if (!login(m_PassWord.GetBuffer()))
	{
		AfxMessageBox(L"登录失败，请检查密码或key是否插入");
		return;
	}
	else
#endif
	{
		{
			//更新密码至配置文件
			GValue gtmp;
			gtmp.SetString(to_utf8(m_PassWord.GetBuffer()).data(), jsonDoc.GetAllocator());
			SetValueByPointer(jsonDoc, "/密码", gtmp);
			//SetValueByPointer(jsonDoc, "/password", StringRef(to_utf8(m_PassWord.GetBuffer()).data()));
		}
		

	

		{
			//设置参数至底层
			if (!setParameter(L"authCode", m_AuthCode.GetBuffer())) { AfxMessageBox(L"设置authcode失败"); return; }
			if (!setParameter(L"rsigncloud", m_RsignCloud.GetBuffer())) { AfxMessageBox(L"设置rsigncloud失败"); return; }
		}
		

#if 1
		{
			//获取certbase64
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
#endif
		

		{
			//保存配置文件
			std::error_code ec;
			fs::copy_file(path_conf.wstring(), path_conf.wstring() + L".bac", fs::copy_options::overwrite_existing, ec);
			if(ec){ AfxMessageBox(L"config.json备份错误"); return; }
			std::string to_write = jsonDocToStr(jsonDoc);
			fs::ofstream ofs(path_conf, std::ios::binary);
			ofs.write(to_write.data(), to_write.length());
			if (ofs.fail()) { AfxMessageBox(L"config.json写入错误"); return; }
		}
		
	}
	CDialogEx::OnOK();
}

CString CDlgPasswd::getPw()
{
	return m_strPw;
}


BOOL CDlgPasswd::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
