
// ServDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "Serv.h"
#include "ServDlg.h"
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


// CServDlg dialog



CServDlg::CServDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SERV_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CServDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DATA, m_sData);
}

BEGIN_MESSAGE_MAP(CServDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_LISTEN, &CServDlg::OnBnClickedListen)
END_MESSAGE_MAP()


// CServDlg message handlers

BOOL CServDlg::OnInitDialog()
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


	m_pListenSocket.SetParentDlg(this);
	m_pConnectSocket.SetParentDlg(this);
	m_pListenSocket.Create(2000);   // 2000 порт 


	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CServDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CServDlg::OnPaint()
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
HCURSOR CServDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CServDlg::OnAccept()
{
	m_pListenSocket.Accept(m_pConnectSocket);
}

void CServDlg::OnReceive(){
	char* pBuf = new char[1025];
	int n = m_pConnectSocket.Receive(pBuf, 1024);
	pBuf[n] = NULL;
	m_sData.SetWindowText(CString(pBuf));
	UpdateData(FALSE);
	OnSend(CString(pBuf));
}

void CServDlg::OnListen()
{
	m_pListenSocket.Listen();	
}



void CServDlg::OnSend(CString tmp){
	CHAR str[80];
	UpdateData(TRUE);
	CString field;

	int matrix[9];

	int index = 0;
	while (AfxExtractSubString(field, tmp, index, _T(' ')))
	{
		if (index < 9)
		{
			matrix[index] = _wtoi(field);
		}
		++index;
	}
	int sum = 0;
	for (int i = 0; i < 9; i++)
	{
		if (i % 2 == 0)
		{
			sum += matrix[i];
		}
	}

	sprintf_s(str, "%d", sum);
	DWORD lstr = 80;

	m_pConnectSocket.Send(str, lstr);
}



void CServDlg::OnBnClickedListen()
{
	// TODO: Add your control notification handler code here
	OnListen();


}
