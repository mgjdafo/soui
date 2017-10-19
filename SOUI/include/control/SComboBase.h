#pragma once

#include "core/SWnd.h"
#include "SRichEdit.h"
#include "SDropDown.h"

namespace SOUI
{
    #define IDC_CB_EDIT          -100
    #define IDC_DROPDOWN_LIST    -200

    /**
    * @class      SComboEdit
    * @brief      ��CommboBox��Ƕ���Edit�ؼ�
    * 
    * Describe    
    */
    class SOUI_EXP SComboEdit:public SEdit
    {
    public:
        /**
        * SComboEdit::SComboEdit
        * @param    SComboBoxBase *pOwner  -- ����       
        * @brief    ���캯��
        *
        * Describe  ���캯��
        */
        SComboEdit(SWindow *pOwner);

        /**
        * SComboEdit::~SComboEdit
        * @brief    ��������
        *
        * Describe  ��������
        */
        virtual ~SComboEdit(){}
    protected:
        /**
        * SComboEdit::OnMouseHover
        * @brief    ���������ͣ�¼�
        * @param    WPARAM wParam 
        * @param    CPoint ptPos -- �������λ��
        * 
        * Describe  �˺�������Ϣ��Ӧ����
        */
        void OnMouseHover(WPARAM wParam, CPoint ptPos);
        /**
        * SComboEdit::OnMouseLeave
        * @brief    ��������뿪�¼�
        * 
        * Describe  �˺�������Ϣ��Ӧ����
        */    
        void OnMouseLeave();
        /**
        * SComboEdit::OnKeyDown
        * @brief    ���̰����¼�
        * @param    UINT nChar -- ������Ӧ����ֵ 
        * @param    UINT nRepCnt -- �ظ�����
        * @param    UINT nFlags -- ��־
        * 
        * Describe  �˺�������Ϣ��Ӧ����
        */   
        void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

        /**
        * SComboEdit::FireEvent
        * @brief    ֪ͨ��Ϣ
        * @param    EventArgs & evt -- �¼����� 
        * 
        * Describe  �˺�������Ϣ��Ӧ����
        */   
        virtual BOOL FireEvent(EventArgs & evt);

        SOUI_MSG_MAP_BEGIN()
            MSG_WM_MOUSEHOVER(OnMouseHover)
            MSG_WM_MOUSELEAVE(OnMouseLeave)
            MSG_WM_KEYDOWN(OnKeyDown)
            SOUI_MSG_MAP_END()
    };

    class SOUI_EXP SDropDownWnd_ComboBox : public SDropDownWnd
    {
    public:
        SDropDownWnd_ComboBox(ISDropDownOwner* pOwner):SDropDownWnd(pOwner){}

        virtual BOOL PreTranslateMessage(MSG* pMsg);
    };


    /**
    * @class      SComboBoxBase
    * @brief      ������CommboBox
    * 
    * Describe    �����������б�
    */
    class SOUI_EXP SComboBase 
        : public SWindow
        , public ISDropDownOwner
    {
        SOUI_CLASS_NAME(SComboBase,L"combobase")
    public:

        /**
        * SComboBoxBase::SComboBoxBase
        * @brief    ���캯��
        *
        * Describe  ���캯��
        */
        SComboBase(void);

        /**
        * SComboBoxBase::~SComboBoxBase
        * @brief    ��������
        *
        * Describe  ��������
        */
        virtual ~SComboBase(void);
        /**
        * SComboBoxBase::GetCurSel
        * @brief    ��ȡѡ��ֵ����
        * @return   ����int  
        *
        * Describe  ��ȡ��ǰѡ������
        */
        virtual int GetCurSel() const =0;

        /**
        * SComboBoxBase::GetCount
        * @brief    ��ȡ���������
        * @return   ����int
        * 
        * Describe  ��ȡ���������
        */ 
        virtual int  GetCount() const =0;

        /**
        * SComboBoxBase::SetCurSel
        * @brief    ���õ�ǰѡ��
        * @param    int iSel -- ѡ������
        * 
        * Describe  ���õ�ǰѡ��
        */ 
        virtual BOOL SetCurSel(int iSel)=0;

        /**
        * SComboBoxEx::GetTextRect
        * @brief    ��ȡ�ı�λ��
        * @param    LPRECT pRect -- �ı�λ��
        *
        * Describe  ��ȡ�ı�λ��
        */
        virtual SStringT GetWindowText();

        virtual SStringT GetLBText(int iItem) =0;
        /**
        * FindString
        * @brief    �����ַ���λ��
        * @param    LPCTSTR pszFind --  ����Ŀ��
        * @param    int nAfter --  ��ʼλ��
        * @return   int -- Ŀ��������ʧ�ܷ���-1��
        * Describe  
        */    
        virtual int FindString(LPCTSTR pszFind,int nAfter=0);

        /**
        * SComboBoxBase::DropDown
        * @brief    �����¼�
        *
        * Describe  �����¼�
        */
        void DropDown();

        /**
        * SComboBoxBase::CloseUp
        * @brief    �����ر�
        *
        * Describe  �����ر�
        */
        void CloseUp();

    protected:
        /**
        * SComboBoxBase::GetDropDownOwner
        * @brief    ��ȡowner
        * @return   SWindow
        *
        * Describe  ��ȡowner
        */
        virtual SWindow* GetDropDownOwner();

        /**
        * SComboBoxBase::OnCreateDropDown
        * @brief    �����¼�
        * @param     SDropDownWnd *pDropDown -- ��������ָ��
        *
        * Describe  �����¼�
        */
        virtual void OnCreateDropDown(SDropDownWnd *pDropDown);

        /**
        * SComboBoxBase::OnDestroyDropDown
        * @brief    �����¼�
        * @param     SDropDownWnd *pDropDown -- ��������ָ��
        * @param     UINT uCode -- ��Ϣ��
        *
        * Describe  �����ر�
        */
        virtual void OnDestroyDropDown(SDropDownWnd *pDropDown);

        /**
        * SComboBoxBase::OnSelChanged
        * @brief    �������ڸı��¼�
        *
        * Describe  �����ر�
        */
        virtual void OnSelChanged();


        virtual BOOL FireEvent(EventArgs &evt);
    protected:

        /**
        * SComboBoxBase::CalcPopupRect
        * @brief    ���㵯������λ��
        * @param    int nHeight -- �������ڸ߶�
        * @param    CRect & rcPopup -- ���浯������Rect
        * @return   BOOL  TRUE -- �ɹ�  FALSE -- ʧ��
        *
        * Describe  ���㵯������λ��,������rcPopup��
        */    
        BOOL CalcPopupRect(int nHeight,CRect & rcPopup);

        /**
        * SComboBoxBase::CreateListBox
        * @brief    ���������б�
        * @param    pugi::xml_node xmlNode  -- xml����
        * @return   BOOL  TRUE -- �ɹ�  FALSE -- ʧ��
        *
        * Describe  ���������б�
        */    
        virtual BOOL CreateListBox(pugi::xml_node xmlNode)=0;

        /**
        * SComboBoxBase::GetListBoxHeight
        * @brief    ��ȡ�����б�߶�
        * @return   ����int �߶�
        *
        * Describe  ��ȡ�����б�߶�
        */        
        virtual int  GetListBoxHeight()=0;

        /**
        * SComboBoxBase::GetDropBtnRect
        * @brief    ��ȡ�����б�ťλ��
        * @param    LPRECT prc -- ��ťRect
        *
        * Describe  ��ȡ�����б��Ҳఴťλ��
        */        
        void GetDropBtnRect(LPRECT prc);
        /**
        * SComboBoxBase::LoadChildren
        * @brief    ��������
        * @param    pugi::xml_node xmlNode  -- xml�ļ�
        * @return   ����BOOL  TRUE -- �ɹ� FALSE -- ʧ��
        *
        * Describe  ��������
        */
        virtual BOOL CreateChildren(pugi::xml_node xmlNode);    
        /**
        * SComboBoxBase::GetTextRect
        * @brief    ��ȡ�ı�λ��
        * @param    LPRECT pRect -- �ı�λ��
        *
        * Describe  ��ȡ�ı�λ��
        */
        virtual void GetTextRect(LPRECT pRect);

        /**
        * SComboBoxBase::SetWindowText
        * @brief    ������ʾ�ı�
        * @param    LPCTSTR pszText -- �ı�
        *
        * Describe  
        */
        virtual void SetWindowText(LPCTSTR pszText);

        virtual void OnColorize(COLORREF cr);
        
        /**
        * SComboBoxBase::OnPaint
        * @brief    ������Ϣ
        * @param    IRenderTarget * pRT -- ����
        * 
        * Describe  �˺�������Ϣ��Ӧ����
        */
        void OnPaint(IRenderTarget * pRT);

        /**
        * SComboBoxBase::OnLButtonDown
        * @brief    ��������¼�
        * @param    UINT nFlags -- ��־
        * @param    CPoint point -- �������
        *
        * Describe  �˺�������Ϣ��Ӧ����
        */
        void OnLButtonDown(UINT nFlags,CPoint pt);

        /**
        * SComboBoxBase::OnMouseMove
        * @brief    ��������ƶ��¼�
        * @param    UINT nFlags -- ��־
        * @param    CPoint point -- �������
        * 
        * Describe  �˺�������Ϣ��Ӧ����
        */
        void OnMouseMove(UINT nFlags,CPoint pt);

        /**
        * SComboBoxBase::OnMouseLeave
        * @brief    ��������ƶ��¼�
        * 
        * Describe  �˺�������Ϣ��Ӧ����
        */
        void OnMouseLeave();

        /**
        * SComboBoxBase::OnKeyDown
        * @brief    ���̰����¼�
        * @param    UINT nChar -- ������Ӧ����ֵ 
        * @param    UINT nRepCnt -- �ظ�����
        * @param    UINT nFlags -- ��־
        * 
        * Describe  �˺�������Ϣ��Ӧ����
        */
        void OnKeyDown( TCHAR nChar, UINT nRepCnt, UINT nFlags );

        /**
        * SComboBoxBase::OnChar
        * @brief    �ַ���Ϣ
        * @param    UINT nChar -- ������Ӧ����ֵ 
        * @param    UINT nRepCnt -- �ظ�����
        * @param    UINT nFlags -- ��־
        * 
        * Describe  �˺�������Ϣ��Ӧ����
        */ 
        void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);

        /**
        * SComboBoxBase::OnDestroy
        * @brief    ������������
        * 
        * Describe  �˺���������������������
        */  
        void OnDestroy();
        /**
        * SComboBoxBase::OnGetDlgCode
        * @brief    ��ȡ��Ϣ��
        * 
        * Describe  ��ȡ��Ϣ��
        */  
        UINT OnGetDlgCode();

        /**
        * SComboBoxBase::IsTabStop
        * @brief    �Ƿ��ֹTAB��
        * 
        * Describe  �Ƿ��ֹTAB��
        */  
        BOOL IsFocusable();

        void OnSetFocus(SWND wndOld);
        
        void OnKillFocus(SWND wndFocus);

        SOUI_ATTRS_BEGIN()
            ATTR_INT(L"dropDown", m_bDropdown, FALSE)
            ATTR_INT(L"dropHeight", m_nDropHeight, FALSE)
            ATTR_INT(L"curSel", m_iInitSel, FALSE)
            ATTR_SKIN(L"btnSkin", m_pSkinBtn, FALSE)
            ATTR_INT(L"animateTime", m_nAnimTime, FALSE)
        SOUI_ATTRS_END()

        SOUI_MSG_MAP_BEGIN()
            MSG_WM_PAINT_EX(OnPaint)
            MSG_WM_LBUTTONDOWN(OnLButtonDown)        
            MSG_WM_MOUSEMOVE(OnMouseMove)
            MSG_WM_MOUSELEAVE(OnMouseLeave)
            MSG_WM_KEYDOWN(OnKeyDown) 
            MSG_WM_CHAR(OnChar)
            MSG_WM_DESTROY(OnDestroy)
            MSG_WM_SETFOCUS_EX(OnSetFocus)
            MSG_WM_KILLFOCUS_EX(OnKillFocus)
        SOUI_MSG_MAP_END()

    protected:
        /**
        * SComboBoxBase::GetEditText
        * @brief    ��ȡ�༭������
        * 
        * Describe  ��ȡ�༭������
        */  
        SStringT GetEditText() const
        {
            if(!m_bDropdown)
            {
                return m_pEdit->GetWindowText();
            }
            else
            {
                return SStringT();
            }
        }

        SRichEdit *m_pEdit;      /**< SRichEditָ�� */
        DWORD     m_dwBtnState;  /**< ��ť״̬      */
        ISkinObj *m_pSkinBtn;    /**< ��ť��Դ      */

        BOOL m_bDropdown;        /**< �Ƿ���   */
        int  m_nDropHeight;      /**< ������߶� */
        int  m_nAnimTime;        /**< ����ʱ��   */
        int  m_iInitSel;         /**< Ĭ��ѡ������ */
        SDropDownWnd *m_pDropDownWnd;  /**< DropDownָ�� */
    };

}