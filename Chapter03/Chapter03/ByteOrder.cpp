#pragma comment(lib, "ws2_32")
#include <winsock2.h>
#include <stdio.h>

int main(int argc, char* argv[]) 
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
		return 1;

	u_short x1 = 0x1234;
	u_long y1 = 0x12345678;
	u_short x2;
	u_long y2;

	printf("h->n\n");
	printf("0x%x->0x%x\n", x1, x2 = htons(x1));
	printf("0x%x->0x%x\n", y1, y2 = htonl(y1));

	printf("n->h\n");
	printf("0x%x->0x%x\n", x2, ntohs(x2));
	printf("0x%x->0x%x\n", y2, ntohs(y2));

	printf("잘못사용된 예 \n");
	printf("0x%x->0x%x\n",x1, htonl(x1));

	WSACleanup();
	return 0;
}