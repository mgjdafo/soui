#pragma once

namespace SOUI
{
class SOUI_EXP STileViewItemLocator : public TObjRefImpl<IObjRef>
{
public:
    STileViewItemLocator(int nItemHei, int nItemWid, int nMarginSize = 0);
    
    void SetAdapter(ILvAdapter *pAdapter);
    
    void OnDataSetChanged() {}
    
    int GetItemHeight(int iItem) const;
    void SetItemHeight(int iItem, int nHeight);
    
    //��ȡitem��CRect(�����TileView)
    CRect GetItemRect(int iItem);
    
    //����TileView��ȣ���TileView��OnSize�е��ã�
    void SetTileViewWidth(int width);
    
    //��ȡitem���С���λ��
    void GetItemRowAndColIndex(int iItem, int &row, int &col);
    
    //�Ƿ�Ϊÿ�е����һ��Ԫ��
    BOOL IsLastInRow(int iItem);
    
    //��ȡ��һ�У�ͬһ�е�Ԫ��index
    int GetUpItem(int iItem);
    //��ȡ��һ�У�ͬһ�е�Ԫ��index
    int GetDownItem(int iItem);
    
    int GetTotalHeight();
    
    int Item2Position(int iItem);
    int Position2Item(int position);
    
    int GetScrollLineSize() const;
    
    int GetMarginSize() const
    {
        return m_nItemMargin;
    }
    
protected:
    //�иߣ����������
    int GetItemLineHeight() const
    {
        return m_nItemHeight + m_nItemMargin;
    }
    
    int m_nItemWidth;      //item��
    int m_nItemHeight;     //item��
    int m_nTileViewWidth;  //TileView��ȣ����ڼ���m_nCountInRow��
    int m_nItemMargin;     //����
    int m_nCountInRow;     //ÿ�е�item����
    
    CAutoRefPtr<ILvAdapter> m_adapter;
};

}
