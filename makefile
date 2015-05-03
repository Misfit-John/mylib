CC=clang
CPPCC=clang++
AR=ar
INCLUDE_FLAGS=-I./header
TARGET=mylib.a

%.o: %.c
	$(CC) $(INCLUDE_FLAGS) -c $< -o $@
%.o: %.cpp
	$(CPPCC) $(INCLUDE_FLAGS) -c $< -o $@

SOURCES=$(wildcard ./*/*.c ./*/*.cpp)
OBJS=$(patsubst %.c, %.o,$(patsubst %.cpp,%.o,$(SOURCES)))

$TARGET:$(OBJS)
	$(AR) -r $(TARGET) $(OBJS) 

test:$(TARGET) libTest.c
	gcc libTest.c $(TARGET) $(INCLUDE_FLAGS) -o tester

clean:
	rm $(TARGET)
	rm $(OBJS)
