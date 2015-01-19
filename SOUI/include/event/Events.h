/**
* Copyright (C) 2014-2050 
* All rights reserved.
* 
* @file       Events.h
* @brief      
* @version    v1.0      
* @author     SOUI group   
* @date       2014/08/02
* 
* Describe    SOUI系统中使用的事件系统
*/

#pragma once

namespace SOUI
{
    class SWindow;

    /*!
    \brief
    Base class used as the argument to all subscribers Event object.

    The base EventArgs class does not contain any useful information, it is intended
    to be specialised for each type of event that can be generated by objects within
    the system.  The use of this base class allows all event subscribers to have the
    same function signature.

    The \a handled field is used to signal whether an event was actually handled or not.  While
    the event system does not look at this value, code at a higher level can use it to determine
    how far to propagate an event.
    */
    class SOUI_EXP EventArgs
    {
    public:
        /*************************************************************************
        Construction
        *************************************************************************/
        EventArgs(SWindow *pSender);

        virtual ~EventArgs(void) {}
        virtual UINT GetEventID()= 0;

        /*************************************************************************
        Data members
        *************************************************************************/
        
        UINT handled; /**< handlers should increment this if they handled the event. */

        int  idFrom; /**< 事件发送者ID */
        LPCWSTR nameFrom; /**< 事件发送者name */

        SWindow *sender;  /**< 产生事件的原始DUI窗口对象，可能和idFrom and nameFrom指定的窗口不同 */
    };

    enum SOUI_EVENTS
    {
        EVT_MOUSE_HOVER=9000,//两个窗口鼠标状态事件
        EVT_MOUSE_LEAVE,

        EVT_CMD=10000,
        EVT_CTXMENU,
        EVT_SETFOCUS,
        EVT_KILLFOCUS,
        EVT_SCROLL,
        EVT_OFEVENT,    //消息二次包装
        EVT_OFPANEL,    //一个itemPanel中的消息的二次包装

        //增加3个itempanel相关的事件,经过EVT_OFPANEL到达应用层
        EVT_ITEMPANEL_CLICK,
        EVT_ITEMPANEL_DBCLICK,
        EVT_ITEMPANEL_RCLICK,

        EVT_TAB_SELCHANGING=11000,
        EVT_TAB_SELCHANGED,

        EVT_LB_GETDISPINFO=12000,
        EVT_LB_SELCHANGING,
        EVT_LB_SELCHANGED,

        EVT_LC_SELCHANGING=13000,
        EVT_LC_SELCHANGED,
		EVT_LC_ITEMDELETED,

        EVT_TB_GETDISPINFO=14000,    
        EVT_TB_SELCHANGING,
        EVT_TB_SELCHANGED,

        EVT_TC_SELCHANGING=15000,
        EVT_TC_SELCHANGED,
        EVT_TC_EXPAND,
        EVT_TC_CHECKSTATE,
        EVT_TC_DBCLICK,    //treectrl的叶子节点双击事件, add by zhaosheng

        EVT_RE_NOTIFY=16000,

        EVT_SLIDER_POS=17000,

        EVT_HEADER_CLICK=18000,
        EVT_HEADER_ITEMCHANGING,
        EVT_HEADER_ITEMCHANGED,
        EVT_HEADER_ITEMSWAP,

        EVT_CB_SELCHANGE=19000,
        EVT_CBE_OFITEM=19500,
        
        EVT_CALENDAR_SELDAY=20000,

        EVT_EXTERNAL_BEGIN=10000000,
    };

    class SOUI_EXP EventCmnArgs : public EventArgs
    {
    public:
        EventCmnArgs(SWindow *pSender,UINT uEvtID):EventArgs(pSender),uID(uEvtID)
        {

        }
        virtual UINT GetEventID(){return uID;}

    protected:
        UINT uID;
    };

    class SOUI_EXP EventCmd : public EventArgs
    {
    public:
        EventCmd(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_CMD};
        virtual UINT GetEventID(){return EventID;}
    };

    class SOUI_EXP EventCtxMenu : public EventArgs
    {
    public:
        EventCtxMenu(SWindow *pWnd):EventArgs(pWnd),bCancel(FALSE){}
        enum{EventID=EVT_CTXMENU};
        virtual UINT GetEventID(){return EventID;}
        POINT           pt;
        BOOL            bCancel;
    };

    class SOUI_EXP EventSetFocus : public EventArgs
    {
    public:
        EventSetFocus(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_SETFOCUS};
        virtual UINT GetEventID(){return EventID;}
    };

    class SOUI_EXP EventKillFocus : public EventArgs
    {
    public:
        EventKillFocus(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_KILLFOCUS};
        virtual UINT GetEventID(){return EventID;}
    };

    class SOUI_EXP EventScroll : public EventArgs
    {
    public:
        EventScroll(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_SCROLL};
        virtual UINT GetEventID(){return EventID;}
        UINT        uSbCode;
        int         nPos;
        BOOL        bVertical;
    };

    class SOUI_EXP EventOfEvent : public EventArgs
    {
    public:
        EventOfEvent(SWindow *pWnd,EventArgs *_pOrgEvt)
            :EventArgs(pWnd)
            ,pOrgEvt(_pOrgEvt)
        {}
        enum{EventID=EVT_OFEVENT};
        virtual UINT GetEventID(){return EventID;}
        EventArgs * pOrgEvt;
    };

    class SItemPanel;
    class SOUI_EXP EventOfPanel : public EventArgs
    {
    public:
        EventOfPanel(SItemPanel *_pPanel,EventArgs *_pOrgEvt);
        enum{EventID=EVT_OFPANEL};
        virtual UINT GetEventID(){return EventID;}

        SItemPanel *pPanel;
        EventArgs * pOrgEvt;
    };
    
    class SOUI_EXP EventOfComoboxExItem : public EventArgs
    {
    public:
        EventOfComoboxExItem(SWindow *pSender,EventCmd *_pOrgEvt);
        enum{EventID=EVT_CBE_OFITEM};
        virtual UINT GetEventID(){return EventID;}

        EventCmd    *  pOrgEvt;
        BOOL           bCancel;
    };
    
    class SOUI_EXP EventTabSelChanging : public EventArgs
    {
    public:
        EventTabSelChanging(SWindow *pWnd):EventArgs(pWnd),bCancel(FALSE){}
        enum{EventID=EVT_TAB_SELCHANGING};
        virtual UINT GetEventID(){return EventID;}
        UINT        uOldSel;
        UINT        uNewSel;
        BOOL        bCancel;
    };

    class SOUI_EXP EventTabSelChanged : public EventArgs
    {
    public:
        EventTabSelChanged(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_TAB_SELCHANGED};
        virtual UINT GetEventID(){return EventID;}
        UINT        uOldSel;
        UINT        uNewSel;
    };

    class SOUI_EXP EventLBGetDispInfo : public EventArgs
    {
    public:
        EventLBGetDispInfo(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_LB_GETDISPINFO};
        virtual UINT GetEventID(){return EventID;}
        int  iItem;
        SWindow * pItem;
        BOOL bSel;
        BOOL bHover;
    };

    class SOUI_EXP EventLBSelChanging : public EventArgs
    {
    public:
        EventLBSelChanging(SWindow *pWnd):EventArgs(pWnd),bCancel(FALSE){
        
        }
        enum{EventID=EVT_LB_SELCHANGING};
        virtual UINT GetEventID(){return EventID;}
        int nNewSel;
        int nOldSel;
        BOOL bCancel;
    };

    class SOUI_EXP EventLBSelChanged : public EventArgs
    {
    public:
        EventLBSelChanged(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_LB_SELCHANGED};
        virtual UINT GetEventID(){return EventID;}
        int nNewSel;
        int nOldSel;
    };

    class SOUI_EXP EventTBGetDispInfo : public EventArgs
    {
    public:
        EventTBGetDispInfo(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_TB_GETDISPINFO};
        virtual UINT GetEventID(){return EventID;}
        HSTREEITEM  hItem;
        SWindow     *pItemWnd;
        BOOL        bSel;
        BOOL        bHover;
    };

    class SOUI_EXP EventTBSelChanging: public EventArgs
    {
    public:
        EventTBSelChanging(SWindow *pWnd):EventArgs(pWnd),bCancel(FALSE){}
        enum{EventID=EVT_TB_SELCHANGING};
        virtual UINT GetEventID(){return EventID;}
        HSTREEITEM hNewSel;
        HSTREEITEM hOldSel;
        BOOL        bCancel;
    };

    class SOUI_EXP EventTBSelChanged: public EventArgs
    {
    public:
        EventTBSelChanged(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_TB_SELCHANGED};
        virtual UINT GetEventID(){return EventID;}
        HSTREEITEM hNewSel;
        HSTREEITEM hOldSel;
    };

    class SOUI_EXP EventRENotify : public EventArgs
    {
    public:
        EventRENotify(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_RE_NOTIFY};
        virtual UINT GetEventID(){return EventID;}
        DWORD iNotify;
        LPVOID pv;
    };

    class SOUI_EXP EventSliderPos : public EventArgs
    {
    public:
        EventSliderPos(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_SLIDER_POS};
        virtual UINT GetEventID(){return EventID;}
        int     nPos;
    };

    //点击表头
    class SOUI_EXP EventHeaderClick : public EventArgs
    {
    public:
        EventHeaderClick(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_HEADER_CLICK};
        virtual UINT GetEventID(){return EventID;}
        int   iItem;
    };

    //点击表头
    class SOUI_EXP EventHeaderItemChanging : public EventArgs
    {
    public:
        EventHeaderItemChanging(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_HEADER_ITEMCHANGING};
        virtual UINT GetEventID(){return EventID;}
        int   iItem;
        int   nWidth;
    };

    //点击表头
    class SOUI_EXP EventHeaderItemChanged : public EventArgs
    {
    public:
        EventHeaderItemChanged(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_HEADER_ITEMCHANGED};
        virtual UINT GetEventID(){return EventID;}
        int   iItem;
        int   nWidth;
    };

    //拖动表项调整位置
    class SOUI_EXP EventHeaderItemSwap : public EventArgs
    {
    public:
        EventHeaderItemSwap(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_HEADER_ITEMSWAP};
        virtual UINT GetEventID(){return EventID;}
        int   iOldIndex;
        int      iNewIndex;
    };

    class SOUI_EXP EventCBSelChange : public EventArgs
    {
    public:
        EventCBSelChange(SWindow *pWnd,int _nCurSel):EventArgs(pWnd),nCurSel(_nCurSel){}
        enum{EventID=EVT_CB_SELCHANGE};
        virtual UINT GetEventID(){return EventID;}
        int nCurSel;
    };

    class SOUI_EXP EventLCSelChanging : public EventArgs
    {
    public:
        EventLCSelChanging(SWindow *pWnd):EventArgs(pWnd),bCancel(FALSE){}
        enum{EventID=EVT_LC_SELCHANGING};
        virtual UINT GetEventID(){return EventID;}
        int nNewSel;
        int nOldSel;
        BOOL bCancel;
    };

    class SOUI_EXP EventLCSelChanged : public EventArgs
    {
    public:
        EventLCSelChanged(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_LC_SELCHANGED};
        virtual UINT GetEventID(){return EventID;}
        int nNewSel;
        int nOldSel;
    };

	class SOUI_EXP EventLCItemDeleted : public EventArgs
	{
	public:
		EventLCItemDeleted(SWindow *pWnd) :EventArgs(pWnd){}
		enum{ EventID = EVT_LC_ITEMDELETED };
		virtual UINT GetEventID(){ return EventID; }
		
		int		nItem;
		DWORD   dwData;
	};

    class SOUI_EXP EventCalendarSelDay : public EventArgs
    {
    public:
        EventCalendarSelDay(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_CALENDAR_SELDAY};
        virtual UINT GetEventID(){return EventID;}
        WORD   wOldDay;
        WORD   wNewDay;
    };


    class SOUI_EXP EventTCSelChanging : public EventArgs
    {
    public:
        EventTCSelChanging(SWindow *pWnd):EventArgs(pWnd),bCancel(FALSE){}
        enum{EventID=EVT_TC_SELCHANGING};
        virtual UINT GetEventID(){return EventID;}
        HSTREEITEM hOldSel;
        HSTREEITEM hNewSel;
        BOOL bCancel;
    };

    class SOUI_EXP EventTCSelChanged : public EventArgs
    {
    public:
        EventTCSelChanged(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_TC_SELCHANGED};
        virtual UINT GetEventID(){return EventID;}
        HSTREEITEM hOldSel;
        HSTREEITEM hNewSel;
    };

    class SOUI_EXP EventTCCheckState : public EventArgs
    {
    public:
        EventTCCheckState(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_TC_CHECKSTATE};
        virtual UINT GetEventID(){return EventID;}
        HSTREEITEM  hItem;
        UINT        uCheckState;
    };

    class SOUI_EXP EventTCExpand : public EventArgs
    {
    public:
        EventTCExpand(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_TC_EXPAND};
        virtual UINT GetEventID(){return EventID;}
        HSTREEITEM  hItem;
        BOOL bCollapsed;
    };

    //双击treectrl的叶子节点 add by zhaosheng
    class SOUI_EXP EventTCDbClick : public EventArgs
    {
    public:
        EventTCDbClick(SWindow *pWnd):EventArgs(pWnd){}
        enum{EventID=EVT_TC_DBCLICK};
        virtual UINT GetEventID(){return EventID;}
        HSTREEITEM hItem;  //双击选中的节点
    };

} // End of  CEGUI namespace section