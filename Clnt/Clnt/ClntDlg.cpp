
// ClntDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Clnt.h"
#include "ClntDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CClntDlg dialog



CClntDlg::CClntDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CLNT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CClntDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA, m_sData);
	DDX_Control(pDX, IDC_DAT, m_sData2);
}

BEGIN_MESSAGE_MAP(CClntDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_CONNECT, &CClntDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_SEND, &CClntDlg::OnBnClickedSend)
	ON_EN_CHANGE(IDC_DAT, &CClntDlg::OnEnChangeDat)
END_MESSAGE_MAP()


// CClntDlg message handlers

BOOL CClntDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
	m_pConnectSocket.SetParentDlg(this);
	m_pConnectSocket.Create();

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CClntDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CClntDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CClntDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CClntDlg::OnConnect()
{
	CString tmp("127.0.0.1");
	m_pConnectSocket.Connect(tmp, 2000);
}
void CClntDlg::OnSend()
{
	CHAR str[80];
	DWORD lstr;
	CString tmp;
	m_sData.GetWindowText(tmp);
	for (int i = 0; i < tmp.GetLength(); i++) {
		str[i] = tmp[i];
	}	
	lstr = m_sData.GetWindowTextLength();
	m_pConnectSocket.Send(str, lstr);

}



void CClntDlg::OnReceive() {	
	char* pBuf = new char[1025];
	int n = m_pConnectSocket.Receive(pBuf, 1024);
	pBuf[n] = NULL;
	m_sData2.SetWindowText(CString(pBuf));
	UpdateData(FALSE);
}

void CClntDlg::OnBnClickedConnect()
{
	// TODO: Add your control notification handler code here
	OnConnect();
}


void CClntDlg::OnBnClickedSend()
{
	// TODO: Add your control notification handler code here
	OnSend();
}


void CClntDlg::OnEnChangeDat()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialogEx::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}
