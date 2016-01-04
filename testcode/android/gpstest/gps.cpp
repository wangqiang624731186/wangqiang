#include <string.h>
#include <stdint.h>
#include <string.h>
#include <sys/cdefs.h>
#include <sys/types.h>

#include <cutils/log.h>
#include <pthread.h>
#include <hardware/gps.h>
#include <utils/Timers.h>


typedef void* (*gps_cbk)(void *);
static pthread_t create_thread_callback(const char* name, void (*start)(void *), void* arg)
{
	gps_cbk gps_thread = (gps_cbk)start;
	printf("%s\n",name);
	pthread_t tid;
    pthread_create(&tid,NULL,gps_thread,arg);
	return tid;
}
static void request_utc_time_callback()
{
}

static void release_wakelock_callback()
{
}

static void acquire_wakelock_callback()
{
}

static void set_capabilities_callback(uint32_t capabilities)
{
}

static void nmea_callback(GpsUtcTime timestamp, const char* nmea, int length)
{
}

static void sv_status_callback(GpsSvStatus* sv_status)
{
}

static void status_callback(GpsStatus* status)
{
}


static void location_callback(GpsLocation* location)
{
    printf("%f %f\n",location->latitude,location->longitude);
}


GpsCallbacks sGpsCallbacks = {
    sizeof(GpsCallbacks),
    location_callback,
    status_callback,
    sv_status_callback,
    nmea_callback,
    set_capabilities_callback,
    acquire_wakelock_callback,
    release_wakelock_callback,
    create_thread_callback,
    request_utc_time_callback,
};


int main(int argc, char** argv)
{
    int err;
    struct hw_module_t* module;

    err = hw_get_module(GPS_HARDWARE_MODULE_ID, (hw_module_t const**)&module);
    if (err != 0) {
        printf("hw_get_module() failed (%s)\n", strerror(-err));
        return 0;
    }

    hw_device_t *device;
    err = module->methods->open(module,GPS_HARDWARE_MODULE_ID,&device);
    if (err != 0) {
        printf(" module->methods->open failed (%s)\n", strerror(-err));
        return 0;
    }

    gps_device_t *gps_device = (gps_device_t *)device;
    const GpsInterface *sGpsInterface;
    sGpsInterface = gps_device->get_gps_interface(gps_device);
    
    if (!sGpsInterface)
    {
        printf("get interface failed\n");
    }

    if ( sGpsInterface->init(&sGpsCallbacks) != 0)
    {
        printf("init failed\n");
    }

    if ( sGpsInterface->start() != 0)
    {
        printf("start failed\n");
    }


    while(1)
    {
        sleep(1);
    }

    return 0;
}
