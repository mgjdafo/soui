#pragma once

namespace SOUI{
    class SOUI_EXP SCaret : public TObjRefImpl<IObjRef>
    {
    public:
        SCaret(SWND swnd,HBITMAP hBmp,int nWid,int nHei);
        
        virtual ~SCaret(void);
        
        virtual RECT Draw(IRenderTarget *pRT,int x, int y, BOOL bErase);
        
    protected:
        CAutoRefPtr<IBitmap>    m_bmpCaret;         /**< ģ������*/
        SWND                    m_owner;            /**< �����������*/
    };
}

