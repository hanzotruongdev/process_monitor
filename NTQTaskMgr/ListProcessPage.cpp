
#include "stdafx.h"
#include <Winternl.h>
#include "perfdata.h"
#include "ListProcessPage.h"
#include "UndocumentStruct.h"
#include "FileDataStruct.h"

UINT    ColumnDataHints[COLUMN_NMAX];
PROCESS_PAGE_SETTING g_structPageSetting = {0};

int CALLBACK TaskMgrCompareProc(LPARAM lParam1, LPARAM lParam2, LPARAM lParamSort);

void InitListProcessPage(CListCtrl * objListCtlProcess)
{
	// Init defalt setting
	g_structPageSetting.bSortAscending = TRUE;
	g_structPageSetting.iSortColumn = 0;
	g_structPageSetting.bViewRealTime = TRUE;
	g_structPageSetting.bRuning = TRUE;

	// init array column info
	ColumnDataHints[0] = COLUMN_IMAGENAME;
	ColumnDataHints[1] = COLUMN_PID;
	ColumnDataHints[2] = COLUMN_CPUUSAGE;
	ColumnDataHints[3] = COLUMN_MEMORY;
	ColumnDataHints[4] = COLUMN_READ_OPERATION;
	ColumnDataHints[5] = COLUMN_WRITE_OPERATION;
	ColumnDataHints[6] = COLUMN_OTHER_OPERATION;
	ColumnDataHints[7] = COLUMN_READ_TRANSFER;
	ColumnDataHints[8] = COLUMN_WRITE_TRANSFER;
	ColumnDataHints[9] = COLUMN_OTHER_TRANSFER;

	objListCtlProcess->InsertColumn(0, L"Process name", LVCFMT_LEFT, 200);
	objListCtlProcess->InsertColumn(1, L"PID", LVCFMT_LEFT, 100);
	objListCtlProcess->InsertColumn(2, L"CPU", LVCFMT_LEFT, 100);
	objListCtlProcess->InsertColumn(3, L"Memory", LVCFMT_LEFT, 100);

	objListCtlProcess->InsertColumn(4, L"ReadOperationsPerSecond", LVCFMT_LEFT, 100);
	objListCtlProcess->InsertColumn(5, L"WriteOperationsPerSecond", LVCFMT_LEFT, 100);
	objListCtlProcess->InsertColumn(6, L"OtherOperationsPerSecond", LVCFMT_LEFT, 100);
	objListCtlProcess->InsertColumn(7, L"ReadTransferPerSecond", LVCFMT_LEFT, 100);
	objListCtlProcess->InsertColumn(8, L"WriteTransferPerSecond", LVCFMT_LEFT, 100);
	objListCtlProcess->InsertColumn(9, L"OtherTransferPerSecond", LVCFMT_LEFT, 100);

	objListCtlProcess->SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
}

void ConfigSetSortColumn(int iColumn)
{
	if (iColumn != g_structPageSetting.iSortColumn)
		g_structPageSetting.iSortColumn = iColumn;
	else
		ConfigToggleSort();
}

void ConfigToggleSort()
{
	g_structPageSetting.bSortAscending = !g_structPageSetting.bSortAscending;
}

void ConfigSetViewStyle(BOOL bViewRealtime)
{
	g_structPageSetting.bViewRealTime = bViewRealtime;
}

BOOL ConfigGetViewStyle()
{
	return g_structPageSetting.bViewRealTime;
}

void ConfigSetRuning(BOOL bRuning)
{
	g_structPageSetting.bRuning = bRuning;
}

BOOL ConfigIsRuning()
{
	return g_structPageSetting.bRuning;
}

BOOL PageDataGetText(ULONG Index, ULONG ColumnIndex, LPTSTR lpText, int nMaxCount)
{
	IO_COUNTERS    iocounters;
	LARGE_INTEGER  time;

	if (ColumnDataHints[ColumnIndex] == COLUMN_IMAGENAME)
		if (g_structPageSetting.bViewRealTime)
			PerfDataGetImageName(Index, lpText, nMaxCount);
		else
			FileDataGetImageName(Index, lpText, nMaxCount);

	if (ColumnDataHints[ColumnIndex] == COLUMN_PID)
		if (g_structPageSetting.bViewRealTime)
			wsprintfW(lpText, L"%lu", PerfDataGetProcessId(Index));
		else
			wsprintfW(lpText, L"%lu", FileDataGetProcessId(Index));
		

	if (ColumnDataHints[ColumnIndex] == COLUMN_CPUUSAGE)
		if (g_structPageSetting.bViewRealTime)
			wsprintfW(lpText, L"%02lu %%", PerfDataGetCPUUsage(Index));
		else
			wsprintfW(lpText, L"%02lu %%", FileDataGetCPUUsage(Index));
		

	if (ColumnDataHints[ColumnIndex] == COLUMN_MEMORY)
		if (g_structPageSetting.bViewRealTime)
			wsprintfW(lpText, L"%lu Kb", PerfDataGetWorkingSetSizeBytes(Index)/1024);
		else
			wsprintfW(lpText, L"%lu Kb", FileDataGetWorkingSetSizeBytes(Index)/1024);
		

	if (ColumnDataHints[ColumnIndex] == COLUMN_READ_OPERATION)
		if (g_structPageSetting.bViewRealTime)
			wsprintfW(lpText, L"%I64u Op/s", PerfDataGetReadOperationsPerSecond(Index));
		else
			wsprintfW(lpText, L"%I64u Op/s", FileDataGetReadOperationsPerSecond(Index));
		

	if (ColumnDataHints[ColumnIndex] == COLUMN_WRITE_OPERATION)
		if (g_structPageSetting.bViewRealTime)
			wsprintfW(lpText, L"%I64u Op/s", PerfDataGetWriteOperationsPerSecond(Index));
		else
			wsprintfW(lpText, L"%I64u Op/s", FileDataGetWriteOperationsPerSecond(Index));
		

	if (ColumnDataHints[ColumnIndex] == COLUMN_OTHER_OPERATION)
		if (g_structPageSetting.bViewRealTime)
			wsprintfW(lpText, L"%I64u Op/s", PerfDataGetOtherOperationsPerSecond(Index));
		else
			wsprintfW(lpText, L"%I64u Op/s", FileDataGetOtherOperationsPerSecond(Index));
		

	if (ColumnDataHints[ColumnIndex] == COLUMN_READ_TRANSFER)
		if (g_structPageSetting.bViewRealTime)
			wsprintfW(lpText, L"%I64u Bytes/s", PerfDataGetReadTransferPerSecond(Index));
		else
			wsprintfW(lpText, L"%I64u Bytes/s", FileDataGetReadTransferPerSecond(Index));
		

	if (ColumnDataHints[ColumnIndex] == COLUMN_WRITE_TRANSFER)
		if (g_structPageSetting.bViewRealTime)
			wsprintfW(lpText, L"%I64u Bytes/s", PerfDataGetWriteTransferPerSecond(Index));
		else
			wsprintfW(lpText, L"%I64u Bytes/s", FileDataGetWriteTransferPerSecond(Index));
		

	if (ColumnDataHints[ColumnIndex] == COLUMN_OTHER_TRANSFER)
		if (g_structPageSetting.bViewRealTime)
			wsprintfW(lpText, L"%I64u Bytes/s", PerfDataGetOtherTransferPerSecond(Index));
		else
			wsprintfW(lpText, L"%I64u Bytes/s", FileDataGetOtherTransferPerSecond(Index));
		
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


void PageUpdateProcess(CListCtrl * objListCtlProcess)
{
	int i;
	ULONG l;
	LV_ITEM item;
	LPPROCESS_PAGE_LIST_ITEM pData;

	objListCtlProcess->SendMessage( WM_SETREDRAW, FALSE, 0);

	/* Remove processes was dead*/
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

	ULONG ulProcessCount = ConfigGetViewStyle()? PerfDataGetProcessCount() : FileDataGetProcessCount();

	/* Check for difference in listview process and performance process counts */
	if (objListCtlProcess->GetItemCount() != ulProcessCount)
	{
		/* Add new processes by checking against the current items */
		for (l = 0; l < ulProcessCount; l++)
		{
			PageAddListItem(l, objListCtlProcess);
		}
	}

	// Update all item in list control
	//
	for (ULONG ulIdx = 0; ulIdx < objListCtlProcess->GetItemCount(); ulIdx++)
	{
		objListCtlProcess->Update(ulIdx);
	}

	objListCtlProcess->SortItems(TaskMgrCompareProc, NULL);

	objListCtlProcess->SendMessage(WM_SETREDRAW, TRUE, 0);
}



void PageAddListItem(ULONG Index, CListCtrl * objListCtlProcess)
{
	LPPROCESS_PAGE_LIST_ITEM	pData;
	int							i;
	LV_ITEM						item;
	BOOL						bAlreadyInList = FALSE;
	ULONG						pid;

	if (g_structPageSetting.bViewRealTime)
		pid = PerfDataGetProcessId(Index);
	else
		pid = FileDataGetProcessId(Index);

	if (pid == 0)
	{
		int i = 0;
		i++;
	}

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

// Sort items by associated lParam
int CALLBACK TaskMgrCompareProc(LPARAM lParam1, LPARAM lParam2, 
										 LPARAM lParamSort)
{
	UNREFERENCED_PARAMETER(lParamSort);
	BOOL bRet = TRUE;

	if (!lParam1 || !lParam2)
		return TRUE;
	LPPROCESS_PAGE_LIST_ITEM item1 = (LPPROCESS_PAGE_LIST_ITEM) lParam1;
	LPPROCESS_PAGE_LIST_ITEM item2 = (LPPROCESS_PAGE_LIST_ITEM) lParam2;

	PPERFDATA  pdata1 = NULL;
	PPERFDATA  pdata2 = NULL;
	
	if (g_structPageSetting.bViewRealTime)
	{
		if (!PerfDataGet(PerfDataGetProcessIndex(item1->ProcessId), &pdata1))
			return bRet;
	}
	else
	{
		if (!FileDataGet(FileDataGetProcessIndex(item1->ProcessId), &pdata1))
			return bRet;
	}

	if (g_structPageSetting.bViewRealTime)
	{
		if (!PerfDataGet(PerfDataGetProcessIndex(item2->ProcessId), &pdata2))
			return bRet;
	}
	else
	{
		if (!FileDataGet(FileDataGetProcessIndex(item2->ProcessId), &pdata2))
			return bRet;
	}

	

	switch (ColumnDataHints[g_structPageSetting.iSortColumn])
	{
	case COLUMN_IMAGENAME:
		{
			bRet = wcscmp(pdata1->ImageName, pdata2->ImageName) > 0;
		}
		break;

	case COLUMN_PID:
		{
			bRet = item1->ProcessId > item2->ProcessId;
		}
		break;

	case COLUMN_CPUUSAGE:
		{
			bRet = pdata1->CPUUsage > pdata2->CPUUsage;
		}
		break;

	case COLUMN_MEMORY:
		{
			bRet = pdata1->WorkingSetSizeBytes > pdata2->WorkingSetSizeBytes;
		}
		break;

	case COLUMN_READ_OPERATION:
		{
			bRet = pdata1->ReadOperationsPerSecond > pdata2->ReadOperationsPerSecond;
		}
		break;

	case COLUMN_WRITE_OPERATION:
		{
			bRet = pdata1->WriteOperationsPerSecond > pdata2->WriteOperationsPerSecond;
		}
		break;

	case COLUMN_OTHER_OPERATION:
		{
			bRet = pdata1->OtherOperationsPerSecond > pdata2->OtherOperationsPerSecond;
		}
		break;

	case COLUMN_READ_TRANSFER:
		{
			bRet = pdata1->ReadTransferPerSecond > pdata2->ReadTransferPerSecond;
		}
		break;

	case COLUMN_WRITE_TRANSFER:
		{
			bRet = pdata1->WriteTransferPerSecond > pdata2->WriteTransferPerSecond;
		}
		break;

	case COLUMN_OTHER_TRANSFER:
		{
			bRet = pdata1->OtherTransferPerSecond > pdata2->OtherTransferPerSecond;
		}
		break;

	default:
		{
			bRet = TRUE;
		}
		break;
	}
	
	return g_structPageSetting.bSortAscending? bRet:!bRet;
}