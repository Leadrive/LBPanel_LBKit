DEBUG_OPTIONS = -g -Wall
OPTIMIZE = -O3

UCLIBCXX_INCLUDES = -I../include/uClibc\+\+

# run "ln -sf /usr/lib/libuClibc++.so.0 /usr/lib/libuClibc++.so" to make this work
UCLIBCXX_LIBS = -luClibc\+\+

SINGLE_C_FILE_PROGRAMS =
SINGLE_CXX_FILE_PROGRAMS = helloworld
SINGLE_FILE_PROGRAMS = $(SINGLE_C_FILE_PROGRAMS) $(SINGLE_CXX_FILE_PROGRAMS)

TARGET_1 =
TARGET_2 =
TARGET_3 =

OBJECTS_1 =
OBJECTS_2 =
OBJECTS_3 =

TARGET = $(TARGET_1) $(TARGET_2) $(TARGET_3)
OBJECTS = $(OBJECTS_1) $(OBJECTS_2) $(OBJECTS_3)

CC = ${CROSS_COMPILE}gcc
CXX = ${CROSS_COMPILE}g++
LD = ${CROSS_COMPILE}ld

CFLAGS = $(DEBUG_OPTIONS) $(OPTIMIZE)
CXXFLAGS = $(DEBUG_OPTIONS) $(OPTIMIZE)
LDFLAGS =

LITE_BEAPI_CFLAGS = $(shell lite-beapi-config --cflags)
LITE_BEAPI_LIBS = $(shell lite-beapi-config --libs)

CFLAGS += $(LITE_BEAPI_CFLAGS)
CXXFLAGS += $(LITE_BEAPI_CFLAGS) $(UCLIBCXX_INCLUDES)
LDFLAGS += $(LITE_BEAPI_LIBS) -llbk

all: targets $(TARGET)

$(C_PROGRAM): $(C_PROGRAM).o
	$(CC) $(DEBUG_OPTIONS) $(OPTIMIZE) $^ -o $@ $(LDFLAGS)

$(CXX_PROGRAM): $(CXX_PROGRAM).o
	$(CXX) $(DEBUG_OPTIONS) $(OPTIMIZE) $^ -o $@ $(LDFLAGS) $(UCLIBCXX_LIBS)

targets:
	for f in $(SINGLE_C_FILE_PROGRAMS) .none; do \
		(test $$f = .none || CC=$(CC) $(MAKE) C_PROGRAM=$$f $$f) \
	done
	for f in $(SINGLE_CXX_FILE_PROGRAMS) .none; do \
		(test $$f = .none || CXX=$(CXX) $(MAKE) CXX_PROGRAM=$$f $$f) \
	done

$(TARGET_1): $(OBJECTS_1)
	$(CXX) $(DEBUG_OPTIONS) $(OPTIMIZE) $^ -o $@ $(LDFLAGS)

$(TARGET_2): $(OBJECTS_2)
	$(CXX) $(DEBUG_OPTIONS) $(OPTIMIZE) $^ -o $@ $(LDFLAGS)

$(TARGET_3): $(OBJECTS_3)
	$(CXX) $(DEBUG_OPTIONS) $(OPTIMIZE) $^ -o $@ $(LDFLAGS)

clean:
	for f in $(TARGET) $(OBJECTS) .none; do \
		(test $$f = .none || test ! -e "$$f" || rm -f $$f); \
	done
	for f in $(SINGLE_FILE_PROGRAMS) $(TARGET) .none; do \
		(test $$f = .none || test ! -e "$$f" || rm -f $$f); \
		(test $$f = .none || test ! -e "$$f.o" || rm -f $$f.o); \
	done

.SUFFIXES: .c .cpp .cxx .cc .o
.c.o:
	$(CC) $(CFLAGS) -c $< -o $@

.cpp.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.cxx.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

.cc.o:
	$(CXX) $(CXXFLAGS) -c $< -o $@

