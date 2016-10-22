
#include "stdafx.h"
#include <windows.h>
#include "perfdata.h"
#include <Winternl.h>
#include "UndocumentStruct.h"
#include "FileDataStruct.h"

PVOID g_pFileData = NULL;
PNTF_HEADER g_pHeader = NULL;
PPERFDATA	g_pData = NULL;


BOOL FileDataInitialize(PVOID pbuffer)
{
	// validate input
	if (!pbuffer)
		return FALSE;

	FileDataUninitialize();

	g_pFileData = pbuffer;
	g_pHeader = (PNTF_HEADER) pbuffer;
	g_pData = (PPERFDATA) &g_pHeader->pData[0];

    return TRUE;
}

void FileDataUninitialize(void)
{
	if (g_pFileData)
	{
		HeapFree(GetProcessHeap(), 0, g_pFileData);
		g_pFileData = NULL;
	}
}


ULONG FileDataGetProcessIndex(ULONG pid)
{
    ULONG idx;

    for (idx = 0; idx < g_pHeader->ProcessCount; idx++)
    {
        if (PtrToUlong(g_pData[idx].ProcessId) == pid)
        {
            break;
        }
    }


    if (idx == g_pHeader->ProcessCount)
    {
        return -1;
    }
    return idx;
}

ULONG FileDataGetProcessCount(void)
{
    return g_pHeader->ProcessCount;
}

ULONG FileDataGetProcessorUsage(void)
{
	ULONG ulCpuUsage = 0;
	ulCpuUsage = (ULONG)(g_pHeader->dbIdleTime + 0.5);

	if (ulCpuUsage > 100)
		ulCpuUsage = 100;

    return ulCpuUsage;
}

ULONG FileDataGetProcessorSystemUsage(void)
{
    return (ULONG)g_pHeader->dbKernelTime;
}

BOOL FileDataGetImageName(ULONG Index, LPWSTR lpImageName, int nMaxCount)
{
    BOOL  bSuccessful;


    if (Index < g_pHeader->ProcessCount) {
        wcsncpy(lpImageName, g_pData[Index].ImageName, nMaxCount);
        bSuccessful = TRUE;
    } else {
        bSuccessful = FALSE;
    }
    return bSuccessful;
}

ULONG FileDataGetProcessId(ULONG Index)
{
    ULONG  ProcessId;

    if (Index < g_pHeader->ProcessCount)
        ProcessId = PtrToUlong(g_pData[Index].ProcessId);
    else
        ProcessId = 0;

    return ProcessId;
}

BOOL FileDataGetUserName(ULONG Index, LPWSTR lpUserName, int nMaxCount)
{
    BOOL  bSuccessful;

    if (Index < g_pHeader->ProcessCount) {
        wcsncpy(lpUserName, g_pData[Index].UserName, nMaxCount);
        bSuccessful = TRUE;
    } else {
        bSuccessful = FALSE;
    }

    return bSuccessful;
}

ULONG FileDataGetSessionId(ULONG Index)
{
    ULONG  SessionId;

    if (Index < g_pHeader->ProcessCount)
        SessionId = g_pData[Index].SessionId;
    else
        SessionId = 0;

    return SessionId;
}

ULONG FileDataGetCPUUsage(ULONG Index)
{
    ULONG  CpuUsage;

    if (Index < g_pHeader->ProcessCount)
        CpuUsage = g_pData[Index].CPUUsage;
    else
        CpuUsage = 0;

	if (CpuUsage > 100)
		CpuUsage = 100;

    return CpuUsage;
}

LARGE_INTEGER FileDataGetCPUTime(ULONG Index)
{
    LARGE_INTEGER  CpuTime = {{0,0}};


    if (Index < g_pHeader->ProcessCount)
        CpuTime = g_pData[Index].CPUTime;

    return CpuTime;
}

ULONG FileDataGetWorkingSetSizeBytes(ULONG Index)
{
    ULONG  WorkingSetSizeBytes;

    if (Index < g_pHeader->ProcessCount)
        WorkingSetSizeBytes = g_pData[Index].WorkingSetSizeBytes;
    else
        WorkingSetSizeBytes = 0;

    return WorkingSetSizeBytes;
}

ULONG FileDataGetPeakWorkingSetSizeBytes(ULONG Index)
{
    ULONG  PeakWorkingSetSizeBytes;


    if (Index < g_pHeader->ProcessCount)
        PeakWorkingSetSizeBytes = g_pData[Index].PeakWorkingSetSizeBytes;
    else
        PeakWorkingSetSizeBytes = 0;


    return PeakWorkingSetSizeBytes;
}

ULONG FileDataGetWorkingSetSizeDelta(ULONG Index)
{
    ULONG  WorkingSetSizeDelta;


    if (Index < g_pHeader->ProcessCount)
        WorkingSetSizeDelta = g_pData[Index].WorkingSetSizeDelta;
    else
        WorkingSetSizeDelta = 0;

    return WorkingSetSizeDelta;
}

ULONG FileDataGetPageFaultCount(ULONG Index)
{
    ULONG  PageFaultCount;


    if (Index < g_pHeader->ProcessCount)
        PageFaultCount = g_pData[Index].PageFaultCount;
    else
        PageFaultCount = 0;


    return PageFaultCount;
}

ULONG FileDataGetPageFaultCountDelta(ULONG Index)
{
    ULONG  PageFaultCountDelta;


    if (Index < g_pHeader->ProcessCount)
        PageFaultCountDelta = g_pData[Index].PageFaultCountDelta;
    else
        PageFaultCountDelta = 0;

    return PageFaultCountDelta;
}

ULONG FileDataGetVirtualMemorySizeBytes(ULONG Index)
{
    ULONG  VirtualMemorySizeBytes;

    if (Index < g_pHeader->ProcessCount)
        VirtualMemorySizeBytes = g_pData[Index].VirtualMemorySizeBytes;
    else
        VirtualMemorySizeBytes = 0;

    return VirtualMemorySizeBytes;
}

ULONG FileDataGetPagedPoolUsagePages(ULONG Index)
{
    ULONG  PagedPoolUsage;

    if (Index < g_pHeader->ProcessCount)
        PagedPoolUsage = g_pData[Index].PagedPoolUsagePages;
    else
        PagedPoolUsage = 0;

    return PagedPoolUsage;
}

ULONG FileDataGetNonPagedPoolUsagePages(ULONG Index)
{
    ULONG  NonPagedPoolUsage;

    if (Index < g_pHeader->ProcessCount)
        NonPagedPoolUsage = g_pData[Index].NonPagedPoolUsagePages;
    else
        NonPagedPoolUsage = 0;

    return NonPagedPoolUsage;
}

ULONG FileDataGetBasePriority(ULONG Index)
{
    ULONG  BasePriority;

    if (Index < g_pHeader->ProcessCount)
        BasePriority = g_pData[Index].BasePriority;
    else
        BasePriority = 0;

    return BasePriority;
}

ULONG FileDataGetHandleCount(ULONG Index)
{
    ULONG  HandleCount;

    if (Index < g_pHeader->ProcessCount)
        HandleCount = g_pData[Index].HandleCount;
    else
        HandleCount = 0;

    return HandleCount;
}

ULONG FileDataGetThreadCount(ULONG Index)
{
    ULONG  ThreadCount;

    if (Index < g_pHeader->ProcessCount)
        ThreadCount = g_pData[Index].ThreadCount;
    else
        ThreadCount = 0;

    return ThreadCount;
}

ULONG FileDataGetUSERObjectCount(ULONG Index)
{
    ULONG  USERObjectCount;

    if (Index < g_pHeader->ProcessCount)
        USERObjectCount = g_pData[Index].USERObjectCount;
    else
        USERObjectCount = 0;

    return USERObjectCount;
}

ULONG FileDataGetGDIObjectCount(ULONG Index)
{
    ULONG  GDIObjectCount;

    if (Index < g_pHeader->ProcessCount)
        GDIObjectCount = g_pData[Index].GDIObjectCount;
    else
        GDIObjectCount = 0;

    return GDIObjectCount;
}

BOOL FileDataGetIOCounters(ULONG Index, PIO_COUNTERS pIoCounters)
{
    BOOL  bSuccessful;

    if (Index < g_pHeader->ProcessCount)
    {
        memcpy(pIoCounters, &g_pData[Index].IOCounters, sizeof(IO_COUNTERS));
        bSuccessful = TRUE;
    }
    else
        bSuccessful = FALSE;

    return bSuccessful;
}

ULONG FileDataGetCommitChargeTotalK(void)
{
    ULONG  Total;
    ULONG  PageSize;

    Total = g_pHeader->SystemPerfInfo.CommittedPages;
    PageSize = g_pHeader->SystemBasicInfo.PageSize;

    Total = Total * (PageSize / 1024);

    return Total;
}

ULONG FileDataGetCommitChargeLimitK(void)
{
    ULONG  Limit;
    ULONG  PageSize;

    Limit = g_pHeader->SystemPerfInfo.CommitLimit;
    PageSize = g_pHeader->SystemBasicInfo.PageSize;

    Limit = Limit * (PageSize / 1024);

    return Limit;
}

ULONG FileDataGetCommitChargePeakK(void)
{
    ULONG  Peak;
    ULONG  PageSize;

    Peak = g_pHeader->SystemPerfInfo.PeakCommitment;
    PageSize = g_pHeader->SystemBasicInfo.PageSize;


    Peak = Peak * (PageSize / 1024);

    return Peak;
}

ULONG FileDataGetKernelMemoryTotalK(void)
{
    ULONG  Total;
    ULONG  Paged;
    ULONG  NonPaged;
    ULONG  PageSize;

    Paged = g_pHeader->SystemPerfInfo.PagedPoolPages;
    NonPaged = g_pHeader->SystemPerfInfo.NonPagedPoolPages;
    PageSize = g_pHeader->SystemBasicInfo.PageSize;


    Paged = Paged * (PageSize / 1024);
    NonPaged = NonPaged * (PageSize / 1024);

    Total = Paged + NonPaged;

    return Total;
}

ULONG FileDataGetKernelMemoryPagedK(void)
{
    ULONG  Paged;
    ULONG  PageSize;


    Paged = g_pHeader->SystemPerfInfo.PagedPoolPages;
    PageSize = g_pHeader->SystemBasicInfo.PageSize;


    Paged = Paged * (PageSize / 1024);

    return Paged;
}

ULONG FileDataGetKernelMemoryNonPagedK(void)
{
    ULONG  NonPaged;
    ULONG  PageSize;

    NonPaged = g_pHeader->SystemPerfInfo.NonPagedPoolPages;
    PageSize = g_pHeader->SystemBasicInfo.PageSize;

    NonPaged = NonPaged * (PageSize / 1024);

    return NonPaged;
}

ULONG FileDataGetPhysicalMemoryTotalK(void)
{
    ULONG  Total;
    ULONG  PageSize;

    Total = g_pHeader->SystemBasicInfo.NumberOfPhysicalPages;
    PageSize = g_pHeader->SystemBasicInfo.PageSize;


    Total = Total * (PageSize / 1024);

    return Total;
}

ULONG FileDataGetPhysicalMemoryAvailableK(void)
{
    ULONG  Available;
    ULONG  PageSize;

    Available = g_pHeader->SystemPerfInfo.AvailablePages;
    PageSize = g_pHeader->SystemBasicInfo.PageSize;

    Available = Available * (PageSize / 1024);

    return Available;
}

ULONG FileDataGetPhysicalMemorySystemCacheK(void)
{
    ULONG  SystemCache;
    ULONG  PageSize;

    PageSize = g_pHeader->SystemBasicInfo.PageSize;
    SystemCache = g_pHeader->SystemCacheInfo.CurrentSizeIncludingTransitionInPages * PageSize;


    return SystemCache / 1024;
}

ULONG FileDataGetSystemHandleCount(void)
{
    ULONG  HandleCount;

    HandleCount = g_pHeader->SystemHandleInfo.NumberOfHandles;

    return HandleCount;
}

ULONG FileDataGetTotalThreadCount(void)
{
    ULONG  ThreadCount = 0;
    ULONG  i;

    for (i=0; i<g_pHeader->ProcessCount; i++)
    {
        ThreadCount += g_pData[i].ThreadCount;
    }

    return ThreadCount;
}

BOOL FileDataGet(ULONG Index, PPERFDATA *lppData)
{
    BOOL  bSuccessful = FALSE;
    if (Index < g_pHeader->ProcessCount)
    {
        *lppData = g_pData + Index;
        bSuccessful = TRUE;
    }
    return bSuccessful;
}

ULONGLONG FileDataGetReadOperationsPerSecond(ULONG Index)
{
	ULONGLONG  ulRetValue;

	if (Index < g_pHeader->ProcessCount)
		ulRetValue = g_pData[Index].ReadOperationsPerSecond;
	else
		ulRetValue = 0;

	return ulRetValue;
}

ULONGLONG FileDataGetWriteOperationsPerSecond(ULONG Index)
{
	ULONGLONG  ulRetValue;

	if (Index < g_pHeader->ProcessCount)
		ulRetValue = g_pData[Index].WriteOperationsPerSecond;
	else
		ulRetValue = 0;

	return ulRetValue;
}

ULONGLONG FileDataGetOtherOperationsPerSecond(ULONG Index)
{
	ULONGLONG  ulRetValue;

	if (Index < g_pHeader->ProcessCount)
		ulRetValue = g_pData[Index].OtherOperationsPerSecond;
	else
		ulRetValue = 0;

	return ulRetValue;
}

ULONGLONG FileDataGetReadTransferPerSecond(ULONG Index)
{
	ULONGLONG  ulRetValue;


	if (Index < g_pHeader->ProcessCount)
		ulRetValue = g_pData[Index].ReadTransferPerSecond;
	else
		ulRetValue = 0;

	return ulRetValue;
}

ULONGLONG FileDataGetWriteTransferPerSecond(ULONG Index)
{
	ULONGLONG  ulRetValue;

	if (Index < g_pHeader->ProcessCount)
		ulRetValue = g_pData[Index].WriteTransferPerSecond;
	else
		ulRetValue = 0;

	return ulRetValue;
}

ULONGLONG FileDataGetOtherTransferPerSecond(ULONG Index)
{
	ULONGLONG  ulRetValue;

	if (Index < g_pHeader->ProcessCount)
		ulRetValue = g_pData[Index].OtherTransferPerSecond;
	else
		ulRetValue = 0;

	return ulRetValue;
}


BOOL FileTakeSnapshot(WCHAR * pszFilePath, PVOID buffer)
{
	HANDLE	hFile = INVALID_HANDLE_VALUE;
	BOOL	bRet = FALSE;
	DWORD	dwSize = 0, dwByteWritten = 0;

	// validate data input
	if (!pszFilePath || !buffer)
		return FALSE;

	if (!pszFilePath[0])
		return FALSE;

	hFile = CreateFile(pszFilePath, GENERIC_WRITE, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return FALSE;

	dwSize = sizeof(NTF_HEADER) + (((PNTF_HEADER)buffer)->ProcessCount) * sizeof(PERFDATA);

	if (!WriteFile(hFile, buffer, dwSize, &dwByteWritten, NULL))
		goto RET;

	if (dwByteWritten < dwSize)
		goto RET;

	bRet = TRUE;


RET:
	if (INVALID_HANDLE_VALUE != hFile)
		CloseHandle(hFile);

	return bRet;
}

BOOL FileReadFileToBuffer(WCHAR * pszFilePath, PVOID * buffer)
{
	HANDLE	hFile = INVALID_HANDLE_VALUE;
	BOOL	bRet = FALSE;
	DWORD	dwSizeHi = 0, dwSizeLow = 0, dwByteRead = 0;

	*buffer = NULL;

	// validate data input
	if (!pszFilePath || !buffer)
		return FALSE;

	if (!pszFilePath[0])
		return FALSE;

	hFile = CreateFile(pszFilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (INVALID_HANDLE_VALUE == hFile)
		return FALSE;

	// get file size
	dwSizeLow = GetFileSize(hFile, &dwSizeHi);
	assert(dwSizeHi == 0);	// file too large

	// allocate buffer size = file size to read data
	*buffer = HeapAlloc(GetProcessHeap(), 0, dwSizeLow);

	if (NULL == *buffer)
		goto RET;

	// read file to buffer
	if (!ReadFile(hFile, *buffer, dwSizeLow, &dwByteRead, NULL))
		goto RET;

	assert(dwByteRead == dwSizeLow);

	bRet = TRUE;

RET:
	if (INVALID_HANDLE_VALUE != hFile)
		CloseHandle(hFile);

	if (!bRet && *buffer)
		HeapFree(GetProcessHeap(), 0, *buffer);

	return bRet;
}

BOOL FileCheckValidSignature(PVOID pbuffer)
{
	// validate input
	if (!pbuffer)
		return FALSE;

	PNTF_HEADER pheader = (PNTF_HEADER) pbuffer;

	return (pheader->wSignature == NTF_SIGNATURE);
}

ULONG FileDataGetMemoryUsage(void)
{
	double douMemoryAvailable = 0;
	douMemoryAvailable = 100.0 * FileDataGetPhysicalMemoryAvailableK() / FileDataGetPhysicalMemoryTotalK();
	return (ULONG) (douMemoryAvailable + 0.5);
}
