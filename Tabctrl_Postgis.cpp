#include "stdafx.h"
#include "resource.h"
#include "Tabctrl_Postgis.h"
#include "CTab_one_Postgis.h"
//#include "CTab_two_Postgis.h"

CTabctrl_Postgis::CTabctrl_Postgis()
{
	m_tabPages[0] = new CTab_one_Postgis;
	m_tabPages[1] = new CTab_one_Postgis;
	m_tabCurrent = 0;
	m_nNumberOfPages = 1;
}

CTabctrl_Postgis::~CTabctrl_Postgis()
{
	for (int i = 0; i<m_nNumberOfPages; i++)
		delete m_tabPages[i];
}

BEGIN_MESSAGE_MAP(CTabctrl_Postgis, CBCGPTabCtrl)

	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CTabctrl_Postgis::Init()
{
	m_tabCurrent = 0;

	m_tabPages[0]->Create(IDD_TAB_1_POSTGIS, this);
	//m_tabPages[1]->Create(IDD_TAB_2_POSTGIS, this);

	m_tabPages[0]->ShowWindow(SW_SHOW); 
	//m_tabPages[1]->ShowWindow(SW_HIDE);

	SetRetanggle();
}

void CTabctrl_Postgis::SetRetanggle()
{
	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;

	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);

	nX = itemRect.left;
	nY = itemRect.bottom + 1;
	nXc = tabRect.right - itemRect.left - 1;
	nYc = tabRect.bottom - nY - 1;

	m_tabPages[0]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	for (int i = 0; i < m_nNumberOfPages; i++)
		m_tabPages[i]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);

}

void CTabctrl_Postgis::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_tabCurrent != GetCurFocus())
	{
		m_tabPages[m_tabCurrent]->ShowWindow(SW_HIDE);
		m_tabCurrent = GetCurFocus();
		m_tabPages[m_tabCurrent]->ShowWindow(SW_SHOW);
		m_tabPages[m_tabCurrent]->SetFocus();
	}

	CBCGPTabCtrl::OnLButtonDown(nFlags, point);
}
