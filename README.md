# ProcessInjectionTool
Process injection tool, in order to explain how different process injection methods works and cool tricks with WINAPI.
## What is process injection ?
Process injection is a name given to the action of injecting remote code in another process.
For example, you take 2 processus, the injector named injector.exe and a classic text editor named notepad.exe.
The objective of injector.exe is to write in the process memory of the notepad.exe processus in order to execute it remotely and hide the execution of potential malicious code.

![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/injection_1.bmp
 "Injection 1")
![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/injection_2.bmp
 "Injection 2")
![alt text](https://raw.githubusercontent.com/Lexsek/ProcessInjectionTool/master/images/injection_3.bmp
 "Injection 3")
Malicious actions will now be executed by notepad.exe, that is quite interesting. Here we used notepad.exe as an example, but imagine a malicious code injecting himself into explorer.exe and reading sensitive file system files, logging them, or injecting into firefox to send the keylogging to the C&C server of the attaquant as firefox is making a lot of network connections.
