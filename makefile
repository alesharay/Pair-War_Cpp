# Makefile for project using Pair-War Game

# Executables to create --------------------------------------------------
APP		  = $(BINDIR)main
LIB		  = $(BINDIR)cpukit.a

# Tools to use -----------------------------------------------------------
CPP		  = g++
AR		  = ar
RM		  = rm -f
MD 			= mkdir bin &&

# Directories ------------------------------------------------------------
APPDIR	= src/
BINDIR	= bin/
INCDIR	= include/
LIBDIR	= lib/

#Build source files ------------------------------------------------------
APPSRCS	= $(wildcard $(APPDIR)*.cpp)
LIBSRCS = $(wildcard $(LIBDIR)*.cpp)

# Build object files -----------------------------------------------------
APPOBJS = $(APPSRCS:.cpp=.o)
LIBOBJS = $(LIBSRCS:.cpp=.o)

# Flags ------------------------------------------------------------------
CFLAGS  = -std=c++0x -I include
LFLAGS  = -L lib $(LIB)

.PHONY: all clean app test run

# Explicit targets to follow ---------------------------------------------
all: $(APP) $(LIB)

$(LIB): $(LIBOBJS)
	$(MD)	$(AR) rvs $(LIB) $(LIBOBJS)

$(APP): $(APPOBJS) $(LIB)
	$(CPP) -o $(APP) $(APPOBJS) -pthread $(LFLAGS)

# Implicit targets to follow ---------------------------------------------
%.o:	%.cpp
	$(CPP) -c $< -o $@ $(CFLAGS)

# User targets to follow -------------------------------------------------
clean:
	$(RM) $(LIB) $(LIBOBJS) $(APP) $(APPOBJS) Log_File.txt -r bin/

run: all
	./$(APP) $(seed)