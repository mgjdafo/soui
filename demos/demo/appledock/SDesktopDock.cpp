#include "StdAfx.h"
#include "SDesktopDock.h"
#include <math.h>
#include <ShellAPI.h>
/*
by ���
@20150510 qq:4361031
*/

//��ʼ��DOCK������Сͼ��ľ������򣬳�ʼͼ���СΪ65��65�����������ȣ�m_DockLen = 650
SDesktopDock::SDesktopDock()
{
	m_Width = 50;        //��ʼ���
	m_Height = 50;
	m_DockLen = 500;
	m_MaxDisc = 200;
	m_MinDisc = 40;
	m_MaxRate = 2;
	m_MinRate = 1;
	m_gap = 5;         //����������ױߵľ���
	m_Init = FALSE;

}
void SDesktopDock::OnPaint(IRenderTarget *pRT)
{
	if (!m_Init)
	{
		m_Init = TRUE;
		CRect rcClient = GetClientRect();
		int cx = rcClient.Width();
		int cy = rcClient.Height();

		double X = (cx - m_DockLen)/2;
		double Y = cy - m_Height - m_gap;
		int i;

		for (i = 0; i < MAX_COUNT; i++)
		{
			m_RTRect[i] = CRect(CPoint(X + m_Width * i+rcClient.left, Y), CSize(m_Width, m_Height));
			m_dRate[i] = 1;
		}
	}
	SPainter painter;
	BeforePaint(pRT,painter);

	GetRTRect();

	for (int i=0; i<MAX_COUNT; i++)
	{
		m_pSkin[i]->Draw(pRT,m_RTRect[i],FALSE);
	}

	AfterPaint(pRT,painter);
}
void SDesktopDock::OnMouseMove(UINT nFlags,CPoint pt)
{
	CRect rc;
	GetClientRect(rc);
	rc.top = rc.bottom - 160;
	static bool OutofRect = true;

	if (rc.PtInRect(pt))
	{
		OutofRect = true;
		m_CPX = pt.x;
		m_CPY = pt.y;
		GetImageRate();
		GetDockLen();
		Invalidate();

		SetCapture();
	}	
	else
	{
		if (!OutofRect)
			return ;

		ReleaseCapture();
		initDockRect();
		Invalidate();
		OutofRect = false;
	}

}

//��ʼ��DOCK������Сͼ��ľ������򣬳�ʼͼ���СΪ65��65�����������ȣ�m_DockLen = 650
void SDesktopDock::initDockRect()
{
	CRect rc;
	GetClientRect(rc);
	int cx = rc.Width();
	int cy = rc.Height();

	//Dock���������ݳ�ʼ��
	m_Width = 50;        //��ʼ���
	m_Height = 50;
	m_DockLen = 500;
	m_MaxDisc = 200;
	m_MinDisc = 40;
	m_MaxRate = 2;
	m_MinRate = 1;
	m_gap = 5;         //����������ױߵľ���

	double X = (cx - m_DockLen)/2;
	double Y = cy - m_Height - m_gap;
	int i;

	for (i = 0; i < MAX_COUNT; i++)
	{
		m_RTRect[i] = CRect(CPoint(X + m_Width * i+rc.left, Y), CSize(m_Width, m_Height));
		m_dRate[i] = 1;
	}

}
void SDesktopDock::OnLButtonUp(UINT nFlags, CPoint point)
{
	for (int i=0; i<MAX_COUNT; i++)
	{
		if (m_RTRect[i].PtInRect(point))
		{
			SMessageBox(NULL,SStringT().Format(_T("����===%d��"),i),_T("���WIFI"),MB_OK);
			if (i==0){
				ShellExecute(NULL, _T("open"),_T("http://www.wf06.com"), NULL, NULL, SW_SHOWNORMAL);

			}else if (i==1){

				ShellExecute(NULL, _T("open"),_T("http://www.sk53.com"), NULL, NULL, SW_SHOWNORMAL);
			}


			return ;
		}
	}
}

//�������ܣ�
//����ͼ�����ű�������m_dRate
//rcOrign:ԭʼ���Σ���С�ľ��Σ���СΪ50��50��
//dRTDisc:��ʱ��������rcOrign���ĵľ��롣
//dRate:��̬ͼ�����ŵı���
//MaxDisc:���������ͼ�����ĵ���Զ���룬����������룬ͼ�β��䡣
//MinDisc:���������ͼ�����ĵ���С����,С��������룬ͼ�β��䡣
void SDesktopDock::GetImageRate()
{
	int i;
	double dRTDisc;
	CPoint cp;

	double a = (m_MinRate - m_MaxRate)/(m_MaxDisc - m_MinDisc);
	double b = m_MinRate - a * m_MaxDisc;

	for (i = 0; i < MAX_COUNT; i++)
	{
		//ȡ��̬�������ĵ�
		//cp = CPoint(m_RTRect[i]->X + m_RTRect[i]->Width/2.0, m_RTRect[i]->Y + m_RTRect[i]->Height/2.0);
		cp = CPoint(m_RTRect[i].left + m_RTRect[i].Width()/2.0, m_RTRect[i].top + m_RTRect[i].Height()/2.0);
		//����������굽��̬�������ĵľ���	
		dRTDisc = sqrt(double(cp.x-m_CPX)*(cp.x-m_CPX) +double(cp.y-m_CPY)*(cp.y-m_CPY));

		if (dRTDisc >= m_MaxDisc)
		{
			m_dRate[i] = m_MinRate;
			continue;
		}
		if (dRTDisc <= m_MinDisc)
		{
			m_dRate[i] = m_MaxRate;
			continue;
		}		

		//����ͼ�����ű���
		m_dRate[i] = a * dRTDisc + b;

		//delete cp;
	}
}

//���㹤�����Ķ�̬���ȡ���RTLen.
void SDesktopDock::GetDockLen()
{
	int i;
	m_DockLen = 0;

	for (i = 0; i < MAX_COUNT; i++)
	{
		m_DockLen +=  m_Width * m_dRate[i];
	}
}

void SDesktopDock::GetRTRect()
{
	CRect rc;
	GetClientRect(rc);
	int cx = rc.Width();
	int cy = rc.Height();
	double X = (cx - m_DockLen)/2.0;
	int i;
	double width;

	for (i = 0; i < MAX_COUNT; i++)
	{
		width = m_Width * m_dRate[i];
		if (i > 0)
			X += m_Width * m_dRate[i-1];
		m_RTRect[i].left = X + rc.left;
		m_RTRect[i].top = cy - m_Height * m_dRate[i] - m_gap;
		m_RTRect[i].right = m_RTRect[i].left + width;
		m_RTRect[i].bottom = m_RTRect[i].top + (m_Height * m_dRate[i]);
	}
}