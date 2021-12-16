#pragma once
#include <BCGPTabctrl.h>


class CTabctrl_Postgis : public CBCGPTabCtrl
{
    DECLARE_DYNAMIC(CTabctrl_Postgis)
public:
    CTabctrl_Postgis();
    virtual ~CTabctrl_Postgis();

    CBCGPDialog*    m_tabPages[2];
    int             m_tabCurrent;
    int             m_nNumberOfPages;
protected:
    DECLARE_MESSAGE_MAP()
public:
    void Init();
    void SetRetanggle();
    afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
    void OnSize(UINT nType, int cx, int cy);
    void TurnOnEnKill();
};

