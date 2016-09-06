#include <gtest/gtest.h>
#include "JZLogger.h"

TEST(FooTest, HandleNoneZeroInput)
{
    EXPECT_EQ(2, 2);
    EXPECT_EQ(1, 1);
    EXPECT_EQ(1, 1);
}

int main(int argc, char* argv[])
{
  JZLoggerInit();
  JZSetLoggerLevel(JZ_LOG_ALL);
  JZSetLoggerOutPutStatue(1,1);
  JZSetLogFileName("test.log");
  JZWRITE_DEBUG("hello");
  JZWRITE_TEST("hello");
  JZWRITE_ERROR("hello");
  JZFUNC_BEGIN_LOG();
  JZFUNC_END_LOG();
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
