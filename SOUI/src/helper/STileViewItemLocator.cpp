#include "souistd.h"
#include "helper/STileViewItemLocator.h"

namespace SOUI
{
//////////////////////////////////////////////////////////////////////////
// STileViewItemLocatorFix
STileViewItemLocator::STileViewItemLocator(int nItemHei, int nItemWid, int nMarginSize /*= 0*/) :
    m_nItemHeight(nItemHei),
    m_nItemWidth(nItemWid),
    m_nItemMargin(nMarginSize),
    m_nTileViewWidth(0),
    m_nCountInRow(1)
{

}

int STileViewItemLocator::GetScrollLineSize() const
{
    return GetItemLineHeight();
}

int STileViewItemLocator::Position2Item(int position)
{
    if(!m_adapter)
    {
        return -1;
    }
    int nRet = position / GetItemLineHeight() * m_nCountInRow;
    
    if(nRet < 0)
    {
        nRet = 0;
    }
    if(nRet > m_adapter->getCount())
    {
        nRet = m_adapter->getCount();
    }
    return nRet;
}

int STileViewItemLocator::Item2Position(int iItem)
{
    return (iItem / m_nCountInRow) * GetItemLineHeight();
}

int STileViewItemLocator::GetTotalHeight()
{
    if(!m_adapter || m_adapter->getCount() == 0)
    {
        return 0;
    }
    int row_count = (m_adapter->getCount() - 1) / m_nCountInRow + 1;
    return GetItemLineHeight() * row_count +  m_nItemMargin;
}

void STileViewItemLocator::SetItemHeight(int iItem, int nHeight)
{
}

int STileViewItemLocator::GetItemHeight(int iItem) const
{
    return m_nItemHeight;
}

void STileViewItemLocator::SetAdapter(ILvAdapter *pAdapter)
{
    m_adapter = pAdapter;
}

CRect STileViewItemLocator::GetItemRect(int iItem)
{
    //���������TileView�ڲ���Rect
    int nRowIdx, nColIdx;
    GetItemRowAndColIndex(iItem, nRowIdx, nColIdx);
    
    CRect rect;
    rect.left = m_nItemMargin + nColIdx * (m_nItemWidth + m_nItemMargin);
    rect.top = m_nItemMargin + nRowIdx * (m_nItemHeight + m_nItemMargin);
    rect.right = rect.left + m_nItemWidth;
    rect.bottom = rect.top + m_nItemHeight;
    return rect;
}

void STileViewItemLocator::SetTileViewWidth(int width)
{
    m_nTileViewWidth = width;
    m_nCountInRow = m_nTileViewWidth / (m_nItemWidth + m_nItemMargin);
    if(m_nCountInRow == 0) m_nCountInRow=1;
}

void STileViewItemLocator::GetItemRowAndColIndex(int iItem, int &row, int &col)
{
    row = (iItem + 1) / m_nCountInRow;
    if(row * m_nCountInRow - 1 >= iItem)
    {
        row--;
    }
    col = m_nCountInRow - ((row + 1) * m_nCountInRow - iItem);
}

BOOL STileViewItemLocator::IsLastInRow(int iItem)
{
    return iItem % m_nCountInRow == m_nCountInRow - 1;
}

int STileViewItemLocator::GetUpItem(int iItem)
{
    int up_idx = iItem - m_nCountInRow;
    //û����һ���ˣ�����ԭֵ
    return up_idx < 0 ? iItem : up_idx;
}

int STileViewItemLocator::GetDownItem(int iItem)
{
    int up_idx = iItem + m_nCountInRow;
    if(up_idx < m_adapter->getCount())
    {
        return up_idx;
    }
    else if((m_adapter->getCount() - 1) / m_nCountInRow == iItem / m_nCountInRow)
    {
        //û����һ���ˣ�����ԭֵ
        return iItem;
    }
    //����һ�У���ͬһ��û��Ԫ�أ�������һ�����һ��Ԫ��
    return m_adapter->getCount() - 1;
}

}
