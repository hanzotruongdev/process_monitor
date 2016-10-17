
// NTQTaskMgrDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

#define TIMER_UPDATE_LIST_PROCESS			1
#define TIMER_UPDATE_LIST_PROCESS_INTERVAL	1000

// CNTQTaskMgrDlg dialog
class CNTQTaskMgrDlg : public CDialogEx
{
// Construction
public:
	CNTQTaskMgrDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_NTQTASKMGR_DIALOG };

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
	void SetApp(CNTQTaskMgrApp * objApp);
	void Cleanup();
	void UpdateDataAndUI(void);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	CString m_csStatus;
	afx_msg void OnLvnGetdispinfoLstProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedLstProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnHdnItemclickLstProcess(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	void MenuHandler(UINT i);
	afx_msg void OnDropFiles(HDROP hDropInfo);

	int m_listCltVerticalDelta;
	int m_listCltHorizontalDelta;

	CEdit m_edtCltStatus;
	CButton m_btnOk;
	afx_msg void OnMenuSelect(UINT nItemID, UINT nFlags, HMENU hSysMenu);
	void ExportPerfToFile();
	BOOL OpenFile(WCHAR * pszFileName = NULL);
	void SwitchToRealTime(void);

	CNTQTaskMgrApp * m_objApp;
	CListCtrl m_listCtlProcess;
};
