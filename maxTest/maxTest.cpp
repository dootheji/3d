// maxTest.cpp : DLL 응용 프로그램을 위해 내보낸 함수를 정의합니다.
//

#include "stdafx.h"
#define maxTest_CLASS_ID Class_ID(0x5602186a, 0x62f34649)

class maxTest : public SceneExport
{
public:
	maxTest() {};
	~maxTest() {};
	int				ExtCount();					// Number of extensions supported
	const TCHAR *	Ext(int n);					// Extension #n (i.e. "3DS")
	const TCHAR *	LongDesc();					// Long ASCII description (i.e. "Autodesk 3D Studio File")
	const TCHAR *	ShortDesc();				// Short ASCII description (i.e. "3D Studio")
	const TCHAR *	AuthorName();				// ASCII Author name
	const TCHAR *	CopyrightMessage();			// ASCII Copyright message
	const TCHAR *	OtherMessage1();			// Other message #1
	const TCHAR *	OtherMessage2();			// Other message #2
	unsigned int	Version();					// Version number * 100 (i.e. v3.01 = 301)
	void			ShowAbout(HWND hWnd);		// Show DLL's "About..." box
	int  DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts = FALSE, DWORD options = 0);

};


int  maxTest::DoExport(const TCHAR *name, ExpInterface *ei, Interface *i, BOOL suppressPrompts, DWORD options)
{
	return true;
}


class maxExportClassDesc : public ClassDesc2
{
public:
	virtual int IsPublic() { return TRUE; }
	virtual void* Create(BOOL) { return new maxTest(); }
	virtual const TCHAR *	ClassName() { return _T("maxTest100"); }
	virtual SClass_ID SuperClassID() { return SCENE_EXPORT_CLASS_ID; }
	virtual Class_ID ClassID() { return maxTest_CLASS_ID; }
	virtual const TCHAR* Category() { return _T("maxTester"); }

	virtual const TCHAR* InternalName() { return _T("maxExportClassDesc"); }	// returns fixed parsable name (scripter-visible name)
	virtual HINSTANCE HInstance() { return hInstance; }
};

ClassDesc2* GetExportDesc() {
	static maxExportClassDesc maxExportDesc;
	return &maxExportDesc;
}

int	maxTest::ExtCount()
{
#pragma message(TODO("Returns the number of file name extensions supported by the plug-in."))
	return 1;
}
const TCHAR * maxTest::Ext(int n)
{
#pragma message(TODO("Return the 'i-th' file name extension (i.e. \"3DS\")."))
	return _T("symax");

}
const TCHAR *	maxTest::LongDesc()
{
#pragma message(TODO("Return long ASCII description (i.e. \"Targa 2.0 Image File\")"))
	return _T("symax Expoter 2.0");
}
const TCHAR *	maxTest::ShortDesc()
{
#pragma message(TODO("Return short ASCII description (i.e. \"Targa\")"))
	return _T("symaxexporter");
}
const TCHAR *	maxTest::AuthorName()
{
#pragma message(TODO("Return ASCII Author name"))
	return _T("sy");
}
const TCHAR *	maxTest::CopyrightMessage()
{
#pragma message(TODO("Return ASCII Copyright message"))
	return _T("");
}
const TCHAR *	maxTest::OtherMessage1()
{
	//TODO: Return Other message #1 if any
	return _T("");
}
const TCHAR *	maxTest::OtherMessage2()
{
	//TODO: Return other message #2 in any
	return _T("");
}
unsigned int	maxTest::Version()
{
#pragma message(TODO("Return Version number * 100 (i.e. v3.01 = 301)"))
	return 100;
}
void			maxTest::ShowAbout(HWND hWnd)
{

}