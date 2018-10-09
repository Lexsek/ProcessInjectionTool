# ProcessInjectionTool

Process injection tool, in order to explain how different process injection methods works and cool tricks with WINAPI.

## Applications, Processus and Threads

There are 3 differents important names that you must understand in Windows before starting explaining injection.
Applications is the main name that you give to an executable, for example firefox.exe.
Processus is the name you give of each instances of the application.
Thread is the name you give to sequences of instructions that can be managed independently.

An application can have 1 or more process running.
Each process have at least 1 thread or more.

![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/threads_process_and_apps.png "AppsProcessusThreads")
 
## Some Windows Structures

There are some windows structures that you must understand aswell.
TEB : Thread Environment Block
    The Thread Environment Block (TEB) structure describes the state of a thread. It is accessible from the FS segment register. 
![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/TEB.bmp
"TEB")
PEB : Process Environment Block
    The Process Environment Block (PEB) is a user-mode data structure that can be used by applications (and by extend by malware) to get information such as the list of loaded modules, process startup arguments, heap address, check whether program is being debugged, find image base address of imported DLLs, ...
![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/PB.bmp 
"PEB")
PEB_LDR_DATA :
    The PEB_LDR_DATA structure is a structure that contains information about all of the loaded modules in the current process. 
![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/PEB_LDR_DATA.bmp
"PEB_LDR_DATA")
LIST_ENTRY :
    A LIST_ENTRY structure describes an entry in a doubly linked list or serves as the header for such a list.
![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/LIST_ENTRY.bmp 
"LIST_ENTRY")
    Flink : For a LIST_ENTRY structure that serves as a list entry, the Flink member points to the next entry in the list or to the list header if there is no next entry in the list. For a LIST_ENTRY structure that serves as the list header, the Flink member points to the first entry in the list or to the LIST_ENTRY structure itself if the list is empty.
    Blink : For a LIST_ENTRY structure that serves as a list entry, the Blink member points to the previous entry in the list or to the list header if there is no previous entry in the list. For a LIST_ENTRY structure that serves as the list header, the Blink member points to the last entry in the list or to the LIST_ENTRY structure itself if the list is empty.
![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/LIST_ENTRY2.bmp 
"LIST_ENTRY2")
LDR_DATA_TABLE_ENTRY :
    LDR_DATA_TABLE_ENTRY structure contains informations about a module.
![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/LDR_DATA_TABLE_ENTRY.bmp 
"LDR_DATA_TABLE_ENTRY")
PROCESS_ENTRY :

## What is process injection ?

Process injection is a name given to the action of injecting remote code in another process.
For example, you take 2 processus, the injector named injector.exe and a classic text editor named notepad.exe.
The objective of injector.exe is to write in the process memory of the notepad.exe processus in order to execute it remotely and hide the execution of potential malicious code.

![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/injection_1.bmp "Injection 1")
![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/injection_2.bmp "Injection 2")
![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/injection_3.bmp "Injection 3")
Malicious actions will now be executed by notepad.exe, that is quite interesting. Here we used notepad.exe as an example, but imagine a malicious code injecting himself into explorer.exe and reading sensitive file system files, logging them, or injecting into firefox to send the keylogging to the C&C server of the attaquant as firefox is making a lot of network connections.
