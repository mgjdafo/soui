#pragma once

#include "SComboBase.h"
#include "SListView.h"

namespace SOUI
{
    class SOUI_EXP SComboView : public SComboBase
    {
        SOUI_CLASS_NAME(SComboView,L"comboview")
    public:
        SComboView(void);
        ~SComboView(void);

        BOOL SetCurSel(int iSel);

        /**
        * SComboView::GetCurSel
        * @brief    ��ȡѡ������
        * @return   ����int -- ѡ������
        * 
        * Describe  ��ȡѡ������
        */ 
        int GetCurSel() const;

        /**
        * SComboView::GetCount
        * @brief    ��ȡ���������
        * @return   ����int
        * 
        * Describe  ��ȡ���������
        */ 
        int  GetCount() const;

        /**
        * SComboView::GetLBText
        * @brief    ��ȡ�ı�
        * @param    int iItem -- ����ֵ
        *
        * Describe  ��ȡ�ı�
        */
        SStringT GetLBText(int iItem);
        
        /**
        * SComboView::GetListBox
        * @brief    ��ȡ�����б�ָ��
        * @param    ����SListBox * 
        *
        * Describe  ��ȡ�����б�ָ��
        */
        SListView * GetListView();

    protected:
        /**
        * SComboView::FireEvent
        * @brief    ֪ͨ��Ϣ
        * @param    EventArgs &evt -- �¼����� 
        * 
        * Describe  �˺�������Ϣ��Ӧ����
        */ 
        virtual BOOL FireEvent(EventArgs &evt);

        /**
        * SComboView::CreateListBox
        * @brief    ���������б�
        * @param    ����BOOL TRUE -- �ɹ� FALSE -- ʧ��
        *
        * Describe  ���������б�
        */
        virtual BOOL CreateListBox(pugi::xml_node xmlNode);

        /**
        * SComboView::GetListBoxHeight
        * @brief    ��ȡ�����б�߶�
        * @param    ����int
        *
        * Describe  ��ȡ�����б�߶�
        */
        virtual int  GetListBoxHeight();

        /**
        * SComboView::OnCreateDropDown
        * @brief    �����б��¼�
        * @param    SDropDownWnd *pDropDown -- �����б�ָ��
        *
        * Describe  �����б��¼�
        */
        virtual void OnCreateDropDown(SDropDownWnd *pDropDown);

        /**
        * SComboView::OnDestroyDropDown
        * @brief    �����б�ر��¼�
        * @param    SDropDownWnd *pDropDown -- �����б�ָ��
        * @param    UINT uCode -- ��Ϣ��
        *
        * Describe  ��ȡ�����б�ָ��
        */
        virtual void OnDestroyDropDown(SDropDownWnd *pDropDown);

        /**
        * SComboView::OnSelChanged
        * @brief    �����б�selected�¼�
        *
        * Describe  �����б�selected�¼�
        */
        virtual void OnSelChanged();

    protected:

        SListView *m_pListBox;  /**< SListBoxָ�� */
    };

}
