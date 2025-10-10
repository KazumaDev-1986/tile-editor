###########################################################################
##### Config
###########################################################################
APP 		:= tile-editor
C			:= gcc
SRCDIR		:= src
OBJDIR		:= obj
INCDIR		:= -I$(SRCDIR)/include
CFLAGS      := -Wall -Wextra
RFLAGS		:= -lopengl32 -lgdi32 -lwinmm 
MKDIR		:= mkdir -p

ifeq ($(OS),Windows_NT)
	LIBSDIR =$(SRCDIR)/lib/windows
else
	UNAMEOS = $(shell uname)
	ifeq ($(UNAMEOS),Linux)
		RFLAGS = -lGL -lm -lpthread -ldl -lrt -lX11 
		LIBSDIR =$(SRCDIR)/lib/linux 	
		LINUX := $(shell uname)
	endif
	ifeq ($(UNAMEOS),Darwin)
		RFLAGS = -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
		LIBSDIR =$(SRCDIR)/lib/macos
	endif
endif

ifdef LINUX
	LIBS := -L$(LIBSDIR) -lraylib
else
	LIBS := $(LIBSDIR)/libraylib.a
endif

ifdef RELEASE
	CFLAGS += -O3 -march=native
else
	CFLAGS += -pedantic -g #-fsanitize=address 
endif

CFLAGS += -std=c17

CFILES 		:= $(shell find $(SRCDIR)/ -type f -iname *.c)
OBJFILES	:= $(patsubst %.c,%.o,$(patsubst $(SRCDIR)%,$(OBJDIR)%,$(CFILES)))
SUBDIR		:= $(shell find $(SRCDIR)/ -type d)
OBJSUBDIRS	:= $(patsubst $(SRCDIR)%,$(OBJDIR)%,$(SUBDIR))

.PHONY: info clean cleanall

$(APP): $(OBJSUBDIRS) $(OBJFILES)
	$(C) $(OBJFILES) -o $(APP) $(CFLAGS) $(LIBS) $(RFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(C) -c $^ -o $(patsubst $(SRCDIR)%,%(OBJDIR),$@) $(INCDIR) $(CFLAGS)

$(OBJSUBDIRS):
	$(MKDIR) $(OBJSUBDIRS)

info:
	$(info $(CFILES))
	$(info $(OBJFILES))
	$(info $(OBJSUBDIR))

clean:
	rm -r $(OBJDIR)

cleanall:
	rm $(APP)
	rm -r $(OBJDIR)
