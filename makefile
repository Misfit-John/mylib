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
TEST_FLAG=-isystem ./test/include
TEST_LIB=test/libtest.a

CFLAGS=$(PLATFORM_FLAG) $(INCLUDE_FLAGS)
CPPFLAGS=$(PLATFORM_FLAG) $(INCLUDE_FLAGS) $(CPP_FLAG)

SOURCES=$(wildcard ./src/*/*.c ./src/*/*.cpp ./src/*.c ./src/*.cpp)
OBJS=$(patsubst %.c, %.o,$(patsubst %.cpp,%.o,$(SOURCES)))
HEADERS=$(wildcard ./header/*.h)
TEST_SOURCES=$(wildcard ./test/src/*.c ./test/src/*.cpp ./test/src/*/*.c ./test/src/*/*.cpp)

$(TARGET):$(OBJS) 
	@echo "============ make target ============="
	$(AR) -r $(TARGET) $(OBJS) 

test:$(TARGET) $(TEST_LIB) $(TEST_SOURCES)
	@echo "============ make test ==============="
	$(CXX) $(TARGET) $(TEST_LIB) $(INCLUDE_FLAGS) $(CPP_FLAG) $(PLATFORM_FLAG) $(TEST_SOURCES) $(TEST_FLAG) -o ./test/tester
	./test/tester

release:clean makefile
	@echo "============ release ================="
	make debug_var=0

depend:$(SOURCES) $(HEADERS)
	@echo "============ now generat dpend ======="
	-rm depend
	-@sh depend_generator.sh "$(CPPFLAGS)" > /dev/null

clean:
	@echo "============ now clean ==============="
	-rm $(TARGET)
	-rm $(OBJS)
	-rm depend

-include depend

