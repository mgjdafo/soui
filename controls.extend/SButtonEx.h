#pragma once

namespace SOUI
{
    class SButtonEx : public SButton
    {
    SOUI_CLASS_NAME(SButtonEx,L"buttonex")
    
    enum{
    FREE_DRAW,
    VERT_ICON_TEXT,
    VERT_TEXT_ICON,
    HORZ_ICON_TEXT,
    HORZ_TEXT_ICON,
    };
    
    public:
        SButtonEx(void);
        ~SButtonEx(void);
        
        HICON SetIcon(HICON hIcon,int nIconSize);
        void  SetIconVisible(bool bVisible);
    public:
        SOUI_ATTRS_BEGIN()
            ATTR_POINT(L"pushOffset",m_ptPushOffet,TRUE)//��ѹ״̬����ƫ��
            ATTR_SKIN(L"icon",m_pIcon,TRUE) //ͼ��SKIN
            ATTR_INT(L"iconIndex",m_iIcon,TRUE)//ͼ����Skin�е�����
            ATTR_ENUM_BEGIN(L"drawMode",int,TRUE)
                ATTR_ENUM_VALUE(L"freeDraw",FREE_DRAW)
                ATTR_ENUM_VALUE(L"vertIconText",VERT_ICON_TEXT)
                ATTR_ENUM_VALUE(L"vertTextIcon",VERT_TEXT_ICON)
                ATTR_ENUM_VALUE(L"horzIconText",HORZ_ICON_TEXT)
                ATTR_ENUM_VALUE(L"horzTextIcon",HORZ_TEXT_ICON)
            ATTR_ENUM_END(m_drawMode)
            ATTR_INT(L"sepSize",m_nSepSize,TRUE)    //FREE_DRAWʱ��Ч
            ATTR_POINT(L"iconPos",m_ptIcon,TRUE)//ͼ����ʾλ��,FREE_DRAWʱ��Ч
            ATTR_POINT(L"textPos",m_ptText,TRUE)//�ı���ʾλ��,FREE_DRAWʱ��Ч
        SOUI_ATTRS_END()
        
    protected:
        virtual CSize GetDesiredSize(LPCRECT pRcContainer);
        
        CSize GetDesiredSize(IRenderTarget *pRT,LPCRECT pRcContainer);
        CSize GetIconSize();
        void DrawIcon(IRenderTarget *pRT,CRect rcIcon);
    protected:
        void OnPaint(IRenderTarget *pRT);
        
        SOUI_MSG_MAP_BEGIN()
            MSG_WM_PAINT_EX(OnPaint)
        SOUI_MSG_MAP_END()
        
    protected:
        HICON       m_hIcon;
        int         m_nIconSize;
        
        ISkinObj * m_pIcon;
        int        m_iIcon;//-1����m_pIcon��һ����ռ��Ƥ��
        CPoint     m_ptIcon;
        CPoint     m_ptText;
        CPoint     m_ptPushOffet;
        int        m_nSepSize;
        int         m_drawMode;
        bool        m_bIconVisible;
    };

}
