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
	volatile clock_t t1;
    BPT<int> test(15);
    // for (int i = 0; i < 30; i++) {
    //  test.insert(30-i);
    //	printf("*********************\n");
    //	test.print();
    //}
	t1 = clock();
	volatile clock_t t3, t4;
    for (int i = 0; i < 10000000; i++) {
        test.insert(i);
    }
	volatile clock_t t2 = clock();
	//t3 = clock();
	//for (int i = 0; i <1000000; i++) {
	//	test.search(i);
	//}
	//t4 = clock();
    printf("time: %ld\n%d", (t2 - t1) / CLOCKS_PER_SEC, test.h);
    return 0;
}
