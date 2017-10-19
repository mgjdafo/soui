#ifndef IMAGE3D_H_CBBEE65C_14A5_4811_9AED_65F25D658C01
#define IMAGE3D_H_CBBEE65C_14A5_4811_9AED_65F25D658C01

#ifdef IMAGE3D_EXPORTS
#define IMAGE3D_API __declspec(dllexport)
#else
	#ifdef USE3DIMAGE_DLL
	#define IMAGE3D_API __declspec(dllimport)
	#else
	#define IMAGE3D_API 
	#endif
#endif

namespace IMAGE3D
{
	struct PARAM3DTRANSFORM
	{
		int     nRotateX;
		int     nRotateY;
		int     nRotateZ;
		int     nOffsetZ;
	};

	struct Quad;
	class IMAGE3D_API C3DTransform
	{
	public:
		C3DTransform()
		{
			m_pSrcBits = 0;

			Initialize();
		}

		virtual ~C3DTransform();
	public:

		//************************************
		// Method:    Render
		// FullName:  IMAGE3D::C3DTransform::Render
		// Access:    public 
		// Returns:   void
		// Qualifier:
		// Parameter: const PARAM3DTRANSFORM & param3d:3D�任����
		//************************************
		void  Render(const PARAM3DTRANSFORM & param3d);

		//************************************
		// Method:    SetImage
		// FullName:  IMAGE3D::C3DTransform::SetImage
		// Access:    public 
		// Returns:   BOOL
		// Qualifier:
		// Parameter: LPBYTE pSour : Դͼ������
		// Parameter: LPBYTE pDest : ���������
		// Parameter: int nWid		:Դͼ���
		// Parameter: int nHei		:Դͼ�߶�
		// Parameter: int nBitsPixel:������ȣ�ֻ֧��24��32λ���ָ�ʽ
		//************************************
		BOOL SetImage(LPBYTE pSour,LPBYTE pDest,int nWid,int nHei,int nBitsPixel);
	protected:
		void  Initialize();
		void  GetQuadByAnimateValue(int nDegreeX, int nDegreeY, int nDegreeZ, int nZOffset, Quad* pOut);

	protected:
		int		m_nSrcWndWidth,m_nSrcWndHeight;
		int		m_nBitsPixel;
		int		m_nSrcPitch;
		LPBYTE  m_pSrcBits;
		LPBYTE  m_pDstBits;
	};

}


#endif // IMAGE3D_H_CBBEE65C_14A5_4811_9AED_65F25D658C01