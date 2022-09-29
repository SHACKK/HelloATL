// dllmain.cpp : DllMain의 구현입니다.

#include "pch.h"
#include "framework.h"
#include "resource.h"
#include "HelloATLProject_i.h"
#include "dllmain.h"

CHelloATLProjectModule _AtlModule;

class CHelloATLProjectApp : public CWinApp
{
public:

// 재정의입니다.
	virtual BOOL InitInstance();
	virtual int ExitInstance();

	DECLARE_MESSAGE_MAP()
};

BEGIN_MESSAGE_MAP(CHelloATLProjectApp, CWinApp)
END_MESSAGE_MAP()

CHelloATLProjectApp theApp;

BOOL CHelloATLProjectApp::InitInstance()
{
	return CWinApp::InitInstance();
}

int CHelloATLProjectApp::ExitInstance()
{
	return CWinApp::ExitInstance();
}
