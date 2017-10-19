#include "stdafx.h"
#include "3dtransform.h"
#include "PerspectiveTransform.h"
#include "3dlib.h"
#include <float.h>
#include <malloc.h>

bool  g_bInitSinCosTable = false;

#define STRIDELEN(WID,BITPIXEL) ((WID*BITPIXEL+31)/32*4)
namespace IMAGE3D
{

	C3DTransform::~C3DTransform()
	{
		if(m_pSrcBits) free(m_pSrcBits);
	}

void  C3DTransform::Initialize()
{

    if (false == g_bInitSinCosTable)
    {
        _control87(_MCW_RC, _RC_DOWN); //����FPU������ģʽ����Bilinear��������Ҫʹ�û��ӿ�float->int

        Build_Sin_Cos_Tables();
        g_bInitSinCosTable = true;
    }
}

// ʹ��3Dͼ���㷨����ȡͼƬ��ת����ĸ�����λ��
void C3DTransform::GetQuadByAnimateValue(int nDegreeX, int nDegreeY, int nDegreeZ, int nZOffset, Quad* pOutQuad)
{
	// .�ֲ�����(�Ծ��ε�������Ϊ�ֲ������ԭ��)
	float x = (float)m_nSrcWndWidth/2;
	float y = (float)m_nSrcWndHeight/2;

	POINT3D  pt3dModel[4] = { 
		{-x, y, 0}, {x, y, 0}, {x, -y, 0}, {-x, -y, 0}
	};
	POINT3D pt3DWorld[4] = {0};
	POINT3D pt3DCamera[4] = {0};

#pragma region // .�ֲ�����->��������
	{
		// .�Ե�ǰֵ��Ϊ�ǶȽ�����ת
		float fDegreeX = (float)nDegreeX;
		float fDegreeY = (float)nDegreeY;
		float fDegreeZ = (float)nDegreeZ;

		MATRIX_4_4  matTemp1, matTemp2;
		MATRIX_4_4  matRotateY, matRotateX, matRotateZ;

		MATRIX_4_4_PTR pLeftArg = NULL;
		if (0 != fDegreeY)
		{
			MAT_IDENTITY_4_4(&matRotateY);
			matRotateY.M00 = Fast_Cos(fDegreeY);
			matRotateY.M02 = -Fast_Sin(fDegreeY);
			matRotateY.M20 = Fast_Sin(fDegreeY);
			matRotateY.M22 = Fast_Cos(fDegreeY);
			
			pLeftArg = &matRotateY;
		}

		if (0 != fDegreeX)
		{

			MAT_IDENTITY_4_4(&matRotateX);
			matRotateX.M11 = Fast_Cos(fDegreeX);
			matRotateX.M12 = Fast_Sin(fDegreeX);
			matRotateX.M21 = -Fast_Sin(fDegreeX);
			matRotateX.M22 = Fast_Cos(fDegreeX);

			if (NULL == pLeftArg)
			{
				pLeftArg = &matRotateX;
			}
			else
			{
				Mat_Mul_4X4(pLeftArg, &matRotateX, &matTemp1);
				pLeftArg = &matTemp1;
			}
		}

		if (0 != fDegreeZ)
		{

			MAT_IDENTITY_4_4(&matRotateZ);
			matRotateZ.M00 = Fast_Cos(fDegreeZ);
			matRotateZ.M01 = Fast_Sin(fDegreeZ);
			matRotateZ.M10 = -Fast_Sin(fDegreeZ);
			matRotateZ.M11 = Fast_Cos(fDegreeZ);

			if (NULL == pLeftArg)
			{
				pLeftArg = &matRotateZ;
			}
			else
			{
				Mat_Mul_4X4(pLeftArg, &matRotateZ, &matTemp2);
				pLeftArg = &matTemp2;
			}
		}

		if (pLeftArg)
		{
			for (int i = 0; i < 4; i++)
				Mat_Mul_VECTOR3D_4X4(&pt3dModel[i], pLeftArg, &pt3DWorld[i]);
		}
		else
		{
			for (int i = 0; i < 4; i++)
			{
				pt3DWorld[i].x = pt3dModel[i].x;
				pt3DWorld[i].y = pt3dModel[i].y;
			}
		}

		// .������Ȼ��ƽ�Ƶ���������� ��0��0��0��λ�ã���˲��ü���ƽ��
		for (int i = 0; i < 4; i++)
		{
			pt3DWorld[i].z += nZOffset;
		}
	}
#pragma endregion

	// ���λ��(����Ĭ�Ͻ���ƽ�����������������ͬһλ�ã�����͸�ӳ���������ֱ�ӾͿ���
	// ������Ļ���������ˣ�ʡ��һ��������
	// ������Ҫע����ǣ����nCameraPos��С�Ļ�������ͼ��ͻ���С��
	CAMERA camerpos = {0};
	float  fCameraPos = 2000.0f;  // ���λ��
	float  d = fCameraPos;      // �������ƽ��ľ��롣����ֵ���һ����������һ�ε���Ļ�����ת��

	VECTOR4D_INITXYZ(&camerpos.WorldPos, 0,0, -fCameraPos);

#pragma region // ��������ת��Ϊ�������
	{
		// ƽ�ƾ���
		MATRIX_4_4  matCameraTrans = {0};
		MAT_IDENTITY_4_4(&matCameraTrans);
		matCameraTrans.M30 = -camerpos.WorldPos.x;
		matCameraTrans.M31 = -camerpos.WorldPos.y;
		matCameraTrans.M32 = -camerpos.WorldPos.z;
		
		// ����Ƕ�Ϊ0������ת

		for (int i = 0; i < 4; i++)
		{
			Mat_Mul_VECTOR3D_4X4(&pt3DWorld[i], &matCameraTrans, &pt3DCamera[i]);
		}
	}
#pragma endregion

#pragma region // �������ת��Ϊ͸������
	POINT3D pt3DPerspectivePos[4];
	for (int i = 0; i < 4; i++)
	{
		float z = pt3DCamera[i].z;  // �����z�����ں�d��ȵľ��룬��������. ��dֵȡ�ıȽ�Сʱ���ᵼ��zΪ��
		float i_z = 1/z;
		if (pt3DCamera[i].z != 0)
		{
			pt3DPerspectivePos[i].x = d * pt3DCamera[i].x * i_z;  // nCameraPos�൱��d
			pt3DPerspectivePos[i].y = d * pt3DCamera[i].y * i_z;  // 
		}
	}
#pragma endregion

	// ת������Ļ������
	for (int i = 0; i < 4; ++i)
	{
		pt3DPerspectivePos[i].x += (m_nSrcWndWidth>>1);
		pt3DPerspectivePos[i].y = -pt3DPerspectivePos[i].y;
		pt3DPerspectivePos[i].y += (m_nSrcWndHeight>>1);
	}

	// ��ֵ������ֵ
	for (int i = 0; i < 4; i++)
	{
		pOutQuad->pos[2*i]   = (int)pt3DPerspectivePos[i].x;
		pOutQuad->pos[2*i+1] = (int)pt3DPerspectivePos[i].y;
	}
}


// ���������øĳɺ궨�壬��Ϊ�����������̫Ƶ����
#define GetLine(pBits, nPitch,y) \
	(pBits + nPitch*(y))


void C3DTransform::Render(const PARAM3DTRANSFORM & param3d)
{
	RECT rc = {0, 0, m_nSrcWndWidth, m_nSrcWndHeight};

	// ���㵱ǰ�Ķ���������Ļ����
	Quad quad;
	GetQuadByAnimateValue(param3d.nRotateX,param3d.nRotateY, param3d.nRotateZ, param3d.nOffsetZ, &quad);

	// ���ڼ������->�����ı��εĶ�Ӧ��ϵ
	PerspectiveTransform perspective;
	perspective.SetQuad(&quad, &rc);
	perspective.ChangeToFixedPoint();

	int   nWidthDst  = m_nSrcWndWidth-1;   // (300->299)�����ݷ�Χ�����Ĵ�С��һ
	int   nHeightDst = m_nSrcWndHeight-1; //

	int nDstPitch = nWidthDst*4;

	float fxSrc = 0;
	float fySrc = 0;
	float *pfxSrc = &fxSrc;  // Ϊ����perspective_transform��ʹ��ָ��
	float *pfySrc = &fySrc;

	LPBYTE pDstBits=m_pDstBits;
	
	int nPixByte=m_nBitsPixel/8;

#if 1  // �ڴ�ѭ��֮ǰ�޳���һЩ�հ�����
	//��Ŀ��ͼƬ���
	memset(pDstBits, 0, nDstPitch * nHeightDst);

	int nMinX = max(0, min(min(min(quad.Ax,quad.Bx),quad.Cx),quad.Dx));
	int nMinY = max(0, min(min(min(quad.Ay,quad.By),quad.Cy),quad.Dy));
	int nMaxX = min(nWidthDst,  max(max(max(quad.Ax,quad.Bx),quad.Cx),quad.Dx));
	int nMaxY = min(nHeightDst, max(max(max(quad.Ay,quad.By),quad.Cy),quad.Dy));

	
	pDstBits += (nMinY*nDstPitch);
	for (int Y = nMinY; Y < nMaxY; Y++)
	{
		LPBYTE pDest=pDstBits;
		for (int X = nMinX; X < nMaxX; X++)
		{
#else
	for (int X = 0, Y = 0; Y < m_nSrcWndHeight; Y++)
	{
		for (X = 0; X < m_nSrcWndWidth; X++)
		{
#endif
			perspective_transform_fp(perspective, X, Y, pfxSrc, pfySrc);

			int nx = 0; //fx;   // ע: ֱ�Ӹ�ֵ int i = floatvalue; �����һ�� _ftol()����
			int ny = 0; //fy;   //     ����Ч�ʽ��͡�����ʹ����Ƕ���ָ�(3D��Ϸ��̴�ʦ���� P918)

			// ������ת������ ע�⣺Ĭ�ϵ�fistp����������ģʽ����Ҫͨ������_control87(_MCW_RC, _RC_DOWN);���е���
#ifndef _WIN64
			__asm	fld    fxSrc;
			__asm	fistp  nx;

			__asm	fld    fySrc;
			__asm	fistp  ny;
#else
            nx = int(fxSrc);
            ny = int(fySrc);
#endif//WIN32

			// 1. ceil��Ч�ʷǳ��ǳ���!ǧ���������
			// ������һ���������heightΪ300��ySrc=299.99999999ʱ��ת��(int)�õ��Ľ����300��
			// ���������жϵĻ��ǳɹ��ģ���������������˵�ySrc>299ʱ���˳�
			if (nx < 0 || nx >= nWidthDst || ny < 0 || ny >= nHeightDst)
			{        
				continue;
			}

			// Ŀ����Դͼ���ض�Ӧ
#if 0
			//////////////////////////////////////////////////////////////////////////
			// �ڽ�ȡ��, �ٶȿ죬���о��
			((DWORD*)pDstBits)[X] = ((DWORD*)(m_pSrcBits + m_nSrcPitch*(int)ySrc))[(int)xSrc];
#else
			//////////////////////////////////////////////////////////////////////////
			// �������Բ�ֵ������Чȥ����ݣ����ٶȷǳ���
			//((DWORD*)pDstBits)[X] = Bilinear(m_pSrcBits, m_nSrcPitch, nx, ny, (float)fxSrc, (float)fySrc);

			//
			// �������Բ�ֵ��ʽ�Ƶ�
			// http://blog.csdn.net/dakistudio/article/details/1767100 �������Բ�ֵ��ʽ�Ƶ�
			//
			// xΪfx������ȡ����yΪfy������ȡ��
			//
			//inline DWORD& Bilinear(BYTE* pBits, const int& nPitch, const int& x, const int& y, const float& fx, const float& fy)
			{
				// �ѽ�ԭʼͼƬ��right/bottom����1px�������ڻ�ȡ x+1, y+1ʱ�ﵽ�����ԵҲ�������
				// ȡ�������ĸ����ص���ɫֵ(x,y) (x+1, y) (x, y+1) (x+1, y+1)

				LPBYTE pValue=GetLine(m_pSrcBits, m_nSrcPitch, ny);
				pValue += nx*nPixByte;

				LPBYTE p0=pValue;//(x,y);
				LPBYTE p2=pValue+nPixByte;//(x+1,y)
				pValue+=m_nSrcPitch;//y+1
				LPBYTE p1=pValue;//(x,y+1)
				LPBYTE p3=pValue+nPixByte;//(x+1,y+1)

				// ���������˷�תΪ�������˷���ͬʱ�Ż�������ת��������
				float u = (float)fxSrc - nx;
				float v = (float)fySrc - ny;
			
#ifndef _WIN64
				float fpm3 = FLOAT_TO_FIXP16(u*v);
				float fpm2 = FLOAT_TO_FIXP16(u*(1.0f-v));
				float fpm1 = FLOAT_TO_FIXP16(v*(1.0f-u));
				float fpm0 = FLOAT_TO_FIXP16((1.0f-u)*(1.0f-v));
				int pm3_16 = 0;
				int pm2_16 = 0;
				int pm1_16 = 0;
				int pm0_16 = 0;
				__asm
				{
					fld    fpm3;
					fistp  pm3_16;
					fld    fpm2;
					fistp  pm2_16;
					fld    fpm1;
					fistp  pm1_16;
					fld    fpm0;
					fistp  pm0_16;
				}
#else
                int pm3_16 = int(FLOAT_TO_FIXP16(u*v));
                int pm2_16 = int(FLOAT_TO_FIXP16(u*(1.0f-v)));
                int pm1_16 = int(FLOAT_TO_FIXP16(v*(1.0f-u)));
                int pm0_16 = int(FLOAT_TO_FIXP16((1.0f-u)*(1.0f-v)));
#endif//WIN32
                pDest = pDstBits + X * nPixByte;
				*pDest++=(BYTE)((pm0_16*(*p0++) + pm1_16*(*p1++) + pm2_16*(*p2++) + pm3_16*(*p3++)) >> FIXP16_SHIFT);
				*pDest++=(BYTE)((pm0_16*(*p0++) + pm1_16*(*p1++) + pm2_16*(*p2++) + pm3_16*(*p3++)) >> FIXP16_SHIFT);
				*pDest++=(BYTE)((pm0_16*(*p0++) + pm1_16*(*p1++) + pm2_16*(*p2++) + pm3_16*(*p3++)) >> FIXP16_SHIFT);
				if(nPixByte==4) *pDest++=(BYTE)((pm0_16*(*p0++) + pm1_16*(*p1++) + pm2_16*(*p2++) + pm3_16*(*p3++)) >> FIXP16_SHIFT);
			}
#endif
		}
		pDstBits += nDstPitch;
	}
}



BOOL C3DTransform::SetImage( LPBYTE pSour,LPBYTE pDest,int nWid,int nHei,int nBitsPixel )
{
	if(nBitsPixel!=24 && nBitsPixel!=32) //ֻ֧��24��32λ
		return FALSE;

	m_nSrcWndWidth=nWid+1,m_nSrcWndHeight=nHei+1;
	m_nSrcPitch=STRIDELEN(m_nSrcWndWidth,nBitsPixel);
	m_pSrcBits=(LPBYTE)calloc(1,m_nSrcPitch*m_nSrcWndHeight);
	m_nBitsPixel=nBitsPixel;
	m_pDstBits=pDest;

	LPBYTE p1=m_pSrcBits+m_nSrcPitch;//bottom-up������������һ��
	LPBYTE p2=pSour;
	int nLen=STRIDELEN(nWid,nBitsPixel);
	for(int i=0;i<nHei;i++)
	{
		memcpy(p1,p2,nLen);
		p1+=m_nSrcPitch;
		p2+=nLen;
	}
	return TRUE;
}

}//end of namespace