#include "stdafx.h"
#include "SMatrixWindow.h"

namespace SOUI
{
SMatrixWindow::SMatrixWindow(void)
:m_fRotate(.0f)
,m_fScaleX(1.0F),m_fScaleY(1.0f)
,m_fSkewX(.0f),m_fSkewY(.0f)
,m_fTransX(.0f),m_fTransY(.0f)
{
}

SMatrixWindow::~SMatrixWindow(void)
{
}

HRESULT SMatrixWindow::OnAttrRotate(const SStringW & strValue,BOOL bLoading)
{
    float fRotate = 0.0f;
    if(1==swscanf(strValue,L"%f",&fRotate))
        m_fRotate = fRotate;
    return bLoading?S_FALSE:S_OK;
}

HRESULT SMatrixWindow::OnAttrScale(const SStringW & strValue,BOOL bLoading)
{
    float fScaleX=0.0f,fScaleY=0.0f;
    if(2!=swscanf(strValue,L"%f,%f",&fScaleX,&fScaleY)) return E_FAIL;
    m_fScaleX = fScaleX;
    m_fScaleY = fScaleY;
    return bLoading?S_FALSE:S_OK;
}

HRESULT SMatrixWindow::OnAttrSkew(const SStringW & strValue,BOOL bLoading)
{
    float fSkewX=0.0f,fSkewY=0.0f;
    if(2!=swscanf(strValue,L"%f,%f",&fSkewX,&fSkewY)) return E_FAIL;
    m_fSkewX = fSkewX;
    m_fSkewY = fSkewY;
    return bLoading?S_FALSE:S_OK;
}

HRESULT SMatrixWindow::OnAttrTranslate(const SStringW & strValue,BOOL bLoading)
{
    float fTransX=0.0f,fTransY=0.0f;
    if(2!=swscanf(strValue,L"%f,%f",&fTransX,&fTransY)) return E_FAIL;
    m_fTransX = fTransX;
    m_fTransY = fTransY;
    return bLoading?S_FALSE:S_OK;
}

void SMatrixWindow::OnPaint(IRenderTarget *pRT)
{
    SPainter painter;
    BeforePaint(pRT,painter);
    CRect rc = GetClientRect();
    if(!m_pBgSkin)
    {
        pRT->DrawText(_T("û��ָ��skin����"),-1,rc,DT_SINGLELINE|DT_VCENTER|DT_VCENTER);
    }else
    {
        SMatrix m,m2;
        m.rotate(m_fRotate)
        .scale(m_fScaleX,m_fScaleY)
        .shear(m_fSkewX,m_fSkewY)
        .translate(m_fTransX,m_fTransY);
        
        pRT->SetTransform(&m,&m2);
        m_pBgSkin->Draw(pRT,rc,0);
        pRT->SetTransform(&m2);
    }
    AfterPaint(pRT,painter);
}
}