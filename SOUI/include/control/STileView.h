#pragma once

#include "core/Swnd.h"
#include "core/SItemPanel.h"
#include "interface/Adapter-i.h"
#include "helper/STileViewItemLocator.h"

namespace SOUI
{

class SOUI_EXP STileView : public SPanel
    , protected IItemContainer
{
    SOUI_CLASS_NAME(STileView, L"tileview")
    
    friend class STileViewDataSetObserver;
public:
    STileView();
    ~STileView();
    
    BOOL SetAdapter(ILvAdapter *adapter);
    
    ILvAdapter *GetAdapter()
    {
        return m_adapter;
    }
    
    STileViewItemLocator *GetItemLocator()
    {
        return m_tvItemLocator;
    }
    
    void SetItemLocator(STileViewItemLocator *pItemLocator);
    void EnsureVisible(int iItem);
    
    void SetSel(int iItem, BOOL bNotify = FALSE);
    int  GetSel()const
    {
        return m_iSelItem;
    }
    
    SItemPanel *HitTest(CPoint &pt);

protected:
    virtual void OnItemSetCapture(SItemPanel *pItem, BOOL bCapture);
    virtual BOOL OnItemGetRect(SItemPanel *pItem, CRect &rcItem);
    virtual BOOL IsItemRedrawDelay();
    virtual void OnItemRequestRelayout(SItemPanel *pItem);
    
protected:
    void onDataSetChanged();
    void onDataSetInvalidated();
    
protected:
    bool OnItemClick(EventArgs *pEvt);

protected:
    virtual BOOL OnScroll(BOOL bVertical, UINT uCode, int nPos);
    virtual int  GetScrollLineSize(BOOL bVertical);
    virtual BOOL CreateChildren(pugi::xml_node xmlNode);
    
    virtual BOOL OnUpdateToolTip(CPoint pt, SwndToolTipInfo &tipInfo);
    virtual UINT OnGetDlgCode();
    virtual BOOL OnSetCursor(const CPoint &pt);
    virtual void OnColorize(COLORREF cr);
protected:
    
    void UpdateScrollBar();
    void RedrawItem(SItemPanel *pItem);
    SItemPanel *GetItemPanel(int iItem);
    CRect CalcItemDrawRect(int iItem);//����itemʵ�ʻ��Ƶ�λ��
    
    void UpdateVisibleItems();
    
    void OnPaint(IRenderTarget *pRT);
    void OnSize(UINT nType, CSize size);
    void OnDestroy();
    
    LRESULT OnMouseEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);
    
    LRESULT OnKeyEvent(UINT uMsg, WPARAM wParam, LPARAM lParam);
    void OnKeyDown(TCHAR nChar, UINT nRepCnt, UINT nFlags);
    
    void OnMouseLeave();
    
    BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
    
    void OnKillFocus(SWND wndFocus);
    
    void OnSetFocus(SWND wndOld);
    
    SOUI_MSG_MAP_BEGIN()
    MSG_WM_PAINT_EX(OnPaint)
    MSG_WM_SIZE(OnSize)
    MSG_WM_DESTROY(OnDestroy)
    MSG_WM_MOUSEWHEEL(OnMouseWheel)
    MSG_WM_MOUSELEAVE(OnMouseLeave)
    MSG_WM_KEYDOWN(OnKeyDown)
    MSG_WM_KILLFOCUS_EX(OnKillFocus)
    MSG_WM_SETFOCUS_EX(OnSetFocus)
    MESSAGE_RANGE_HANDLER_EX(WM_MOUSEFIRST, WM_MOUSELAST, OnMouseEvent)
    MESSAGE_RANGE_HANDLER_EX(WM_KEYFIRST, WM_KEYLAST, OnKeyEvent)
    MESSAGE_RANGE_HANDLER_EX(WM_IME_STARTCOMPOSITION, WM_IME_KEYLAST, OnKeyEvent)
    SOUI_MSG_MAP_END()
    
    SOUI_ATTRS_BEGIN()
    ATTR_INT(L"marginSize", m_nMarginSize, FALSE)
    ATTR_INT(L"wantTab", m_bWantTab, FALSE)
    SOUI_ATTRS_END()
protected:
    CAutoRefPtr<ILvAdapter>           m_adapter;
    CAutoRefPtr<ILvDataSetObserver>   m_observer;
    CAutoRefPtr<STileViewItemLocator>  m_tvItemLocator;//�б��λ�ӿ�
    struct ItemInfo
    {
        SItemPanel *pItem;
        int nType;
    };
    
    int                             m_iFirstVisible;//��һ����ʾ������
    SList<ItemInfo>                 m_lstItems; //��ǰ������ʾ����
    SItemPanel                     *m_itemCapture;//The item panel that has been set capture.
    
    int                             m_iSelItem;
    SItemPanel                     *m_pHoverItem;
    
    SArray<SList<SItemPanel *> *>    m_itemRecycle; //item����վ,ÿһ����ʽ�ڻ���վ�б���һ���б��Ա��ظ�����
    
    pugi::xml_document              m_xmlTemplate;
    int                             m_nMarginSize;
    BOOL                            m_bWantTab;
    BOOL                            m_bDatasetInvalidated;
};
}
