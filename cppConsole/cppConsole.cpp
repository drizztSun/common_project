// cppConsole.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>

#include <map>

using std::map;


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


struct student_grade{
	char name[20];
	int stu_code;

	int grade;
	int eglish_grade;
	char grade2;
	char eglish_grade2;
	bool failed_or_not;
	bool eg_failed_or_not;
};

// global variable
student_grade stua = { "owen", 20150402391, 97.5, 100, 'A', 'A', false, true };

struct point {
	int x, y;
};


void test_point() {

	//1:members of a structure can be accessed by the"."operator.
	//ex:
	printf("1:members of a structure can be accessed by the dot(.) operator.\nex:\n");
	struct point point1 = { 2, 4 };//{x, y}
	printf("now:x:%d y:%d\n", point1.x, point1.y);
	point1.x = 10;
	printf("now:x:%d y:%d\n", point1.x, point1.y);
	point1.y = 20;
	printf("now:x:%d y:%d\n\n", point1.x, point1.y);

	//2:You can create a array with structures. 
    //ex:

	printf("2:You can create a array with structures.\nex:\n");
	struct point aop[10];
	aop[0].x = 10;
	aop[0].y = 20;
	printf("output: x:%d y:%d \n\n", aop[0].x, aop[0].y);

	//3:You can use a pointer for a class , if we have a pointer to a structure, members 
	//of a structure can be accessed by "->"operator(It looks like a pointer).
    //ex:
	printf("3:You can use a pointer for a class , if we have a pointer to a structure, members of a "); 
	printf("structure can be accessed by pointer(->) operator(It looks like a pointer).\nex:\n");

	struct point p1 = { 1, 2 };

	struct point *p2 = &p1;

	printf("p2: x: %d y:%d\n\n", p2->x, p2->y);

	

}

void test_bit_operator() {

	// '<<' '>>' '&', '|' '^'


	int i = 1;

	i <<= 2; // left-move 2 bit, becoming  0100, is equal to i*2*2

	i >>= 1; // right-move 1 bit, becoming 0010, equal to i//2

	int j = 1 & 0;

	




	return;
}

int main() {


	map<int, int> dp;

	dp.insert({ 1, 2 });
	dp.insert({ 2, 3 });
	dp.insert({ 3, 4 });
	dp.insert({ 4, 5 });
	dp.insert({ 5, 6 });

	for (auto it = begin(dp); it != dp.end(); it++) {

		// std::cout << it->first << ":" << it->second << std::endl;

		it = dp.erase(it);
	}

}

/*

	test_bit_operator();

	// static variable 
	static int vc = 100;

	vc = 250;

	//local variable
	int a = 90;
	
	unsigned int ua = -100;
	printf(" ua %u \n", ua);

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

	{
		int num;

		num = 1;
		
		num = 3;

		printf("%d \n", num++); // get value, do +1
		// do(i)
		// i++

		printf("%d \n", num);

		printf("%d \n \n\n\n\n", ++num); // do +1, get value
		// i += 1
		// do(i)
	}


	test_point();
	
	return 1;

}

*/




