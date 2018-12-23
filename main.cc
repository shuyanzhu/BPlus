#include <iostream>
#include <time.h>
#include <stdlib.h>

#include "include/vector/vector.h"
#include "include/BPT.h"
using namespace std;

int main()
{
    BPT<int> test(5);
    volatile clock_t t1, t2;
    t1 = clock();

    //// 顺序/倒序插入速度测试
    // for (int i = 0; i < 10000000; i++) {
    //    test.insert(i);
    //}
    // for (int i = 0; i < 10000000; i++) {
    // test.insert(10000000-i);
    //}

    //乱序插入、删除正确性测试，速度测试
    srand(1);
    for (int i = 0; i < 10000000; i++) {
        test.insert(rand() % 10000000);
    }
    // test.print(0);
    // test.search(17400);
    // for (int i = 0; i < 1000000; i++) {
    //    test.remove(rand() % 10000000);
    //}
    // test.print(0);

    t2 = clock();
    printf("time: %ld\n%d", (t2 - t1) / CLOCKS_PER_SEC, test.h);
    // system("pause");
    return 0;
}