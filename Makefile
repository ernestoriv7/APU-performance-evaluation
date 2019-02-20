# OpenCL include directory
OCL_INC = /opt/amdgpu-pro/lib/x86_64-linux-gnu/

# OpenCL lib directory
OCL_LIB = /opt/amdgpu-pro/lib/x86_64-linux-gnu/

# C compiler to use
CC = gcc

# compile-time flags
CFLAGS = -Wall -O3 -ggdb3 -g -pg

# header file directories
INCLUDES = -I/usr/include -I${OCL_INC} -I./Utils

# library paths
LFLAGS = -L${OCL_LIB}

# libraries
LIBS = -lOpenCL -lm -lpthread 

# source files
SRCS = $(wildcard src/*.c) Utils/utils.c Utils/bmp-utils.c Utils/gold.c

# object files 
#OBJS = $(SRCS:%.c=/obj/%.o)
OBJS=$(patsubst %.c,$(OBJDIR)%.o,$(SRCS))

OBJDIR = obj/
# executable file 
MAIN = raytracer

.PHONY: clean

all:    $(MAIN)

$(MAIN): $(OBJS) 
	$(CC) $(CFLAGS) $(INCLUDES) -o $(MAIN) $(OBJS) $(LFLAGS) $(LIBS)


$(OBJDIR)%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $<  -o $@

clean:
	$(RM) obj/src/*.o obj/Utils/*.o *~ $(MAIN) gmon.out scenes/cpu/* scenes/apu/* scenes/gpu/* execution/*.ppm execution/gmon.out *.ppm
