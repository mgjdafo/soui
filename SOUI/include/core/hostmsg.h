// SOUI�Զ��崰����ϢID
// 2015��12��3��
#pragma once

#define HOSTMSG_BASE     (WM_USER+10000)

#define UM_UPDATESWND    (HOSTMSG_BASE+100)    //���͵��������ڵ�����ˢ�·Ǳ�����ϴ��ڵ��Զ�����Ϣ, wParam:SWND
#define UM_SCRIPTTIMER   (HOSTMSG_BASE+201)    //�ű���ʱ����Ϣ
#define UM_MENUEVENT     (HOSTMSG_BASE+202)     //ģ��˵��ؼ��¼���wparam:0, lparam:EventArg *

#define SPYMSG_BASE      (HOSTMSG_BASE+1000)
#define SPYMSG_SETSPY    (SPYMSG_BASE+0)     //����SPY��Ϣ���մ��ھ��

#define SPYMSG_SWNDENUM  (SPYMSG_BASE+1)     //ö�ٴ����б�,wparam:SWND,lparam:SWindow::GetWindow
//���ش��ڵ�SWNDֵ

#define SPYMSG_SWNDINFO  (SPYMSG_BASE+2)      //��ȡ�������ԣ�wparam:swnd

#define SPYMSG_HITTEST   (SPYMSG_BASE+3)    //lparam:pos

