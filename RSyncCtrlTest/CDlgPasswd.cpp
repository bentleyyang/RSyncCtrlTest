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
	DDX_Control(pDX, IDC_EDIT2, m_etAuthCode);
	DDX_Control(pDX, IDC_EDIT3, m_etCloudUrl);
	DDX_Control(pDX, IDC_EDIT4, m_etTokenLogin);
	DDX_Control(pDX, IDC_EDIT5, m_etTokenEncrypt);
	DDX_Control(pDX, IDC_EDIT6, m_etTokenDecrypt);
	DDX_Control(pDX, IDC_EDIT7, m_etTokenSeal);
	DDX_Control(pDX, IDC_EDIT8, m_etTokenCert);
	DDX_Control(pDX, IDC_EDIT9, m_etTimePerTest);
}


BEGIN_MESSAGE_MAP(CDlgPasswd, CDialogEx)
	ON_BN_CLICKED(IDOK, &CDlgPasswd::OnBnClickedOk)
END_MESSAGE_MAP()


// CDlgPasswd 消息处理程序


void CDlgPasswd::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码

	GetDlgItemText(IDC_EDIT1, m_strPw);
	GetDlgItemText(IDC_EDIT2, m_strAuthCode);
	GetDlgItemText(IDC_EDIT3, m_strCloudUrl);
	GetDlgItemText(IDC_EDIT4, m_strTokenLogin);
	GetDlgItemText(IDC_EDIT5, m_strTokenEncrypt);
	GetDlgItemText(IDC_EDIT6, m_strTokenDecrypt);
	GetDlgItemText(IDC_EDIT7, m_strTokenSeal);
	GetDlgItemText(IDC_EDIT8, m_strTokenCert);
	GetDlgItemText(IDC_EDIT9, m_strTimePerTest);

	m_PassWord = m_strPw;
	m_AuthCode = m_strAuthCode;
	m_RsignCloud = m_strCloudUrl;
	m_TokenLogin = m_strTokenLogin;
	m_TokenEncrypt = m_strTokenEncrypt;
	m_TokenDecrypt = m_strTokenDecrypt;
	m_TokenSeal = m_strTokenSeal;
	m_TokenCert = m_strTokenCert;
	m_TimePerTest = std::stoul(m_strTimePerTest.GetBuffer());

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

	{
		//获取证书列表
		auto seallist = getSealList();
		if (!seallist.first) { AfxMessageBox(L"获取签章列表失败，请检查签章Token是否过期"); return; }
		else if (seallist.second.empty()) { AfxMessageBox(L"签章列表为空"); return; }
		else { m_SealList = seallist.second; }
	}

	using namespace rapidjson;
	std::wstring path_conf = to_wstr(Poco::Path::current()+("config.json"));

	if (!login(m_PassWord.GetBuffer()))
	{
		AfxMessageBox(L"登录失败，请检查密码或key是否插入");
		return;
	}
	else
	{
		{
			//更新密码至配置文件
			GValue gtmp;
			gtmp.SetString(to_u8(m_PassWord.GetBuffer()).data(), jsonDoc.GetAllocator());
			SetValueByPointer(jsonDoc, u8"/密码", gtmp);
			//SetValueByPointer(jsonDoc, "/password", StringRef(to_u8(m_PassWord.GetBuffer()).data()));
			
			gtmp.SetString(to_u8(m_AuthCode.GetBuffer()).data(), jsonDoc.GetAllocator());
			SetValueByPointer(jsonDoc, u8"/授权码", gtmp);
			gtmp.SetString(to_u8(m_RsignCloud.GetBuffer()).data(), jsonDoc.GetAllocator());
			SetValueByPointer(jsonDoc, u8"/服务器地址", gtmp);
			gtmp.SetString(to_u8(m_TokenLogin.GetBuffer()).data(), jsonDoc.GetAllocator());
			SetValueByPointer(jsonDoc, u8"/token/登录token", gtmp);
			gtmp.SetString(to_u8(m_TokenEncrypt.GetBuffer()).data(), jsonDoc.GetAllocator());
			SetValueByPointer(jsonDoc, u8"/token/加密token", gtmp);
			gtmp.SetString(to_u8(m_TokenDecrypt.GetBuffer()).data(), jsonDoc.GetAllocator());
			SetValueByPointer(jsonDoc, u8"/token/解密token", gtmp);
			gtmp.SetString(to_u8(m_TokenSeal.GetBuffer()).data(), jsonDoc.GetAllocator());
			SetValueByPointer(jsonDoc, u8"/token/签章token", gtmp);
			gtmp.SetString(to_u8(m_TokenCert.GetBuffer()).data(), jsonDoc.GetAllocator());
			SetValueByPointer(jsonDoc, u8"/token/证书token", gtmp);

			SetValueByPointer(jsonDoc, u8"/time per test", m_TimePerTest);
		}




		{
			//设置参数至底层
			if (!setParameter(L"authCode", m_AuthCode.GetBuffer())) { AfxMessageBox(L"设置authcode失败"); return; }
			if (!setParameter(L"rsigncloud", m_RsignCloud.GetBuffer())) { AfxMessageBox(L"设置rsigncloud失败"); return; }
		}

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


		{
			//保存配置文件
			Poco::File(to_u8(path_conf)).copyTo(to_u8(path_conf+(L".bac")));
			std::string to_write = jsonDocToStr(jsonDoc);
			Poco::FileOutputStream ofs(to_u8(path_conf), std::ios::binary|std::ios::trunc);
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
	auto exitFn = [this]()->BOOL {CDialogEx::OnCancel(); return TRUE; };

	using namespace rapidjson;
	std::wstring path_conf = to_wstr(Poco::Path::current()+("config.json"));

	{
		//手机云证等参数读取
		std::error_code ec;
		uint64_t len = Poco::File(to_u8(path_conf)).getSize();
		if (ec) { AfxMessageBox(L"config.json不存在"); return exitFn(); }
		std::vector<char> u8(len + 1, '\0');
		Poco::FileInputStream ifs(to_u8(path_conf), std::ios::binary);
		ifs.read(u8.data(), len);
		if (ifs.fail()) { AfxMessageBox(L"config.json读取错误"); return exitFn(); }
		jsonDoc.Parse(uint8_t(u8[0]) == 0xef ? u8.data() + 3 : u8.data());
		if (jsonDoc.HasParseError()) { AfxMessageBox(L"config.json解析错误"); return exitFn(); }
		const Value* token_login = GetValueByPointer(jsonDoc, u8"/token/登录token");
		const Value* token_encrypt = GetValueByPointer(jsonDoc, u8"/token/加密token");
		const Value* token_decrypt = GetValueByPointer(jsonDoc, u8"/token/解密token");
		const Value* token_seal = GetValueByPointer(jsonDoc, u8"/token/签章token");
		const Value* token_cert = GetValueByPointer(jsonDoc, u8"/token/证书token");
		const Value* password = GetValueByPointer(jsonDoc, u8"/密码");
		const Value* authCode = GetValueByPointer(jsonDoc, u8"/授权码");
		const Value* rsigncloud = GetValueByPointer(jsonDoc, u8"/服务器地址");
		const Value* time_per_test = GetValueByPointer(jsonDoc, u8"/time per test");
		if (!token_login || !token_encrypt || !token_decrypt || !token_seal || !token_cert || !password
			|| !authCode || !rsigncloud/* || !time_per_test*/) {
			AfxMessageBox(L"config.json解析错误"); return exitFn();
		}

		m_TokenLogin = to_wstr(token_login->GetString()).data();
		m_TokenEncrypt = to_wstr(token_encrypt->GetString()).data();
		m_TokenDecrypt = to_wstr(token_decrypt->GetString()).data();
		m_TokenSeal = to_wstr(token_seal->GetString()).data();
		m_TokenCert = to_wstr(token_cert->GetString()).data();
		m_PassWord = to_wstr(password->GetString()).data();
		m_AuthCode = to_wstr(authCode->GetString()).data();
		m_RsignCloud = to_wstr(rsigncloud->GetString()).data();
		m_TimePerTest = time_per_test ? time_per_test->GetUint() : 1;

	}

	{
		SetDlgItemText(IDC_EDIT1, m_PassWord);
		SetDlgItemText(IDC_EDIT2, m_AuthCode);
		SetDlgItemText(IDC_EDIT3, m_RsignCloud);
		SetDlgItemText(IDC_EDIT4, m_TokenLogin);
		SetDlgItemText(IDC_EDIT5, m_TokenEncrypt);
		SetDlgItemText(IDC_EDIT6, m_TokenDecrypt);
		SetDlgItemText(IDC_EDIT7, m_TokenSeal);
		SetDlgItemText(IDC_EDIT8, m_TokenCert);

		m_etTimePerTest.SetWindowTextW(std::to_wstring(m_TimePerTest).data());
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}
