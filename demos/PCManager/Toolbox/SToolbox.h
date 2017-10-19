#pragma once
#include <core/Swnd.h>
#include <control/SCmnCtrl.h>

namespace SOUI
{
class SToolbox:public SImageButton
{
	SOUI_CLASS_NAME(SSwitch,L"toolbox")
public:
	SToolbox():m_IconOffsetX(0), m_IconOffsetY(-8), m_TextOffsetX(0), m_TextOffsetY(18), m_pIcon(NULL)
	{

	}
	~SToolbox(){}
protected://��Ϣ����SOUI�ؼ�����Ϣ�����WTL��MFC�����ƣ��������Ƶ�ӳ�����ͬ�������Ƶ���Ϣӳ���
	void OnPaint(IRenderTarget *pRT);
	//SOUI�ؼ���Ϣӳ���
	SOUI_MSG_MAP_BEGIN()	
		MSG_WM_PAINT_EX(OnPaint)   
	SOUI_MSG_MAP_END()

	ISkinObj    *m_pIcon;	//ͼ��
	SStringT    m_strText; //����
	int			m_IconOffsetX, m_IconOffsetY, m_TextOffsetX, m_TextOffsetY;//��Ծ���λ��ƫ����
	SOUI_ATTRS_BEGIN()
		ATTR_SKIN(L"icon", m_pIcon, TRUE)
		ATTR_STRINGT(L"text", m_strText, FALSE)
	SOUI_ATTRS_END()
};
}