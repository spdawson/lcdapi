lib_LTLIBRARIES = liblcdapi.la
liblcdapi_la_SOURCES = \
	api/LCDBar.cpp \
	api/LCDBigNumber.cpp \
	api/LCDClient.cpp \
	api/LCDConnection.cpp \
	api/LCDElement.cpp \
	api/LCDException.cpp \
	api/LCDFrame.cpp \
	api/LCDHorizontalBar.cpp \
	api/LCDIcon.cpp \
	api/LCDLock.cpp \
	api/LCDMutex.cpp \
	api/LCDScreen.cpp \
	api/LCDScroller.cpp \
	api/LCDText.cpp \
	api/LCDTitle.cpp \
	api/LCDUtils.cpp \
	api/LCDVerticalBar.cpp \
	api/LCDWidget.cpp \
	sensors/LCDCpuSensor.cpp \
	sensors/LCDKdeMultimediaSensor.cpp \
	sensors/LCDSensor.cpp \
	sensors/LCDSystemSensor.cpp \
	sensors/LCDTimeSensor.cpp

lcdapiincludedir = $(includedir)/lcdapi/include
lcdapiinclude_HEADERS = \
	include/LCDConstants.h \
	include/LCDHeaders.h
lcdapiapidir = $(includedir)/lcdapi/api
lcdapiapi_HEADERS = \
	api/LCDBar.h \
	api/LCDBigNumber.h \
	api/LCDClient.h \
	api/LCDConnection.h \
	api/LCDElement.h \
	api/LCDException.h \
	api/LCDFrame.h \
	api/LCDHorizontalBar.h \
	api/LCDIcon.h \
	api/LCDLock.h \
	api/LCDMutex.h \
	api/LCDScreen.h \
	api/LCDScroller.h \
	api/LCDText.h \
	api/LCDTitle.h \
	api/LCDUtils.h \
	api/LCDVerticalBar.h \
	api/LCDWidget.h
lcdapikeysdir = $(includedir)/lcdapi/keys
lcdapikeys_HEADERS = \
	keys/LCDCallback.h
lcdapimenusdir = $(includedir)/lcdapi/menus
lcdapimenus_HEADERS = \
	menus/LCDMenuEventHandler.h
lcdapisensorsdir = $(includedir)/lcdapi/sensors
lcdapisensors_HEADERS = \
	sensors/LCDCpuSensor.h \
	sensors/LCDKdeMultimediaSensor.h \
	sensors/LCDSensor.h \
	sensors/LCDSystemSensor.h \
	sensors/LCDTimeSensor.h

liblcdapi_la_CXXFLAGS = \
	-Wall -Wextra -Weffc++ -Wold-style-cast \
	-Werror -Wno-error=unused-parameter -Wno-error=unused-function \
	-fPIC \
	-g0 -DNODEBUG -Os

ACLOCAL_AMFLAGS = -I m4
