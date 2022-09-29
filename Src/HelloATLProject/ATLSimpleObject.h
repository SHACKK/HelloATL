// ATLSimpleObject.h : CATLSimpleObject 선언

#pragma once
#include "resource.h"       // 주 기호입니다.
#include "HelloATLProject_i.h"
#include <ShlObj.h>
#include <comdef.h>
#include <vector>
#include <string>

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "단일 스레드 COM 개체는 전체 DCOM 지원을 포함하지 않는 Windows Mobile 플랫폼과 같은 Windows CE 플랫폼에서 제대로 지원되지 않습니다. ATL이 단일 스레드 COM 개체의 생성을 지원하고 단일 스레드 COM 개체 구현을 사용할 수 있도록 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA를 정의하십시오. rgs 파일의 스레딩 모델은 DCOM Windows CE가 아닌 플랫폼에서 지원되는 유일한 스레딩 모델이므로 'Free'로 설정되어 있습니다."
#endif

using namespace ATL;


// CATLSimpleObject

class ATL_NO_VTABLE CATLSimpleObject :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CATLSimpleObject, &CLSID_ATLSimpleObject>,
	public IDispatchImpl<IATLSimpleObject, &IID_IATLSimpleObject, &LIBID_HelloATLProjectLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IShellExtInit,
	public IContextMenu
{
public:
	CATLSimpleObject()
	{
	}

DECLARE_REGISTRY_RESOURCEID(106)


BEGIN_COM_MAP(CATLSimpleObject)
	COM_INTERFACE_ENTRY(IATLSimpleObject)
	COM_INTERFACE_ENTRY(IDispatch)
	COM_INTERFACE_ENTRY(IShellExtInit)
	COM_INTERFACE_ENTRY(IContextMenu)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

protected:
	HBITMAP m_AkdanBmp;
	std::vector<std::basic_string<TCHAR>> m_vecFiles;

public:
	//IShellExtInit 내부 가상함수 구현
	STDMETHODIMP Initialize(LPCITEMIDLIST pidFolder, LPDATAOBJECT pDataObj, HKEY hProgID);

	// IContextMenu 내부 가상함수 구현
	STDMETHODIMP GetCommandString(UINT_PTR idCmd, UINT uFlags, UINT* pwReserved, LPSTR pszName, UINT cchMax);
	STDMETHODIMP InvokeCommand(LPCMINVOKECOMMANDINFO pCmdInfo);
	STDMETHODIMP QueryContextMenu(HMENU hMenu, UINT uMenuIndex, UINT uidFirstCmd, UINT uidLastCmd, UINT uFlags);
};

OBJECT_ENTRY_AUTO(__uuidof(ATLSimpleObject), CATLSimpleObject)
