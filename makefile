#don't indent!

debug_var=1
ifeq ($(debug_var),1)
DEBUG_FLAG=-g -DDEBUG
else
DEBUG_FLAG=-DRELEASE
endif
CC=clang
CPPCC=clang++
AR=ar
PLATFORM_FLAG=-D_LINUX_ $(DEBUG_FLAG) 
INCLUDE_FLAGS=-I./header $(PLATFORM_FLAG)
CPP_FLAG=--std=c++0x
TARGET=mylib.a

%.o: %.c makefile
	$(CC) $(INCLUDE_FLAGS) $(PLATFORM_FLAG) -c $< -o $@
%.o: %.cpp makefile
	$(CPPCC) $(CPP_FLAG) $(INCLUDE_FLAGS) $(PLATFORM_FLAG) -c $< -o $@

SOURCES=$(wildcard ./*/*.c ./*/*.cpp)
OBJS=$(patsubst %.c, %.o,$(patsubst %.cpp,%.o,$(SOURCES)))

$(TARGET):$(OBJS) makefile
	$(AR) -r $(TARGET) $(OBJS) 

test:$(TARGET) libTest.cpp
	clang++ libTest.cpp $(TARGET) $(INCLUDE_FLAGS) $(CPP_FLAG) -o tester

release:clean makefile
	make debug_var=0	

clean:
	rm $(TARGET)
	rm $(OBJS)
