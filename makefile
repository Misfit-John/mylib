#don't indent!
debug_var=1
ifeq ($(debug_var),1)
RELEASE_FLAG=-DDEBUG -g -fprofile-arcs -ftest-coverage
else
RELEASE_FLAG=-DRELEASE
endif

#CC=clang
#CXX=clang++
AR=ar
PLATFORM_FLAG=-D_LINUX_ $(RELEASE_FLAG) 
INCLUDE_FLAGS=-I./header 
CPP_FLAG=--std=c++11
TARGET=mylib.a
TEST_FLAG=-isystem ./test/include
TEST_LIB=test/libtest.a

CFLAGS=$(PLATFORM_FLAG) $(INCLUDE_FLAGS) $(TEST_FLAG)
CPPFLAGS=$(PLATFORM_FLAG) $(INCLUDE_FLAGS) $(CPP_FLAG) $(TEST_FLAG)

SOURCES=$(wildcard ./src/*/*.c ./src/*/*.cpp ./src/*.c ./src/*.cpp)
OBJS=$(patsubst %.c, %.o,$(patsubst %.cpp,%.o,$(SOURCES)))
HEADERS=$(wildcard ./header/*.h)
TEST_SOURCES=$(wildcard ./test/src/*.c ./test/src/*.cpp ./test/src/*/*.c ./test/src/*/*.cpp)
TEST_OBJECTS=$(patsubst %.c, %.o,$(patsubst %.cpp,%.o,$(TEST_SOURCE)))

$(TARGET):$(OBJS) 
	@echo "============ make target ============="
	$(AR) -r $(TARGET) $(OBJS) 

test:$(TARGET) $(TEST_LIB) $(TEST_OBJECTS)
	@echo "============ make test ==============="
	$(CXX) $(TARGET) $(TEST_LIB) $(INCLUDE_FLAGS) $(CPP_FLAG) $(PLATFORM_FLAG) $(TEST_OBJECTS) $(TEST_FLAG) -o ./target/tester
	./target/tester

release:clean makefile
	@echo "============ release ================="
	make debug_var=0

depend:$(SOURCES) $(HEADERS)
	@echo "============ now generat dpend ======="
	-rm depend
	-@sh depend_generator.sh "$(CPPFLAGS)" > /dev/null

clean:
	@echo "============ now clean ==============="
	-find . -name "*.gcda" -exec rm {} \;
	-find . -name "*.gcno" -exec rm {} \;
	-rm $(TARGET)
	-rm $(OBJS)
	-rm depend

-include depend

