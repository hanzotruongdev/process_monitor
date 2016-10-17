
// NTQTaskMgrDlg.cpp : implementation file
//

#include "stdafx.h"
#include <windows.h>
#include <Winternl.h>

#include "NTQTaskMgr.h"
#include "NTQTaskMgrDlg.h"
#include "afxdialogex.h"
#include "perfdata.h"
#include "ListProcessPage.h"
#include "UndocumentStruct.h"
#include "FileDataStruct.h"

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
	DDX_Control(pDX, IDC_EDT_STATUS, m_edtCltStatus);
	DDX_Control(pDX, IDOK, m_btnOk);
}

BEGIN_MESSAGE_MAP(CNTQTaskMgrDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_TIMER()
	ON_NOTIFY(LVN_GETDISPINFO, IDC_LST_PROCESS, &CNTQTaskMgrDlg::OnLvnGetdispinfoLstProcess)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LST_PROCESS, &CNTQTaskMgrDlg::OnLvnItemchangedLstProcess)
	ON_NOTIFY(HDN_ITEMCLICK, 0, &CNTQTaskMgrDlg::OnHdnItemclickLstProcess)
	ON_WM_SIZE()
	ON_WM_MENUSELECT()
	ON_COMMAND_RANGE(ID_FILE_TAKESNAPSHOT,ID_FILE_REALTIME, MenuHandler)
	ON_WM_DROPFILES()
END_MESSAGE_MAP()


// CNTQTaskMgrDlg message handlers
#define IDM_DDD 16
#define IDM_EEE 17

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
			pSysMenu->AppendMenu(MF_STRING, IDM_DDD, L"DDD");
			pSysMenu->AppendMenu(MF_STRING, IDM_EEE, L"EEE");
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

	// calculate control position in dialog to make dynamic dialog
	//
	RECT rectDlg, rectList, rectBtnOk;
	GetClientRect(&rectDlg);
	m_listCtlProcess.GetClientRect(&rectList);

	m_listCltVerticalDelta = rectDlg.bottom - rectList.bottom;
	m_listCltHorizontalDelta = rectDlg.right - rectList.right;

	// parse commandline
	CCommandLineInfo objCommand;
	CString csFilePath;

	m_objApp->ParseCommandLine(objCommand);

	if (objCommand.m_nShellCommand == CCommandLineInfo::FileOpen)
	{
		OpenFile(objCommand.m_strFileName.GetBuffer());
	}

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
	ULONG ulCountProcess, ulProcesorsUsage, ulRamUsage;
	if (ConfigGetViewStyle() == TRUE)
	{ 
		ulCountProcess = PerfDataGetProcessCount();
		ulProcesorsUsage = PerfDataGetProcessorUsage();
		ulRamUsage = PerfDataGetMemoryUsage();
	}
	else
	{
		ulCountProcess = FileDataGetProcessCount();
		ulProcesorsUsage = FileDataGetProcessorUsage();
		ulRamUsage = FileDataGetMemoryUsage();
	}


	// update status
	m_csStatus.Format(L"Cpu usage: %02d - Memory: %02d - Count process: %d", ulProcesorsUsage, ulRamUsage, ulCountProcess);
	UpdateData(FALSE);

	// if view realtime
	if (ConfigIsRuning() && ConfigGetViewStyle() == TRUE)	
		PageUpdateProcess(&m_listCtlProcess);
}


void CNTQTaskMgrDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: Add your message handler code here and/or call default
	switch (nIDEvent)
	{
	case TIMER_UPDATE_LIST_PROCESS:
		{
			if (TRUE == ConfigGetViewStyle())
			{
				PerfDataRefresh();
			}

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
	ULONG          Index = 9999;
	ULONG          ColumnIndex;
	LPPROCESS_PAGE_LIST_ITEM  pData;

	if (!(pnmdi->item.mask & LVIF_TEXT))
		return;

	pData = (LPPROCESS_PAGE_LIST_ITEM)pnmdi->item.lParam;
	Index = ConfigGetViewStyle()? PerfDataGetProcessIndex(pData->ProcessId): FileDataGetProcessIndex(pData->ProcessId);
	ColumnIndex = pnmdi->item.iSubItem;

	PageDataGetText(Index, ColumnIndex, pnmdi->item.pszText, pnmdi->item.cchTextMax);
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

	ConfigSetSortColumn(phdr->iItem);
	PageUpdateProcess(&m_listCtlProcess);
}




void CNTQTaskMgrDlg::OnSize(UINT nType, int cx, int cy)
{
	RECT rectDlg, rectList, rectBtnOk, rectEdtStatus;

	CDialogEx::OnSize(nType, cx, cy);

	if (m_listCtlProcess.m_hWnd != nullptr )
	{
		GetClientRect(&rectDlg);
		m_edtCltStatus.GetClientRect(&rectEdtStatus);
		m_btnOk.GetClientRect(&rectBtnOk);

		m_edtCltStatus.SetWindowPos(NULL, 5, rectDlg.bottom - rectEdtStatus.bottom - 5, 
			rectEdtStatus.right, rectEdtStatus.bottom,0);

		m_listCtlProcess.SetWindowPos(NULL, 0, 0, 
			rectDlg.right - m_listCltHorizontalDelta, 
			rectDlg.bottom - m_listCltVerticalDelta, 0);

		m_btnOk.SetWindowPos(NULL, rectDlg.right - rectBtnOk.right - 5, rectDlg.bottom - rectBtnOk.bottom - 5,
			rectBtnOk.right, rectBtnOk.bottom, 0);
	}


	
}


void CNTQTaskMgrDlg::OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu)
{
	CDialogEx::OnMenuSelect(nItemID, nFlags, hSysMenu);

	// TODO: Add your message handler code here
	if (! (MF_MOUSESELECT & nFlags))
		return;

}

void CNTQTaskMgrDlg::MenuHandler(UINT i)
{
	switch (i)
	{
	case ID_FILE_REALTIME:
		SwitchToRealTime();
		break;

	case ID_FILE_TAKESNAPSHOT:
		ExportPerfToFile();
		break;

	case ID_FILE_OPEN_SNAPSHOT:
		OpenFile();
		break;

	case ID_FILE_EXIT:
		this->PostMessage(WM_QUIT, 0, 0);
		break;

	case ID_HELP_README:
		{
			MessageBox(L"No more to read...");
		}
		break;

	case ID_HELP_ABOUT:
		{
			CAboutDlg dlgAbout;
			dlgAbout.DoModal();
		}
		break;

	default:
		break;
	}
}

// 
// menu ID_FILE_TAKE_SNAPSHOT handler
//
void CNTQTaskMgrDlg::ExportPerfToFile()
{
	CString strPathname;
	WCHAR szFilters[]= L"NTQ TaskMgr File (*.NTF)|*.NTF|All Files (*.*)|*.*||";
	PVOID buffer = NULL;

	// take snapshot to buffer
	if (!PerfDataTakeSnapshot(&buffer))
		return;

	// use CFileDialog to get export file path
	//
	CFileDialog fileDlg(FALSE, L"ntf", L"*.ntf",
		OFN_PATHMUSTEXIST| OFN_OVERWRITEPROMPT, szFilters, this);

	if( fileDlg.DoModal ()!=IDOK )
		goto RET;

	strPathname = fileDlg.GetPathName();
	
	// write snapshot buffer to file
	//
	FileTakeSnapshot(strPathname.GetBuffer(), buffer);

RET:
	// cleanup beffor return
	if (buffer)
	{
		HeapFree(GetProcessHeap(), 0, buffer);
	}
}

BOOL CNTQTaskMgrDlg::OpenFile(WCHAR * pszFile)
{
	BOOL bRet = FALSE;
	CString strPathname;
	PVOID buffer = NULL;

	if (pszFile == NULL)
	{
		// use CFileDialog to get export file path
		//
		WCHAR szFilters[]= L"NTQ TaskMgr File (*.NTF)|*.NTF|All Files (*.*)|*.*||";
		CFileDialog fileDlg(TRUE, L"ntf", L"*.ntf",
			OFN_FILEMUSTEXIST| OFN_HIDEREADONLY, szFilters, this);

		if( fileDlg.DoModal ()!=IDOK )
			goto RET;

		strPathname = fileDlg.GetPathName();
	}
	else
	{
		strPathname = pszFile;
	}

	// read file to buffer
	if (FALSE == FileReadFileToBuffer(strPathname.GetBuffer(), &buffer) )
	{
		MessageBox(L"Read file error!");
		goto RET;
	}

	if (FALSE == FileCheckValidSignature(buffer))
	{
		MessageBox(L"File is corupted!");
		goto RET;
	}

	// change windows title
	this->SetWindowText(CString(L"NTQTaskMgr | ") + strPathname);

	// change config
	FileDataInitialize(buffer);
	ConfigSetViewStyle(FALSE);
	m_listCtlProcess.DeleteAllItems();
	PageUpdateProcess(&m_listCtlProcess);

	bRet = TRUE;
	
RET:
	return bRet;
}

void CNTQTaskMgrDlg::SwitchToRealTime(void)
{
	ConfigSetViewStyle(TRUE);	// switch to realtime
	m_listCtlProcess.DeleteAllItems();
	PageUpdateProcess(&m_listCtlProcess);
	SetWindowText(L"NTQTaskMgr");

	// clear old data
	FileDataUninitialize();
}

void CNTQTaskMgrDlg::Cleanup()
{
	ConfigSetRuning(FALSE);
	FileDataUninitialize();
	PerfDataUninitialize();
}




void CNTQTaskMgrDlg::OnDropFiles(HDROP hDropInfo)
{
	CDialog::OnDropFiles( hDropInfo );
	WCHAR szBuf[MAX_PATH];
	PVOID buffer = NULL;

	int nCntFiles= DragQueryFile( hDropInfo, -1, 0,0 );
	if (nCntFiles > 1)
	{
		MessageBox(L"Single document. Only open 1 file!", L"Caution", MB_ICONINFORMATION);
		return;
	}

	::DragQueryFile( hDropInfo, 0, szBuf, sizeof(szBuf));

	// read file to buffer
	if (FALSE == FileReadFileToBuffer(szBuf, &buffer))
	{
		MessageBox(L"Read file error!");
		return;
	}

	if (FALSE == FileCheckValidSignature(buffer))
	{
		MessageBox(L"File is corupted!");
		return;
	}

	// change windows title
	this->SetWindowText(CString(L"NTQTaskMgr | ") + CString(szBuf));

	// change config
	FileDataInitialize(buffer);
	ConfigSetViewStyle(FALSE);
	m_listCtlProcess.DeleteAllItems();
	PageUpdateProcess(&m_listCtlProcess);

}

void CNTQTaskMgrDlg::SetApp(CNTQTaskMgrApp * objApp)
{
	m_objApp = objApp;
}
