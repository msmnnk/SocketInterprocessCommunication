#pragma once
#include <afxsock.h>


class CServDlg;
class CMySocket : public CSocket
{
public:
	CMySocket();
	virtual ~CMySocket();
	CServDlg* m_pDlg;
	void SetParentDlg(CServDlg* pDlg);

	virtual void OnAccept(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};