#include "stdafx.h"
#include "resource.h"
#include "BCGPSymbolizer.h"
#include "Tabctrl_Postgis.h"
#include "Tab_one_Postgis.h"
#include "Tab_two_Postgis.h"

IMPLEMENT_DYNAMIC(CTabctrl_Postgis, CBCGPTabCtrl)

CTabctrl_Postgis::CTabctrl_Postgis()
{
	m_tabPages[0] = new CTab_one_Postgis;
	m_tabPages[1] = new CTab_two_Postgis;
	m_tabCurrent = 0;
	m_nNumberOfPages = 2;
}

CTabctrl_Postgis::~CTabctrl_Postgis()
{
	//for (int i = 0; i<m_nNumberOfPages; i++)
		//delete m_tabPages[i];
}

BEGIN_MESSAGE_MAP(CTabctrl_Postgis, CBCGPTabCtrl)
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()

void CTabctrl_Postgis::Init()
{
	m_tabCurrent = 0;

	m_tabPages[0]->Create(IDD_TAB_1_POSTGIS, this);
	m_tabPages[1]->Create(IDD_TAB_2_POSTGIS, this);

	m_tabPages[0]->ShowWindow(SW_SHOW); 
	m_tabPages[1]->ShowWindow(SW_HIDE);

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

void CTabctrl_Postgis::OnSize(UINT nType, int cx, int cy)
{
	CBCGPTabCtrl::OnSize(nType, cx, cy);

	CRect tabRect, itemRect;
	int nX, nY, nXc, nYc;
	GetClientRect(&tabRect);
	GetItemRect(0, &itemRect);
	nX = itemRect.left;
	nY = itemRect.bottom + 1;
	nXc = tabRect.right - itemRect.left - 1;
	nYc = tabRect.bottom - nY - 1;

	for (int i = 0; i < m_nNumberOfPages; i++)
	{
		m_tabPages[i]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_HIDEWINDOW);
	}
	m_tabPages[m_tabCurrent]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	/*for (int i = m_numberOfPages - 1; i >= 0; i--) {
		m_tabPages[i]->SetWindowPos(&wndTop, nX, nY, nXc, nYc, SWP_SHOWWINDOW);
	}*/
	//m_tabPages[m_tapCurrent]->SetFocus();
}

void CTabctrl_Postgis::TurnOnEnKill()
{
	for (int i = 0; i < m_nNumberOfPages; i++)
	{
		CTab_one_Postgis* Tab = (CTab_one_Postgis*)m_tabPages[i];
		Tab->m_activeEnKill = TRUE;
	}
}