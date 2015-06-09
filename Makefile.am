SUBDIRS = docs

lib_LTLIBRARIES = liblcdapi.la
liblcdapi_la_SOURCES = \
	lcdapi/api/LCDBar.cpp \
	lcdapi/api/LCDBigNumber.cpp \
	lcdapi/api/LCDClient.cpp \
	lcdapi/api/LCDConnection.cpp \
	lcdapi/api/LCDElement.cpp \
	lcdapi/api/LCDException.cpp \
	lcdapi/api/LCDFrame.cpp \
	lcdapi/api/LCDHorizontalBar.cpp \
	lcdapi/api/LCDIcon.cpp \
	lcdapi/api/LCDLock.cpp \
	lcdapi/api/LCDMutex.cpp \
	lcdapi/api/LCDScreen.cpp \
	lcdapi/api/LCDScroller.cpp \
	lcdapi/api/LCDText.cpp \
	lcdapi/api/LCDTitle.cpp \
	lcdapi/api/LCDUtils.cpp \
	lcdapi/api/LCDVerticalBar.cpp \
	lcdapi/api/LCDWidget.cpp \
	lcdapi/sensors/LCDCpuSensor.cpp \
	lcdapi/sensors/LCDKdeMultimediaSensor.cpp \
	lcdapi/sensors/LCDSensor.cpp \
	lcdapi/sensors/LCDSystemSensor.cpp \
	lcdapi/sensors/LCDTimeSensor.cpp

lcdapiincludedir = $(includedir)/lcdapi/include
lcdapiinclude_HEADERS = \
	lcdapi/include/LCDConstants.h \
	lcdapi/include/LCDHeaders.h
lcdapiapidir = $(includedir)/lcdapi/api
lcdapiapi_HEADERS = \
	lcdapi/api/LCDBar.h \
	lcdapi/api/LCDBigNumber.h \
	lcdapi/api/LCDClient.h \
	lcdapi/api/LCDConnection.h \
	lcdapi/api/LCDElement.h \
	lcdapi/api/LCDException.h \
	lcdapi/api/LCDFrame.h \
	lcdapi/api/LCDHorizontalBar.h \
	lcdapi/api/LCDIcon.h \
	lcdapi/api/LCDLock.h \
	lcdapi/api/LCDMutex.h \
	lcdapi/api/LCDScreen.h \
	lcdapi/api/LCDScroller.h \
	lcdapi/api/LCDText.h \
	lcdapi/api/LCDTitle.h \
	lcdapi/api/LCDUtils.h \
	lcdapi/api/LCDVerticalBar.h \
	lcdapi/api/LCDWidget.h
lcdapikeysdir = $(includedir)/lcdapi/keys
lcdapikeys_HEADERS = \
	lcdapi/keys/LCDCallback.h
lcdapimenusdir = $(includedir)/lcdapi/menus
lcdapimenus_HEADERS = \
	lcdapi/menus/LCDMenuEventHandler.h
lcdapisensorsdir = $(includedir)/lcdapi/sensors
lcdapisensors_HEADERS = \
	lcdapi/sensors/LCDCpuSensor.h \
	lcdapi/sensors/LCDKdeMultimediaSensor.h \
	lcdapi/sensors/LCDSensor.h \
	lcdapi/sensors/LCDSystemSensor.h \
	lcdapi/sensors/LCDTimeSensor.h

liblcdapi_la_CXXFLAGS = \
	-Wall -Wextra -Weffc++ -Wold-style-cast \
	-Werror -Wno-error=unused-parameter -Wno-error=unused-function \
	-fdiagnostics-color=always \
	-fPIC \
	-g0 -DNODEBUG -Os

ACLOCAL_AMFLAGS = -I m4

docsdir = $(datarootdir)/doc/$(PACKAGE)
exampledir = $(pkgdatadir)/examples

htmldocs := $(shell find docs/html -mindepth 1)

dist_docs_DATA = \
	$(htmldocs)
dist_example_DATA = \
	example/client.cpp
