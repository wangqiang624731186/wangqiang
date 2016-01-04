// File: ExampleService.cpp
#include "ExampleClass.h"
#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>
namespace android {
	sem_init(&Example::list_sem, 0,0);
	int ExampleClass::a = 0;
	int ExampleClass::c = 0;	
	int ExampleClass::get_class_size()
    {
		return sizeof(ExampleClass);
    }

    ExampleClass::ExampleClass()
    { 

		b = 0;
		d = 0;
    }

    ExampleClass::~ExampleClass()
    {
    }
	
	int ExampleClass::get_a()
	{
		return a;
	}
	
	void ExampleClass::set_a(int val)
	{
		a = val;
	}
	
	int ExampleClass::get_c()
	{
		return c;
	}
	
	void ExampleClass::set_c(int val)
	{
		c = val;
	}
	
	int ExampleClass::get_b()
	{
		return b;
	}
	
	void ExampleClass::set_b(int val)
	{
		b = val;
	}
	
	int ExampleClass::get_d()
	{
		return d;
	}
	
	void ExampleClass::set_d(int val)
	{
		d = val;
	}
}; //namespace
