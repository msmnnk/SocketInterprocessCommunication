
// ClntDlg.h : header file
//

#pragma once
#include "CMySocket.h"


// CClntDlg dialog
class CClntDlg : public CDialogEx
{
// Construction
public:
	CClntDlg(CWnd* pParent = nullptr);	// standard constructor
	CMySocket m_pConnectSocket;

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CLNT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	void OnConnect();
	void OnSend();
	void OnReceive();
	CEdit m_sData;
	afx_msg void OnBnClickedConnect();
	afx_msg void OnBnClickedSend();
	CEdit m_sData2;
	afx_msg void OnEnChangeDat();
};
