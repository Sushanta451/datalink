#include <gtest/gtest.h>

#include "datalink/version.hpp"
#include "net/version.hpp"

TEST(Version, CoreReportsProjectVersion) {
  EXPECT_STREQ(datalink::version(), "0.1.0");
}

TEST(Version, TransportReportsProjectVersion) {
  EXPECT_EQ(net::version(), "0.1.0");
}
