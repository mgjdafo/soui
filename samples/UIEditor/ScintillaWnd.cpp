// ScintillaWnd.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "ScintillaWnd.h"
#include <shlwapi.h>

#include "Scintilla.h"
#include "SciLexer.h"

#define STR_SCINTILLAWND _T("Scintilla")
#define STR_SCINTILLADLL _T("SciLexer.dll")

//////////////////////////////////////////////////////////////////////////
CScintillaModule::CScintillaModule()
{
	m_hModule=LoadLibrary(STR_SCINTILLADLL);
}

CScintillaModule::~CScintillaModule()
{
	if(m_hModule) FreeLibrary(m_hModule);
}

//////////////////////////////////////////////////////////////////////////

// CScintillaWnd
const COLORREF black = RGB(0,0,0);
const COLORREF white = RGB(0xff,0xff,0xff);
const COLORREF orange = RGB(0x80, 0x80, 0);
const COLORREF darkGreen = RGB(0, 0x80, 0);
const COLORREF darkBlue = RGB(0x80, 0x80, 0);
const COLORREF red = RGB(1,0,0);
const COLORREF yellow = RGB(1,1,0);
const COLORREF liteBlue = RGB(0x80,0x80,1);

static const int MARGIN_SCRIPT_FOLD_INDEX = 1;

CScintillaWnd::CScintillaWnd()
{
	
}

CScintillaWnd::~CScintillaWnd()
{
}

BOOL CScintillaWnd::Create(LPCTSTR lpszWindowName, DWORD dwStyle, const RECT& rect, HWND hParent, UINT nID,HINSTANCE hInst)
{
	HWND hWnd=CreateWindowEx(WS_EX_CLIENTEDGE, STR_SCINTILLAWND, lpszWindowName, dwStyle,rect.left,rect.top,rect.right-rect.left,rect.bottom-rect.top, hParent,(HMENU)nID,hInst,NULL);
	if(!hWnd) return FALSE;
	SubclassWindow(hWnd);
	InitScintillaWnd();
	return TRUE;
}

// ��ʾ�к�
void CScintillaWnd::UpdateLineNumberWidth(void)
{
	char tchLines[32];    
	int  iLineMarginWidthNow;    
	int  iLineMarginWidthFit;  

	sprintf((tchLines),(" %i "),    
		SendMessage(SCI_GETLINECOUNT,0,0)); 

	iLineMarginWidthNow = SendMessage(    
		SCI_GETMARGINWIDTHN,0,0);    
	iLineMarginWidthFit = SendMessage(    
		SCI_TEXTWIDTH,STYLE_LINENUMBER,(LPARAM)tchLines);    

	if (iLineMarginWidthNow != iLineMarginWidthFit)     
	{    
		SendMessage(SCI_SETMARGINWIDTHN,0,    
			iLineMarginWidthFit);   
	} 
}

/***********************************************************************
 *             map_fileW
 *
 * Helper function to map a file to memory:
 *  name			-	file name
 *  [RETURN] ptr		-	pointer to mapped file
 *  [RETURN] filesize           -       pointer size of file to be stored if not NULL
 */
static const LPBYTE map_file( LPCTSTR name, LPDWORD filesize )
{
    HANDLE hFile, hMapping;
    LPBYTE ptr = NULL;

    hFile = CreateFile( name, GENERIC_READ, FILE_SHARE_READ, NULL,
                         OPEN_EXISTING, FILE_FLAG_RANDOM_ACCESS, 0 );
    if (hFile != INVALID_HANDLE_VALUE)
    {
        hMapping = CreateFileMapping( hFile, NULL, PAGE_READONLY, 0, 0, NULL );
        if (hMapping)
        {
            ptr =(LPBYTE) MapViewOfFile( hMapping, FILE_MAP_READ, 0, 0, 0 );
            CloseHandle( hMapping );
            if (filesize)
                *filesize = GetFileSize( hFile, NULL );
        }
        CloseHandle( hFile );
    }
    return ptr;
}

BOOL CScintillaWnd::OpenFile(LPCTSTR lpFileName)
{
	DWORD dwSize=0;
	const LPBYTE pbuf=map_file(lpFileName,&dwSize);
	if(!pbuf) return FALSE;
	SStringA str;
	if(dwSize>2 && pbuf[0]==0xFF  && pbuf[1]==0xFE)
	{//utf16
		SStringW strBuf((LPCWSTR)(pbuf+2),dwSize/2-1);
		str=S_CW2A(strBuf,CP_UTF8);
	}else if(dwSize>3 && pbuf[0]==0xEF && pbuf[1]==0xBB && pbuf[2]==0xBF)
	{//utf8��ǩ��
		str=SStringA((LPCSTR)(pbuf+3),dwSize-3);
	}else
	{//utf8��ǩ��
        str=SStringA((LPCSTR)pbuf,dwSize);
	}
	UnmapViewOfFile( pbuf );
	SendMessage(SCI_CLEARALL);
	SendMessage(SCI_ADDTEXT, str.GetLength(),
		reinterpret_cast<LPARAM>((LPCSTR)str));

	SendMessage(SCI_SETUNDOCOLLECTION, 1);
	::SetFocus(m_hWnd);
	SendMessage(EM_EMPTYUNDOBUFFER);
	SendMessage(SCI_SETSAVEPOINT);
	SendMessage(SCI_GOTOPOS, 0);
	UpdateLineNumberWidth();

	m_strFileName=lpFileName;
	return TRUE;
}



void CScintillaWnd::GetRange(int start, int end, char* text)
{
	TEXTRANGEA tr;
	tr.chrg.cpMin = start;
	tr.chrg.cpMax = end;
	tr.lpstrText = (text);
	SendMessage(EM_GETTEXTRANGE, 0, reinterpret_cast<LPARAM>(&tr));
}

#define BLOCKSIZE	1024
BOOL CScintillaWnd::SaveFile( LPCTSTR lpFileName )
{
	FILE *f=_tfopen(lpFileName,_T("wb"));
	if(!f) return FALSE;
	BYTE bom[3]={0xef,0xbb,0xbf};
	fwrite(bom,3,1,f);

	char data[BLOCKSIZE + 1];
	int lengthDoc = SendMessage(SCI_GETLENGTH);
	for (int i = 0; i < lengthDoc; i += BLOCKSIZE) {
		int grabSize = lengthDoc - i;
		if (grabSize > BLOCKSIZE)
			grabSize = BLOCKSIZE;
		GetRange(i, i + grabSize, data);
		fwrite(data,1,grabSize,f);
	}
	fclose(f);
	return TRUE;
}

void CScintillaWnd::InitScintillaWnd(void)
{
	SendMessage(SCI_SETCODEPAGE,SC_CP_UTF8);//UTF8
	SendMessage(SCI_USEPOPUP,0,0); //�ر��Ҽ��˵������ɸ�����view����Ӧ


	//����ȫ��Ĭ��style��Ĭ��styleֻ��û����ȷ��ѡ��ʱ�ᱻӦ��
	SetAStyle(STYLE_DEFAULT, black, white, 11, "����");
	SendMessage(SCI_STYLECLEARALL);	// ��ȫ��Ĭ��styleӦ�õ�����
	
	//�������Ĭ�ϵ�Ctrl��ݼ���Ϣ,�����������
	char key = 'A';
	while (key <= 'Z')
	{
		int keyDefinition = key + (SCMOD_CTRL << 16);
		SendMessage(SCI_CLEARCMDKEY,(WPARAM)keyDefinition,(LPARAM)0);
		keyDefinition = key + ((SCMOD_CTRL+SCMOD_ALT) << 16);
		SendMessage(SCI_CLEARCMDKEY,(WPARAM)keyDefinition,(LPARAM)0);
		keyDefinition = key + ((SCMOD_CTRL+SCMOD_SHIFT) << 16);
		SendMessage(SCI_CLEARCMDKEY,(WPARAM)keyDefinition,(LPARAM)0);
		key += 1;
	}
	//�Զ����
	SendMessage(SCI_AUTOCSETSEPARATOR, static_cast<WPARAM>(10), 0);
	
	//��ʾ��ǰ�еĵ���ɫ����
	SendMessage(SCI_SETCARETLINEVISIBLE,TRUE,0);
	SendMessage(SCI_SETCARETLINEBACK, RGB(210,210,210),0);
	SendMessage(SCI_SETCARETLINEBACKALPHA,100,0);

	SetXmlLexer();
	UpdateLineNumberWidth();
}

void CScintillaWnd::SetAStyle(int style, COLORREF fore, COLORREF back, int size, const char* face)
{
	SendMessage(SCI_STYLESETFORE, style, fore);
	SendMessage(SCI_STYLESETBACK, style, back);
	if (size >= 1)
		SendMessage(SCI_STYLESETSIZE, style, size);
	if (face) 
		SendMessage(SCI_STYLESETFONT, style, reinterpret_cast<LPARAM>(face));
}

void CScintillaWnd::SetXmlLexer()
{
	SendMessage(SCI_SETLEXER, SCLEX_XML);
	SendMessage(SCI_SETSTYLEBITS, 7);

	// ����ȫ��style. ��Щ���Ի���������ѡ��ʱ��Ӧ��.
	SetAStyle(STYLE_DEFAULT, black, white, 11, "Verdana");
	SendMessage(SCI_STYLECLEARALL);

	const COLORREF CR_RED = RGB(0xFF, 0, 0);
	const COLORREF CR_OFFWHITE = RGB(0xFF, 0xFB, 0xF0);
	const COLORREF CR_DARKGREEN = RGB(0, 0x80, 0);
	const COLORREF CR_DARKBLUE = RGB(0, 0, 0x80);

	SendMessage(SCI_STYLESETBOLD, STYLE_CONTROLCHAR, 1); 
	// Hypertext default is used for all the document's text
	SetAStyle(SCE_H_DEFAULT, black, white, 11, "����");

	SetAStyle(SCE_H_TAG, 128);
	SetAStyle(SCE_H_TAGEND, 128);
	SetAStyle(SCE_H_ATTRIBUTE, CR_RED);
	SetAStyle(SCE_H_NUMBER, RGB(0x80,0,0x80));
	SetAStyle(SCE_H_DOUBLESTRING, RGB(0,0,0x80));
	SetAStyle(SCE_H_SINGLESTRING, RGB(0,0,0x80));
	SetAStyle(SCE_H_OTHER, RGB(0x80,0,0x80));
	SetAStyle(SCE_H_COMMENT, RGB(0,0x80,0));
	SetAStyle(SCE_H_ENTITY, RGB(0x80,0,0x80));

	SetAStyle(SCE_H_XMLSTART, CR_DARKBLUE);	// <?
	SetAStyle(SCE_H_XMLEND, CR_DARKBLUE);		// ?>

	SetAStyle(SCE_HB_DEFAULT, black);
	SetAStyle(SCE_HB_COMMENTLINE, CR_DARKGREEN);
	SetAStyle(SCE_HB_NUMBER, RGB(0,0x80,0x80));
	SetAStyle(SCE_HB_WORD, CR_DARKBLUE);
	SendMessage(SCI_STYLESETBOLD, SCE_HB_WORD, 1);
	SetAStyle(SCE_HB_STRING, RGB(0x80,0,0x80));
	SetAStyle(SCE_HB_IDENTIFIER, black);

	const COLORREF lightBlue = RGB(0xA6, 0xCA, 0xF0);

	SendMessage(SCI_STYLESETBACK, SCE_HB_STRINGEOL, RGB(0x7F,0x7F,0xFF));
	SendMessage(SCI_STYLESETFONT, SCE_HB_COMMENTLINE, 
		reinterpret_cast<LPARAM>("����"));


	// ���ô����۵�����
	SendMessage(SCI_SETPROPERTY, (WPARAM)"fold", (LPARAM)"1");
	SendMessage(SCI_SETPROPERTY, (WPARAM)"fold.compact", (LPARAM)"0");
	SendMessage(SCI_SETPROPERTY, (WPARAM)"fold.html", (LPARAM)"1");
	SendMessage(SCI_SETPROPERTY, (WPARAM)"fold.html.preprocessor", (LPARAM)"1");
	SendMessage(SCI_SETMARGINWIDTHN, MARGIN_SCRIPT_FOLD_INDEX, 0);
	SendMessage(SCI_SETMARGINTYPEN,  MARGIN_SCRIPT_FOLD_INDEX, SC_MARGIN_SYMBOL);
	SendMessage(SCI_SETMARGINMASKN, MARGIN_SCRIPT_FOLD_INDEX, SC_MASK_FOLDERS);
	SendMessage(SCI_SETMARGINWIDTHN, MARGIN_SCRIPT_FOLD_INDEX, 20);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDER, SC_MARK_PLUS); //�۵�ʱ��ʾ +
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPEN, SC_MARK_MINUS); //��ʱ��ʾ -
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEREND, SC_MARK_EMPTY);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERMIDTAIL, SC_MARK_EMPTY);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDEROPENMID, SC_MARK_EMPTY);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERSUB, SC_MARK_EMPTY);
	SendMessage(SCI_MARKERDEFINE, SC_MARKNUM_FOLDERTAIL, SC_MARK_EMPTY);

	SendMessage(SCI_SETFOLDFLAGS, 16, 0); // 16  �۵����һ����

	SendMessage(SCI_SETMARGINSENSITIVEN, MARGIN_SCRIPT_FOLD_INDEX, 1);
	//---------�����۵��������-----------
}

LRESULT CScintillaWnd::OnNotify( int idCtrl, LPNMHDR pnmh )
{
	if(pnmh->hwndFrom!=m_hWnd) return 0;
	LRESULT lRet=0;
	SCNotification *pSCNotification = (SCNotification*)pnmh;
	switch(pnmh->code)
	{
	case SCN_MARGINCLICK:
		{
			int nLine = SendMessage(SCI_LINEFROMPOSITION,(WPARAM)pSCNotification->position);
			SendMessage(SCI_TOGGLEFOLD,(WPARAM)nLine);
		}
		break;
	default:
		break;
	}
	return lRet;
}