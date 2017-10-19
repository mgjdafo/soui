#pragma once
#include <core/Swnd.h>

namespace SOUI
{
class  SSwitch : public SWindow
{
	SOUI_CLASS_NAME(SSwitch,L"switch")
public:
	SSwitch();
	~SSwitch();
protected://SWindow���麯��
	virtual CSize GetDesiredSize(LPCRECT pRcContainer);
public://���Դ���
	BOOL IsOpen() {return m_BOpen;}
protected://��Ϣ����SOUI�ؼ�����Ϣ�����WTL��MFC�����ƣ��������Ƶ�ӳ�����ͬ�������Ƶ���Ϣӳ���
    void OnPaint(IRenderTarget *pRT);
    void OnTimer(char cTimerID);
	void OnLButtonUp(UINT nFlags, CPoint point);
	void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	HRESULT OnAttrOpen(const SStringW& strValue, BOOL bLoading);
	void SetOpen(BOOL bOpen);
	UINT _GetDrawState();
	virtual void OnStateChanged(DWORD dwOldState,DWORD dwNewState);

    //SOUI�ؼ���Ϣӳ���
    SOUI_MSG_MAP_BEGIN()	
        MSG_WM_TIMER_EX(OnTimer)    //��ʱ����Ϣ
        MSG_WM_PAINT_EX(OnPaint)    //���ڻ�����Ϣ
		MSG_WM_LBUTTONUP(OnLButtonUp)
		MSG_WM_KEYDOWN(OnKeyDown)
	SOUI_MSG_MAP_END()

	ISkinObj *m_pSkin;  /**< ISkinObj���� */
	ISkinObj *m_pSkinForce; //

	SOUI_ATTRS_BEGIN()
		ATTR_SKIN(L"skin", m_pSkin, TRUE)
		ATTR_SKIN(L"skinforce", m_pSkinForce, TRUE)
		ATTR_CUSTOM(L"open",OnAttrOpen)
	SOUI_ATTRS_END()
private:
	BOOL m_BOpen;			//�Ƿ�Ϊ��״̬
	BOOL m_BOpenTarget;     //Ŀ��״̬
	BOOL m_BChangeing;      //���ڸı�״̬..
	int  m_Iinterval;		//�������
	int  m_FrameCount;		//����֡��
	int  m_FrameNow;		//��ǰ֡

};

}