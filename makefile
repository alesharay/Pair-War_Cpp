# Makefile for project using pthreads

# Executables to create --------------------------------------------------
APP		  = $(BINDIR)main
LIB		  = $(BINDIR)cpukit.a
TST		  = $(BINDIR)test

# Tools to use -----------------------------------------------------------
CPP		  = g++
AR		  = ar
RM		  = rm -f

# Directories ------------------------------------------------------------
APPDIR	= src/
BINDIR	= bin/
INCDIR	= include/
LIBDIR	= lib/
#TSTDIR	= tests/

#Build source files ------------------------------------------------------
APPSRCS	= $(wildcard $(APPDIR)*.cpp)
LIBSRCS = $(wildcard $(LIBDIR)*.cpp)
#TSTSRCS = $(wildcard $(TSTDIR)*.cpp)

# Build object files -----------------------------------------------------
APPOBJS = $(APPSRCS:.cpp=.o)
LIBOBJS = $(LIBSRCS:.cpp=.o)
#TSTOBJS = $(TSTSRCS:.cpp=.o)

# Flags ------------------------------------------------------------------
CFLAGS  = -std=c++0x -I include
LFLAGS  = -L lib $(LIB)

.PHONY: all clean app test run

# Explicit targets to follow ---------------------------------------------
all: $(APP) $(LIB)
#$(TST)

$(LIB): $(LIBOBJS)
	$(AR) rvs $(LIB) $(LIBOBJS)

$(APP): $(APPOBJS) $(LIB)
	$(CPP) -o $(APP) $(APPOBJS) -pthread $(LFLAGS)

#$(TST): $(LIB) $(TSTOBJS)
#	$(CPP) -o $(TST) $(TSTOBJS) $(LFLAGS)

# Implicit targets to follow ---------------------------------------------
%.o:	%.cpp
	$(CPP) -c $< -o $@ $(CFLAGS)

# User targets to follow -------------------------------------------------
clean:
	$(RM) $(LIB) $(LIBOBJS) $(APP) $(APPOBJS) log.txt
#$(TST) $(TSTOBJS)

app: all
	./$(APP) $(seed)

#test: all
#	./$(TST)

run: all
	./$(APP) $(seed)
#	./$(TST)
