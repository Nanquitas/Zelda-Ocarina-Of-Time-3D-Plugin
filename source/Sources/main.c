#include "global.h"
#include "configs.h"
#include "cheats.h"

Handle fsUserHandle;
FS_archive sdmcArchive = { 0x9, (FS_path) { PATH_EMPTY, 1, (u8*)"" } };
u32 threadStack[0x1000];
u32 IoBaseLcd;
u32 IoBasePad;
int isNewNtr;
int32_t socuRet = 1234;

void gamePluginEntry();

int	main()
{
	Handle		hThread;
	u32			socuBuffer;
	u32			ret;

	initSharedFunc();
	socuBuffer = plgRequestMemory(0x10000);
	//initSrv();
	//socuRet = SOC_Initialize((int32_t *)socuBuffer, 0x10000);
	//exitSrv();
	ret = svc_createThread(&hThread, gamePluginEntry, 0, &threadStack[0x1000], 0x3F, 0xFFFFFFFE);

}