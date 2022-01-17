#include <gtest/gtest.h>

#include "uint128_t.h"

TEST(Constructor, standard){
    const uint128_t value(0x0123456789abcdefULL);
    const uint128_t original = value;

    EXPECT_EQ(uint128_t(), 0);
    EXPECT_EQ(value, original);
    EXPECT_EQ(uint128_t(std::move(value)), original);
    EXPECT_EQ(value, 0x0123456789abcdefULL);
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
    for(uint8_t hi = 0; hi < 2; hi++){
        for(uint8_t lo = 0; lo < 2; lo++){
            const uint128_t val(hi, lo);
            EXPECT_EQ(val.upper(), hi);
            EXPECT_EQ(val.lower(), lo);
        }
    }

    EXPECT_EQ(uint128_t((uint8_t)  0x01ULL,               (uint8_t)  0x01ULL).upper(),               (uint8_t)  0x01ULL);
    EXPECT_EQ(uint128_t((uint16_t) 0x0123ULL,             (uint16_t) 0x0123ULL).upper(),             (uint16_t) 0x0123ULL);
    EXPECT_EQ(uint128_t((uint32_t) 0x01234567ULL,         (uint32_t) 0x01234567ULL).upper(),         (uint32_t) 0x01234567ULL);
    EXPECT_EQ(uint128_t((uint64_t) 0x0123456789abcdefULL, (uint64_t) 0x0123456789abcdefULL).upper(), (uint64_t) 0x0123456789abcdefULL);

    EXPECT_EQ(uint128_t((uint8_t)  0x01ULL,               (uint8_t)  0x01ULL).lower(),               (uint8_t)  0x01ULL);
    EXPECT_EQ(uint128_t((uint16_t) 0x0123ULL,             (uint16_t) 0x0123ULL).lower(),             (uint16_t) 0x0123ULL);
    EXPECT_EQ(uint128_t((uint32_t) 0x01234567ULL,         (uint32_t) 0x01234567ULL).lower(),         (uint32_t) 0x01234567ULL);
    EXPECT_EQ(uint128_t((uint64_t) 0x0123456789abcdefULL, (uint64_t) 0x0123456789abcdefULL).lower(), (uint64_t) 0x0123456789abcdefULL);
}

static const uint64_t EXPECTED_UINT64_T = 0xfedcba9876543210ULL;

TEST(Constructor, Hex_String) {
    static const std::string INPUT_STRING = "fedcba9876543210fedcba9876543210";

    {
        const uint128_t value(INPUT_STRING, 16);
        EXPECT_EQ(value.upper(), EXPECTED_UINT64_T);
        EXPECT_EQ(value.lower(), EXPECTED_UINT64_T);
    }

    // too long, only read last 32 nibbles
    {
        const uint128_t value("1" + INPUT_STRING, 16);
        EXPECT_EQ(value.upper(), EXPECTED_UINT64_T);
        EXPECT_EQ(value.lower(), EXPECTED_UINT64_T);
    }
}

TEST(Constructor, Dec_String) {
    static const std::string INPUT_STRING = "338770000845734292534325025077361652240";

    {
        const uint128_t value(INPUT_STRING, 10);
        EXPECT_EQ(value.upper(), EXPECTED_UINT64_T);
        EXPECT_EQ(value.lower(), EXPECTED_UINT64_T);
    }

    // too long
    {
        const uint128_t value("1" + INPUT_STRING, 10);
        EXPECT_EQ(value.upper(), EXPECTED_UINT64_T);
        EXPECT_EQ(value.lower(), EXPECTED_UINT64_T);
    }
}

TEST(Constructor, Oct_String) {
    static const std::string INPUT_STRING = "3766713523035452062041773345651416625031020";

    {
        const uint128_t value(INPUT_STRING, 8);
        EXPECT_EQ(value.upper(), EXPECTED_UINT64_T);
        EXPECT_EQ(value.lower(), EXPECTED_UINT64_T);
    }

    // too long
    {
        const uint128_t value("1" + INPUT_STRING, 8);
        EXPECT_EQ(value.upper(), EXPECTED_UINT64_T);
        EXPECT_EQ(value.lower(), EXPECTED_UINT64_T);
    }
}

TEST(Constructor, Bin_String) {
    static const std::string INPUT_STRING = "11111110110111001011101010011000011101100101010000110010000100001111111011011100101110101001100001110110010101000011001000010000";

    {
        const uint128_t value(INPUT_STRING, 2);
        EXPECT_EQ(value.upper(), EXPECTED_UINT64_T);
        EXPECT_EQ(value.lower(), EXPECTED_UINT64_T);
    }

    // too long
    {
        const uint128_t value("1" + INPUT_STRING, 2);
        EXPECT_EQ(value.upper(), EXPECTED_UINT64_T);
        EXPECT_EQ(value.lower(), EXPECTED_UINT64_T);
    }
}
