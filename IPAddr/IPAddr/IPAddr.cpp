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

	//String ������ IPv4 �ּҸ� long ������ �ּҷ� ��ȯ
	printf("IPv4 �ּ�(��ȯ��) = %s\n", ipv4test);
	printf("IPv4 �ּ�(��ȯ��) = %0x%x\n", inet_addr(ipv4test));

	//Long ������ �ּҸ� String ������ IPv4�ּҷ� ��ȯ
	IN_ADDR ipv4num;
	ipv4num.s_addr = inet_addr(ipv4test);
	printf("IPv4 �ּ�(�ٽ� ��ȯ��) = %s\n", inet_ntoa(ipv4num));

	printf("\n");

	printf("IPv6 �ּ�(��ȯ��) = %s\n", ipv6test);
	//String ������ IPv6 �ּҸ� 16byte ������ ���� �ּ� ����ü ���·� ��ȯ
	SOCKADDR_IN6 ipv6num;
	int addrlen = sizeof(ipv6num);
	WSAStringToAddress(ipv6test, AF_INET6, NULL, (SOCKADDR*)&ipv6num, &addrlen );
	for (int i = 0; i < 16; i++)
		printf("%02x", ipv6num.sin6_addr.u.Byte[i] );
	//String ������ IPv4 �ּҸ� long ������ �ּҷ� ��ȯ
	char ipaddr[50];
	DWORD ipaddrlen = sizeof(ipaddr);
	WSAAddressToString((SOCKADDR*)&ipv6num, sizeof(ipv6num),NULL, ipaddr, &ipaddrlen);
	printf("IPv6 �ּ�(�ٽ� ��ȯ ��) = %s\n", ipaddr);

	WSACleanup();
	return 0;
}