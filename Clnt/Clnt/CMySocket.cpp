#include "pch.h"
#include "CMySocket.h"
#include "Clnt.h"
#include "ClntDlg.h"
#include "afxwin.h"

// CMySocket
CMySocket::CMySocket(){

}

CMySocket::~CMySocket(){

}

// CMySocket member functions

void CMySocket::SetParentDlg(CClntDlg* pDlg){
	m_pDlg = pDlg;
}


void CMySocket::OnReceive(int nErrorCode) {	
	AfxMessageBox(CString("Ответ получен"));
	m_pDlg->OnReceive();
	CSocket::OnReceive(nErrorCode);
}