// ATLSimpleObject.cpp : CATLSimpleObject 구현

#include "pch.h"
#include "ATLSimpleObject.h"


// CATLSimpleObject

STDMETHODIMP_(HRESULT __stdcall) CATLSimpleObject::Initialize(LPCITEMIDLIST pidFolder, LPDATAOBJECT pDataObj, HKEY hProgID)
{
	FORMATETC fmt = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM stg = { TYMED_HGLOBAL };
	HDROP hDrop;

	// 데이터 객체에서 CF_HDROP 데이터를 찾는다.
	// 그러한 데이터가 없다면 Windows 탐색기로 오류 코드를 반환한다.
	if (FAILED(pDataObj->GetData(&fmt, &stg)))
		return	E_INVALIDARG;

	// 실제 데이터에 대한 핸들을 얻는다.
	hDrop = (HDROP)GlobalLock(stg.hGlobal);
	// 유효한 핸들인지 검사한다.
	if (hDrop == NULL)
		return E_INVALIDARG;
	
	// 상태 확인 - 적어도 하나 이상의 파일 이름을 가지고 있는지 확인한다.
	UINT uNumFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
	HRESULT hr = S_OK;
	if (uNumFiles == 0)
	{
		GlobalUnlock(stg.hGlobal);
		ReleaseStgMedium(&stg);
		return E_INVALIDARG;
	}

	// 첫 번째 파일의 이름을 얻어와서 멤버변수 m_szFile에 보관한다.
	if (DragQueryFile(hDrop, 0, m_szFile, MAX_PATH) == 0)
		hr = E_INVALIDARG;

	GlobalUnlock(stg.hGlobal);
	ReleaseStgMedium(&stg);

	return hr;
}

STDMETHODIMP_(HRESULT __stdcall) CATLSimpleObject::GetCommandString(UINT idCmd, UINT uFlags, UINT* pwReserved, LPSTR pszName, UINT cchMax)
{
	USES_CONVERSION;
	// idCmd 검사
	// 메뉴에 하나의 항목만을 추가할 것이므로 이 값은 항상 0 이어야 함.
	if (idCmd != 0)
		return E_INVALIDARG;

	// Windows 탐색기가 도움말 문자열을 요청할 경우
	// 제공된 버퍼에 우리가 가진 문자열을 복사하면 된다.
	if (uFlags & GCS_HELPTEXT)
	{
		LPCTSTR szText = TEXT("This is the simple shell extensions' help");
		if (uFlags & GCS_UNICODE)
			lstrcpyW((LPWSTR)pszName, T2CW(szText));
		else
			lstrcpyA(pszName, T2CA(szText));
		return S_OK;
	}

	return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) CATLSimpleObject::InvokeCommand(LPCMINVOKECOMMANDINFO pCmdInfo)
{
	if (HIWORD(pCmdInfo->lpVerb) != 0)
		return E_INVALIDARG;

	switch (LOWORD(pCmdInfo->lpVerb))
	{
	case 0:
	{
		TCHAR szMsg[MAX_PATH + 32];
		wsprintf(szMsg, TEXT("The Selected File was \n\n%s"), m_szFile);
		MessageBox(pCmdInfo->hwnd, szMsg, TEXT("SimpleShlExt"), MB_ICONINFORMATION);
		return S_OK;
	}
	}
	return E_NOTIMPL;
}

STDMETHODIMP_(HRESULT __stdcall) CATLSimpleObject::QueryContextMenu(HMENU hMenu, UINT uMenuIndex, UINT uidFirstCmd, UINT uidLastCmd, UINT uFlags)
{
	// uFlags가 CMF_DEFAULTONLY를 포함하고 있다면 특별히 할 것이 없다.
	if (uFlags & CMF_DEFAULTONLY)
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 0);

	InsertMenu(hMenu, uMenuIndex, MF_BYPOSITION, uidFirstCmd, TEXT("SimpleShlExt Test Item"));

	return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, 1);
}
