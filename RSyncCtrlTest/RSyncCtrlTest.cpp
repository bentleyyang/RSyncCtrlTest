﻿
// RSyncCtrlTest.cpp: 定义应用程序的类行为。
//

#include "stdafx.h"
#include "RSyncCtrlTest.h"
#include "RSyncCtrlTestDlg.h"
#include "CDRS_CertSafe.h"

#include <experimental/filesystem>

#include <cppunit/ui/mfc/TestRunner.h>
#include <cppunit/extensions/TestFactoryRegistry.h>
#include "cppunit/TestRunner.h"
#include "cppunit/TestResult.h"
#include "cppunit/TestResultCollector.h"
#include "cppunit/TextOutputter.h"

#include "CDlgPasswd.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define CPPUNIT_CMD 0
namespace fs { using namespace std::experimental::filesystem; };


// CRSyncCtrlTestApp

BEGIN_MESSAGE_MAP(CRSyncCtrlTestApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CRSyncCtrlTestApp 构造

CRSyncCtrlTestApp::CRSyncCtrlTestApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的 CRSyncCtrlTestApp 对象

CRSyncCtrlTestApp theApp;


// CRSyncCtrlTestApp 初始化

BOOL CRSyncCtrlTestApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。  否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 激活“Windows Native”视觉管理器，以便在 MFC 控件中启用主题
	CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerWindows));

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("应用程序向导生成的本地应用程序"));

	//CRSyncCtrlTestDlg dlg;
	//m_pMainWnd = &dlg;
	//INT_PTR nResponse = dlg.DoModal();
	//if (nResponse == IDOK)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “确定”来关闭对话框的代码
	//}
	//else if (nResponse == IDCANCEL)
	//{
	//	// TODO: 在此放置处理何时用
	//	//  “取消”来关闭对话框的代码
	//}
	//else if (nResponse == -1)
	//{
	//	TRACE(traceAppMsg, 0, "警告: 对话框创建失败，应用程序将意外终止。\n");
	//	TRACE(traceAppMsg, 0, "警告: 如果您在对话框上使用 MFC 控件，则无法 #define _AFX_NO_MFC_CONTROLS_IN_DIALOGS。\n");
	//}
	//
	//// 删除上面创建的 shell 管理器。
	//if (pShellManager != nullptr)
	//{
	//	delete pShellManager;
	//}

//#if !defined(_AFXDLL) && !defined(_AFX_NO_MFC_CONTROLS_IN_DIALOGS)
//	ControlBarCleanUp();
//#endif

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。

	MyCreateWindow(MyWndProc, &s_hMainWnd);

	CDlgPasswd dlg;
	if (dlg.DoModal() == IDOK)
	{
		CppUnit::TestResult r;
		CppUnit::TestResultCollector rc;
		r.addListener(&rc);

#if CPPUNIT_CMD
		CppUnit::TestRunner runner;
#else
		//CPPUNIT_NS::MfcUi::TestRunner runner;
		CppUnit::MfcTestRunner runner;
#endif

		//runner.addTest(CPPUNIT_NS::TestFactoryRegistry::getRegistry().makeTest());
		//runner.addTest(InterfaceTestWithLogin::suite());
		CppUnit::TestFactoryRegistry &registry = CppUnit::TestFactoryRegistry::getRegistry("登录测试");
		CppUnit::TestFactoryRegistry &registry2 = CppUnit::TestFactoryRegistry::getRegistry("无登录测试(拔掉key)");
		runner.addTest(registry.makeTest());
		runner.addTest(registry2.makeTest());

#if CPPUNIT_CMD
		runner.run(r);
#else
		runner.run();
#endif

#if CPPUNIT_CMD
		std::ofstream ofs(fs::current_path().append(L"/test_log.txt"));
		if (!ofs.is_open())
		{
			AfxMessageBox(L"无法打开日志文件");
		}
		CppUnit::TextOutputter o(&rc, ofs);
		o.write();
#else
#endif
	}

	
	
	MyDestroyWindow();
	return FALSE;
}

