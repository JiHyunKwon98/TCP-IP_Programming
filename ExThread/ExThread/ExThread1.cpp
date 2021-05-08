//스레드 생성과 종료, 인자 전달
#include <windows.h>
#include <stdio.h>

//스레드 함수에 32비트보다 큰 값을 전달하기 위한 구주체를 정의한다.
struct Point3D {
	int x, y, z;
};

DWORD WINAPI MyThread(LPVOID arg) {

	// void형 포인터를 Point3D형 포인터로 형변환하여 구조체 멤버 x, y, z에 접근한다.
	Point3D* pt = (Point3D*)arg;
	
	// 무한 루프를 돌면서 1초마다 스레드 ID와 x, y, z를 출력한다.
	while (1) {
		printf("Running My Thread() %d : %d, %d, %d\n",
			GetCurrentThreadId(), pt->x, pt->y, pt->z);
		Sleep(1000);
	}
	// 스레드 함수가 리턴함으로써 스레드가 종료한다. 무한루프를 돌기 때문에 실제로 이 코드는 
	// 수행되지 않는다.
	return 0;
}

int main(int argc, char* argv[]) {

	// 스레드 두개를 생성하되, 오루가 발생하면 1(실패) 리턴 , 응용프로그램 종료 
	//첫번째 스레드 생성
	Point3D pt1 = { 10, 20, 30 };
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread, &pt1, 0, NULL);
	if (hThread1 == NULL) return 1;
	CloseHandle(hThread1);

	//두번쩨 스레드 생성
	Point3D pt2 = {40, 50, 60};
	HANDLE hThread2 = CreateThread(NULL, 0, MyThread, &pt2, 0, NULL);
	if (hThread2 == NULL) return 1;
	CloseHandle(hThread2);

	// 주 스레드는 무한루프를 돌면서 1초마다 스레드 ID를 출력한다. 이 부분을 제거하면 주 스레드가 
	//0을 리턴하면서 응용프로그램, 즉 프로세스가 종료한다.
	while (1) {
		printf("Running main() %d\n", GetCurrentThreadId());
		Sleep(1000);
	}

	return 0; //스레드 자동 종료 
}