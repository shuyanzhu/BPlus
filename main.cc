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
    clock_t t1, t2;
    t1 = clock();
    BPT<int> test(3);
    // for (int i = 0; i < 30; i++) {
    //  test.insert(30-i);
    //	printf("*********************\n");
    //	test.print();
    //}

    for (int i = 0; i < 10000000; i++) {
        test.insert(i);
    }
    t2 = clock();
    printf("time: %ld\n", (t2 - t1) / CLOCKS_PER_SEC);
    return 0;
}
