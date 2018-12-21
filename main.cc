/*************************************************************************
    > File Name: main.cc
    > Author: 朱会茗
    > Mail: 1294206499@qq.com
    > Created Time: 2018年12月19日 星期三 16时39分49秒
 ************************************************************************/

#include <iostream>
#include <time.h>

#include "include/vector/vector.h"
#include "include/BPT.h"
using namespace std;

int main()
{
	BPT<int> test(3);
	volatile clock_t t1, t2;
	t1 = clock();

     for (int i = 0; i < 8; i++) {
		test.insert(i);
    	printf("*********************\n");
    	test.print();
    }
	test.remove(4);
	 test.remove(0);
	 printf("*********************\n");
	 test.print();
    //for (int i = 0; i < 10000000; i++) {
    //    test.insert(10000000-i);
    //}

	 t2 = clock();
	printf("time: %ld\n%d", (t2 - t1) / CLOCKS_PER_SEC, test.h);

    return 0;
}
