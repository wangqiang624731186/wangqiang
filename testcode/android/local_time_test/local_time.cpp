#include <string.h>
#include <stdint.h>
#include <string.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <cutils/log.h>
#include <pthread.h>
#include <hardware/local_time_hal.h>
#include <utils/Timers.h>



int main(int argc, char** argv)
{
	int res;
    const hw_module_t* mod;
	local_time_hw_device_t* dev_ = NULL;


    res = hw_get_module_by_class(LOCAL_TIME_HARDWARE_MODULE_ID, NULL, &mod);
    if (res) {
        printf("Failed to open local time HAL module (res = %d)", res);
    } else {
        res = local_time_hw_device_open(mod, &dev_);
        if (res) {
            printf("Failed to open local time HAL device (res = %d)", res);
            dev_ = NULL;
        }
    }


    while(1)
    {
			
		printf("dev_->get_local_time(dev_) %lld\n",dev_->get_local_time(dev_));

		printf("dev_->get_local_freq(dev_) %lld\n",dev_->get_local_freq(dev_));
        sleep(1);
    }

    return 0;
}
