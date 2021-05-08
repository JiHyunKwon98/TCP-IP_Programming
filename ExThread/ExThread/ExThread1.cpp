//������ ������ ����, ���� ����
#include <windows.h>
#include <stdio.h>

//������ �Լ��� 32��Ʈ���� ū ���� �����ϱ� ���� ����ü�� �����Ѵ�.
struct Point3D {
	int x, y, z;
};

DWORD WINAPI MyThread(LPVOID arg) {

	// void�� �����͸� Point3D�� �����ͷ� ����ȯ�Ͽ� ����ü ��� x, y, z�� �����Ѵ�.
	Point3D* pt = (Point3D*)arg;
	
	// ���� ������ ���鼭 1�ʸ��� ������ ID�� x, y, z�� ����Ѵ�.
	while (1) {
		printf("Running My Thread() %d : %d, %d, %d\n",
			GetCurrentThreadId(), pt->x, pt->y, pt->z);
		Sleep(1000);
	}
	// ������ �Լ��� ���������ν� �����尡 �����Ѵ�. ���ѷ����� ���� ������ ������ �� �ڵ�� 
	// ������� �ʴ´�.
	return 0;
}

int main(int argc, char* argv[]) {

	// ������ �ΰ��� �����ϵ�, ���簡 �߻��ϸ� 1(����) ���� , �������α׷� ���� 
	//ù��° ������ ����
	Point3D pt1 = { 10, 20, 30 };
	HANDLE hThread1 = CreateThread(NULL, 0, MyThread, &pt1, 0, NULL);
	if (hThread1 == NULL) return 1;
	CloseHandle(hThread1);

	//�ι��� ������ ����
	Point3D pt2 = {40, 50, 60};
	HANDLE hThread2 = CreateThread(NULL, 0, MyThread, &pt2, 0, NULL);
	if (hThread2 == NULL) return 1;
	CloseHandle(hThread2);

	// �� ������� ���ѷ����� ���鼭 1�ʸ��� ������ ID�� ����Ѵ�. �� �κ��� �����ϸ� �� �����尡 
	//0�� �����ϸ鼭 �������α׷�, �� ���μ����� �����Ѵ�.
	while (1) {
		printf("Running main() %d\n", GetCurrentThreadId());
		Sleep(1000);
	}

	return 0; //������ �ڵ� ���� 
}