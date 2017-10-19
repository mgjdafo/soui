//////////////////////////////////////////////////////////////////////////
// RichEditObj.h
// 

#pragma once
#include <TOM.h>
#include "core/Sobject.h"
#include "unknown/obj-ref-impl.hpp"
#include "res.mgr/SFontPool.h"
#include "interface/render-i.h"
#include <atlcomcli.h>
#include "IRichEditObjHost.h"

#define REOBJ_FIRST   ((RichEditObj*)-1)    /*�Ӷ�������ڿ�ͷ*/
#define REOBJ_LAST    NULL                  /*�Ӷ��������ĩβ*/

#define DECLARE_REOBJ(obj,name) \
    SOUI_CLASS_NAME(obj,name) \
    static RichEditObj* CreateObject(){ return new obj; }

class RichEditObj : public SObject
{
public:
    enum AlignType
    {
        ALIGN_LEFT,
        ALIGN_CENTER,
        ALIGN_RIGHT
    };

    RichEditObj();
    virtual ~RichEditObj();

    ULONG               AddRef();
    ULONG               Release();

    virtual BOOL        InitFromXml(pugi::xml_node xmlNode);
    virtual void        DrawObject(IRenderTarget *);
    virtual LRESULT     ProcessMessage(UINT msg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
    virtual BOOL        OnUpdateToolTip(CPoint pt, SwndToolTipInfo &tipInfo);
    virtual BOOL        InsertIntoHost(IRichEditObjHost * pHost);
    virtual void        UpdatePosition();
    virtual void        SetDirty(BOOL);
    virtual BOOL        NeedToProcessMessage()      {return FALSE; }
    virtual AlignType   GetAlign()                  { return m_alignType; }
    virtual void        SetAlign(AlignType align)   { m_alignType = align; }
    virtual CRect       GetRect()                   { return m_rcObj; }
    virtual void        OffsetCharRange(int nOffset);
    CHARRANGE           GetCharRange()              { return m_chrContent; }
    SStringW            GetId()                     { return m_strId; }
    void                AdjustMessageParam(UINT msg, WPARAM& wParam, LPARAM& lParam);

    //
    // ������
    //
    UINT                GetChildrenCount();
    void                InsertChild(RichEditObj *pNewChild, RichEditObj *pInsertAfter=REOBJ_LAST);
    BOOL                RemoveChild(RichEditObj *pChild);
    BOOL                CreateChildren(pugi::xml_node xmlNode);
    RichEditObj *       GetById(LPCWSTR lpszId);
    RichEditObj *       FindChildByName(LPCWSTR pszName , int nDeep=-1);
    RichEditObj *       GetParent()     const { return m_pParent; }
    RichEditObj *       GetNext()       const { return m_pNextSibling; }
    RichEditObj *       GetPrev()       const { return m_pPrevSibling; }
    RichEditObj *       GetLastChild()  const { return m_pLastChild; }
    RichEditObj *       GetFirstChild() const { return m_pFirstChild; }
    void                DestroyObject();
    BOOL                DestroyChild(RichEditObj * pChild);
    void                OnDestroy();

protected:

    SOUI_ATTRS_BEGIN()
        ATTR_RECT(L"margin", m_rcMargin, FALSE)
        ATTR_STRINGW(L"id", m_strId, FALSE)
        ATTR_STRINGW(L"name", m_strName, FALSE)
        ATTR_ENUM_BEGIN(L"align",AlignType,FALSE)
            ATTR_ENUM_VALUE(L"left",ALIGN_LEFT)
            ATTR_ENUM_VALUE(L"center",ALIGN_CENTER)
            ATTR_ENUM_VALUE(L"right",ALIGN_RIGHT)
        ATTR_ENUM_END(m_alignType)
    SOUI_ATTRS_END()

    RichEditObj *       m_pParent;          /**< ���ڵ� */
    RichEditObj *       m_pFirstChild;      /**< ��һ�ӽڵ� */
    RichEditObj *       m_pLastChild;       /**< ���ڵ� */
    RichEditObj *       m_pNextSibling;     /**< ǰһ�ֵܽڵ� */
    RichEditObj *       m_pPrevSibling;     /**< ��һ�ֵܽڵ� */
    UINT                m_nChildrenCount;   /**< �ӽڵ����� */

    ULONG               m_ulRef;
    SStringW            m_strId;
    SStringW            m_strName;
    IRichEditObjHost *  m_pObjectHost;      /**< ����richedit           */
    CHARRANGE           m_chrContent;       /**< ��richedit������ַ��±�,�����Ϣ����Ҫ*/
    CRect               m_rcMargin;         /**< �������߾�         */
    CRect               m_rcObj;            /**< ��richedit�����λ��  */
    BOOL                m_bDirty;           /**< λ����Ϣ�ı���       */
    AlignType           m_alignType;        /**< ���뷽ʽ,��ָ����Ķ��뷽ʽ*/
};

class RichEditText : public RichEditObj
{
    DECLARE_REOBJ(RichEditText, L"text")

public:
    RichEditText();
    ~RichEditText(){}

    BOOL        InitFromXml(pugi::xml_node xmlNode);
    BOOL        InsertIntoHost(IRichEditObjHost * pHost);
    int         GetLineCount() { return m_nLineCount; }

protected:
    SOUI_ATTRS_BEGIN()
        ATTR_STRINGW(L"font-face", m_strFont, FALSE)
        ATTR_COLOR(L"color", m_crText, FALSE)
        ATTR_INT(L"underline", m_bUnderline, FALSE)
        ATTR_INT(L"bold", m_bBold, FALSE)
        ATTR_INT(L"italic", m_bItalic, FALSE)
        ATTR_INT(L"font-size", m_nFontSize, FALSE)
    SOUI_ATTRS_END()

    COLORREF    m_crText;
    SStringW    m_strFont;
    SStringW    m_strText;
    int         m_nLineCount;
    BOOL        m_bUnderline;
    BOOL        m_bBold;
    BOOL        m_bItalic;
    int         m_nFontSize;
};

class RichEditBkImg : public RichEditObj
{
    DECLARE_REOBJ(RichEditBkImg, L"bkimage")

public:
    RichEditBkImg();
    ~RichEditBkImg(){}

    void    DrawObject(IRenderTarget *);
    void    CalcPosition(POSITION_ITEM * pItemsPos, int nPosCount);
    CRect   GetRect();

protected:
    HRESULT OnInternalAttrPos(POSITION_ITEM* pPosItem, int& nPosCount, const SStringW& strValue, BOOL bLoading);
    HRESULT OnAttrPos(const SStringW& strValue, BOOL bLoading);

    BOOL    ParsePosition34(POSITION_ITEM* pPosItem, const SStringW & strPos3, const SStringW &strPos4 );
    BOOL    ParsePosition12(POSITION_ITEM* pPosItem, const SStringW & strPos1, const SStringW &strPos2 );
    BOOL    StrPos2ItemPos(const SStringW &strPos, POSITION_ITEM & pos);
    int     PositionItem2Value(const POSITION_ITEM &pos ,int nMin, int nMax,BOOL bX);

    SOUI_ATTRS_BEGIN()
        ATTR_STRINGW(L"id", m_strId, TRUE)
        ATTR_STRINGW(L"src", m_strSource, TRUE)
        ATTR_CUSTOM(L"pos", OnAttrPos)
    SOUI_ATTRS_END()

    int             m_nPosCount;        /**< ������/���ж���ʱ��������� */
    POSITION_ITEM   m_itemPos[4];       /**< ��pos���Զ����ֵ, m_nPosCount >0 ʱ��Ч*/

    SStringW        m_strId;
    SStringW        m_strSource;
};

class RichEditBubble : public RichEditBkImg
{
    DECLARE_REOBJ(RichEditBubble, L"bubble")

public:
    RichEditBubble();
    ~RichEditBubble(){}
    void    DrawObject(IRenderTarget *);
    CRect   GetRect();

protected:
    HRESULT OnAttrPosRight(const SStringW& strValue, BOOL bLoading);
    HRESULT OnAttrPosLeft(const SStringW& strValue, BOOL bLoading);

    SOUI_ATTRS_BEGIN()
        ATTR_STRINGW(L"left-bubble", m_strLeftBubble, TRUE)
        ATTR_STRINGW(L"right-bubble", m_strRightBubble, TRUE)
        ATTR_CUSTOM(L"pos-left", OnAttrPosLeft)
        ATTR_CUSTOM(L"pos-right", OnAttrPosRight)
    SOUI_ATTRS_END()

    int             m_nLeftPosCount;        /**< ������/���ж���ʱ��������� */
    POSITION_ITEM   m_itemLeftPos[4];       /**< ��pos���Զ����ֵ, m_nLeftPosCount >0 ʱ��Ч*/

    int             m_nRightPosCount;       /**< �����Ҷ���ʱ��������� */
    POSITION_ITEM   m_itemRightPos[4];      /**< ��pos���Զ����ֵ, m_nRightPosCount >0 ʱ��Ч*/

    SStringW        m_strLeftBubble;
    SStringW        m_strRightBubble;
};


class RichEditAvatar : public RichEditBkImg
{
    DECLARE_REOBJ(RichEditAvatar, L"avatar")

public:
    RichEditAvatar();
    ~RichEditAvatar(){}
    void    DrawObject(IRenderTarget *);
    CRect   GetRect();

protected:
    HRESULT OnAttrPosRight(const SStringW& strValue, BOOL bLoading);
    HRESULT OnAttrPosLeft(const SStringW& strValue, BOOL bLoading);

    SOUI_ATTRS_BEGIN()
        ATTR_CUSTOM(L"pos-left", OnAttrPosLeft)
        ATTR_CUSTOM(L"pos-right", OnAttrPosRight)
    SOUI_ATTRS_END()

    int             m_nLeftPosCount;     /**< ������/���ж���ʱ��������� */
    POSITION_ITEM   m_itemLeftPos[4];    /**< ��pos���Զ����ֵ, m_nPosCount >0 ʱ��Ч*/

    int             m_nRightPosCount;    /**< �����Ҷ���ʱ��������� */
    POSITION_ITEM   m_itemRightPos[4];   /**< ��pos���Զ����ֵ, m_nLeftPosCount >0 ʱ��Ч*/
};

class RichEditPara : public RichEditObj
{
    DECLARE_REOBJ(RichEditPara, L"para")

public:
    RichEditPara();
    ~RichEditPara(){}

    CRect   GetRect();
    void    UpdatePosition();
    BOOL    InsertIntoHost(IRichEditObjHost * pHost);
    void    SetAlign(AlignType align);
    BOOL    IsWrapped();
    void    OffsetCharRange(int nOffset);

protected:
    BOOL    CalcParagraphRect();
    BOOL    GetLineRect(int nLineNo, CRect& rcLine);

    SOUI_ATTRS_BEGIN()
        ATTR_INT(L"break", m_bBreakAtTheEnd, FALSE)
        ATTR_INT(L"simulate-align", m_bSimulateAlign, FALSE)
        ATTR_INT(L"disable-layout", m_bDisableLayout, FALSE)
    SOUI_ATTRS_END()

    BOOL    m_bWrapped;          /**< �Ƿ�һ����ʾ����,�Զ�������*/
    BOOL    m_bNeedUpdateLayout; /**< ����Ƿ���Ҫ������������*/
    BOOL    m_bSimulateAlign;    /**< �Ƿ�ģ���Ҷ��롣������������,�ﵽ�Ҷ���Ч��*/
    int     m_bBreakAtTheEnd;    /**< �Ƿ��ڶ�������һ���س�*/
    int     m_nLineCount;        /**< �ı�������,�����ж��Ƿ��Զ�������*/
    BOOL    m_bInited;
    BOOL    m_bDisableLayout;    /**< ����Ҫ���� */
};

//////////////////////////////////////////////////////////////////////////
// RichEditContent
class RichEditContent : public RichEditObj
{
    #define THRESHOLD_FOR_AUTOLAYOUT 1024 // �Զ����ֵķ�ֵ

    DECLARE_REOBJ(RichEditContent, L"RichEditContent")

public:
    RichEditContent():m_bAutoLayout(FALSE){}
    ~RichEditContent(){}

    void        UpdatePosition();
    SStringW    GetType() { return m_strType; }
    CRect       GetRect();

protected:
    SOUI_ATTRS_BEGIN()
        ATTR_STRINGW(L"type", m_strType, FALSE)
        ATTR_INT(L"auto-layout", m_bAutoLayout, TRUE) /**< �Ƿ��Զ�����,�����ûḲ��align����*/
    SOUI_ATTRS_END()

    SStringW    m_strType;
    BOOL        m_bAutoLayout;
};
