BIN = client
INCLUDEDIRS = ../include
LIBDIR = ../lib
CXXFLAGS = \
	$(foreach i,$(INCLUDEDIRS),-I$(i)) -L$(LIBDIR) -lstdc++ -lpthread -llcdapi

.PHONY: all clean

all: $(BIN)

clean:
	$(RM) $(BIN)
