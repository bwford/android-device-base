
#include <errno.h>
#define  LOG_TAG  "libzhw"
#include <cutils/log.h>
#include <cutils/sockets.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include <hardware/libzhw.h>

#include "i2c-dev.h"

#define LIBZHW_DEBUG 1

#if LIBZHW_DEBUG
#  define D(...)   ALOGD(__VA_ARGS__)
#else
#  define D(...)   ((void)0)
#endif

#define PRESSURE_ADDR 0x28
#define POW_MICRO_ADDR 0x42

const char* bus3name = "/dev/i2c-3";
int bus3fd = 0;


int sciaps_read_micro(uint8_t address, uint8_t* buffer, int length)
{
	int bytesRead;

	if(ioctl(bus3fd, I2C_SLAVE, POW_MICRO_ADDR) < 0){
		ALOGE("failed to acquire bus address: 0x%x", POW_MICRO_ADDR);
		return -1;
	}

	if((bytesRead = write(bus3fd, &address, 1)) != 1){
		ALOGE("failed to write address to micro: %d", bytesRead);
		return -1;
	}

	bytesRead = read(bus3fd, buffer, length);
	if(bytesRead != length){
		ALOGW("read %d bytes", bytesRead);
	}

	return bytesRead;
}

int sciaps_write_micro(uint8_t address, uint8_t* buffer, int length)
{
	if(ioctl(bus3fd, I2C_SLAVE, POW_MICRO_ADDR) < 0){
		ALOGE("failed to acquire bus address: 0x%x", POW_MICRO_ADDR);
		return -1;
	}

	uint8_t writeBuffer[256];
	writeBuffer[0] = address;
	memcpy(&writeBuffer[1], buffer, length);

	int bytesWritten = write(bus3fd, writeBuffer, length+1);
	if(bytesWritten-1 != length) {
		ALOGW("wrote %d bytes", bytesWritten);
	}

	return bytesWritten-1;
}

int sciaps_read_pressure(uint8_t* buffer, int length)
{
	if(buffer == NULL || length < 2 || length > 4){
		ALOGE("buffer must be 2 or 4 bytes");
		return -1;
	}

	if(ioctl(bus3fd, I2C_SLAVE, PRESSURE_ADDR) < 0){
		ALOGE("failed to acquire bus address: 0x%x", PRESSURE_ADDR);
		return -1;
	}

	int bytesRead = read(bus3fd, buffer, length);
	if(bytesRead != length){
		ALOGW("wrote %d bytes", bytesRead);
	}

	return bytesRead;
}

static int close_libzhw(struct hw_device_t* device)
{
	return 0;
}

static int open_libzhw(const struct hw_module_t* module, char const* name,
	struct hw_device_t** device)
{
	ALOGD("in open_libzhw");
	struct libzhw_device_t* dev;
	dev = calloc(1, sizeof(struct libzhw_device_t));
	if(!dev) {
		return -ENOMEM;
	}

	dev->common.tag = HARDWARE_DEVICE_TAG;
	dev->common.version = 0;
	dev->common.module = (struct hw_module_t*)module;
	dev->common.close = close_libzhw;

	dev->read_micro = sciaps_read_micro;
	dev->write_micro = sciaps_write_micro;
	dev->read_pressure = sciaps_read_pressure;

	*device = &dev->common;

	D("LIBZ HW start initialization process...");

	if((bus3fd = open(bus3name, O_RDWR)) < 0){
		ALOGE("could not open %s\n", bus3name);
		return -1;
	}

	D("LIBZ HW initialization successful");

	return 0;
}

static struct hw_module_methods_t module_methods = {
	.open = open_libzhw
};

struct hw_module_t HAL_MODULE_INFO_SYM = {
	.tag = HARDWARE_MODULE_TAG,
	.version_major = 1,
	.version_minor = 0,
	.id = SCIAPS_LIBZHW_MODULE_ID,
	.name = "Sciaps LIBZ HW Module",
	.author = "SciAps (Paul Soucy)",
	.methods = &module_methods
};