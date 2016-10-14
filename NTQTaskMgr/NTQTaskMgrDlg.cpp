
// NTQTaskMgrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NTQTaskMgr.h"
#include "NTQTaskMgrDlg.h"
#include "afxdialogex.h"
#include "perfdata.h"
#include "ListProcessPage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CNTQTaskMgrDlg dialog



CNTQTaskMgrDlg::CNTQTaskMgrDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNTQTaskMgrDlg::IDD, pParent)
	, m_csStatus(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CNTQTaskMgrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LST_PROCESS, m_listCtlProcess);
	DDX_Text(pDX, IDC_EDT_STATUS, m_csStatus);
}

BEGIN_MESSAGE_MAP(CNTQTaskMgrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LST_PROCESS, &CNTQTaskMgrDlg::OnLvnGetdispinfoLstProcess)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LST_PROCESS, &CNTQTaskMgrDlg::OnLvnItemchangedLstProcess)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CNTQTaskMgrDlg::OnHdnItemclickLstProcess)
END_MESSAGE_MAP()


// CNTQTaskMgrDlg message handlers

BOOL CNTQTaskMgrDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// init performance
	//
	PerfDataInitialize();

	// NoiTQ: my code
	//
	InitListProcessPage(&m_listCtlProcess);
	SetTimer(TIMER_UPDATE_LIST_PROCESS, TIMER_UPDATE_LIST_PROCESS_INTERVAL, NULL);

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNTQTaskMgrDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CNTQTaskMgrDlg::OnPaint()
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
HCURSOR CNTQTaskMgrDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CNTQTaskMgrDlg::UpdateDataAndUI(void)
{
	CString csTemp;
	ULONG ulIndex = 0;
	PPERFDATA pdata = NULL;
	ULONG ulCountProcess = PerfDataGetProcessCount();

	// update status
	m_csStatus.Format(L"Cpu usage: %02d - Count process: %d", PerfDataGetProcessorUsage(), ulCountProcess);
	UpdateData(FALSE);

	UpdateProcess(&m_listCtlProcess);
}


void CNTQTaskMgrDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case TIMER_UPDATE_LIST_PROCESS:
		{
			PerfDataRefresh();
			UpdateDataAndUI();
		}
		break;

	default:
		CDialogEx::OnTimer(nIDEvent);

	}
		
}

void CNTQTaskMgrDlg::OnLvnGetdispinfoLstProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	NMLVDISPINFO *pnmdi = reinterpret_cast<NMLVDISPINFO*>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	LPNMHEADER     pnmhdr;
	ULONG          Index;
	ULONG          ColumnIndex;
	LPPROCESS_PAGE_LIST_ITEM  pData;

	if (!(pnmdi->item.mask & LVIF_TEXT))
		return;

	pData = (LPPROCESS_PAGE_LIST_ITEM)pnmdi->item.lParam;
	Index = PerfDataGetProcessIndex(pData->ProcessId);
	ColumnIndex = pnmdi->item.iSubItem;

	PerfDataGetText(Index, ColumnIndex, pnmdi->item.pszText, pnmdi->item.cchTextMax);
}


void CNTQTaskMgrDlg::OnLvnItemchangedLstProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;
}


void CNTQTaskMgrDlg::OnHdnItemclickLstProcess(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMHEADER phdr = reinterpret_cast<LPNMHEADER>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	SetSortColumn(phdr->iItem);
}


