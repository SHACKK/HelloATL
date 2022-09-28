// dllmain.h : 모듈 클래스의 선언입니다.

class CHelloATLProjectModule : public ATL::CAtlDllModuleT< CHelloATLProjectModule >
{
public :
	DECLARE_LIBID(LIBID_HelloATLProjectLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_HELLOATLPROJECT, "{e5467b0f-409b-4566-a638-955ede39099b}")
};

extern class CHelloATLProjectModule _AtlModule;
