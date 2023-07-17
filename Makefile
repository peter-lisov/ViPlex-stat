CC = g++
CFLAGS = -c -Wall `wx-config --cxxflags` 
LDFLAGS = -l sqlite3 `wx-config --libs`
SOURCES = main.cpp playlist.cpp screens.cpp
OBJECTS = $(SOURCES:.cpp=.o)
EXECUTABLE = ViPlex-stat

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o $(PROGRAM)
