#don't indent!
debug_var=1
ifeq ($(debug_var),1)
DEBUG_FLAG=-g -DDEBUG
else
DEBUG_FLAG=-DRELEASE
endif

CC=clang
CXX=clang++
AR=ar
PLATFORM_FLAG=-D_LINUX_ $(DEBUG_FLAG) 
INCLUDE_FLAGS=-I./header 
CPP_FLAG=--std=c++0x
TARGET=mylib.a

CFLAGS=$(PLATFORM_FLAG) $(INCLUDE_FLAGS)
CPPFLAGS=$(PLATFORM_FLAG) $(INCLUDE_FLAGS) $(CPP_FLAG)

SOURCES=$(wildcard ./*/*.c ./*/*.cpp)
OBJS=$(patsubst %.c, %.o,$(patsubst %.cpp,%.o,$(SOURCES)))
HEADERS=$(wildcard ./header/*.h)

$(TARGET):$(OBJS) 
	@echo "============ make target ============="
	$(AR) -r $(TARGET) $(OBJS) 

test:$(TARGET) libTest.o
	@echo "============ make test ==============="
	$(CXX) libTest.o $(TARGET) $(INCLUDE_FLAGS) $(CPP_FLAG) $(PLATFORM_FLAG) -o tester

release:clean makefile
	@echo "============ release ================="
	make debug_var=0

depend:$(SOURCES) $(HEADERS)
	@echo "============ now generat dpend ======="
	-@sh depend_generator.sh "$(CPPFLAGS)" > /dev/null

clean:
	@echo "============ now clean ==============="
	-rm $(TARGET)
	-rm $(OBJS)

-include depend
