AUTOMAKE_OPTIONS = subdir-objects

bin_PROGRAMS = client
client_SOURCES = client.cpp
client_LDFLAGS = -L.. -lpthread -llcdapi
client_CXXFLAGS = -I../include \
	-Wall -Wextra -Weffc++ -Wold-style-cast \
	-Werror
