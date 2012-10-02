BIN = client
INCLUDEDIRS = ../include
LIBDIR = ../lib
CXXFLAGS = \
	$(foreach i,$(INCLUDEDIRS),-I$(i)) \
	-Wall -Wextra -Weffc++ -Wold-style-cast \
	-Werror -Wno-error=unused-parameter -Wno-error=unused-function
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
