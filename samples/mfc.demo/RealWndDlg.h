#pragma once

class CRealWndDlg : public SOUI::SHostDialog
{
public:
    CRealWndDlg(void);
    ~CRealWndDlg(void);

    //��ӦMFC.button�İ�����Ϣ, nID==100Ϊ��XML��ָ����realwnd��id���ԡ�
    void OnBtnClick( UINT uNotifyCode, int nID, HWND wndCtl )
    {
        if(uNotifyCode == BN_CLICKED && nID == 100)
        {
            SOUI::SMessageBox(m_hWnd,_T("the real mfc button is clicked!"),_T("mfc.demo"),MB_OK|MB_ICONEXCLAMATION);
        }
    }

    //��Ϣӳ���
    BEGIN_MSG_MAP_EX(CRealWndDlg)
        MSG_WM_COMMAND(OnBtnClick)
        CHAIN_MSG_MAP(SOUI::SHostDialog)
        REFLECT_NOTIFICATIONS_EX()
    END_MSG_MAP()
};
