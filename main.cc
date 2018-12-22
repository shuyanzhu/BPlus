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
#include"include/BPT.h"
using namespace std;

int main()
{

	BPT<int> test(5);
	volatile clock_t t1, t2;
	t1 = clock();

	// 顺序/倒序插入速度测试
	//for (int i = 0; i < 10000000; i++) {
	//    test.insert(i);
	//}
	//for (int i = 0; i < 10000000; i++) {
	// test.insert(10000000-i);
	//}

	// 乱序插入、删除正确性测试，速度测试
	srand(0);
	for (int i = 0; i < 10000000; i++) {
		test.insert(rand()*rand());
	}
	test.print(0);
	for (int i = 0; i < 10000; i++) {
		test.remove(rand());
	}
	test.print(0);


	t2 = clock();
	printf("time: %ld\n%d", (t2 - t1) / CLOCKS_PER_SEC, test.h);

	return 0;
}
