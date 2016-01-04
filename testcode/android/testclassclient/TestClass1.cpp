// File: Example.cpp
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include "../testclass/ExampleClass.h"
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
#include <utils/String8.h>


using namespace android;

int main(int argc, char** argv)
{
	ExampleClass *test1 = new ExampleClass;
	int (ExampleClass::*p)();
	p = &(test1->get_class_size);
	printf("a:%d\n",test1->get_a());
	printf("b:%d\n",test1->get_b());
	printf("c:%d\n",test1->get_c());
	printf("d:%d\n",test1->get_d());
	printf("p:%d %p %p\n",test1->get_class_size(),test1,p);			
	
	/*test1->set_a(1);
	test1->set_b(2);
	test1->set_c(3);
	test1->set_d(4);
	
		
	printf("a:%d\n",test1->get_a());
	printf("b:%d\n",test1->get_b());
	printf("c:%d\n",test1->get_c());
	printf("d:%d\n",test1->get_d());*/
	
	ExampleClass *test2 = new ExampleClass;
		p = &(test2->get_class_size);
	printf("a:%d\n",test2->get_a());
	printf("b:%d\n",test2->get_b());
	printf("c:%d\n",test2->get_c());
	printf("d:%d\n",test2->get_d());
	printf("p:%d %p %p\n",test2->get_class_size(),test2,p);			
    return 0;
}

