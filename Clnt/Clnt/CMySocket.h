#pragma once
#include <afxsock.h>

class CClntDlg;
class CMySocket : public CSocket
{
public:
	CMySocket();
	virtual ~CMySocket();
	CClntDlg* m_pDlg;
	void SetParentDlg(CClntDlg* pDlg);
	virtual void OnReceive(int nErrorCode);

};