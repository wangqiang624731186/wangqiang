#ifndef ANDROID_EXAMPLE_CLASS_H
#define ANDROID_EXAMPLE_CLASS_H
#include <utils/threads.h>
#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/BpBinder.h>
#include <binder/Parcel.h>

namespace android {
    class ExampleClass
    {
        public:
            ExampleClass();
            virtual ~ExampleClass();
			int get_class_size();
			static int get_a();
			static void set_a(int val);
			static int get_c();
			static void set_c(int val);
			 int get_b();
			 void set_b(int val);
			 int get_d();
			 void set_d(int val);
		public:
			static int a;
			int b;
		private:
			static int c;
			int d;
	};
}; //namespace
#endif
