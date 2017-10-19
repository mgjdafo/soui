#pragma once

#include "interface/render-i.h"

namespace SOUI
{
	/// <summary>
	///		���汾�����ȥ���˶�8��16��24λ��֧��,
	/// </summary>
	class SOUI_EXP SDIBHelper
	{
    public:
		
        static bool Colorize(IBitmap * pBmp, COLORREF crRef);
		
        static bool Colorize(COLORREF & crTarget,COLORREF crRef);

		static bool GrayImage(IBitmap * pBmp); 
        
        //����ͼƬ��ƽ��ɫ
        //IBitmap *pBmp:ͼƬԴ
        //int nPercent:��Чֵ�ٷֱȣ�90������ߺ����5%��ֵ�ᶪ����������ƽ����
        //int int nBlockSize:�ֿ��С, ÿ�μ���һ�������ɫƽ��ֵ��
        static COLORREF CalcAvarageColor(IBitmap *pBmp,int nPercent=90,int nBlockSize=5);
    };

}//namespace SOUI