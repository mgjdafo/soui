
// mfc.demo.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "mfc.demo.h"
#include "mfc.demoDlg.h"
#include "SouiRealWndHandler.h"
using namespace SOUI;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifdef _DEBUG
#define COM_IMGDECODER  _T("imgdecoder-wicd.dll")
#define COM_RENDER_GDI  _T("render-gdid.dll")
#else
#define COM_IMGDECODER  _T("imgdecoder-wic.dll")
#define COM_RENDER_GDI  _T("render-gdi.dll")
#endif


#ifdef _DEBUG
#define SYS_NAMED_RESOURCE _T("soui-sys-resourced.dll")
#else
#define SYS_NAMED_RESOURCE _T("soui-sys-resource.dll")
#endif


// CmfcdemoApp ����

CmfcdemoApp::CmfcdemoApp()
{
	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CmfcdemoApp ����

CmfcdemoApp theApp;


// CmfcdemoApp ��ʼ��

BOOL CmfcdemoApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();

	HRESULT hRes = CoInitialize(NULL);
	SASSERT(SUCCEEDED(hRes));

    {//��һ�����ź���Ҫ����֤���������ľֲ�������CoUninitialize()֮ǰ�ͷ�

        SComLoader imgDecLoader;
        SComLoader renderLoader;
        CAutoRefPtr<IImgDecoderFactory> pImgDecoderFactory;
        CAutoRefPtr<IRenderFactory> pRenderFactory;
        imgDecLoader.CreateInstance(COM_IMGDECODER,(IObjRef**)&pImgDecoderFactory);
        renderLoader.CreateInstance(COM_RENDER_GDI,(IObjRef**)&pRenderFactory);

        pRenderFactory->SetImgDecoderFactory(pImgDecoderFactory);

        SApplication *pSouiApp=new SApplication(pRenderFactory,theApp.m_hInstance);

        //����ϵͳ��Դ
        HMODULE hSysResource=LoadLibrary(SYS_NAMED_RESOURCE);
        if(hSysResource)
        {
            CAutoRefPtr<IResProvider> sysSesProvider;
            CreateResProvider(RES_PE,(IObjRef**)&sysSesProvider);
            sysSesProvider->Init((WPARAM)hSysResource,0);
            pSouiApp->LoadSystemNamedResource(sysSesProvider);
        }

        CAutoRefPtr<IResProvider>   pResProvider;
        CreateResProvider(RES_PE,(IObjRef**)&pResProvider);
        pResProvider->Init((WPARAM)theApp.m_hInstance,0);

        pSouiApp->AddResProvider(pResProvider);    //����Դ����Ƥ��

        //�����洰�ڴ���ӿ�
        CSouiRealWndHandler * pRealWndHandler = new CSouiRealWndHandler();
        pSouiApp->SetRealWndHandler(pRealWndHandler);
        pRealWndHandler->Release();

	    CmfcdemoDlg dlg;
	    m_pMainWnd = &dlg;
	    dlg.DoModal();
    	
        delete pSouiApp;

    }

	CoUninitialize();

	return FALSE;
}
