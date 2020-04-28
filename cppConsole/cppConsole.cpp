// cppConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



void TestUnorderMap();

void Test_Unordered_set();

void test_vector_morden_cpp();

void Test_share_ptr();


void insert_sort(int* a, int length) {

	for (int i = 1; i < length; i++) {

		for (int j = i; j > 0; j--) {
			if (a[j] < a[j - 1]) {
				int k = a[j];
				a[j] = a[j-1];
				a[j-1] = k;
			}
			else {
				break;
			}
		}
	}
}

void buboule_sort(int* a, int length) {

	for (int i = 0; i < length-1; i++) {
		for (int j = 0; j < length - i-1; j++) {
			if (a[j] > a[j + 1]) {
				int k = a[j+1];
				a[j+1] = a[j];
				a[j] = k;
			}
		}
	}
}

void select_sort(int* a, int length) {

	for (int i = 0; i < length - 1; i++) {
		int s = 0;
		for (int j = 0; j < length - i; j++) {
			if (a[j] > a[s]) {
				s = j;
			}
		}
		int t = a[s];
		a[s] = a[length - i - 1];
		a[length - i - 1] = t;
	}
}

int main() {

	int a = 90;
	float b = 3.1416;

	double c = 3.14;

	short d = 10;

	char e = 'a';

	int f[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };


	printf("%d size: %d \n", a, sizeof(a));
	printf("%f size:%d \n", b, sizeof(b));
	printf("%f size:%d\n", c, sizeof(c));
	printf("%d size: %d\n", d, sizeof(d));
	printf("%c size: %d\n", e, sizeof(e));
	printf("%p size: %d\n", f, sizeof(f));

	for (int i = 0; i < 10; i++) { // for( init ; condition; stepover;) for(;true;)
		if (f[i] % 2 == 0) {
			printf("%d is a even number , %d times 2 = %d\n", f[i], f[i], f[i] * 2);

		}
		else if (f[i] % 2 == 1) {
			printf("%d is a odd number , %d times 2 = %d\n", f[i], f[i], f[i] * 2);
					}



	}

	int j = 0;
	while(j < 10) {
		printf("%d \n", j * j *j);
		j++;
	}

	int array[5] = { 5, 4, 3, 2, 1 };
	insert_sort(array, 5);

	int arr[5] = { 5, 4, 3, 2, 1 };
	buboule_sort(arr, 5);

	int o[5] = { 1, 3, 2, 5, 4};
	select_sort(o, 5);

	return 1;

}

