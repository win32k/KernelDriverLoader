#include <Windows.h>
#include <stdio.h>

BOOL Load() {
	HANDLE hSCManager;
	HANDLE hService;
	SERVICE_STATUS ss;

	hSCManager = OpenSCManager(NULL, NULL, SC_MANAGER_CREATE_SERVICE);

	if (hSCManager)
	{
		hService = CreateService(hSCManager, "WinDrv",
			"Windows Test Driver",
			SERVICE_START | DELETE | SERVICE_STOP,
			SERVICE_KERNEL_DRIVER,
			SERVICE_DEMAND_START,
			SERVICE_ERROR_IGNORE,
			"C:\\windows\\tasks\\windrv.sys",
			NULL, NULL, NULL, NULL, NULL);

		if (!hService)
		{
			hService = OpenService(hSCManager, "WinDrv",
				SERVICE_START | DELETE | SERVICE_STOP);
		}

		if (hService)
		{
			StartService(hService, 0, NULL);
			printf("Loaded");
			Sleep(10000); // The time the Driver will be loaded for 
			printf("Closed Driver");
			ControlService(hService, SERVICE_CONTROL_STOP, &ss);
			DeleteService(hService);
			CloseServiceHandle(hService);
		}
		CloseServiceHandle(hSCManager);
	}
}

void main() 
{
	Load();
}