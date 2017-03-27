#include <gtest/gtest.h>

#include "uint128_t.h"

TEST(Constructor, standard){
    uint128_t value(0x0123456789abcdefULL);
    const uint128_t original = value;

    EXPECT_EQ(uint128_t(), 0);
    EXPECT_EQ(value, original);
    EXPECT_EQ(uint128_t(std::move(value)), original);
    EXPECT_EQ(value, 0);
}

TEST(Constructor, one){
    EXPECT_EQ(uint128_t(true).upper(),  false);
    EXPECT_EQ(uint128_t(true).lower(),   true);
    EXPECT_EQ(uint128_t(false).upper(), false);
    EXPECT_EQ(uint128_t(false).lower(), false);

    EXPECT_EQ(uint128_t((uint8_t)  0x01ULL).upper(),               0ULL);
    EXPECT_EQ(uint128_t((uint16_t) 0x0123ULL).upper(),             0ULL);
    EXPECT_EQ(uint128_t((uint32_t) 0x01234567ULL).upper(),         0ULL);
    EXPECT_EQ(uint128_t((uint64_t) 0x0123456789abcdefULL).upper(), 0ULL);

    EXPECT_EQ(uint128_t((uint8_t)  0x01ULL).lower(),               (uint8_t)  0x01ULL);
    EXPECT_EQ(uint128_t((uint16_t) 0x0123ULL).lower(),             (uint16_t) 0x0123ULL);
    EXPECT_EQ(uint128_t((uint32_t) 0x01234567ULL).lower(),         (uint32_t) 0x01234567ULL);
    EXPECT_EQ(uint128_t((uint64_t) 0x0123456789abcdefULL).lower(), (uint64_t) 0x0123456789abcdefULL);
}

TEST(Constructor, two){
    EXPECT_EQ(uint128_t(true,  true).upper(),   true);
    EXPECT_EQ(uint128_t(true,  true).lower(),   true);
    EXPECT_EQ(uint128_t(true,  false).upper(),  true);
    EXPECT_EQ(uint128_t(true,  false).lower(), false);
    EXPECT_EQ(uint128_t(false, false).upper(), false);
    EXPECT_EQ(uint128_t(false, false).lower(), false);
    EXPECT_EQ(uint128_t(false, true).upper(),  false);
    EXPECT_EQ(uint128_t(false, true).lower(),   true);

    EXPECT_EQ(uint128_t((uint8_t)  0x01ULL,               (uint8_t)  0x01ULL).upper(),               (uint8_t)  0x01ULL);
    EXPECT_EQ(uint128_t((uint16_t) 0x0123ULL,             (uint16_t) 0x0123ULL).upper(),             (uint16_t) 0x0123ULL);
    EXPECT_EQ(uint128_t((uint32_t) 0x01234567ULL,         (uint32_t) 0x01234567ULL).upper(),         (uint32_t) 0x01234567ULL);
    EXPECT_EQ(uint128_t((uint64_t) 0x0123456789abcdefULL, (uint64_t) 0x0123456789abcdefULL).upper(), (uint64_t) 0x0123456789abcdefULL);

    EXPECT_EQ(uint128_t((uint8_t)  0x01ULL,               (uint8_t)  0x01ULL).lower(),               (uint8_t)  0x01ULL);
    EXPECT_EQ(uint128_t((uint16_t) 0x0123ULL,             (uint16_t) 0x0123ULL).lower(),             (uint16_t) 0x0123ULL);
    EXPECT_EQ(uint128_t((uint32_t) 0x01234567ULL,         (uint32_t) 0x01234567ULL).lower(),         (uint32_t) 0x01234567ULL);
    EXPECT_EQ(uint128_t((uint64_t) 0x0123456789abcdefULL, (uint64_t) 0x0123456789abcdefULL).lower(), (uint64_t) 0x0123456789abcdefULL);
}
