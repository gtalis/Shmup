EXECUTABLE     = shmup
INCLUDES       = ../src libpng

linux_SOURCES  := native.c main.c
linux_OBJECTS  := $(linux_SOURCES:.c=.o)

engine_SOURCES := $(wildcard ../src/*.c)
engine_OBJECTS := $(engine_SOURCES:.c=.o) 

libpng_SOURCES := $(wildcard libpng/*.c)
# Do not compile pngtest.c
libpng_SOURCES := $(filter-out libpng/pngtest.c,$(libpng_SOURCES))
libpng_OBJECTS := $(libpng_SOURCES:.c=.o)

SDL_CFLAGS ?= `sdl-config --cflags`
SDL_LDFLAGS ?= `sdl-config --libs`
ZLIB_CFLAGS ?= `pkg-config zlib --cflags`
ZLIB_LDFLAGS ?= `pkg-config zlib --libs`
OPENAL_CFLAGS ?= `pkg-config openal --cflags`
OPENAL_LDFLAGS ?= `pkg-config openal --libs`

CFLAGS   = -Wall -Wextra -Wmissing-prototypes -DLINUX $(addprefix -I,$(INCLUDES))
CFLAGS  += $(SDL_CFLAGS)  $(ZLIB_CFLAGS) $(OPENAL_CFLAGS)
LDFLAGS  =  $(SDL_LDFLAGS) $(ZLIB_LDFLAGS) $(OPENAL_LDFLAGS) -lGLESv1_CL -lGLESv1_CM -lSDL_mixer -lm -z

OBJECTS = $(linux_OBJECTS) $(engine_OBJECTS) $(libpng_OBJECTS)

all: $(EXECUTABLE)

.PHONY: debug
debug: CFLAGS += -g
debug: all

.PHONY: release
release: CFLAGS += -DRELEASE
release: all

shmup: $(OBJECTS)
	$(CC) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) -o $@ -c $(CFLAGS) $<

.PHONY: clean
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)

