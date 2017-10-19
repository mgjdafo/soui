#pragma once
#include <core/sskin.h>

namespace SOUI
{
    /*usage
    <imgframe2 src="imgx:png_test{0,0,100,100}" xxx/>
    */
    class SSkinImgFrame2 : public SSkinImgFrame
    {
    SOUI_CLASS_NAME(SSkinImgFrame2,L"imgframe2")
    public:
        SSkinImgFrame2(void);
        ~SSkinImgFrame2(void);
        
        virtual SIZE GetSkinSize();
        
        virtual bool SetImage(IBitmap *pImg){return false;}
        
        SOUI_ATTRS_BEGIN()
            ATTR_CUSTOM(L"src",OnAttrSrc)
            /* offcut-left/right/top/bottom ��Ϊ���ͼ������ͼ֮���пհ� */
            /* ���ﶨ���Ӧ����ͼͼƬ�и���������Ҷ��٣���ֹ�и������ͼƬ�����õı���   */
            ATTR_RECT(L"offcut",m_offset,FALSE)
        SOUI_ATTRS_END()
        
    protected:
        LRESULT OnAttrSrc(const SStringW & strValue,BOOL bLoading);

        virtual void _Draw(IRenderTarget *pRT, LPCRECT rcDraw, DWORD dwState,BYTE byAlpha);

        CRect m_rcImg;
        CRect m_offset;
        SStringW m_strImgKey;
    };

}
