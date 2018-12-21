/*************************************************************************
    > File Name: main.cc
    > Author: 朱会茗
    > Mail: 1294206499@qq.com
    > Created Time: 2018年12月19日 星期三 16时39分49秒
 ************************************************************************/

#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "include/vector/vector.h"
#include "include/BPT.h"
using namespace std;

int main()
{
	int del[5] = { 38, 40, 42, 76, 0 };
	srand(1);
	BPT<int> test(10);
	volatile clock_t t1, t2;
	t1 = clock();

	//for (int i = 0; i < 8; i++) {
	//	test.insert(i);
	//	printf("*********************\n");
	//	test.print();
	//}
  //   for (int i = 0; i < 28; i++) {
		// int n = rand() % 100;
		// printf("insert %d\n", n);
		//test.insert(n);
  //  	printf("*********************\n");
  //  	test.print(1);
  //  }
	 //test.print(1);

	 //printf("insert done++++++++++++++++++++++++++++++++++++++\n");
	 //for (int i = 0; i < 15; i++) {
		// int n;
		// printf("delete :%d\n", n = rand()%100);
		// test.remove(n);
		// printf("*********************\n");
		// test.print(1);
	 //}
	 //for (int i = 0; i < 5; i++) {
		// printf("delete :%d\n", del[i]);
		// test.remove(del[i]);
		// printf("*********************\n");
		// test.print(1);
	 //}
    for (int i = 0; i < 10000000; i++) {
        test.insert(rand()*rand());
    }
	test.print(0);
	for (int i = 0; i < 1000; i++) {
		test.remove(rand()%1000);
	}
//	test.print(0);
	 t2 = clock();
	printf("time: %ld\n%d", (t2 - t1) / CLOCKS_PER_SEC, test.h);

    return 0;
}
