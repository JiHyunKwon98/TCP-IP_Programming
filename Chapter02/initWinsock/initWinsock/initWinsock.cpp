#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>

void err_quit(const char* msg) {
	LPVOID IpMsgBug;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL,
		WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&IpMsgBug, 0, NULL);
	MessageBox(NULL, (LPCSTR)IpMsgBug, msg, MB_ICONERROR);
	LocalFree(IpMsgBug);
	exit(1);

}

int f(int x) {
	if (x >= 0) {
		WSASetLastError(0);
		return 0;
	}
	else {
		WSASetLastError(WSAEMSGSIZE);
		return SOCKET_ERROR;
	}
}


int main(int argc, char* argv[]) {

	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0) {
		return 1;
	}

	/*printf("%#x\n", wsa.wVersion);
	printf("%#x\n", wsa.wHighVersion);
	printf("%s\n", wsa.szDescription);
	printf("%s\n", wsa.szSystemStatus);
	*/

	MessageBox(NULL, "원속 초기화 성공", "알림", MB_OK);

	SOCKET tcp_sock = WSASocket(AF_INET6, SOCK_STREAM, 0, NULL, 0, 0);
	if (tcp_sock == INVALID_SOCKET) {
		err_quit("socket()");
	}
	MessageBox(NULL, "TCP 소켓 생성 성공", "알림", MB_OK);
	closesocket(tcp_sock);


	/*int retval = f(0);
	if (retval == SOCKET_ERROR) {
		err_quit("f()");
	}
	*/

	WSACleanup();
	return 0;
}