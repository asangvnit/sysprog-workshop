#include <gtest/gtest.h>
#include "helloprint.h"

// Demonstrate some basic assertions.
TEST(HelloTest, BasicAssertions) {
  // Expect two strings not to be equal.
  EXPECT_STRNE( "hello", get_hello().c_str() );
  EXPECT_STREQ( "Hello World Indeed!", get_hello().c_str() );
}
