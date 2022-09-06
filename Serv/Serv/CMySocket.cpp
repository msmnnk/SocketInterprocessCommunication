#include "pch.h"
#include "CMySocket.h"
#include "Serv.h"
#include "ServDlg.h"
#include "afxwin.h"
#include "stdio.h";

// CMySocket

CMySocket::CMySocket(){
}

CMySocket::~CMySocket(){
}

void CMySocket::SetParentDlg(CServDlg* pDlg){
	m_pDlg = pDlg;
}

void CMySocket::OnAccept(int nErrorCode){
	AfxMessageBox(CString("Есть соединение"));
	m_pDlg->OnAccept();
	CSocket::OnAccept(nErrorCode);
}

void CMySocket::OnReceive(int nErrorCode){
	AfxMessageBox(CString("Данные получены"));
	m_pDlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}