#include "UnitTest.h"
int main(int argc, const char* argv[]){
	CuString *output = CuStringNew();
	CuSuite* suite = CuSuiteNew();
    for(int i=0;i<sizeof(testlist)/sizeof(TestFunction);++i) SUITE_ADD_TEST(suite, testlist[i]);
    CuSuiteRun(suite);
	CuSuiteSummary(suite, output);
	CuSuiteDetails(suite, output);
	printf("%s\n", output->buffer);
    CuStringDelete(output);
    return 0;
}