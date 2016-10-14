
#ifndef STATUS_INFO_LENGTH_MISMATCH
#define STATUS_INFO_LENGTH_MISMATCH	((NTSTATUS)0xC0000004L)
#endif

// 
// typedef enum _SYSTEM_INFORMATION_CLASS
// {
// 	SystemBasicInformation=0x0000,
// 	SystemProcessorInformation=0x0001,
// 	SystemPerformanceInformation=0x0002,
// 	SystemTimeOfDayInformation=0x0003,
// 	SystemPathInformation=0x0004,
// 	SystemProcessInformation=0x0005,
// 	SystemCallCountInformation=0x0006,
// 	SystemDeviceInformation=0x0007,
// 	SystemProcessorPerformanceInformation=0x0008,
// 	SystemFlagsInformation=0x0009,
// 	SystemCallTimeInformation=0x000A,
// 	SystemModuleInformation=0x000B,
// 	SystemLocksInformation=0x000C,
// 	SystemStackTraceInformation=0x000D,
// 	SystemPagedPoolInformation=0x000E,
// 	SystemNonPagedPoolInformation=0x000F,
// 	SystemHandleInformation=0x0010,
// 	SystemObjectInformation=0x0011,
// 	SystemPageFileInformation=0x0012,
// 	SystemVdmInstemulInformation=0x0013,
// 	SystemVdmBopInformation=0x0014,
// 	SystemFileCacheInformation=0x0015,
// 	SystemPoolTagInformation=0x0016,
// 	SystemInterruptInformation=0x0017,
// 	SystemDpcBehaviorInformation=0x0018,
// 	SystemFullMemoryInformation=0x0019,
// 	SystemLoadGdiDriverInformation=0x001A,
// 	SystemUnloadGdiDriverInformation=0x001B,
// 	SystemTimeAdjustmentInformation=0x001C,
// 	SystemSummaryMemoryInformation=0x001D,
// 	SystemMirrorMemoryInformation=0x001E,
// 	SystemPerformanceTraceInformation=0x001F,
// 	SystemCrashDumpInformation=0x0020,
// 	SystemExceptionInformation=0x0021,
// 	SystemCrashDumpStateInformation=0x0022,
// 	SystemKernelDebuggerInformation=0x0023,
// 	SystemContextSwitchInformation=0x0024,
// 	SystemRegistryQuotaInformation=0x0025,
// 	SystemExtendServiceTableInformation=0x0026,
// 	SystemPrioritySeperation=0x0027,
// 	SystemVerifierAddDriverInformation=0x0028,
// 	SystemVerifierRemoveDriverInformation=0x0029,
// 	SystemProcessorIdleInformation=0x002A,
// 	SystemLegacyDriverInformation=0x002B,
// 	SystemCurrentTimeZoneInformation=0x002C,
// 	SystemLookasideInformation=0x002D,
// 	SystemTimeSlipNotification=0x002E,
// 	SystemSessionCreate=0x002F,
// 	SystemSessionDetach=0x0030,
// 	SystemSessionInformation=0x0031,
// 	SystemRangeStartInformation=0x0032,
// 	SystemVerifierInformation=0x0033,
// 	SystemVerifierThunkExtend=0x0034,
// 	SystemSessionProcessInformation=0x0035,
// 	SystemLoadGdiDriverInSystemSpace=0x0036,
// 	SystemNumaProcessorMap=0x0037,
// 	SystemPrefetcherInformation=0x0038,
// 	SystemExtendedProcessInformation=0x0039,
// 	SystemRecommendedSharedDataAlignment=0x003A,
// 	SystemComPlusPackage=0x003B,
// 	SystemNumaAvailableMemory=0x003C,
// 	SystemProcessorPowerInformation=0x003D,
// 	SystemEmulationBasicInformation=0x003E,
// 	SystemEmulationProcessorInformation=0x003F,
// 	SystemExtendedHandleInformation=0x0040,
// 	SystemLostDelayedWriteInformation=0x0041,
// 	SystemBigPoolInformation=0x0042,
// 	SystemSessionPoolTagInformation=0x0043,
// 	SystemSessionMappedViewInformation=0x0044,
// 	SystemHotpatchInformation=0x0045,
// 	SystemObjectSecurityMode=0x0046,
// 	SystemWatchdogTimerHandler=0x0047,
// 	SystemWatchdogTimerInformation=0x0048,
// 	SystemLogicalProcessorInformation=0x0049,
// 	SystemWow64SharedInformationObsolete=0x004A,
// 	SystemRegisterFirmwareTableInformationHandler=0x004B,
// 	SystemFirmwareTableInformation=0x004C,
// 	SystemModuleInformationEx=0x004D,
// 	SystemVerifierTriageInformation=0x004E,
// 	SystemSuperfetchInformation=0x004F,
// 	SystemMemoryListInformation=0x0050,
// 	SystemFileCacheInformationEx=0x0051,
// 	SystemThreadPriorityClientIdInformation=0x0052,
// 	SystemProcessorIdleCycleTimeInformation=0x0053,
// 	SystemVerifierCancellationInformation=0x0054,
// 	SystemProcessorPowerInformationEx=0x0055,
// 	SystemRefTraceInformation=0x0056,
// 	SystemSpecialPoolInformation=0x0057,
// 	SystemProcessIdInformation=0x0058,
// 	SystemErrorPortInformation=0x0059,
// 	SystemBootEnvironmentInformation=0x005A,
// 	SystemHypervisorInformation=0x005B,
// 	SystemVerifierInformationEx=0x005C,
// 	SystemTimeZoneInformation=0x005D,
// 	SystemImageFileExecutionOptionsInformation=0x005E,
// 	SystemCoverageInformation=0x005F,
// 	SystemPrefetchPatchInformation=0x0060,
// 	SystemVerifierFaultsInformation=0x0061,
// 	SystemSystemPartitionInformation=0x0062,
// 	SystemSystemDiskInformation=0x0063,
// 	SystemProcessorPerformanceDistribution=0x0064,
// 	SystemNumaProximityNodeInformation=0x0065,
// 	SystemDynamicTimeZoneInformation=0x0066,
// 	SystemCodeIntegrityInformation=0x0067,
// 	SystemProcessorMicrocodeUpdateInformation=0x0068,
// 	SystemProcessorBrandString=0x0069,
// 	SystemVirtualAddressInformation=0x006A,
// 	SystemLogicalProcessorAndGroupInformation=0x006B,
// 	SystemProcessorCycleTimeInformation=0x006C,
// 	SystemStoreInformation=0x006D,
// 	SystemRegistryAppendString=0x006E,
// 	SystemAitSamplingValue=0x006F,
// 	SystemVhdBootInformation=0x0070,
// 	SystemCpuQuotaInformation=0x0071,
// 	SystemNativeBasicInformation=0x0072,
// 	SystemErrorPortTimeouts=0x0073,
// 	SystemLowPriorityIoInformation=0x0074,
// 	SystemBootEntropyInformation=0x0075,
// 	SystemVerifierCountersInformation=0x0076,
// 	SystemPagedPoolInformationEx=0x0077,
// 	SystemSystemPtesInformationEx=0x0078,
// 	SystemNodeDistanceInformation=0x0079,
// 	SystemAcpiAuditInformation=0x007A,
// 	SystemBasicPerformanceInformation=0x007B,
// 	SystemQueryPerformanceCounterInformation=0x007C,
// 	SystemSessionBigPoolInformation=0x007D,
// 	SystemBootGraphicsInformation=0x007E,
// 	SystemScrubPhysicalMemoryInformation=0x007F,
// 	SystemBadPageInformation=0x0080,
// 	SystemProcessorProfileControlArea=0x0081,
// 	SystemCombinePhysicalMemoryInformation=0x0082,
// 	SystemEntropyInterruptTimingInformation=0x0083,
// 	SystemConsoleInformation=0x0084,
// 	SystemPlatformBinaryInformation=0x0085,
// 	SystemThrottleNotificationInformation=0x0086,
// 	SystemHypervisorProcessorCountInformation=0x0087,
// 	SystemDeviceDataInformation=0x0088,
// 	SystemDeviceDataEnumerationInformation=0x0089,
// 	SystemMemoryTopologyInformation=0x008A,
// 	SystemMemoryChannelInformation=0x008B,
// 	SystemBootLogoInformation=0x008C,
// 	SystemProcessorPerformanceInformationEx=0x008D,
// 	SystemSpare0=0x008E,
// 	SystemSecureBootPolicyInformation=0x008F,
// 	SystemPageFileInformationEx=0x0090,
// 	SystemSecureBootInformation=0x0091,
// 	SystemEntropyInterruptTimingRawInformation=0x0092,
// 	SystemPortableWorkspaceEfiLauncherInformation=0x0093,
// 	SystemFullProcessInformation=0x0094,
// 	MaxSystemInfoClass=0x0095
// } SYSTEM_INFORMATION_CLASS_UNDOC;


typedef struct _SYSTEM_PERFORMANCE_INFORMATION_UNDOC // Size=344
{
	LARGE_INTEGER IdleProcessTime; // Size=8 Offset=0
	LARGE_INTEGER IoReadTransferCount; // Size=8 Offset=8
	LARGE_INTEGER IoWriteTransferCount; // Size=8 Offset=16
	LARGE_INTEGER IoOtherTransferCount; // Size=8 Offset=24
	ULONG IoReadOperationCount; // Size=4 Offset=32
	ULONG IoWriteOperationCount; // Size=4 Offset=36
	ULONG IoOtherOperationCount; // Size=4 Offset=40
	ULONG AvailablePages; // Size=4 Offset=44
	ULONG CommittedPages; // Size=4 Offset=48
	ULONG CommitLimit; // Size=4 Offset=52
	ULONG PeakCommitment; // Size=4 Offset=56
	ULONG PageFaultCount; // Size=4 Offset=60
	ULONG CopyOnWriteCount; // Size=4 Offset=64
	ULONG TransitionCount; // Size=4 Offset=68
	ULONG CacheTransitionCount; // Size=4 Offset=72
	ULONG DemandZeroCount; // Size=4 Offset=76
	ULONG PageReadCount; // Size=4 Offset=80
	ULONG PageReadIoCount; // Size=4 Offset=84
	ULONG CacheReadCount; // Size=4 Offset=88
	ULONG CacheIoCount; // Size=4 Offset=92
	ULONG DirtyPagesWriteCount; // Size=4 Offset=96
	ULONG DirtyWriteIoCount; // Size=4 Offset=100
	ULONG MappedPagesWriteCount; // Size=4 Offset=104
	ULONG MappedWriteIoCount; // Size=4 Offset=108
	ULONG PagedPoolPages; // Size=4 Offset=112
	ULONG NonPagedPoolPages; // Size=4 Offset=116
	ULONG PagedPoolAllocs; // Size=4 Offset=120
	ULONG PagedPoolFrees; // Size=4 Offset=124
	ULONG NonPagedPoolAllocs; // Size=4 Offset=128
	ULONG NonPagedPoolFrees; // Size=4 Offset=132
	ULONG FreeSystemPtes; // Size=4 Offset=136
	ULONG ResidentSystemCodePage; // Size=4 Offset=140
	ULONG TotalSystemDriverPages; // Size=4 Offset=144
	ULONG TotalSystemCodePages; // Size=4 Offset=148
	ULONG NonPagedPoolLookasideHits; // Size=4 Offset=152
	ULONG PagedPoolLookasideHits; // Size=4 Offset=156
	ULONG AvailablePagedPoolPages; // Size=4 Offset=160
	ULONG ResidentSystemCachePage; // Size=4 Offset=164
	ULONG ResidentPagedPoolPage; // Size=4 Offset=168
	ULONG ResidentSystemDriverPage; // Size=4 Offset=172
	ULONG CcFastReadNoWait; // Size=4 Offset=176
	ULONG CcFastReadWait; // Size=4 Offset=180
	ULONG CcFastReadResourceMiss; // Size=4 Offset=184
	ULONG CcFastReadNotPossible; // Size=4 Offset=188
	ULONG CcFastMdlReadNoWait; // Size=4 Offset=192
	ULONG CcFastMdlReadWait; // Size=4 Offset=196
	ULONG CcFastMdlReadResourceMiss; // Size=4 Offset=200
	ULONG CcFastMdlReadNotPossible; // Size=4 Offset=204
	ULONG CcMapDataNoWait; // Size=4 Offset=208
	ULONG CcMapDataWait; // Size=4 Offset=212
	ULONG CcMapDataNoWaitMiss; // Size=4 Offset=216
	ULONG CcMapDataWaitMiss; // Size=4 Offset=220
	ULONG CcPinMappedDataCount; // Size=4 Offset=224
	ULONG CcPinReadNoWait; // Size=4 Offset=228
	ULONG CcPinReadWait; // Size=4 Offset=232
	ULONG CcPinReadNoWaitMiss; // Size=4 Offset=236
	ULONG CcPinReadWaitMiss; // Size=4 Offset=240
	ULONG CcCopyReadNoWait; // Size=4 Offset=244
	ULONG CcCopyReadWait; // Size=4 Offset=248
	ULONG CcCopyReadNoWaitMiss; // Size=4 Offset=252
	ULONG CcCopyReadWaitMiss; // Size=4 Offset=256
	ULONG CcMdlReadNoWait; // Size=4 Offset=260
	ULONG CcMdlReadWait; // Size=4 Offset=264
	ULONG CcMdlReadNoWaitMiss; // Size=4 Offset=268
	ULONG CcMdlReadWaitMiss; // Size=4 Offset=272
	ULONG CcReadAheadIos; // Size=4 Offset=276
	ULONG CcLazyWriteIos; // Size=4 Offset=280
	ULONG CcLazyWritePages; // Size=4 Offset=284
	ULONG CcDataFlushes; // Size=4 Offset=288
	ULONG CcDataPages; // Size=4 Offset=292
	ULONG ContextSwitches; // Size=4 Offset=296
	ULONG FirstLevelTbFills; // Size=4 Offset=300
	ULONG SecondLevelTbFills; // Size=4 Offset=304
	ULONG SystemCalls; // Size=4 Offset=308
	ULONGLONG CcTotalDirtyPages; // Size=8 Offset=312
	ULONGLONG CcDirtyPageThreshold; // Size=8 Offset=320
	LONGLONG ResidentAvailablePages; // Size=8 Offset=328
	ULONGLONG SharedCommittedPages; // Size=8 Offset=336
} SYSTEM_PERFORMANCE_INFORMATION_UNDOC, * PSYSTEM_PERFORMANCE_INFORMATION_UNDOC;

typedef struct _SYSTEM_FILECACHE_INFORMATION // Size=36
{
	ULONG CurrentSize; // Size=4 Offset=0
	ULONG PeakSize; // Size=4 Offset=4
	ULONG PageFaultCount; // Size=4 Offset=8
	ULONG MinimumWorkingSet; // Size=4 Offset=12
	ULONG MaximumWorkingSet; // Size=4 Offset=16
	ULONG CurrentSizeIncludingTransitionInPages; // Size=4 Offset=20
	ULONG PeakSizeIncludingTransitionInPages; // Size=4 Offset=24
	ULONG TransitionRePurposeCount; // Size=4 Offset=28
	ULONG Flags; // Size=4 Offset=32
} SYSTEM_FILECACHE_INFORMATION, * PSYSTEM_FILECACHE_INFORMATION;

typedef enum _SYSTEM_HANDLE_FLAGS
{
	PROTECT_FROM_CLOSE=1,
	INHERIT=2
} SYSTEM_HANDLE_FLAGS;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO // Size=16
{
	USHORT UniqueProcessId; // Size=2 Offset=0
	USHORT CreatorBackTraceIndex; // Size=2 Offset=2
	UCHAR ObjectTypeIndex; // Size=1 Offset=4
	SYSTEM_HANDLE_FLAGS HandleAttributes; // Size=1 Offset=5
	USHORT HandleValue; // Size=2 Offset=6
	PVOID Object; // Size=4 Offset=8
	ULONG GrantedAccess; // Size=4 Offset=12
} SYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION // Size=20
{
	ULONG NumberOfHandles; // Size=4 Offset=0
	SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1]; // Size=16 Offset=4
} SYSTEM_HANDLE_INFORMATION, * PSYSTEM_HANDLE_INFORMATION;

typedef struct _SYSTEM_PROCESS_INFORMATION_UNDOC // Size=184
{
	ULONG NextEntryOffset; // Size=4 Offset=0
	ULONG NumberOfThreads; // Size=4 Offset=4
	LARGE_INTEGER WorkingSetPrivateSize; // Size=8 Offset=8
	ULONG HardFaultCount; // Size=4 Offset=16
	ULONG NumberOfThreadsHighWatermark; // Size=4 Offset=20
	ULONGLONG CycleTime; // Size=8 Offset=24
	LARGE_INTEGER CreateTime; // Size=8 Offset=32
	LARGE_INTEGER UserTime; // Size=8 Offset=40
	LARGE_INTEGER KernelTime; // Size=8 Offset=48
	UNICODE_STRING ImageName; // Size=8 Offset=56
	LONG BasePriority; // Size=4 Offset=64
	PVOID UniqueProcessId; // Size=4 Offset=68
	PVOID InheritedFromUniqueProcessId; // Size=4 Offset=72
	ULONG HandleCount; // Size=4 Offset=76
	ULONG SessionId; // Size=4 Offset=80
	ULONG UniqueProcessKey; // Size=4 Offset=84
	ULONG PeakVirtualSize; // Size=4 Offset=88
	ULONG VirtualSize; // Size=4 Offset=92
	ULONG PageFaultCount; // Size=4 Offset=96
	ULONG PeakWorkingSetSize; // Size=4 Offset=100
	ULONG WorkingSetSize; // Size=4 Offset=104
	ULONG QuotaPeakPagedPoolUsage; // Size=4 Offset=108
	ULONG QuotaPagedPoolUsage; // Size=4 Offset=112
	ULONG QuotaPeakNonPagedPoolUsage; // Size=4 Offset=116
	ULONG QuotaNonPagedPoolUsage; // Size=4 Offset=120
	ULONG PagefileUsage; // Size=4 Offset=124
	ULONG PeakPagefileUsage; // Size=4 Offset=128
	ULONG PrivatePageCount; // Size=4 Offset=132
	LARGE_INTEGER ReadOperationCount; // Size=8 Offset=136
	LARGE_INTEGER WriteOperationCount; // Size=8 Offset=144
	LARGE_INTEGER OtherOperationCount; // Size=8 Offset=152
	LARGE_INTEGER ReadTransferCount; // Size=8 Offset=160
	LARGE_INTEGER WriteTransferCount; // Size=8 Offset=168
	LARGE_INTEGER OtherTransferCount; // Size=8 Offset=176
} SYSTEM_PROCESS_INFORMATION_UNDOC, *PSYSTEM_PROCESS_INFORMATION_UNDOC;

typedef struct _SYSTEM_BASIC_INFORMATION_UNDOC // Size=44
{
	ULONG Reserved; // Size=4 Offset=0
	ULONG TimerResolution; // Size=4 Offset=4
	ULONG PageSize; // Size=4 Offset=8
	ULONG NumberOfPhysicalPages; // Size=4 Offset=12
	ULONG LowestPhysicalPageNumber; // Size=4 Offset=16
	ULONG HighestPhysicalPageNumber; // Size=4 Offset=20
	ULONG AllocationGranularity; // Size=4 Offset=24
	ULONG MinimumUserModeAddress; // Size=4 Offset=28
	ULONG MaximumUserModeAddress; // Size=4 Offset=32
	ULONG ActiveProcessorsAffinityMask; // Size=4 Offset=36
	UCHAR NumberOfProcessors; // Size=1 Offset=40
} SYSTEM_BASIC_INFORMATION_UNDOC, * PSYSTEM_BASIC_INFORMATION_UNDOC;

typedef struct _SYSTEM_TIMEOFDAY_INFORMATION_UNDOC // Size=48
{
	LARGE_INTEGER BootTime; // Size=8 Offset=0
	LARGE_INTEGER CurrentTime; // Size=8 Offset=8
	LARGE_INTEGER TimeZoneBias; // Size=8 Offset=16
	ULONG TimeZoneId; // Size=4 Offset=24
	ULONG Reserved; // Size=4 Offset=28
	ULONGLONG BootTimeBias; // Size=8 Offset=32
	ULONGLONG SleepTimeBias; // Size=8 Offset=40
} SYSTEM_TIMEOFDAY_INFORMATION_UNDOC, *PSYSTEM_TIMEOFDAY_INFORMATION_UNDOC;

typedef struct _SYSTEM_FILECACHE_INFORMATION_UNDOC // Size=36
{
	ULONG CurrentSize; // Size=4 Offset=0
	ULONG PeakSize; // Size=4 Offset=4
	ULONG PageFaultCount; // Size=4 Offset=8
	ULONG MinimumWorkingSet; // Size=4 Offset=12
	ULONG MaximumWorkingSet; // Size=4 Offset=16
	ULONG CurrentSizeIncludingTransitionInPages; // Size=4 Offset=20
	ULONG PeakSizeIncludingTransitionInPages; // Size=4 Offset=24
	ULONG TransitionRePurposeCount; // Size=4 Offset=28
	ULONG Flags; // Size=4 Offset=32
} SYSTEM_FILECACHE_INFORMATION_UNDOC, *PSYSTEM_FILECACHE_INFORMATION_UNDOC;


typedef struct _SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_UNDOC // Size=48
{
	LARGE_INTEGER IdleTime; // Size=8 Offset=0
	LARGE_INTEGER KernelTime; // Size=8 Offset=8
	LARGE_INTEGER UserTime; // Size=8 Offset=16
	LARGE_INTEGER DpcTime; // Size=8 Offset=24
	LARGE_INTEGER InterruptTime; // Size=8 Offset=32
	ULONG InterruptCount; // Size=4 Offset=40
} SYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_UNDOC, *PSYSTEM_PROCESSOR_PERFORMANCE_INFORMATION_UNDOC;
