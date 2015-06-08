if HAVE_DOXYGEN
directory = $(top_srcdir)/docs/man/man3

dist_man_MANS = $(directory)/constants.3 $(directory)/keys.3 $(directory)/lcdapi_LCDBar.3 $(directory)/lcdapi_LCDBigNumber.3 \
	$(directory)/lcdapi_LCDCallback.3 $(directory)/lcdapi_LCDClient.3 $(directory)/lcdapi_LCDCpuSensor.3 $(directory)/lcdapi_LCDElement.3 \
	$(directory)/lcdapi_LCDException.3 $(directory)/lcdapi_LCDFrame.3 $(directory)/lcdapi_LCDHorizontalBar.3 $(directory)/lcdapi_LCDIcon.3 \
	$(directory)/lcdapi_LCDKdeMultimediaSensor.3 $(directory)/lcdapi_LCDLock.3 $(directory)/lcdapi_LCDMenuEventHandler.3 \
	$(directory)/lcdapi_LCDMutex.3 $(directory)/lcdapi_LCDScreen.3 $(directory)/lcdapi_LCDScroller.3 $(directory)/lcdapi_LCDSensor.3 \
	$(directory)/lcdapi_LCDSystemSensor.3 $(directory)/lcdapi_LCDText.3 $(directory)/lcdapi_LCDTimeSensor.3 $(directory)/lcdapi_LCDTitle.3 \
	$(directory)/lcdapi_LCDVerticalBar.3 $(directory)/lcdapi_LCDWidget.3 $(directory)/main.3 $(directory)/menu_constants.3 $(directory)/menus.3 \
	$(directory)/screen_constants.3 $(directory)/sensors.3 $(directory)/widgets.3
$(directory)/constants.3: doxyfile.stamp
$(directory)/keys.3: doxyfile.stamp
$(directory)/lcdapi_LCDBar.3: doxyfile.stamp
$(directory)/lcdapi_LCDBigNumber.3: doxyfile.stamp
$(directory)/lcdapi_LCDCallback.3: doxyfile.stamp
$(directory)/lcdapi_LCDClient.3: doxyfile.stamp
$(directory)/lcdapi_LCDCpuSensor.3: doxyfile.stamp
$(directory)/lcdapi_LCDElement.3: doxyfile.stamp
$(directory)/lcdapi_LCDException.3: doxyfile.stamp
$(directory)/lcdapi_LCDFrame.3: doxyfile.stamp
$(directory)/lcdapi_LCDHorizontalBar.3: doxyfile.stamp
$(directory)/lcdapi_LCDIcon.3: doxyfile.stamp
$(directory)/lcdapi_LCDKdeMultimediaSensor.3: doxyfile.stamp
$(directory)/lcdapi_LCDLock.3: doxyfile.stamp
$(directory)/lcdapi_LCDMenuEventHandler.3: doxyfile.stamp
$(directory)/lcdapi_LCDMutex.3: doxyfile.stamp
$(directory)/lcdapi_LCDScreen.3: doxyfile.stamp
$(directory)/lcdapi_LCDScroller.3: doxyfile.stamp
$(directory)/lcdapi_LCDSensor.3: doxyfile.stamp
$(directory)/lcdapi_LCDSystemSensor.3: doxyfile.stamp
$(directory)/lcdapi_LCDText.3: doxyfile.stamp
$(directory)/lcdapi_LCDTimeSensor.3: doxyfile.stamp
$(directory)/lcdapi_LCDTitle.3: doxyfile.stamp
$(directory)/lcdapi_LCDVerticalBar.3: doxyfile.stamp
$(directory)/lcdapi_LCDWidget.3: doxyfile.stamp
$(directory)/main.3: doxyfile.stamp
$(directory)/menu_constants.3: doxyfile.stamp
$(directory)/menus.3: doxyfile.stamp
$(directory)/screen_constants.3: doxyfile.stamp
$(directory)/sensors.3: doxyfile.stamp
$(directory)/widgets.3: doxyfile.stamp

doxyfile.stamp:
	$(DOXYGEN) Doxyfile
	echo Timestamp > doxyfile.stamp

CLEANFILES = doxyfile.stamp

all-local: doxyfile.stamp
clean-local:
	$(RM) -r $(top_srcdir)/docs/man
	$(RM) -r $(top_srcdir)/docs/html
endif
