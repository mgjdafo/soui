/**
 * Copyright (C) 2014-2050 SOUI�Ŷ�
 * All rights reserved.
 * 
 * @file       SDateTimeEdit.h
 * @brief      ͨ�ÿؼ�
 * @version    v1.0      
 * @author     soui      
 * @date       2014-06-27
 * 
 * Describe    ʱ��ؼ�
 */

#pragma once

#include <control/SRichEdit.h>
#include <helper/STime.h>

namespace SOUI{

//===========================================================================
// Summary:
//     SMaskEdit is a CXTPEdit derived class. It allows text masking to be
//     applied to the control to format it for special editing restrictions.
//===========================================================================
/**
 * @class      SMaskEdit
 * @brief      ���������
 * 
 * Describe    ���������  ��Ҫ���ڹ̶������ʽ
 */
class SMaskEdit : public SEdit
{
    SOUI_CLASS_NAME(SMaskEdit, L"maskedit")

public:
    /**
     * SMaskEdit::SMaskEdit
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    SMaskEdit();
    /**
     * SMaskEdit::CanUseMask
     * @brief    �Ƿ�����mask����
     * @return   ����BOOL
     * 
     * Describe  �Ƿ�����mask����
     */
    BOOL CanUseMask() const;
    /**
     * SMaskEdit::SetUseMask
     * @brief    ����mask����
     * @param    BOOL bUseMask  -- TRUE FALSE
     * 
     * Describe  ����mask����
     */
    void SetUseMask(BOOL bUseMask);
    /**
     * SMaskEdit::CanOverType
     * @brief    �Ƿ����ø�д����
     * @param    ����BOOL
     * 
     * Describe  �Ƿ����ø�д����
     */
    BOOL CanOverType() const;

    /**
     * SMaskEdit::SetOverType
     * @brief    ���ø�д����
     * @param    BOOL bOverType  -- TRUE FALSE     
     * 
     * Describe  ���ø�д����
     */    
    void SetOverType(BOOL bOverType);

    /**
     * SMaskEdit::PosInRange
     * @brief    �Ƿ�����mask����
     * @param    ����BOOL
     * 
     * Describe  �Ƿ�����mask����
     */
    BOOL PosInRange(int nPos) const;

    /**
     * SMaskEdit::CanUseMask
     * @brief    �Ƿ�����mask����
     * @param    ����BOOL
     * 
     * Describe  �Ƿ�����mask����
     */
    TCHAR GetPromptChar() const;
    /**
     * SMaskEdit::CanUseMask
     * @brief    �Ƿ�����mask����
     * @param    ����BOOL
     * 
     * Describe  �Ƿ�����mask����
     */    
    SStringT GetPromptString(int nLength) const;
    /**
     * SMaskEdit::CanUseMask
     * @brief    �Ƿ�����mask����
     * @param    ����BOOL
     * 
     * Describe  �Ƿ�����mask����
     */  
    void  SetPromptChar(TCHAR ch, BOOL bAutoReplace = TRUE);


    BOOL            MaskCut();
    BOOL            MaskCopy();
    void            MaskReplaceSel(LPCTSTR lpszNewText);
    BOOL            MaskPaste();
    void            MaskDeleteSel();
    BOOL            MaskClear();
    void            MaskSelectAll();
    BOOL            IsModified() const;
    void            SetMaskedText(LPCTSTR lpszMaskedText, int nPos = 0, BOOL bUpdateWindow = TRUE);
    virtual BOOL    SetEditMask(LPCTSTR lpszMask, LPCTSTR lpszLiteral, LPCTSTR lpszDefault=NULL);
    TCHAR           ConvertUnicodeAlpha(TCHAR nChar, BOOL bUpperCase) const;
    virtual BOOL    CheckChar(TCHAR& nChar, int nPos);
    virtual BOOL    ProcessMask(TCHAR& nChar, int nEndPos);

    void            DeleteCharAt(int nPos);
    void            InsertCharAt(int nPos, TCHAR nChar);

    SStringT         GetMaskedText(int nStartPos = 0, int nEndPos = -1) const;

    void            GetMaskState(BOOL bCorrectSelection = TRUE);
    void            SetMaskState();

    void            MaskGetSel();

    BOOL            CopyToClipboard(const SStringT& strText);

    BOOL            IsPromptPos(int nPos) const;
    BOOL            IsPromptPos(const SStringT& strLiteral, int nPos) const;

    BOOL            CorrectPosition(int& nPos, BOOL bForward = TRUE);

    void            CorrectWindowText();

    virtual BOOL    IsPrintChar(TCHAR nChar);
    virtual BOOL    IsAlphaChar(TCHAR nChar);
    virtual void    NotifyPosNotInRange();
    virtual void    NotifyInvalidCharacter(TCHAR /*nChar*/, TCHAR /*chMask*/);
    void            ProcessChar(TCHAR nChar);

protected:
  
    /**
     * SMaskEdit::OnCreate
     * @brief    ������Ϣ��Ӧ����
     * @param    LPVOID
     * @return   ����ֵint
     *
     * Describe  �˺�������Ϣ��Ӧ����
     */
    int  OnCreate(LPVOID);
  
    /**
     * SMaskEdit::OnChar
     * @brief    �ַ���Ϣ
     * @param    UINT nChar -- ������Ӧ����ֵ 
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */ 
    void  OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
  
    /**
     * SMaskEdit::OnKeyDown
     * @brief    ���̰����¼�
     * @param    UINT nChar -- ������Ӧ����ֵ 
     * @param    UINT nRepCnt -- �ظ�����
     * @param    UINT nFlags -- ��־
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */ 
    void  OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
  
    /**
     * SMaskEdit::OnSetFocus
     * @brief    ���ý���
     * 
     * Describe  �˺�������Ϣ��Ӧ����
     */
    void  OnSetFocus(SWND wndOld);
protected:
    int             m_nStartChar;       // Current position of the first character in the current selection.
    int             m_nEndChar;         // Current position of the first non-selected character past the end of the current selection.
    BOOL            m_bUseMask;         // TRUE to use the edit mask.
    BOOL            m_bOverType;        // TRUE to over type the text, set with VK_INSERT key press.
    BOOL            m_bModified;        // TRUE if mask edit has been modified.
    TCHAR           m_chPrompt;         // Prompt character used to identify the text entry.
    SStringT         m_strMask;          // Buffer that holds the actual edit mask value.
    SStringT         m_strDefault;       // Contains the edit controls default display text.
    SStringT         m_strWindowText;    // Buffer that holds the actual edit text.
    SStringT         m_strLiteral;       // Literal format that restricts where the user can enter text.

protected:
   SOUI_MSG_MAP_BEGIN()
        MSG_WM_CREATE(OnCreate)
        MSG_WM_CHAR(OnChar)
        MSG_WM_KEYDOWN(OnKeyDown)
        MSG_WM_SETFOCUS_EX(OnSetFocus)
   SOUI_MSG_MAP_END()
};

/**
 * @class      SDateEdit
 * @brief      ���ڱ༭��
 * 
 * Describe    ���ڱ༭��
 */
class  SDateEdit : public SMaskEdit
{
    SOUI_CLASS_NAME(SDateEdit, L"dateedit")

public:
      
    /**
     * SDateEdit::SDateEdit
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    SDateEdit();
    /**
     * SDateEdit::SetDateTime
     * @brief    ��������
     * @param    LPCTSTR strDate -- �����ַ���
     *
     * Describe  ��������
     */
    virtual void SetDateTime(LPCTSTR strDate);
    /**
     * SDateEdit::SetDateTime
     * @brief    ��������
     * @param    CTime tm -- ���������
     *
     * Describe  ��������
     */
    virtual void SetDateTime(CTime tm);
    
    /**
     * SDateEdit::GetWindowDateTime
     * @brief    ��ȡϵͳʱ��
     * @return   SStringT �����ַ���    
     *
     * Describe  ��ȡϵͳʱ��
     */
    virtual SStringT GetWindowDateTime();
       
    virtual BOOL    ProcessMask(TCHAR& nChar, int nEndPos);
protected:
    /**
     * SDateEdit::OnCreate
     * @brief    ��Ϣ��Ӧ����
     * @return   int    
     *
     * Describe  ��Ϣ��Ӧ����
     */
    int OnCreate(LPVOID);

protected:
   SOUI_MSG_MAP_BEGIN()
        MSG_WM_CREATE(OnCreate)
   SOUI_MSG_MAP_END()
};

//===========================================================================
//  CDxTimeEdit
/**
 * @class      STimeEdit
 * @brief      ʱ��༭��
 * 
 * Describe    ʱ��༭��
 */
class  STimeEdit : public SDateEdit
{
    SOUI_CLASS_NAME(STimeEdit, L"timeedit")

public:
    /**
     * STimeEdit::STimeEdit
     * @brief    ���캯��
     *
     * Describe  ���캯��
     */
    STimeEdit();

public:
    
    /**
     * SDateEdit::SetHours
     * @brief    ����Сʱ
     *
     * Describe  ����Сʱ
     */
    virtual void    SetHours(int nHours);
    /**
     * SDateEdit::SetMins
     * @brief    ���÷���
     *
     * Describe  ���÷���
     */
    virtual void    SetMins(int nMins);
    /**
     * SDateEdit::SetTime
     * @brief    ����ʱ��
     * @param    int nHours -- Сʱ
     * @param    int nMins  -- ����
     *
     * Describe  ����ʱ��
     */
    virtual void    SetTime(int nHours, int nMins);
    /**
     * SDateEdit::GetHours
     * @brief    ��ȡСʱ
     * @return   ����int
     *
     * Describe  ��ȡСʱ
     */

    int             GetHours() const;
    /**
     * SDateEdit::GetMins
     * @brief    ��ȡ����
     * @return   ����int
     *
     * Describe  ���÷���
     */

    int             GetMins() const;

    virtual BOOL    ProcessMask(TCHAR& nChar, int nEndPos);
    void            SetMilitary(BOOL bMilitary = TRUE);

protected:
    int             m_nHours;  /**< Сʱ */
    int             m_nMins;   /**< ���� */
    BOOL            m_bMilitary; /**<  */

protected:
    /**
     * STimeEdit::OnCreate
     * @brief    ��Ϣ��Ӧ����
     * @return   int    
     *
     * Describe  ��Ϣ��Ӧ����
     */
    int             OnCreate(LPVOID);

protected:
   SOUI_MSG_MAP_BEGIN()
        MSG_WM_CREATE(OnCreate)
   SOUI_MSG_MAP_END()
};

//////////////////////////////////////////////////////////////////////
inline int STimeEdit::GetHours() const
{
    return m_nHours;
}

inline int STimeEdit::GetMins() const
{
    return m_nMins;
}

inline void STimeEdit::SetMilitary(BOOL bMilitary)
{
    m_bMilitary = bMilitary;

}


}//end of namespace
