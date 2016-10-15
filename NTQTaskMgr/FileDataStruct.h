

typedef struct _NTF_HEADER
{
	WORD											wSignature;		// signature of noitq taskmanager file 'NTF'
	ULONG											ProcessCount;	// count of process
	double											dbIdleTime;		// invert of %IdleTime = %cpu time
	double											dbKernelTime;
	double											dbSystemTime;
	LARGE_INTEGER									liOldIdleTime;
	double											OldKernelTime;
	SYSTEM_PERFORMANCE_INFORMATION_UNDOC			SystemPerfInfo;
	SYSTEM_BASIC_INFORMATION_UNDOC					SystemBasicInfo;
	SYSTEM_FILECACHE_INFORMATION					SystemCacheInfo;
	SYSTEM_HANDLE_INFORMATION						SystemHandleInfo;
	PSID											SystemUserSid;
	DWORD											pData[1];
} NTF_HEADER, *PNTF_HEADER;

BOOL	FileDataInitialize(PVOID pbuffer);
void	FileDataUninitialize(void);


BOOL    FileDataGet(ULONG Index, PPERFDATA *lppData);
ULONG   FileDataGetProcessIndex(ULONG pid);
ULONG	FileDataGetProcessCount(void);
ULONG	FileDataGetProcessorUsage(void);
ULONG	FileDataGetProcessorSystemUsage(void);

BOOL	FileDataGetImageName(ULONG Index, LPTSTR lpImageName, int nMaxCount);
ULONG	FileDataGetProcessId(ULONG Index);
BOOL	FileDataGetUserName(ULONG Index, LPTSTR lpUserName, int nMaxCount);
ULONG	FileDataGetSessionId(ULONG Index);
ULONG	FileDataGetCPUUsage(ULONG Index);
LARGE_INTEGER	FileDataGetCPUTime(ULONG Index);
ULONG	FileDataGetWorkingSetSizeBytes(ULONG Index);
ULONG	FileDataGetPeakWorkingSetSizeBytes(ULONG Index);
ULONG	FileDataGetWorkingSetSizeDelta(ULONG Index);
ULONG	FileDataGetPageFaultCount(ULONG Index);
ULONG	FileDataGetPageFaultCountDelta(ULONG Index);
ULONG	FileDataGetVirtualMemorySizeBytes(ULONG Index);
ULONG	FileDataGetPagedPoolUsagePages(ULONG Index);
ULONG	FileDataGetNonPagedPoolUsagePages(ULONG Index);
ULONG	FileDataGetBasePriority(ULONG Index);
ULONG	FileDataGetHandleCount(ULONG Index);
ULONG	FileDataGetThreadCount(ULONG Index);
ULONG	FileDataGetUSERObjectCount(ULONG Index);
ULONG	FileDataGetGDIObjectCount(ULONG Index);
BOOL	FileDataGetIOCounters(ULONG Index, PIO_COUNTERS pIoCounters);

ULONG	FileDataGetCommitChargeTotalK(void);
ULONG	FileDataGetCommitChargeLimitK(void);
ULONG	FileDataGetCommitChargePeakK(void);

ULONG	FileDataGetKernelMemoryTotalK(void);
ULONG	FileDataGetKernelMemoryPagedK(void);
ULONG	FileDataGetKernelMemoryNonPagedK(void);

ULONG	FileDataGetPhysicalMemoryTotalK(void);
ULONG	FileDataGetPhysicalMemoryAvailableK(void);
ULONG	FileDataGetPhysicalMemorySystemCacheK(void);

ULONG	FileDataGetSystemHandleCount(void);

ULONG	FileDataGetTotalThreadCount(void);

ULONGLONG FileDataGetReadOperationsPerSecond(ULONG Index);
ULONGLONG FileDataGetWriteOperationsPerSecond(ULONG Index);
ULONGLONG FileDataGetOtherOperationsPerSecond(ULONG Index);
ULONGLONG FileDataGetReadTransferPerSecond(ULONG Index);
ULONGLONG FileDataGetWriteTransferPerSecond(ULONG Index);
ULONGLONG FileDataGetOtherTransferPerSecond(ULONG Index);

BOOL FileTakeSnapshot(WCHAR * pszFilePath, PVOID buffer);
BOOL FileReadFileToBuffer(WCHAR * pszFilePath, PVOID * buffer);