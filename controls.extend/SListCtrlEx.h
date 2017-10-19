/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�(ˮľ֮��
 * All rights reserved.
 * 
 * @file       SListCtrlex.h
 * @brief      
 * @version    v1.0      
 * @author     soui      
 * @date       2015-02-05
 * 
 * Describe    ��չ�б�� 
 */ 
#pragma  once

#include <core/SPanel.h>
#include <core/Sitempanel.h>
#include <control/SHeaderCtrl.h>

namespace SOUI
{
/** 
 * @class     SListBox
 * @brief     ��չ�б��
 *
 * Describe   ��չ�б��
 */
#define IDC_LSTCEX_SELECT -300
class SListCtrlEx :public SScrollView
    ,public IItemContainer
{
public:

    SOUI_CLASS_NAME(SListCtrlEx, L"listctrlex")
    
    /**
     * SListCtrlEx::SListBox
     * @brief    ���캯��
     *
     * Describe  ���캯��  
     */
    SListCtrlEx();

    /**
     * SListBox::~SListBox
     * @brief    ��������
     *
     * Describe  ��������  
     */
    virtual ~SListCtrlEx();

    /**
     * SListCtrlEx::DeleteAllItems
     * @brief    ɾ������
     * @param    BOOL bUpdate -- �Ƿ����
     *
     * Describe  ɾ������
     */
    void DeleteAllItems(BOOL bUpdate=TRUE);

    /**
     * SListCtrlEx::DeleteItem
     * @brief    ɾ��ָ����
     * @param    int iItem -- ����
     *
     * Describe  ɾ��ָ����
     */
    void DeleteItem(int iItem);

    /**
     * SListCtrlEx::InsertItem
     * @brief    ��������
     * @param    int iItem -- ����
     * @param    pugi::xml_node xmlNode -- xml�ļ�
     * @param    DWORD dwData  --  ��������
     *
     * Describe  ��ĳ��֮�����
     */
    int InsertItem(int iItem,pugi::xml_node xmlNode,LPARAM dwData=0);

    /**
     * SListCtrlEx::InsertItem
     * @brief    ��������
     * @param    int iItem -- ����
     * @param    LPCWSTR pszXml -- xml�ļ�
     * @param    DWORD dwData  --  ��������
     *
     * Describe  ��ĳ��֮�����
     */
    int InsertItem(int iItem,LPCWSTR pszXml,LPARAM dwData=0);
    
    /**
     * SListCtrlEx::SetCurSel
     * @brief    ����ѡ����
     * @param    int nIndex -- ��ѡ������
     *
     * Describe  ����ѡ����
     */
    BOOL SetCurSel(int iItem);

    /**
     * SListCtrlEx::EnsureVisible
     * @brief    ����ĳ����ʾ
     * @param    int nIndex  -- ����
     *
     * Describe  ����ĳ����ʾ
     */
    void EnsureVisible(int iItem);

    /**
     * SListCtrlEx::GetCurSel
     * @brief    ��ȡ��ǰѡ��������
     * @return   ����int
     *
     * Describe  ��ȡ��ǰѡ��������
     */
    int GetCurSel();


    /**
     * SListCtrlEx::GetItemPanel
     * @brief    ��ȡָ����ṹ
     * @param    int iItem -- ����
     * @return   ����SWindow
     *
     * Describe  ��ȡָ��������
     */
    SWindow * GetItemPanel(int iItem);

    /**
     * SListCtrlEx::GetItemData
     * @brief    ��ȡ��������
     * @param    int nIndex -- ѡ������
     * @return   ����LPARAM
     *
     * Describe  ��ȡ��������
     */
    LPARAM GetItemData(int iItem);

    /**
     * SListCtrlEx::SetItemData
     * @brief    ����ѡ�������
     * @param    int nIndex -- ѡ������
     * @param    LPARAM lParam  -- ��������
     * @return   ����BOOL
     *
     * Describe  ����ѡ�������
     */
    void SetItemData(int iItem,LPARAM lParam);

    /**
     * SListCtrlEx::SetItemCount
     * @brief    ������Ŀ����
     * @param    int nItems ��Ŀ����
     * @param    LPCTSTR pszXmlTemplate ��ʾʱʹ�õ�XMLģ�壬
     *           Ϊ��ʱʹ��XML�ű���ָ����template�ӽڵ�����
     * @return   ������Ŀ����
     *
     * Describe  ����ѡ�������
     */
    BOOL SetItemCount(int nItems,LPCTSTR pszXmlTemplate=NULL);

    /**
     * SListCtrlEx::GetItemCount
     * @brief    ��ȡ��Ŀ����
     * @return   ���� int 
     *
     * Describe  ��ȡ��Ŀ����
     */
    int GetItemCount() ;

    /**
     * SListCtrlEx::GetItemHeight
     * @brief    ��ȡ�߶�
     * @return   ����int 
     *
     * Describe  ��ȡ�߶�
     */
    int GetItemHeight()
    {
        return m_nItemHeight;
    }

    /**
     * SListCtrlEx::RedrawItem
     * @brief    �ػ�ѡ��
     * @param    int iItem  -- ����
     *
     * Describe  �ػ�ѡ��
     */
    void RedrawItem(int iItem);

    /**
     * SListCtrlEx::HitTest
     * @brief    ��ȡ��������Ϣ
     * @param    CPoint &pt -- ����
     *
     * Describe  �Զ��޸�pt��λ��Ϊ��Ե�ǰ���ƫ����
     */
    int HitTest(CPoint &pt);

protected:
    /**
     * SListCtrlEx::OnItemSetCapture
     * @brief     
     * @param     SItemPanel *pItem
     * @param     BOOL bCapture
     *
     * Describe  
     */    
    virtual void OnItemSetCapture(SItemPanel *pItem,BOOL bCapture);

    /**
     * SListCtrlEx::OnItemGetRect
     * @brief     
     * @param     SItemPanel *pItem
     * @param     CRect &rcItem
     *
     * Describe   
     */
    virtual BOOL OnItemGetRect(SItemPanel *pItem,CRect &rcItem);

    /**
     * SListCtrlEx::IsItemRedrawDelay
     * @brief    
     *
     * Describe  
     */
    virtual BOOL IsItemRedrawDelay(){return m_bItemRedrawDelay;}

    virtual void OnItemRequestRelayout(SItemPanel *pItem);
protected:

    /**
     * SListCtrlEx::UpdatePanelsIndex
     * @brief    ��������
     * @param    UINT nFirst
     * @param    UINT nLast
     *
     * Describe  ��������
     */   
    void UpdatePanelsIndex(UINT nFirst=0,UINT nLast=-1);

    /**
     * SListCtrlEx::GetItemRect
     * @brief    ��ȡָ��λ��
     * @param    int iItem -- ����
     * @return   ����CRect 
     *
     * Describe  ��������
     */
    CRect    GetItemRect(int iItem);

    /**
     * SListCtrlEx::OnPaint
     * @brief    ����
     * @param    IRenderTarget *pRT -- �����豸
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnPaint(IRenderTarget * pRT);

    /**
     * SListCtrlEx::OnSize
     * @brief    ��Ϣ��Ӧ����
     * @param    UINT nType --
     * @param    CSize size -- 
     *
     * Describe  ��ȡĳ�������  
     */
    void OnSize(UINT nType, CSize size);

    /**
     * SListCtrlEx::DrawItem
     * @brief    ����
     * @param    IRenderTarget *pRT  -- �����豸
     * @param    CRect & rc -- λ��
     * @param    int iItem -- ����
     *
     * Describe  ����
     */
    virtual void DrawItem(IRenderTarget *pRT, CRect &rcItem, int iItem);

    /**
     * SListCtrlEx::CreateChildren
     * @brief    ��������
     * @param    pugi::xml_node xmlNode -- xml�ļ�
     *
     * Describe  ͨ������xml�ļ�����
     */
    virtual BOOL CreateChildren(pugi::xml_node xmlNode);

    /**
     * SListCtrlEx::OnUpdateToolTip
     * @brief    ������ʾ
     * @param    CPoint pt --  ��Ӧλ��
     * @param    SwndToolTipInfo & tipInfo --  ��ʾ��Ϣ
     * @return   BOOL 
     *
     * Describe  
     */
    virtual BOOL OnUpdateToolTip(CPoint pt, SwndToolTipInfo & tipInfo);

    /**
     * SListCtrlEx::NotifySelChange
     * @brief    �޸�ѡ����
     * @param    int nOldSel -- ��ѡ����
     * @param    int nNewSel -- ��ѡ����
     *
     * Describe  �޸�ѡ����
     */
    void NotifySelChange(int nOldSel,int nNewSel, BOOL checkBox = FALSE);

    /**
     * SListCtrlEx::OnMouseEvent
     * @brief    �Զ�����Ϣ��Ӧ����
     * @param    UINT uMsg -- �����Ϣ����
     * @param    WPARAM wParam -- wParam
     * @param    LPARAM lParam -- lParam
     * @return   ����LRESULT
     *
     * Describe  �Զ�����Ϣ��Ӧ����
     */
    LRESULT OnMouseEvent(UINT uMsg,WPARAM wParam,LPARAM lParam);

    /**
     * SListCtrlEx::OnKeyEvent
     * @brief    �Զ�����Ϣ��Ӧ����
     * @param    UINT uMsg -- ������Ϣ����
     * @param    WPARAM wParam -- wParam
     * @param    LPARAM lParam -- lParam
     * @return   ����LRESULT
     * 
     * Describe  �Զ�����Ϣ��Ӧ����
     */
    LRESULT OnKeyEvent( UINT uMsg,WPARAM wParam,LPARAM lParam );

    /**
     * SListCtrlEx::OnMouseLeave
     * @brief    �Զ�����Ϣ��Ӧ����
     * 
     * Describe  �Զ�����Ϣ��Ӧ����
     */
    void OnMouseLeave();

    /**
     * SListCtrlEx::OnMouseWheel
     * @brief    �������¼�
     * @param    UINT nFlags -- ��־
     * @param    short zDelta -- ���ֹ����ľ���
     * @param    CPoint pt -- ����
     * @return   ����BOOL
     * 
     * Describe  �������¼�
     */
    BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);

    /**
     * SListCtrlEx::OnKeyDown
     * @brief    ��������
     * @param    TCHAR nChar -- ����ֵ
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );

    /**
     * SListCtrlEx::OnChar
     * @brief    ��������
     * @param    TCHAR nChar -- ����ֵ
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     *
     * Describe  ��Ϣ��Ӧ���� 
     */
    void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

    /**
     * SListCtrlEx::OnGetDlgCode
     * @brief    ��ȡ������Ϣ��
     * @param    ����UINT
     *
     * Describe  ��ȡ������Ϣ��
     */
    UINT OnGetDlgCode();

    /**
     * SListCtrlEx::OnSetCursor
     * @brief    �������λ��
     * @param    ����BOOL
     *
     * Describe  �������λ��
     */
    virtual BOOL OnSetCursor(const CPoint &pt);

    /**
     * SListCtrlEx::OnViewOriginChanged
     * @brief    
     * @param    CPoint ptOld  --
     * @param    CPoint ptNew  -- 
     *
     * Describe  
     */
    virtual void OnViewOriginChanged(CPoint ptOld,CPoint ptNew);

    /**
     * SListCtrlEx::OnDestroy
     * @brief    ����
     *
     * Describe  ����
     */
    void OnDestroy();

    /**
     * SListCtrlEx::OnSetFocus
     * @brief    ��ý���
     *
     * Describe  ��ý���
     */
    void OnSetFocus(SWND wndOld);

    /**
     * SListCtrlEx::OnKillFocus
     * @brief    ʧȥ����
     *
     * Describe  ʧȥ����
     */
    void OnKillFocus(SWND wndFocus);

    /**
     * SListCtrlEx::OnNcCalcSize
     * @brief    ����ǿͻ�����С
     * @param    BOOL bCalcValidRects -- ��С
     * @param    LPARAM lParam -- ���Ӳ���
     * Describe  ����ǿͻ�����С
     */
    LRESULT OnNcCalcSize(BOOL bCalcValidRects, LPARAM lParam);

    /**
     * SListCtrlEx::Relayout
     * @brief    ���²���
     *
     * Describe  ���²���
     */
    void Relayout();
protected:
	SArray<SItemPanel *> m_arrItems;  /**< ������Ŀ������ */
    int        m_nItemHeight;     /**< �߶�          */
    int        m_iSelItem;     /**< ѡ����Ŀ      */
    int        m_iHoverItem;   /**< Hover״̬��Ŀ */
    int        m_iScrollSpeed; /**< �����ٶ�      */
	BOOL    m_bHotTrack;    /**<  */

    pugi::xml_document m_xmlTempl;     /**< �б�ģ��XML */
    SItemPanel   *m_pCapturedFrame;    /**< ��ǰ������setcapture���б��� */
    ISkinObj     *m_pItemSkin;         /**< �б���ı���skin */
	SStringW m_strSelectRangeSkin;         /**< ѡ���skin */
    COLORREF     m_crItemBg;           /**< ����ɫ */
    COLORREF     m_crItemSelBg;        /**< ѡ�б���ɫ */
	COLORREF     m_crItemHotBg;        /**< Hot����ɫ */
    BOOL       m_bItemRedrawDelay;     /**< �����ػ�ʱ���� */      
	SWindow *m_pWndRectangle;  /**< ����ѡ��� */
	CRect m_rcWnd;/**< ѡ���λ�� */
	CPoint m_ptTmp;
	BOOL m_bMouseDown;
	BOOL m_bStartSelect;
	BOOL m_bCheckBox;
	BOOL m_bMultiSelection;
	CPoint m_ptOrigin;  /**< */
	 int GetTopIndex() const;
	 virtual BOOL OnScroll(BOOL bVertical,UINT uCode,int nPos);
	 void UpdateHeaderCtrl();
	 CRect GetListRect();
	 int             m_nHeaderHeight;  /**< �б�ͷ�߶� */
	 SHeaderCtrl*  m_pHeader;  /**< �б�ͷ�ؼ� */
	 int InsertColumn(int nIndex, LPCTSTR pszText, int nWidth, LPARAM lParam=0);
	virtual void    UpdateChildrenPosition();
	 virtual void UpdateScrollBar();
	int GetCountPerPage(BOOL bPartial);
	bool OnHeaderClick(EventArgs *pEvt);
	bool OnHeaderSizeChanging(EventArgs *pEvt);
	bool OnHeaderSwap(EventArgs *pEvt);
	int GetColumnCount() const;
public:
    SOUI_ATTRS_BEGIN()
		ATTR_INT(L"headerHeight", m_nHeaderHeight, FALSE)
        ATTR_INT(L"itemHeight", m_nItemHeight, FALSE)
        ATTR_SKIN(L"itemSkin", m_pItemSkin, TRUE) 
		ATTR_STRINGW(L"selectRangeSkin", m_strSelectRangeSkin, FALSE)
        ATTR_COLOR(L"colorItemBkgnd",m_crItemBg,FALSE)
        ATTR_COLOR(L"colorItemSelBkgnd",m_crItemSelBg,FALSE)
		ATTR_COLOR(L"colorItemHotBkgnd",m_crItemHotBg,FALSE)
        ATTR_INT(L"itemRedrawDelay", m_bItemRedrawDelay, TRUE)
		ATTR_INT(L"hotTrack",m_bHotTrack,FALSE)
		ATTR_INT(L"multiSelection", m_bMultiSelection, TRUE)
    SOUI_ATTRS_END()

    SOUI_MSG_MAP_BEGIN()
        MSG_WM_MOUSEWHEEL(OnMouseWheel)
        MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST,WM_MOUSELAST,OnMouseEvent)
        MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST,WM_KEYLAST,OnKeyEvent)
        MESSAGE_RANGE_HANDLER_EX(WM_IME_STARTCOMPOSITION,WM_IME_KEYLAST,OnKeyEvent)
        MESSAGE_HANDLER_EX(WM_IME_CHAR,OnKeyEvent)
        MSG_WM_DESTROY(OnDestroy)
        MSG_WM_PAINT_EX(OnPaint)
        MSG_WM_MOUSELEAVE(OnMouseLeave)
        MSG_WM_KEYDOWN(OnKeyDown)
        MSG_WM_CHAR(OnChar)
        MSG_WM_SIZE(OnSize)
        MSG_WM_SETFOCUS_EX(OnSetFocus)
        MSG_WM_KILLFOCUS_EX(OnKillFocus)
        MSG_WM_NCCALCSIZE(OnNcCalcSize)
    SOUI_MSG_MAP_END()
};

}//namespace SOUI