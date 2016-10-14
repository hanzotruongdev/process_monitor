

#define COLUMN_NMAX 25

#define COLUMN_IMAGENAME            0
#define COLUMN_PID                  1
#define COLUMN_CPUUSAGE             2
#define COLUMN_MEMORY				3
#define COLUMN_READ_OPERATION		4
#define COLUMN_WRITE_OPERATION		5
#define COLUMN_OTHER_OPERATION		6

#define COLUMN_READ_TRANSFER		7
#define COLUMN_WRITE_TRANSFER		8
#define COLUMN_OTHER_TRANSFER		9

typedef struct
{
	ULONG ProcessId;
} PROCESS_PAGE_LIST_ITEM, *LPPROCESS_PAGE_LIST_ITEM;

typedef struct _PROCESS_PAGE_SETTING
{
	int		iSortColumn;
	BOOL	bSortAscending;
} PROCESS_PAGE_SETTING, *PPROCESS_PAGE_SETTING;

// setting funtion
void SetSortColumn(int iColumn);
void ToggleSort();

// data funtion
void InitListProcessPage(CListCtrl * objListCtlProcess);
BOOL PerfDataGetText(ULONG Index, ULONG ColumnIndex, LPTSTR lpText, int nMaxCount);
void UpdateProcess(CListCtrl * objListCtlProcess);
void AddListItem(ULONG Index, CListCtrl * objListCtlProcess);