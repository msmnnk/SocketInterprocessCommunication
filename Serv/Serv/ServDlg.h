
// ServDlg.h : header file
//

#pragma once
#include "CMySocket.h"
#include <string>
// CServDlg dialog
class CServDlg : public CDialogEx
{
// Construction
public:
	CServDlg(CWnd* pParent = nullptr);	// standard constructor
	CMySocket m_pListenSocket;
	CMySocket m_pConnectSocket;




// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_SERV_DIALOG };
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
	CEdit m_sData;
	void OnAccept();
	void OnReceive();
	void OnListen();
	void OnSend(CString tmp);
	afx_msg void OnBnClickedListen();
};
