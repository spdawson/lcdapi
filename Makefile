PROJECT_ROOT = .

PROJECT_VERSION = 0.2

AR = ar
CC = g++
LD = g++
MAKE_DOC = doxygen
MKDIR = mkdir -p
RM = rm -rf
MV = mv
CP = cp -R
MK_TAR = tar zcf $(TAR_FILE)
CLEAN_BACKUPS = find . -type f | grep "~$\" | xargs rm -f
INCFLAGS = -I$(INCLUDE_DIR) -I$(SRC_DIR) -I$(KEYS_SRC_DIR)
CFLAGS = -fPIC $(INCFLAGS) -g
LDFLAGS = -shared
DEPEND= makedepend -Y $(INCFLAGS)

INCLUDE_DIR = $(PROJECT_ROOT)/include
SRC_DIR = $(PROJECT_ROOT)/api
SENSOR_SRC_DIR = $(PROJECT_ROOT)/sensors
KEYS_SRC_DIR = $(PROJECT_ROOT)/keys
EXAMPLE_DIR = $(PROJECT_ROOT)/example
OBJ_DIR = $(PROJECT_ROOT)/obj
LIB_DIR = $(PROJECT_ROOT)/lib
DOC_DIR = $(PROJECT_ROOT)/doc
LIB_NAME = liblcdapi.so

DELIVERY_DIR = lcdapi-$(PROJECT_VERSION)
DELIVERED = $(SRC_DIR) $(SENSOR_SRC_DIR) $(KEYS_SRC_DIR) $(EXAMPLE_DIR) $(DOC_DIR) $(INCLUDE_DIR) COPYING CHANGELOG Makefile

TAR_FILE = $(DELIVERY_DIR).tar.gz
DOC_CONFIG = Doxyfile

LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

LIB_SRCS = $(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SENSOR_SRC_DIR)/*.cpp) $(wildcard $(KEYS_SRC_DIR)/*.cpp)
LIB_OBJS = $(LIB_SRCS:%.cpp=$(OBJ_DIR)/%.o)

all: $(LIB_TARGET) doc

clean:
	$(RM) $(OBJ_DIR) $(LIB_DIR) core

depend: $(LIB_SRCS)
	$(DEPEND) $(LIB_SRCS) 2>/dev/null

docs: doc_clean
	cd $(DOC_DIR); \
	$(MAKE_DOC) $(DOC_CONFIG)

doc_clean:
	cd $(DOC_DIR); \
	$(RM) html

deliver: clean doc_clean
	$(CLEAN_BACKUPS)
	$(RM) $(TAR_FILE)
	$(MKDIR) $(DELIVERY_DIR)
	$(CP) $(DELIVERED) $(DELIVERY_DIR)
	$(MK_TAR) $(DELIVERY_DIR)
	$(RM) $(DELIVERY_DIR)

$(LIB_TARGET): $(LIB_OBJS)
	@$(MKDIR) $(LIB_DIR)
	$(LD) $(LDFLAGS) -o $(LIB_TARGET) $(LIB_OBJS)


$(OBJ_DIR)/%.o: %.cpp
	@$(MKDIR) $(OBJ_DIR)/api $(OBJ_DIR)/sensors $(OBJ_DIR)/keys
	$(CC) $(CFLAGS) $(INC_FLAGS) -c -o $@ $<


# DO NOT DELETE

./api/LCDBar.o: ./api/LCDBar.h ./api/LCDWidget.h ./api/LCDElement.h
./api/LCDBar.o: ./api/LCDMutex.h
./api/LCDBigNumber.o: ./api/LCDBigNumber.h ./api/LCDWidget.h
./api/LCDBigNumber.o: ./api/LCDElement.h ./api/LCDMutex.h
./api/LCDClient.o: ./api/LCDClient.h ./api/LCDConnection.h ./api/LCDElement.h
./api/LCDClient.o: ./api/LCDMutex.h ./api/LCDLock.h ./api/LCDException.h
./api/LCDClient.o: ./include/LCDConstants.h
./api/LCDConnection.o: ./api/LCDConnection.h ./api/LCDException.h
./api/LCDConnection.o: ./include/LCDConstants.h
./api/LCDElement.o: ./api/LCDElement.h ./api/LCDMutex.h ./api/LCDLock.h
./api/LCDFrame.o: ./api/LCDFrame.h ./api/LCDWidget.h ./api/LCDElement.h
./api/LCDFrame.o: ./api/LCDMutex.h
./api/LCDHorizontalBar.o: ./api/LCDHorizontalBar.h ./api/LCDBar.h
./api/LCDHorizontalBar.o: ./api/LCDWidget.h ./api/LCDElement.h
./api/LCDHorizontalBar.o: ./api/LCDMutex.h
./api/LCDIcon.o: ./api/LCDIcon.h ./api/LCDWidget.h ./api/LCDElement.h
./api/LCDIcon.o: ./api/LCDMutex.h
./api/LCDMutex.o: ./api/LCDMutex.h
./api/LCDScreen.o: ./api/LCDScreen.h ./include/LCDConstants.h
./api/LCDScreen.o: ./api/LCDElement.h ./api/LCDMutex.h ./api/LCDUtils.h
./api/LCDScroller.o: ./api/LCDScroller.h ./api/LCDWidget.h ./api/LCDElement.h
./api/LCDScroller.o: ./api/LCDMutex.h
./api/LCDText.o: ./api/LCDText.h ./api/LCDWidget.h ./api/LCDElement.h
./api/LCDText.o: ./api/LCDMutex.h
./api/LCDTitle.o: ./api/LCDTitle.h ./api/LCDWidget.h ./api/LCDElement.h
./api/LCDTitle.o: ./api/LCDMutex.h
./api/LCDVerticalBar.o: ./api/LCDVerticalBar.h ./api/LCDBar.h
./api/LCDVerticalBar.o: ./api/LCDWidget.h ./api/LCDElement.h ./api/LCDMutex.h
./api/LCDWidget.o: ./api/LCDWidget.h ./api/LCDElement.h ./api/LCDMutex.h
./sensors/LCDCpuSensor.o: ./sensors/LCDCpuSensor.h ./sensors/LCDSensor.h
./sensors/LCDCpuSensor.o: ./api/LCDWidget.h ./api/LCDElement.h
./sensors/LCDCpuSensor.o: ./api/LCDMutex.h ./api/LCDUtils.h
./sensors/LCDKdeMultimediaSensor.o: ./sensors/LCDKdeMultimediaSensor.h
./sensors/LCDKdeMultimediaSensor.o: ./sensors/LCDSensor.h ./api/LCDWidget.h
./sensors/LCDKdeMultimediaSensor.o: ./api/LCDElement.h ./api/LCDMutex.h
./sensors/LCDKdeMultimediaSensor.o: ./api/LCDUtils.h
./sensors/LCDSensor.o: ./api/LCDWidget.h ./api/LCDElement.h ./api/LCDMutex.h
./sensors/LCDSensor.o: ./api/LCDUtils.h ./sensors/LCDSensor.h
./sensors/LCDSensor.o: ./api/LCDWidget.h
./sensors/LCDSystemSensor.o: ./sensors/LCDSystemSensor.h
./sensors/LCDSystemSensor.o: ./sensors/LCDSensor.h ./api/LCDWidget.h
./sensors/LCDSystemSensor.o: ./api/LCDElement.h ./api/LCDMutex.h
./sensors/LCDTimeSensor.o: ./sensors/LCDTimeSensor.h ./sensors/LCDSensor.h
./sensors/LCDTimeSensor.o: ./api/LCDWidget.h ./api/LCDElement.h
./sensors/LCDTimeSensor.o: ./api/LCDMutex.h
