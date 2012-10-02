BIN = client
INCLUDEDIRS = ../include
LIBDIR = ../lib
CXXFLAGS = \
	$(foreach i,$(INCLUDEDIRS),-I$(i))
LDFLAGS = \
	-L$(LIBDIR) -lstdc++ -lpthread -llcdapi

.PHONY: all clean

all: $(BIN)

$(BIN): $(BIN).o
	$(CXX) -o $@ $< $(LDFLAGS)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(BIN) $(BIN).o
