#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	char* ipv4test = "147.46.114.70";
	char* ipv6test = "2001:0230:abcd:ffab:0023:eb00:ffff:1111";

	//String 형태의 IPv4 주소를 long 형태의 주소로 변환
	printf("IPv4 주소(변환전) = %s\n", ipv4test);
	printf("IPv4 주소(변환후) = %0x%x\n", inet_addr(ipv4test));

	//Long 형태의 주소를 String 형태의 IPv4주소로 변환
	IN_ADDR ipv4num;
	ipv4num.s_addr = inet_addr(ipv4test);
	printf("IPv4 주소(다시 변환후) = %s\n", inet_ntoa(ipv4num));

	printf("\n");

	printf("IPv6 주소(변환전) = %s\n", ipv6test);
	//String 형태의 IPv6 주소를 16byte 형태의 소켓 주소 구조체 형태로 변환
	SOCKADDR_IN6 ipv6num;
	int addrlen = sizeof(ipv6num);
	WSAStringToAddress(ipv6test, AF_INET6, NULL, (SOCKADDR*)&ipv6num, &addrlen );
	for (int i = 0; i < 16; i++)
		printf("%02x", ipv6num.sin6_addr.u.Byte[i] );
	//String 형태의 IPv4 주소를 long 형태의 주소로 변환
	char ipaddr[50];
	DWORD ipaddrlen = sizeof(ipaddr);
	WSAAddressToString((SOCKADDR*)&ipv6num, sizeof(ipv6num),NULL, ipaddr, &ipaddrlen);
	printf("IPv6 주소(다시 변환 후) = %s\n", ipaddr);

	WSACleanup();
	return 0;
}