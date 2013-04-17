PROJECT_ROOT = .

PROJECT_VERSION = 0.5

CXXINCFLAGS = -I$(INCLUDE_DIR) $(foreach i,$(SRC_DIRS),-I$(i))
CXXWARNFLAGS = \
	-Wall -Wextra -Weffc++ -Wold-style-cast \
	-Werror -Wno-error=unused-parameter -Wno-error=unused-function
INSTALL = install
STRIP = strip

DESTDIR = /
COMPONENTS = api keys menus sensors
INCLUDE_DIR = $(PROJECT_ROOT)/include
SRC_DIRS = $(foreach i,$(COMPONENTS),$(PROJECT_ROOT)/$(i))
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
	$(SRC_DIRS) \
	$(EXAMPLE_DIR) \
	$(DOC_DIR) \
	$(INCLUDE_DIR) \
	COPYING \
	ChangeLog \
	Makefile

TAR_FILE = $(DELIVERY_DIR).tar.gz
DOC_CONFIG = Doxyfile

LIB_TARGET = $(LIB_DIR)/$(LIB_NAME)

LIB_SRCS = $(foreach i,$(SRC_DIRS),$(wildcard $(i)/*.cpp))
LIB_OBJS = $(LIB_SRCS:%.cpp=$(OBJ_DIR)/%.o)
LIB_DEPENDS = $(LIB_SRCS:%.cpp=$(DEPEND_DIR)/%.d)

.PHONY: all development release clean docs doc_clean deliver install uninstall
all: release

development release: $(LIB_TARGET)

development: CXXDEBUGFLAGS += -g3 -DDEBUG -O0
release: CXXDEBUGFLAGS += -g0 -DNODEBUG -Os

clean:
	find . -type f -name '*~' -delete
	$(RM) -r $(DEPEND_DIR) $(OBJ_DIR) $(LIB_DIR)

docs: doc_clean
	cd $(DOC_DIR); \
	doxygen $(DOC_CONFIG)

doc_clean:
	$(RM) -r $(DOC_DIR)/html

deliver: clean doc_clean
	$(RM) $(TAR_FILE)
	mkdir -p $(DELIVERY_DIR)
	cp -R $(DELIVERED) $(DELIVERY_DIR)
	tar caf $(TAR_FILE) $(DELIVERY_DIR)
	$(RM) -r $(DELIVERY_DIR)

$(LIB_TARGET): $(LIB_DEPENDS) $(LIB_OBJS)
	mkdir -p $(LIB_DIR)
	$(CXX) $(LDFLAGS) -shared -o $@ \
		$(LIB_OBJS) $(foreach i,$(LIBS),-l$(i))
	$(STRIP) --strip-unneeded $@

FULL_CXXFLAGS = \
	$(CXXFLAGS) $(CXXDEBUGFLAGS) -fPIC $(CXXWARNFLAGS) $(CXXINCFLAGS)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(foreach i,$(COMPONENTS),$(OBJ_DIR)/$(i))
	$(CXX) $(FULL_CXXFLAGS) -c -o $@ $<

$(DEPEND_DIR)/%.d: %.cpp
	@mkdir -p $(foreach i,$(COMPONENTS),$(DEPEND_DIR)/$(i))
	$(CXX) $(FULL_CXXFLAGS) -MM -MP $< | \
		sed -r -e "s,^(\w+\.o:),$(OBJ_DIR)/\1," > $@

install:
	$(INSTALL) -m 0755 -d $(DESTDIR)/usr/lib
	$(INSTALL) -m 0755 -t $(DESTDIR)/usr/lib $(LIB_DIR)/$(LIB_NAME)
	$(INSTALL) -m 0755 -d $(DESTDIR)/usr/include/$(PROJECT_NAME)
	for i in include $(COMPONENTS); do \
		$(INSTALL) -m 0755 -d $(DESTDIR)/usr/include/$(PROJECT_NAME)/$$i && \
		$(INSTALL) -m 0644 -t $(DESTDIR)/usr/include/$(PROJECT_NAME)/$$i \
			$(PROJECT_ROOT)/$$i/*.h; \
	done

uninstall:
	$(RM) $(DESTDIR)/usr/lib/$(LIB_NAME)
	$(RM) -r $(DESTDIR)/usr/include/$(PROJECT_NAME)

ifdef LIB_DEPENDS

ifneq (clean, $(MAKECMDGOALS))
# Don't whinge if any of the files to be included are missing.
-include $(LIB_DEPENDS)
endif

endif
