// MainDlg.h : interface of the CMainDlg class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

class CMainDlg : public CDialogImpl<CMainDlg>
{
	struct VSENVCFG
	{
		CString strName;
		CString strVsDir;
		CString strDataTarget;
		CString strEntrySrc;
		CString strEntryTarget;
		CString strScriptSrc;
	};
public:
	enum { IDD = IDD_MAINDLG };

	BEGIN_MSG_MAP_EX(CMainDlg)
		MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)
		MESSAGE_HANDLER(WM_DESTROY, OnDestroy)
		COMMAND_ID_HANDLER(IDCANCEL, OnCancel)
		COMMAND_ID_HANDLER(IDC_BROWSE2, OnBrowseSouiDir)
		COMMAND_ID_HANDLER(IDC_INSTALL, OnInstall)
		COMMAND_ID_HANDLER(IDC_UNINSTALL, OnUninstall)
		COMMAND_ID_HANDLER(IDC_SETOUTSOFT, OnSetoutsoft)
	END_MSG_MAP()

	CString m_strWizardDir;//����Ŀ¼

	CString GetVSDir(LPCTSTR pszEnvName)
	{
		CString strRet;
		strRet.GetEnvironmentVariable(pszEnvName);
		if(!strRet.IsEmpty()) strRet=strRet.Left(strRet.GetLength()-14);//14=length("Common7\Tools\")
		return strRet;
	}

	LRESULT OnDestroy(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		CListViewCtrl vslist;
		vslist.Attach(GetDlgItem(IDC_VSLIST));
		for(int i=0;i<vslist.GetItemCount();i++)
		{
			delete (VSENVCFG*)vslist.GetItemData(i);
		}
		return 0;
	}

	LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
	{
		// center the dialog on the screen
		CenterWindow();

		// set icons
		HICON hIcon = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXICON), ::GetSystemMetrics(SM_CYICON));
		SetIcon(hIcon, TRUE);
		HICON hIconSmall = AtlLoadIconImage(IDR_MAINFRAME, LR_DEFAULTCOLOR, ::GetSystemMetrics(SM_CXSMICON), ::GetSystemMetrics(SM_CYSMICON));
		SetIcon(hIconSmall, FALSE);

		CListViewCtrl vslist;
		vslist.Attach(GetDlgItem(IDC_VSLIST));
		ListView_SetExtendedListViewStyleEx(vslist.m_hWnd,LVS_EX_CHECKBOXES,LVS_EX_CHECKBOXES);
		
		TCHAR szDir[1000];
		GetCurrentDirectory(1000,szDir);
		m_strWizardDir=szDir;

		CString szVsList=m_strWizardDir+=_T("\\vslist.ini");
		int i=0;
		for(;;)
		{
			CString entry;
			entry.Format(_T("vs_%d"),++i);
			TCHAR szBuf[1000];
			if(0==GetPrivateProfileString(entry,_T("name"),NULL,szBuf,1000,szVsList))
				break;

			VSENVCFG *pEnvCfg=new VSENVCFG;
			pEnvCfg->strName=szBuf;
			GetPrivateProfileString(entry,_T("envname"),NULL,szBuf,1000,szVsList);
			pEnvCfg->strVsDir=GetVSDir(szBuf);
			if(pEnvCfg->strVsDir.IsEmpty())
			{
				delete pEnvCfg;
				continue;
			}
			GetPrivateProfileString(entry,_T("entryfilesrc"),NULL,szBuf,1000,szVsList);
			pEnvCfg->strEntrySrc=szBuf;
			GetPrivateProfileString(entry,_T("entryfiletarget"),NULL,szBuf,1000,szVsList);
			pEnvCfg->strEntryTarget=szBuf;
			GetPrivateProfileString(entry,_T("wizarddatatarget"),NULL,szBuf,1000,szVsList);
			pEnvCfg->strDataTarget=szBuf;
			
			GetPrivateProfileString(entry,_T("scriptsrc"),NULL,szBuf,1000,szVsList);
			pEnvCfg->strScriptSrc=szBuf;

			int iItem=vslist.InsertItem(vslist.GetItemCount(),pEnvCfg->strName);
			vslist.SetItemData(iItem,(DWORD_PTR)pEnvCfg);
		}

		TCHAR szPath[MAX_PATH];
		if(GetEnvironmentVariable(_T("SOUIPATH"),szPath,MAX_PATH))
		{
			SetDlgItemText(IDC_SOUIDIR,szPath);
		}else
		{
			GetCurrentDirectory(MAX_PATH,szPath);
			TCHAR *pUp=_tcsrchr(szPath,_T('\\'));
			if(pUp)
			{
				_tcscpy(pUp,_T("\\SOUI"));
				if(GetFileAttributes(szPath)!=INVALID_FILE_ATTRIBUTES)
				{
					*pUp=0;
					SetDlgItemText(IDC_SOUIDIR,szPath);
				}
			}
		}

		return TRUE;
	}

	LRESULT OnSetoutsoft(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		ShellExecute(0,_T("open"),_T("http://www.setoutsoft.cn"),NULL,NULL,SW_SHOWNORMAL);
		return 0;
	}

	LRESULT OnBrowseSouiDir(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CFolderDialog folderDlg;
		if(folderDlg.DoModal()==IDOK)
		{
			SetDlgItemText(IDC_SOUIDIR,folderDlg.GetFolderPath());
		}
		return 0;
	}

	LRESULT OnInstall(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		SetCurrentDirectory(m_strWizardDir);

		CListViewCtrl vslist;
		vslist.Attach(GetDlgItem(IDC_VSLIST));

		if(GetFileAttributes(_T("SouiWizard"))==INVALID_FILE_ATTRIBUTES)
		{
			MessageBox(_T("��ǰĿ¼��û���ҵ�SOUI��������"),_T("����"),MB_OK|MB_ICONSTOP);
			return 0;
		}
		TCHAR szSouiDir[MAX_PATH]={0},szSourCore[MAX_PATH];
		int nLen=GetDlgItemText(IDC_SOUIDIR,szSouiDir,MAX_PATH);
		if(szSouiDir[nLen-1]==_T('\\')) szSouiDir[--nLen]=0;

        _tcscpy(szSourCore,szSouiDir);
		_tcscat(szSourCore,_T("\\SOUI"));
		if(GetFileAttributes(szSourCore)==INVALID_FILE_ATTRIBUTES)
		{
			MessageBox(_T("��ǰĿ¼��û���ҵ�SOUI��Դ����"),_T("����"),MB_OK|MB_ICONSTOP);
			return 0;
		}
		//���û�������

		CRegKey reg;
		if(ERROR_SUCCESS==reg.Open(HKEY_LOCAL_MACHINE,_T("System\\CurrentControlSet\\Control\\Session Manager\\Environment"),KEY_SET_VALUE|KEY_QUERY_VALUE))
		{
			reg.SetStringValue(_T("SOUIPATH"),szSouiDir);
			DWORD dwSize=0;
			LONG lRet = reg.QueryStringValue(_T("Path"),NULL,&dwSize);
			if(ERROR_SUCCESS == lRet)
			{//�޸�path��������
                CString str;
                TCHAR * pBuf=str.GetBufferSetLength(dwSize);
                lRet = reg.QueryStringValue(_T("Path"),pBuf,&dwSize);
                str.ReleaseBuffer();
                
                CString strSouiBin(szSouiDir);
                strSouiBin+= _T("\\bin");
                if(StrStrI(str,strSouiBin) == NULL)
                {//�Ѿ����ú�������
                    if(str.IsEmpty())
                        str=strSouiBin;
                    else
                        str=strSouiBin+_T(";")+str;
                    reg.SetStringValue(_T("Path"),str);
                }
			}
			reg.Close();
			DWORD_PTR msgResult=0;
			//�㲥���������޸���Ϣ
			SendMessageTimeout(HWND_BROADCAST, WM_SETTINGCHANGE, 0,LPARAM(_T("Environment")), SMTO_ABORTIFHUNG, 5000, &msgResult);
		}else
		{
			MessageBox(_T("��ӻ�������ʧ��"),_T("����"),MB_OK|MB_ICONSTOP);
			return 0;
		}

		//׼�������ļ�
		TCHAR szFrom[1024]={0};
		TCHAR szTo[1024]={0};
		SHFILEOPSTRUCT shfo;
		shfo.pFrom=szFrom;
		shfo.pTo=szTo;

		for(int i=0;i<vslist.GetItemCount();i++)
		{
			if(!vslist.GetCheckState(i)) continue;

			VSENVCFG *pCfg=(VSENVCFG*)vslist.GetItemData(i);
            //�����������
			BOOL bOK = TRUE;
			if(bOK)
			{
				shfo.wFunc=FO_COPY;
				shfo.fFlags=FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION;
				memset(szFrom,0,sizeof(szFrom));
				memset(szTo,0,sizeof(szTo));
				_tcscpy(szFrom,_T("entry\\*.*"));
				_tcscpy(szTo,pCfg->strVsDir);
				_tcscat(szTo,pCfg->strDataTarget);
				bOK = 0==SHFileOperation(&shfo);
			}
			//��дSouiWizard.vsz
			if(bOK)
			{
				_tcscpy(szFrom,pCfg->strEntrySrc);
				_tcscat(szFrom,_T("\\SouiWizard.vsz"));
				_tcscpy(szTo,pCfg->strVsDir);
				_tcscat(szTo,pCfg->strEntryTarget);
                _tcscat(szTo,_T("\\SouiWizard.vsz"));
				
				CopyFile(szFrom,szTo,FALSE);
								
				FILE *f=_tfopen(szTo,_T("r"));
				if(f)
				{
				    char szBuf[4096];
				    int nReaded=fread(szBuf,1,4096,f);
				    szBuf[nReaded]=0;
				    fclose(f);
				    
				    f=_tfopen(szTo,_T("w"));
				    if(f)
                    {//���ԭ����������д��������
                        CStringA str=szBuf;
                        str.Replace("%SOUIPATH%",CT2A(szSouiDir));
                        fwrite((LPCSTR)str,1,str.GetLength(),f);
                        fclose(f);
                    }
				}
			}

			CString strMsg;
			strMsg.Format(_T("Ϊ%s��װSOUI��:%s"),pCfg->strName,bOK?_T("�ɹ�"):_T("ʧ��"));
			::SendMessage(GetDlgItem(IDC_LOG),LB_ADDSTRING,0,(LPARAM)(LPCTSTR)strMsg);
		}

		return 0;
	}

	LRESULT OnUninstall(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		CListViewCtrl vslist;
		vslist.Attach(GetDlgItem(IDC_VSLIST));

		SHFILEOPSTRUCT shfo={0};
		shfo.pTo=NULL;
		shfo.wFunc=FO_DELETE;
		shfo.fFlags=FOF_NOCONFIRMMKDIR|FOF_NOCONFIRMATION|FOF_SILENT;

		for(int i=0;i<vslist.GetItemCount();i++)
		{
			if(!vslist.GetCheckState(i)) continue;

			VSENVCFG *pCfg=(VSENVCFG*)vslist.GetItemData(i);
            //remove entry files
            CString strSource=pCfg->strVsDir+pCfg->strEntryTarget+_T("\\SouiWizard.ico");
            BOOL bOK = DeleteFile(strSource);
            if(bOK)
            {
                strSource=pCfg->strVsDir+pCfg->strEntryTarget+_T("\\SouiWizard.vsdir");
                bOK = DeleteFile(strSource);
            }
            if(bOK)
            {
                strSource=pCfg->strVsDir+pCfg->strEntryTarget+_T("\\SouiWizard.vsz");
                bOK = DeleteFile(strSource);
            }

			CString strMsg;
			strMsg.Format(_T("��%s��ж��SOUI��%s"),pCfg->strName,bOK?_T("�ɹ�"):_T("ʧ��"));
			::SendMessage(GetDlgItem(IDC_LOG),LB_ADDSTRING,0,(LPARAM)(LPCTSTR)strMsg);

		}
		return 0;
	}

	LRESULT OnCancel(WORD /*wNotifyCode*/, WORD wID, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
	{
		EndDialog(wID);
		return 0;
	}
};
