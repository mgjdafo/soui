//SOUI�������

#pragma  once

#include <com-def.h>
#include <string/tstring.h>

#define COM_IMGDECODER  _T("imgdecoder-gdip")

#ifdef _DEBUG
#define COM_RENDER_GDI  _T("render-gdid.dll")
#define COM_RENDER_SKIA _T("render-skiad.dll")
#define COM_SCRIPT_LUA _T("scriptmodule-luad.dll")
#define COM_TRANSLATOR _T("translatord.dll")
#define COM_ZIPRESPROVIDER _T("resprovider-zipd.dll")
#define COM_LOG4Z   _T("log4zd.dll")
#else
#define COM_RENDER_GDI  _T("render-gdi.dll")
#define COM_RENDER_SKIA _T("render-skia.dll")
#define COM_SCRIPT_LUA _T("scriptmodule-lua.dll")
#define COM_TRANSLATOR _T("translator.dll")
#define COM_ZIPRESPROVIDER _T("resprovider-zip.dll")
#define COM_LOG4Z   _T("log4z.dll")
#endif

#ifdef LIB_SOUI_COM
#pragma message("LIB_SOUI_COM")

#pragma comment(lib,"Usp10")
#pragma comment(lib,"opengl32")

#ifdef _DEBUG
    #pragma comment(lib,"skiad")
    #pragma comment(lib,"zlibd")
    #pragma comment(lib,"pngd")
    #ifdef DLL_CORE
    #pragma comment(lib,"lua-52d")
    #pragma comment(lib,"scriptmodule-luad")
    #endif
    #pragma comment(lib,"render-gdid")
    #pragma comment(lib,"render-skiad")
    #pragma comment(lib,"imgdecoder-wicd")
    #pragma comment(lib,"imgdecoder-stbd")
    #pragma comment(lib,"imgdecoder-pngd")
    #pragma comment(lib,"imgdecoder-gdipd")
    #pragma comment(lib,"translatord")
    #pragma comment(lib,"resprovider-zipd")
    #pragma comment(lib,"log4zd")
#else//_DEBUG

    #pragma comment(lib,"skia")
    #pragma comment(lib,"zlib")
    #pragma comment(lib,"png")
    #ifdef DLL_CORE
    #pragma comment(lib,"lua-52")
    #pragma comment(lib,"scriptmodule-lua")
    #endif

    #pragma comment(lib,"imgdecoder-wic")
    #pragma comment(lib,"imgdecoder-stb")
    #pragma comment(lib,"imgdecoder-png")
    #pragma comment(lib,"imgdecoder-gdip")
    #pragma comment(lib,"render-gdi")
    #pragma comment(lib,"render-skia")
    #pragma comment(lib,"translator")
    #pragma comment(lib,"resprovider-zip")
    #pragma comment(lib,"log4z")
#endif//_DEBUG

namespace SOUI
{
    namespace IMGDECODOR_WIC
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace IMGDECODOR_STB
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace IMGDECODOR_PNG
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace IMGDECODOR_GDIP
    {
        BOOL SCreateInstance(IObjRef **);
    }

    namespace RENDER_GDI
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace RENDER_SKIA
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace SCRIPT_LUA
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace TRANSLATOR
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace RESPROVIDER_ZIP
    {
        BOOL SCreateInstance(IObjRef **);
    }
    namespace LOG4Z
    {
        BOOL SCreateInstance(IObjRef **);
    }
}//end of soui

class SComMgr
{
public:
    SComMgr(LPCTSTR pszImgDecoder = NULL)
    {
        if(pszImgDecoder) m_strImgDecoder = pszImgDecoder;
        else m_strImgDecoder = COM_IMGDECODER;
    }

    BOOL CreateImgDecoder(IObjRef ** ppObj)
    {
        if(m_strImgDecoder == _T("imgdecoder-wic"))
            return SOUI::IMGDECODOR_WIC::SCreateInstance(ppObj);
        else if(m_strImgDecoder == _T("imgdecoder-stb"))
            return SOUI::IMGDECODOR_STB::SCreateInstance(ppObj);
        else if(m_strImgDecoder == _T("imgdecoder-png"))
            return SOUI::IMGDECODOR_PNG::SCreateInstance(ppObj);
        else if(m_strImgDecoder == _T("imgdecoder-gdip"))
            return SOUI::IMGDECODOR_GDIP::SCreateInstance(ppObj);
        else
        {
            SASSERT(0);
            return FALSE;
        }
    }

    BOOL CreateRender_GDI(IObjRef **ppObj)
    {
        return SOUI::RENDER_GDI::SCreateInstance(ppObj);
    }

    BOOL CreateRender_Skia(IObjRef **ppObj)
    {
        return SOUI::RENDER_SKIA::SCreateInstance(ppObj);
    }
    BOOL CreateScrpit_Lua(IObjRef **ppObj)
    {
        return SOUI::SCRIPT_LUA::SCreateInstance(ppObj);
    }

    BOOL CreateTranslator(IObjRef **ppObj)
    {
        return SOUI::TRANSLATOR::SCreateInstance(ppObj);
    }
    BOOL CreateResProvider_ZIP(IObjRef **ppObj)
    {
        return SOUI::RESPROVIDER_ZIP::SCreateInstance(ppObj);
    }
    
    BOOL CreateLog4z(IObjRef **ppObj)
    {
        return SOUI::LOG4Z::SCreateInstance(ppObj);
    }

    SOUI::SStringT    m_strImgDecoder;
};

#else
	
#include <com-loader.hpp>


class SComMgr
{
public:
    SComMgr(LPCTSTR pszImgDecoder = NULL)
    {
        if(pszImgDecoder) m_strImgDecoder = pszImgDecoder;
        else m_strImgDecoder = COM_IMGDECODER;
    }

    BOOL CreateImgDecoder(IObjRef ** ppObj)
    {
#ifdef _DEBUG
        SOUI::SStringT strImgDecoder = m_strImgDecoder+_T("d.dll");
#else
        SOUI::SStringT strImgDecoder = m_strImgDecoder+_T(".dll");
#endif
        return imgDecLoader.CreateInstance(strImgDecoder,ppObj);
    }
    
    BOOL CreateRender_GDI(IObjRef **ppObj)
    {
        return renderLoader.CreateInstance(COM_RENDER_GDI,ppObj);
    }

    BOOL CreateRender_Skia(IObjRef **ppObj)
    {
        return renderLoader.CreateInstance(COM_RENDER_SKIA,ppObj);
    }
    BOOL CreateScrpit_Lua(IObjRef **ppObj)
    {
        return scriptLoader.CreateInstance(COM_SCRIPT_LUA,ppObj);
    }

    BOOL CreateTranslator(IObjRef **ppObj)
    {
        return transLoader.CreateInstance(COM_TRANSLATOR,ppObj);
    }
    BOOL CreateResProvider_ZIP(IObjRef **ppObj)
    {
        return zipResLoader.CreateInstance(COM_ZIPRESPROVIDER,ppObj);
    }

    BOOL CreateLog4z(IObjRef **ppObj)
    {
        return log4zLoader.CreateInstance(COM_LOG4Z,ppObj);
    }
protected:
    //SComLoaderʵ�ִ�DLL��ָ��������������SOUIҪ�����COM�����
    SComLoader imgDecLoader;
    SComLoader renderLoader;
    SComLoader transLoader;
    SComLoader scriptLoader;
    SComLoader zipResLoader;
    SComLoader log4zLoader;
    
    SOUI::SStringT m_strImgDecoder;
};
#endif
