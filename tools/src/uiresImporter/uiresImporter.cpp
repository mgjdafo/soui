// uiresIndexMake.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#ifdef _UNICODE
typedef std::wstring tstring;
#else
typedef std::string  tstring;
#endif

void printUsage();
void ImportResource(xml_node xmlNode, const tstring & strUiresDir,const tstring & strNamePrefix,xml_node xmlSkin);

bool g_bEnableColorize = true;//Ĭ��Ƥ��������ɫ

int _tmain(int argc, _TCHAR* argv[])
{
    tstring strUiresDir;    //uires·��������ڵ�ǰ·��
    tstring strSubDirs;     //��������Ŀ¼�б���Ŀ¼֮��ʹ�á�|���ֿ�.
    tstring strImgDir;      //ͼƬĿ¼����Ҫ����Ŀ¼�б��ظ���imglist: file[3].png imgframe: file[3{2,2,2,2}].png
    bool    bBackup=true;
    int c;

    _tprintf(_T("%s\n"),GetCommandLine());

    while ((c = getopt(argc, argv, _T("p:s:i:b:c:"))) != EOF || optarg!=NULL)
    {
        switch (c)
        {
        case 'p':strUiresDir=optarg;break;
        case 's':strSubDirs=optarg;break;
        case 'i':strImgDir=optarg;break;
        case 'b': bBackup = _tcsicmp(optarg,_T("no"))==0?false:true;
        case 'c': g_bEnableColorize = _tcsicmp(optarg,_T("no"))==0?false:true;
        default: break;
        }
    }
    
    if(strUiresDir.empty() || strSubDirs.empty() || strImgDir.empty())
    {
        printUsage();
        return 1;
    }

    SetCurrentDirectory(strUiresDir.c_str());
    xml_document docUiIdx;
    if(!docUiIdx.load_file("uires.idx"))
    {
        printf("load uires.idx failed.");
        return 2;
    }
    
    vector<tstring> vecSubDirs;

    int iStart = 0;
    while(iStart<strSubDirs.size())
    {
        int iFind = strSubDirs.find(_T('|'),iStart);
        if(iFind == strSubDirs.npos)
            iFind = strSubDirs.size();
        tstring strSubDir = strSubDirs.substr(iStart,iFind - iStart);
        vecSubDirs.push_back(strSubDir);
        iStart = iFind + 1;
    }

    xml_node xmlRes = docUiIdx.child(_T("resource"));
    for(int i=0;i<vecSubDirs.size();i++)
    {
        xml_node xmlType = xmlRes.child(vecSubDirs[i].c_str());
        //make sure xmlType is an empty element
        if(xmlType) xmlRes.remove_child(xmlType);
        xmlType = xmlRes.append_child(vecSubDirs[i].c_str());
        
        ImportResource(xmlType,vecSubDirs[i].c_str(),_T(""),xml_node());
    }
    
    xml_node xmlImage = xmlRes.child(strImgDir.c_str());
    if(xmlImage) xmlRes.remove_child(xmlImage);
    xmlImage = xmlRes.append_child(strImgDir.c_str());

    xml_document docSkin;
    docSkin.load_file(L"values\\skin.xml");
    xml_node xmlSkin = docSkin.child(_T("skin"));
    if(!xmlSkin) xmlSkin = docSkin.append_child(_T("skin"));
    ImportResource(xmlImage,strImgDir,_T(""),xmlSkin);
    
    if(bBackup)
    {//��������
        ::CopyFile(_T("uires.idx"),_T("uires.bak.idx"),FALSE);
        ::CopyFile(_T("values\\skin.xml"),_T("values\\skin.bak.xml"),FALSE);
    }
    docUiIdx.save_file(L"uires.idx");
    docSkin.save_file(L"values\\skin.xml");
	return 0;
}

void printUsage()
{
    LPCTSTR  szUsage[] =
    {
        _T("UiresImporter Usage: uiresImporter -p path -s subdirs -i image -b backup -c enableColorize\n"),
        _T("\tpath: specify uires path\n"),
        _T("\tsubdirs: specify subdirectorys that will be auto imported.\n"),
        _T("\timage: specify directory that will be auto imported as skin objects.\n"),
        _T("\t\timage name uses suffix format [states{left,top,right,bottom}] to identify skin format.\n"),
        _T("\tbackup: specify backup operating.\n"),
        _T("\t\t yes (defult) - backup\n"),
        _T("\t\t no - ignore backup\n"),
        _T("\tenableColorize: specify default skin enable colorize attibute.\n"),
        _T("\t\t yes (defult) - enable colorize\n"),
        _T("\t\t no - disable colorize\n"),
    };
    for(int i= 0;i< ARRAYSIZE(szUsage);i++)
    {
        _tprintf(szUsage[i]);
    }
}

void ImportResource(xml_node xmlNode, const tstring & strUiresDir,const tstring & strNamePrefix,xml_node xmlSkin)
{
    WIN32_FIND_DATA fd;
    HANDLE hContext = ::FindFirstFile((strUiresDir+_T("\\*.*")).c_str(), &fd);
    if(hContext!=INVALID_HANDLE_VALUE)
    {
        while(::FindNextFile(hContext,&fd))
        {
            if(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
            {
                if(_tcscmp(fd.cFileName,_T(".")) == 0 || _tcscmp(fd.cFileName,_T("..")) == 0)
                    continue;
                ImportResource(xmlNode, strUiresDir+_T("\\")+ fd.cFileName, strNamePrefix+ fd.cFileName + _T("."),xmlSkin);
            }else
            {
                xml_node newFile = xmlNode.append_child(_T("file"));
                TCHAR szName[MAX_PATH],szExt[50];
                _tsplitpath(fd.cFileName,NULL,NULL,szName,szExt);

                tstring strName,strPath;
                strName = strNamePrefix+szName;
                strPath = strUiresDir + _T("\\") + fd.cFileName;
                if(xmlSkin)
                {
                    LPTSTR p = _tcsrchr(szName,'[');
                    {
                        if(p) *p = 0;
                        strName = strNamePrefix+szName;
                        tstring src = xmlNode.name();
                        src += _T(":");
                        src += strName;
                        
                        xml_node node = xmlSkin.find_child_by_attribute(_T("name"),strName.c_str());
                        if(node) xmlSkin.remove_child(node);//�Զ�ʹ���µ�Ƥ���滻ԭ��Ƥ����

                        int nStates=1, left=-1,top=-1,right=-1,bottom=-1;
                        int nValues = 0;

                        int nColorize = g_bEnableColorize?1:0, //��ɫ��־ {ec=0/1}
                            nAutoFit = 1,  //����Ӧ��־{fit=0/1}
                            nTile = 0,     //ƽ�̱�־{tile=0/1}
                            nVertical = 0, //��ͼ��ֱ���б�־{vert=0/1}
                            nFilter=0;     //�����˾�:{filter=0/1/2/3} 0=null,1=low,2=midium,3=high
                        
                        if(p)
                        {
                            nValues = _stscanf(p+1,_T("%d{%d,%d,%d,%d}]"),&nStates,&left,&top,&right,&bottom);

                            LPCTSTR pszFind = _tcsstr(p+1,_T("{ec="));
                            if(pszFind) nColorize = _ttoi(pszFind+4);
                            pszFind = _tcsstr(p+1,_T("{fit="));
                            if(pszFind) nAutoFit = _ttoi(pszFind+5);
                            pszFind = _tcsstr(p+1,_T("{filter="));
                            if(pszFind) nFilter = _ttoi(pszFind+8);
                            pszFind = _tcsstr(p+1,_T("{tile="));
                            if(pszFind) nTile = _ttoi(pszFind+6);
                            pszFind = _tcsstr(p+1,_T("{vert="));
                            if(pszFind) nVertical = _ttoi(pszFind+6);
                        }

                        xml_node il = xmlSkin.append_child();
                        il.append_attribute(_T("name")).set_value(strName.c_str());
                        il.append_attribute(_T("src")).set_value(src.c_str());
                        il.append_attribute(_T("states")).set_value(nStates);
                        if(nValues==0 || nValues == 1)
                        {//imglist
                            il.set_name(_T("imglist"));
                        }else if(nValues==3 || nValues == 5)
                        {//imgframe
                            il.set_name(_T("imgframe"));

                            TCHAR szMargin[100];
                            _stprintf(szMargin,_T("%d,%d,%d,%d"),left,top,right==-1?left:right,bottom==-1?top:bottom);
                            il.append_attribute(_T("margin")).set_value(szMargin);
                        }

                        //���ø��ֿ�������
                        if(nColorize == 0) il.append_attribute(_T("enableColorize")).set_value(0);
                        if(nAutoFit == 0) il.append_attribute(_T("autoFit")).set_value(0);
                        if(nTile !=0 ) il.append_attribute(_T("tile")).set_value(1);
                        if(nVertical != 0 ) il.append_attribute(_T("vertical")).set_value(1);
                        switch(nFilter)
                        {
                        case 1:il.append_attribute(_T("filterLevel")).set_value(_T("low"));break;
                        case 2:il.append_attribute(_T("filterLevel")).set_value(_T("midium"));break;
                        case 3:il.append_attribute(_T("filterLevel")).set_value(_T("high"));break;
                        }
                    }
                }
                newFile.append_attribute(L"name").set_value(strName.c_str());
                newFile.append_attribute(L"path").set_value(strPath.c_str());
            }
        }
        ::FindClose(hContext);
    }
}