#pragma once
#include "CuTest.h"
void test1(CuTest *tc)
{
    CuAssertPtrEquals(tc, 1437, 1437);
}
void test2(CuTest *tc)
{
    CuAssertPtrEquals(tc, 1437, 1438);
}
void test3(CuTest *tc)
{
    CuAssertPtrEquals(tc, 1438, 1438);
}
void test4(CuTest *tc)
{
    CuAssertPtrEquals(tc, 1438, 1437);
}
TestFunction testlist[] = {
    test1,
    test2,
    test3,
    test4,
};