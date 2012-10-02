BIN = client
INCLUDEDIRS = ../include
LIBDIR = ../lib
LIBS = stdc++ pthread lcdapi
CXXFLAGS = \
	$(foreach i,$(INCLUDEDIRS),-I$(i)) \
	-Wall -Wextra -Weffc++ -Wold-style-cast \
	-Werror -Wno-error=unused-parameter -Wno-error=unused-function
LDFLAGS = -L$(LIBDIR) $(foreach i,$(LIBS),-l$(i))
STRIP = strip

.PHONY: all clean

all: $(BIN)

$(BIN): $(BIN).o
	$(CXX) -o $@ $< $(LDFLAGS)
	$(STRIP) --strip-unneeded $(BIN)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -o $@ $<

clean:
	$(RM) $(BIN) $(BIN).o
