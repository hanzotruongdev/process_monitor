
#include "stdafx.h"
#include "perfdata.h"
#include "ListProcessPage.h"

UINT    ColumnDataHints[COLUMN_NMAX];



void InitListProcessPage(CListCtrl * objListCtlProcess)
{
	ColumnDataHints[0] = COLUMN_IMAGENAME;
	ColumnDataHints[1] = COLUMN_PID;
	ColumnDataHints[2] = COLUMN_CPUUSAGE;
	ColumnDataHints[3] = COLUMN_MEMORY;

	objListCtlProcess->InsertColumn(0, L"Process name", LVCFMT_LEFT, 200);
	objListCtlProcess->InsertColumn(1, L"PID", LVCFMT_LEFT, 150);
	objListCtlProcess->InsertColumn(2, L"CPU", LVCFMT_LEFT, 150);
	objListCtlProcess->InsertColumn(3, L"Memory", LVCFMT_LEFT, 150);

	objListCtlProcess->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
}

BOOL PerfDataGetText(ULONG Index, ULONG ColumnIndex, LPTSTR lpText, int nMaxCount)
{
	IO_COUNTERS    iocounters;
	LARGE_INTEGER  time;

	if (ColumnDataHints[ColumnIndex] == COLUMN_IMAGENAME)
		PerfDataGetImageName(Index, lpText, nMaxCount);

	if (ColumnDataHints[ColumnIndex] == COLUMN_PID)
		wsprintfW(lpText, L"%lu", PerfDataGetProcessId(Index));

	if (ColumnDataHints[ColumnIndex] == COLUMN_CPUUSAGE)
		wsprintfW(lpText, L"%02lu %%", PerfDataGetCPUUsage(Index));

	if (ColumnDataHints[ColumnIndex] == COLUMN_MEMORY)
		wsprintfW(lpText, L"%lu Kb", PerfDataGetWorkingSetSizeBytes(Index)/1024);

	return FALSE;
}

BOOL ProcessRunning(ULONG ProcessId) 
{
	HANDLE hProcess;
	DWORD exitCode;

	if (ProcessId == 0) {
		return TRUE;
	}

	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
	if (hProcess == NULL) {
		return FALSE;
	}

	if (GetExitCodeProcess(hProcess, &exitCode)) {
		CloseHandle(hProcess);
		return (exitCode == STILL_ACTIVE);
	}

	CloseHandle(hProcess);
	return FALSE;
}


void UpdateProcess(CListCtrl * objListCtlProcess)
{
	int i;
	ULONG l;
	LV_ITEM item;
	LPPROCESS_PAGE_LIST_ITEM pData;

	objListCtlProcess->SendMessage( WM_SETREDRAW, FALSE, 0);

	/* Remove old processes */
	for (i = 0; i < objListCtlProcess->GetItemCount(); i++)
	{
		memset(&item, 0, sizeof (LV_ITEM));
		item.mask = LVIF_PARAM;
		item.iItem = i;
		(void)objListCtlProcess->GetItem(&item);
		pData = (LPPROCESS_PAGE_LIST_ITEM)item.lParam;
		if (!ProcessRunning(pData->ProcessId))
		{
			(void)objListCtlProcess->DeleteItem(i);
			HeapFree(GetProcessHeap(), 0, pData);
		}
	}

	/* Check for difference in listview process and performance process counts */
	if (objListCtlProcess->GetItemCount() != PerfDataGetProcessCount())
	{
		/* Add new processes by checking against the current items */
		for (l = 0; l < PerfDataGetProcessCount(); l++)
		{
			AddListItem(l, objListCtlProcess);
		}
	}

	// 	if (TaskManagerSettings.SortColumn != -1)
	// 	{
	// 		(void)ListView_SortItems(hProcessPageListCtrl, ProcessPageCompareFunc, NULL);
	// 	}

	objListCtlProcess->SendMessage(WM_SETREDRAW, TRUE, 0);

	// Update all item in list control
	//
	for (ULONG ulIdx = 0; ulIdx < objListCtlProcess->GetItemCount(); ulIdx++)
	{
		objListCtlProcess->Update(ulIdx);
	}
}



void AddListItem(ULONG Index, CListCtrl * objListCtlProcess)
{
	LPPROCESS_PAGE_LIST_ITEM	pData;
	int							i;
	LV_ITEM						item;
	BOOL						bAlreadyInList = FALSE;
	ULONG						pid;

	pid = PerfDataGetProcessId(Index);

	/* Check to see if it's already in our list */
	for (i=0; i<objListCtlProcess->GetItemCount(); i++)
	{
		memset(&item, 0, sizeof(LV_ITEM));
		item.mask = LVIF_PARAM;
		item.iItem = i;
		(void)objListCtlProcess->GetItem( &item);
		pData = (LPPROCESS_PAGE_LIST_ITEM)item.lParam;
		if (pData->ProcessId == pid)
		{
			bAlreadyInList = TRUE;
			break;
		}
	}

	if (!bAlreadyInList)  /* Add */
	{
		pData = (LPPROCESS_PAGE_LIST_ITEM)HeapAlloc(GetProcessHeap(), 0, sizeof(PROCESS_PAGE_LIST_ITEM));
		pData->ProcessId = pid;

		/* Add the item to the list */
		memset(&item, 0, sizeof(LV_ITEM));
		item.mask = LVIF_TEXT|LVIF_PARAM;
		item.pszText = LPSTR_TEXTCALLBACK;
		item.iItem = objListCtlProcess->GetItemCount();
		item.lParam = (LPARAM)pData;
		(void)objListCtlProcess->InsertItem(&item);
	}
}
