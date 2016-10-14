

#define COLUMN_NMAX 25

#define COLUMN_IMAGENAME            0
#define COLUMN_PID                  1
#define COLUMN_CPUUSAGE             2
#define COLUMN_MEMORY				3

typedef struct
{
	ULONG ProcessId;
} PROCESS_PAGE_LIST_ITEM, *LPPROCESS_PAGE_LIST_ITEM;



void InitListProcessPage(CListCtrl * objListCtlProcess);
BOOL PerfDataGetText(ULONG Index, ULONG ColumnIndex, LPTSTR lpText, int nMaxCount);
void UpdateProcess(CListCtrl * objListCtlProcess);
void AddListItem(ULONG Index, CListCtrl * objListCtlProcess);