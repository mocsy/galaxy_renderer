CC             = g++
MAKE           = make

INCLUDES       = -Iinclude

CFLAGS         = $(INCLUDES) -c -Wall -pedantic -std=c++11 -finput-charset=UTF-8 -DGLEW_STATIC -ggdb

LIB_PATHS      = -Llib
LIBS_STATIC_FREETYPE  = -lfreetype
LIBS_STATIC_OPENGL    = -lglew32 -lglfw3 -lopengl32
LIBS_STATIC_SYSTEM    =
LIBS_SHARED_FREETYPE  =
LIBS_SHARED_OPENGL    =
LIBS_SHARED_SYSTEM    =

ifeq ($(MSYSTEM), MINGW64)
	LIBS_STATIC_SYSTEM += -lwinmm -mwindows
else
endif

LIBS_STATIC    = -Wl,-Bstatic  $(LIBS_STATIC_FREETYPE) $(LIBS_STATIC_OPENGL) $(LIBS_STATIC_SYSTEM)
LIBS_SHARED    = -Wl,-Bdynamic $(LIBS_SHARED_FREETYPE) $(LIBS_SHARED_OPENGL) $(LIBS_SHARED_SYSTEM)
LIBS           = $(LIBS_STATIC) $(LIBS_SHARED)

LIBS_LIB       =
LDFLAGS        = ${LIB_PATHS} ${LIBS}
LDFLAGS_LIB    = ${LIB_PATHS} ${LIBS_LIB}


find = $(foreach dir,$(1),$(foreach d,$(wildcard $(dir)/*),$(call find,$(d),$(2))) $(wildcard $(dir)/$(strip $(2))))

SOURCES_LIB       = $(call find, src, *.cpp)
SOURCES           = main.cpp $(SOURCES_LIB)
OBJECTS           = $(SOURCES:.cpp=.o)
OBJECTS_LIB       = $(SOURCES_LIB:.cpp=.o)
STATIC_TARGET     = lib/libgalaxy_renderer.a
EXECUTABLE_TARGET = galaxy_renderer.exe


all: $(SOURCES) $(STATIC_TARGET) check $(EXECUTABLE_TARGET)
#	./$(EXECUTABLE_TARGET)


$(EXECUTABLE_TARGET): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS)


$(STATIC_TARGET): $(OBJECTS_LIB)
	ar rcs $@ $(OBJECTS_LIB)


check: $(STATIC_TARGET)
#	+$(MAKE) -C ./tests check


.cpp.o:
	$(CC) ${CFLAGS} $< -o $@


clean:
#	$(MAKE) -C ./tests clean
	rm -f $(OBJECTS_LIB)
	rm -f $(OBJECTS)
	rm -f $(STATIC_TARGET)
	rm -f $(EXECUTABLE_TARGET)
	rm -f gmon.out

