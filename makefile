CC=clang
CPPCC=clang++
AR=ar
PLATFOR_FLAG=-D_LINUX_
INCLUDE_FLAGS=-I./header $(PLATFOR_FLAG)
TARGET=mylib.a

%.o: %.c
	$(CC) $(INCLUDE_FLAGS) -c $< -o $@
%.o: %.cpp
	$(CPPCC) $(INCLUDE_FLAGS) -c $< -o $@

SOURCES=$(wildcard ./*/*.c ./*/*.cpp)
OBJS=$(patsubst %.c, %.o,$(patsubst %.cpp,%.o,$(SOURCES)))

$TARGET:$(OBJS)
	$(AR) -r $(TARGET) $(OBJS) 

test:$(TARGET) libTest.cpp
	clang++ libTest.cpp $(TARGET) $(INCLUDE_FLAGS) -o tester

clean:
	rm $(TARGET)
	rm $(OBJS)
