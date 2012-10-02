PROJECT_ROOT = .

PROJECT_VERSION = 0.3

INCFLAGS = -I$(INCLUDE_DIR) -I$(SRC_DIR) -I$(KEYS_SRC_DIR)
CFLAGS = -g \
	-Wall -Wextra -Weffc++ -Wold-style-cast -Werror -Wno-error=unused-parameter -Wno-error=unused-function
INSTALL = install
STRIP = strip

DESTDIR = /
INCLUDE_DIR = $(PROJECT_ROOT)/include
SRC_DIR = $(PROJECT_ROOT)/api
SENSOR_SRC_DIR = $(PROJECT_ROOT)/sensors
KEYS_SRC_DIR = $(PROJECT_ROOT)/keys
EXAMPLE_DIR = $(PROJECT_ROOT)/example
OBJ_DIR = $(PROJECT_ROOT)/obj
LIB_DIR = $(PROJECT_ROOT)/lib
DOC_DIR = $(PROJECT_ROOT)/doc
DEPEND_DIR = $(PROJECT_ROOT)/depend
PROJECT_NAME = lcdapi
LIB_NAME = lib$(PROJECT_NAME).so
LIBS = stdc++ pthread

DELIVERY_DIR = $(PROJECT_NAME)-$(PROJECT_VERSION)
DELIVERED = \
	$(SRC_DIR) \
	$(SENSOR_SRC_DIR) \
	$(KEYS_SRC_DIR) \
	$(EXAMPLE_DIR) \
	$(DOC_DIR) \
	$(INCLUDE_DIR) \
	COPYING \
	CHANGELOG \
	Makefile

TAR_FILE = $(DELIVERY_DIR).tar.gz
DOC_CONFIG = Doxyfile

LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

LIB_SRCS = \
	$(wildcard $(SRC_DIR)/*.cpp) \
	$(wildcard $(SENSOR_SRC_DIR)/*.cpp) \
	$(wildcard $(KEYS_SRC_DIR)/*.cpp)
LIB_OBJS = $(LIB_SRCS:%.cpp=$(OBJ_DIR)/%.o)
LIB_DEPENDS = $(LIB_SRCS:%.cpp=$(DEPEND_DIR)/%.d)

.PHONY: all clean depend docs doc_clean deliver install uninstall
all: $(LIB_TARGET)

clean:
	$(RM) -r $(DEPEND_DIR) $(OBJ_DIR) $(LIB_DIR) core

depend: $(LIB_DEPENDS)

docs: doc_clean
	cd $(DOC_DIR); \
	doxygen $(DOC_CONFIG)

doc_clean:
	$(RM) -r $(DOC_DIR)/html

deliver: clean doc_clean
	find . -type f -name '*~' -delete
	$(RM) $(TAR_FILE)
	mkdir -p $(DELIVERY_DIR)
	cp -R $(DELIVERED) $(DELIVERY_DIR)
	tar caf $(TAR_FILE) $(DELIVERY_DIR)
	$(RM) -r $(DELIVERY_DIR)

$(LIB_TARGET): depend $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	$(CXX) $(LDFLAGS) -shared -o $(LIB_TARGET) $(LIB_OBJS) $(foreach i,$(LIBS),-l$(i))
	$(STRIP) --strip-unneeded $(LIB_TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(OBJ_DIR)/api $(OBJ_DIR)/sensors $(OBJ_DIR)/keys
	$(CXX) $(CFLAGS) $(INCFLAGS) -c -o $@ $<

$(DEPEND_DIR)/%.d: %.cpp
	@mkdir -p $(DEPEND_DIR)/api $(DEPEND_DIR)/sensors $(DEPEND_DIR)/keys
	$(CXX) $(CFLAGS) $(INCFLAGS) -MM -MP $< > $@

install:
	$(INSTALL) -m 0755 -d $(DESTDIR)/usr/lib
	$(INSTALL) -m 0755 -t $(DESTDIR)/usr/lib $(LIB_DIR)/$(LIB_NAME)
	$(INSTALL) -m 0755 -d $(DESTDIR)/usr/include/$(PROJECT_NAME)
	for i in api include keys sensors; do \
		$(INSTALL) -m 0755 -d $(DESTDIR)/usr/include/$(PROJECT_NAME)/$$i && \
		$(INSTALL) -m 0644 -t $(DESTDIR)/usr/include/$(PROJECT_NAME)/$$i \
			$(PROJECT_ROOT)/$$i/*.h; \
	done

uninstall:
	$(RM) $(DESTDIR)/usr/lib/$(LIB_NAME)
	$(RM) -r $(DESTDIR)/usr/include/$(PROJECT_NAME)

ifdef LIB_DEPENDS

ifneq (depend, $(MAKECMDGOALS))
ifneq (clean, $(MAKECMDGOALS))
ifneq (0, $(MAKELEVEL))
# Don't whinge if any of the files to be included are missing.
-include $(LIB_DEPENDS)
endif
endif
endif

endif
