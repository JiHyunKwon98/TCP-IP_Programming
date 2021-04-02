#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>

#define TESTNAME "www.syu.ac.kr"

//소켓 함수 오류 출력
void err_display(const char* msg) {
	LPVOID IpMsgBuf;
	FormatMessage(
		FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM,
		NULL, WSAGetLastError(),
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&IpMsgBuf, 0, NULL);
	printf(" [ %s ] %s ", msg, (char*)IpMsgBuf);
	LocalFree(IpMsgBuf);
}

//도메인 이름 -> Ipv4 주소 
BOOL GetIPAddr(const char *name, IN_ADDR*addr) {
	HOSTENT *ptr = gethostbyname(name);
	if (ptr == NULL) {
		err_display("gethostbyname()");
		return FALSE;
	}
	if (ptr->h_addrtype != AF_INET)
		return FALSE;
	memcpy(addr, ptr->h_addr_list, ptr->h_length);
	return TRUE;
	}
BOOL GetDomainName(IN_ADDR addr, char* name, int namelen) {
	HOSTENT* ptr = gethostbyaddr((char*)&addr, sizeof(addr), AF_INET);
	if (ptr == NULL) {
		err_display("gethostbyaddr()");
		return FALSE;
	}
	if (ptr->h_addrtype != AF_INET)
		return FALSE;
	strncpy(name, ptr->h_name, namelen);
	return TRUE;
}

int main(int argc, char* argv[]) {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	printf("도메인 이름(변환전) = %s\n", TESTNAME);

	//도메인 이름 -> IP주소
	IN_ADDR addr;
	if (GetIPAddr(TESTNAME, &addr)) {
	//성공이면 결과 출력 
		printf("IP주소 (변환후)=%s\n", inet_ntoa(addr));

		//Ip주소 -> 도메인 이름 
		char name[256];
		if (GetDomainName(addr, name, sizeof(name))) {
			//성공이면 결과 출력
			printf("도메인 이름(다시 변환 후) = %s\n", name);
		}

		WSACleanup();
		return 0;
	
	}

}