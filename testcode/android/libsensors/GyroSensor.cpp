/*
 * Copyright (C) 2012-2013 Freescale Semiconductor, Inc.
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <fcntl.h>
#include <errno.h>
#include <math.h>
#include <stdlib.h>
#include <poll.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/select.h>
#include <dlfcn.h>
#include <cutils/log.h>
#include <cutils/properties.h>
#include "GyroSensor.h"
#define GYRO_DATA_NAME    "lsm330dlc_gyr" 
#define GYRO_SYSFS_PATH   "/sys/devices/platform/imx-i2c.1/i2c-1"
#define GYRO_SYSFS_DELAY  "poll"
#define GYRO_SYSFS_ENABLE "enable_device"
#define GYRO_EVENT_X ABS_X
#define GYRO_EVENT_Y ABS_Y
#define GYRO_EVENT_Z ABS_Z

#define LOG_TAG "GyroSensor"
	
GyroSensor::GyroSensor()
: SensorBase(NULL, GYRO_DATA_NAME),
      mEnabled(0),
      mPendingMask(0),
      mInputReader(4),
      mDelay(0)
{
    memset(&mPendingEvent, 0, sizeof(mPendingEvent));
	memset(mClassPath, '\0', sizeof(mClassPath));
	
    mPendingEvent.version = sizeof(sensors_event_t);
    mPendingEvent.sensor  = ID_GY;
    mPendingEvent.type    = SENSOR_TYPE_GYROSCOPE;
    mPendingEvent.gyro.status = SENSOR_STATUS_ACCURACY_HIGH;
	mUser = 0;
	if(sensor_get_class_path(mClassPath))
	{
		ALOGE("Can`t find the Gyro sensor!");
	}
}

GyroSensor::~GyroSensor()
{
}

int GyroSensor::setEnable(int32_t handle, int en)
{
	int err = 0;
    uint32_t newState  = en;
	if(handle != ID_GY )
		return -1;
	if(en)
		mUser++;
	else{
		mUser--;
		if(mUser < 0)
			mUser = 0;
	}
	if(mUser > 0)
		err = enable_sensor();
	else
		err = disable_sensor();
	if(handle == ID_GY ) {
		if(en)
         	mEnabled++;
		else
			mEnabled--;

		if(mEnabled < 0)
			mEnabled = 0;
    }
	update_delay();
	ALOGD("GyroelSensor enable %d ,usercount %d, handle %d ,mEnabled %d",en ,mUser, handle ,mEnabled);
    return err;
}

int GyroSensor::setDelay(int32_t handle, int64_t ns)
{
    if (ns < 0)
        return -EINVAL;

    mDelay = ns;
    return update_delay();
}

int GyroSensor::update_delay()
{
    return set_delay(mDelay);
}

int GyroSensor::readEvents(sensors_event_t* data, int count)
{
    if (count < 1)
        return -EINVAL;

    ssize_t n = mInputReader.fill(data_fd);
    if (n < 0)
        return n;

    int numEventReceived = 0;
    input_event const* event;
    while (count && mInputReader.readEvent(&event)) {
        int type = event->type;
        if ((type == EV_ABS) || (type == EV_REL) || (type == EV_KEY)) {
            processEvent(event->code, event->value);
            mInputReader.next();
        } else if (type == EV_SYN) {
            int64_t time = timevalToNano(event->time);
			if (mPendingMask) {
				mPendingMask = 0;
				mPendingEvent.timestamp = time;
				if (mEnabled) {
					*data++ = mPendingEvent;
					count--;
					numEventReceived++;
				}
			}
            if (!mPendingMask) {
                mInputReader.next();
            }
        } else {
            ALOGE("GyroSensor: unknown event (type=%d, code=%d)",
                    type, event->code);
            mInputReader.next();
        }
    }

    return numEventReceived;
}

void GyroSensor::processEvent(int code, int value)
{

    switch (code) {
        case GYRO_EVENT_X :
            mPendingMask = 1;
            mPendingEvent.gyro.x =  value * CONVERT_GYRO_X;
            break;
        case GYRO_EVENT_Y :
            mPendingMask = 1;
            mPendingEvent.gyro.y =  value * CONVERT_GYRO_Y;
            break;
        case GYRO_EVENT_Z :
            mPendingMask = 1;
            mPendingEvent.gyro.z =  value * CONVERT_GYRO_Z;
            break;
		defualt:
			break;
    }
}

int GyroSensor::writeEnable(int isEnable) {
	/*char attr[PATH_MAX] = {'\0'};
	if(mClassPath[0] == '\0')
		return -1;

	strcpy(attr, mClassPath);
	strcat(attr,"/");
	strcat(attr,GYRO_SYSFS_ENABLE);

	int fd = open(attr, O_RDWR);
	if (0 > fd) {
		ALOGE("Could not open (write-only) SysFs attribute \"%s\" (%s).", attr, strerror(errno));
		return -errno;
	}

	char buf[2];

	if (isEnable) {
		buf[0] = '1';
	} else {
		buf[0] = '0';
	}
	buf[1] = '\0';

	int err = 0;
	err = write(fd, buf, sizeof(buf));

	if (0 > err) {
		err = -errno;
		ALOGE("Could not write SysFs attribute \"%s\" (%s).", attr, strerror(errno));
	} else {
		err = 0;
	}

	close(fd);

	return err;*/
	return 0;
}

int GyroSensor::writeDelay(int64_t ns) {
	char attr[PATH_MAX] = {'\0'};
	if(mClassPath[0] == '\0')
		return -1;

	strcpy(attr, mClassPath);
	strcat(attr,"/");
	strcat(attr,GYRO_SYSFS_DELAY);

	int fd = open(attr, O_RDWR);
	if (0 > fd) {
		ALOGE("Could not open (write-only) SysFs attribute \"%s\" (%s).", attr, strerror(errno));
		return -errno;
	}
	if (ns > 10240000000LL) {
		ns = 10240000000LL; /* maximum delay in nano second. */
	}
	if (ns < 312500LL) {
		ns = 312500LL; /* minimum delay in nano second. */
	}

    char buf[80];
    sprintf(buf, "%lld", ns/1000/1000);
    write(fd, buf, strlen(buf)+1);
    close(fd);
    return 0;

}

int GyroSensor::enable_sensor() {
	return writeEnable(1);
}

int GyroSensor::disable_sensor() {
	return writeEnable(0);
}

int GyroSensor::set_delay(int64_t ns) {
	return writeDelay(ns);
}

int GyroSensor::getEnable(int32_t handle) {
	return (handle == ID_GY) ? mEnabled : 0;
}

int GyroSensor::sensor_get_class_path(char *class_path)
{
	char dirname[] = GYRO_SYSFS_PATH;
	char buf[256];
	int res;
	DIR *dir;
	struct dirent *de;
	int fd = -1;
	int found = 0;

	dir = opendir(dirname);
	if (dir == NULL)
		return -1;

	while((de = readdir(dir))) {

		sprintf(class_path, "%s/%s", dirname, de->d_name);
		snprintf(buf, sizeof(buf), "%s/name", class_path);

		fd = open(buf, O_RDONLY);
		if (fd < 0) {
		    continue;
		}
		if ((res = read(fd, buf, sizeof(buf))) < 0) {
		    close(fd);
		    continue;
		}
		buf[res - 1] = '\0';
		if (strcmp(buf, GYRO_DATA_NAME) == 0) {
		    found = 1;
		    close(fd);
		    break;
		}

		close(fd);
		fd = -1;
	}
	closedir(dir);
	//ALOGE("the G sensor dir is %s",class_path);

	if (found) {
		return 0;
	}else {
		*class_path = '\0';
		return -1;
	}
}

/*****************************************************************************/

