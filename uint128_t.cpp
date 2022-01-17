#include "uint128_t.build"

#include <algorithm>
#include <cctype>
#include <sstream>

const uint128_t uint128_0(0);
const uint128_t uint128_1(1);

uint128_t::uint128_t(const std::string & s, uint8_t base) {
    init(s.c_str(), s.size(), base);
}

uint128_t::uint128_t(const char *s, const std::size_t len, uint8_t base) {
    init(s, len, base);
}

uint128_t::uint128_t(const bool & b)
    : uint128_t((uint8_t) b)
{}

void uint128_t::init(const char *s, std::size_t len, uint8_t base) {
    if ((s == NULL) || !len || (s[0] == '\x00')){
        LOWER = UPPER = 0;
        return;
    }

    while (*s && len && std::isspace(*s)) {
        ++s;
        len--;
    }

    // no prefixes
    switch (base) {
        case 16:
            _init_hex(s, len);
            break;
        case 10:
            _init_dec(s, len);
            break;
        case 8:
            _init_oct(s, len);
            break;
        case 2:
            _init_bin(s, len);
            break;
        default:
            // should probably throw error here
            break;
    }
}

void uint128_t::_init_hex(const char *s, std::size_t len) {
    // 2**128 = 0x100000000000000000000000000000000.
    static const std::size_t MAX_LEN = 32;

    LOWER = UPPER = 0;
    if (!s || !len) {
        return;
    }

    const std::size_t max_len = std::min(len, MAX_LEN);
    const std::size_t starting_index = (MAX_LEN < len)?(len - MAX_LEN):0;
    const std::size_t double_lower = sizeof(LOWER) * 2;
    const std::size_t lower_len = (max_len >= double_lower)?double_lower:max_len;
    const std::size_t upper_len = (max_len >= double_lower)?(max_len - double_lower):0;

    std::stringstream lower_s, upper_s;
    upper_s << std::hex << std::string(s + starting_index, upper_len);
    lower_s << std::hex << std::string(s + starting_index + upper_len, lower_len);

    // should check for errors
    upper_s >> UPPER;
    lower_s >> LOWER;
}

void uint128_t::_init_dec(const char *s, std::size_t len){
    // 2**128 = 340282366920938463463374607431768211456.
    static const std::size_t MAX_LEN = 39;

    LOWER = UPPER = 0;
    if (!s || !len) {
        return;
    }

    const std::size_t max_len = std::min(len, MAX_LEN);
    const std::size_t starting_index = (MAX_LEN < len)?(len - MAX_LEN):0;
    s += starting_index;

    for (std::size_t i = 0; *s && ('0' <= *s) && (*s <= '9') && (i < max_len); ++s, ++i){
        *this *= 10;
        *this += *s - '0';
    }
}

void uint128_t::_init_oct(const char *s, std::size_t len){
    // 2**128 = 0o4000000000000000000000000000000000000000000.
    static const std::size_t MAX_LEN = 43;

    LOWER = UPPER = 0;
    if (!s || !len) {
        return;
    }

    const std::size_t max_len = std::min(len, MAX_LEN);
    const std::size_t starting_index = (MAX_LEN < len)?(len - MAX_LEN):0;
    s += starting_index;

    for (std::size_t i = 0; *s && ('0' <= *s) && (*s <= '7') && (i < max_len); ++s, ++i){
        *this *= 8;
        *this += *s - '0';
    }
}

void uint128_t::_init_bin(const char *s, std::size_t len){
    // 2**128 = 0x100000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000.
    static const std::size_t MAX_LEN = 128;

    LOWER = UPPER = 0;
    if (!s || !len) {
        return;
    }

    const std::size_t max_len = std::min(len, MAX_LEN);
    const std::size_t starting_index = (MAX_LEN < len)?(len - MAX_LEN):0;
    const std::size_t eight_lower = sizeof(LOWER) * 8;
    const std::size_t lower_len = (max_len >= eight_lower)?eight_lower:max_len;
    const std::size_t upper_len = (max_len >= eight_lower)?(max_len - eight_lower):0;
    s += starting_index;

    for (std::size_t i = 0; *s && ('0' <= *s) && (*s <= '1') && (i < upper_len); ++s, ++i){
        UPPER <<= 1;
        UPPER |= *s - '0';
    }

    for (std::size_t i = 0; *s && ('0' <= *s) && (*s <= '1') && (i < lower_len); ++s, ++i){
        LOWER <<= 1;
        LOWER |= *s - '0';
    }
}

uint128_t & uint128_t::operator=(const bool & rhs) {
    UPPER = 0;
    LOWER = rhs;
    return *this;
}

uint128_t::operator bool() const{
    return (bool) (UPPER | LOWER);
}

uint128_t::operator uint8_t() const{
    return (uint8_t) LOWER;
}

uint128_t::operator uint16_t() const{
    return (uint16_t) LOWER;
}

uint128_t::operator uint32_t() const{
    return (uint32_t) LOWER;
}

uint128_t::operator uint64_t() const{
    return (uint64_t) LOWER;
}

uint128_t uint128_t::operator&(const uint128_t & rhs) const{
    return uint128_t(UPPER & rhs.UPPER, LOWER & rhs.LOWER);
}

uint128_t & uint128_t::operator&=(const uint128_t & rhs){
    UPPER &= rhs.UPPER;
    LOWER &= rhs.LOWER;
    return *this;
}

uint128_t uint128_t::operator|(const uint128_t & rhs) const{
    return uint128_t(UPPER | rhs.UPPER, LOWER | rhs.LOWER);
}

uint128_t & uint128_t::operator|=(const uint128_t & rhs){
    UPPER |= rhs.UPPER;
    LOWER |= rhs.LOWER;
    return *this;
}

uint128_t uint128_t::operator^(const uint128_t & rhs) const{
    return uint128_t(UPPER ^ rhs.UPPER, LOWER ^ rhs.LOWER);
}

uint128_t & uint128_t::operator^=(const uint128_t & rhs){
    UPPER ^= rhs.UPPER;
    LOWER ^= rhs.LOWER;
    return *this;
}

uint128_t uint128_t::operator~() const{
    return uint128_t(~UPPER, ~LOWER);
}

uint128_t uint128_t::operator<<(const uint128_t & rhs) const{
    const uint64_t shift = rhs.LOWER;
    if (((bool) rhs.UPPER) || (shift >= 128)){
        return uint128_0;
    }
    else if (shift == 64){
        return uint128_t(LOWER, 0);
    }
    else if (shift == 0){
        return *this;
    }
    else if (shift < 64){
        return uint128_t((UPPER << shift) + (LOWER >> (64 - shift)), LOWER << shift);
    }
    else if ((128 > shift) && (shift > 64)){
        return uint128_t(LOWER << (shift - 64), 0);
    }
    else{
        return uint128_0;
    }
}

uint128_t & uint128_t::operator<<=(const uint128_t & rhs){
    *this = *this << rhs;
    return *this;
}

uint128_t uint128_t::operator>>(const uint128_t & rhs) const{
    const uint64_t shift = rhs.LOWER;
    if (((bool) rhs.UPPER) || (shift >= 128)){
        return uint128_0;
    }
    else if (shift == 64){
        return uint128_t(0, UPPER);
    }
    else if (shift == 0){
        return *this;
    }
    else if (shift < 64){
        return uint128_t(UPPER >> shift, (UPPER << (64 - shift)) + (LOWER >> shift));
    }
    else if ((128 > shift) && (shift > 64)){
        return uint128_t(0, (UPPER >> (shift - 64)));
    }
    else{
        return uint128_0;
    }
}

uint128_t & uint128_t::operator>>=(const uint128_t & rhs){
    *this = *this >> rhs;
    return *this;
}

bool uint128_t::operator!() const{
    return !(bool) (UPPER | LOWER);
}

bool uint128_t::operator&&(const uint128_t & rhs) const{
    return ((bool) *this && rhs);
}

bool uint128_t::operator||(const uint128_t & rhs) const{
     return ((bool) *this || rhs);
}

bool uint128_t::operator==(const uint128_t & rhs) const{
    return ((UPPER == rhs.UPPER) && (LOWER == rhs.LOWER));
}

bool uint128_t::operator!=(const uint128_t & rhs) const{
    return ((UPPER != rhs.UPPER) | (LOWER != rhs.LOWER));
}

bool uint128_t::operator>(const uint128_t & rhs) const{
    if (UPPER == rhs.UPPER){
        return (LOWER > rhs.LOWER);
    }
    return (UPPER > rhs.UPPER);
}

bool uint128_t::operator<(const uint128_t & rhs) const{
    if (UPPER == rhs.UPPER){
        return (LOWER < rhs.LOWER);
    }
    return (UPPER < rhs.UPPER);
}

bool uint128_t::operator>=(const uint128_t & rhs) const{
    return ((*this > rhs) | (*this == rhs));
}

bool uint128_t::operator<=(const uint128_t & rhs) const{
    return ((*this < rhs) | (*this == rhs));
}

uint128_t uint128_t::operator+(const uint128_t & rhs) const{
    return uint128_t(UPPER + rhs.UPPER + ((LOWER + rhs.LOWER) < LOWER), LOWER + rhs.LOWER);
}

uint128_t & uint128_t::operator+=(const uint128_t & rhs){
    UPPER += rhs.UPPER + ((LOWER + rhs.LOWER) < LOWER);
    LOWER += rhs.LOWER;
    return *this;
}

uint128_t uint128_t::operator-(const uint128_t & rhs) const{
    return uint128_t(UPPER - rhs.UPPER - ((LOWER - rhs.LOWER) > LOWER), LOWER - rhs.LOWER);
}

uint128_t & uint128_t::operator-=(const uint128_t & rhs){
    *this = *this - rhs;
    return *this;
}

uint128_t uint128_t::operator*(const uint128_t & rhs) const{
    // split values into 4 32-bit parts
    uint64_t top[4] = {UPPER >> 32, UPPER & 0xffffffff, LOWER >> 32, LOWER & 0xffffffff};
    uint64_t bottom[4] = {rhs.UPPER >> 32, rhs.UPPER & 0xffffffff, rhs.LOWER >> 32, rhs.LOWER & 0xffffffff};
    uint64_t products[4][4];

    // multiply each component of the values
    for(int y = 3; y > -1; y--){
        for(int x = 3; x > -1; x--){
            products[3 - x][y] = top[x] * bottom[y];
        }
    }

    // first row
    uint64_t fourth32 = (products[0][3] & 0xffffffff);
    uint64_t third32  = (products[0][2] & 0xffffffff) + (products[0][3] >> 32);
    uint64_t second32 = (products[0][1] & 0xffffffff) + (products[0][2] >> 32);
    uint64_t first32  = (products[0][0] & 0xffffffff) + (products[0][1] >> 32);

    // second row
    third32  += (products[1][3] & 0xffffffff);
    second32 += (products[1][2] & 0xffffffff) + (products[1][3] >> 32);
    first32  += (products[1][1] & 0xffffffff) + (products[1][2] >> 32);

    // third row
    second32 += (products[2][3] & 0xffffffff);
    first32  += (products[2][2] & 0xffffffff) + (products[2][3] >> 32);

    // fourth row
    first32  += (products[3][3] & 0xffffffff);

    // move carry to next digit
    third32  += fourth32 >> 32;
    second32 += third32  >> 32;
    first32  += second32 >> 32;

    // remove carry from current digit
    fourth32 &= 0xffffffff;
    third32  &= 0xffffffff;
    second32 &= 0xffffffff;
    first32  &= 0xffffffff;

    // combine components
    return uint128_t((first32 << 32) | second32, (third32 << 32) | fourth32);
}

uint128_t & uint128_t::operator*=(const uint128_t & rhs){
    *this = *this * rhs;
    return *this;
}

void uint128_t::ConvertToVector(std::vector<uint8_t> & ret, const uint64_t & val) const {
    ret.push_back(static_cast<uint8_t>(val >> 56));
    ret.push_back(static_cast<uint8_t>(val >> 48));
    ret.push_back(static_cast<uint8_t>(val >> 40));
    ret.push_back(static_cast<uint8_t>(val >> 32));
    ret.push_back(static_cast<uint8_t>(val >> 24));
    ret.push_back(static_cast<uint8_t>(val >> 16));
    ret.push_back(static_cast<uint8_t>(val >> 8));
    ret.push_back(static_cast<uint8_t>(val));
}

void uint128_t::export_bits(std::vector<uint8_t> &ret) const {
    ConvertToVector(ret, const_cast<const uint64_t&>(UPPER));
    ConvertToVector(ret, const_cast<const uint64_t&>(LOWER));
}

std::pair <uint128_t, uint128_t> uint128_t::divmod(const uint128_t & lhs, const uint128_t & rhs) const{
    // Save some calculations /////////////////////
    if (rhs == uint128_0){
        throw std::domain_error("Error: division or modulus by 0");
    }
    else if (rhs == uint128_1){
        return std::pair <uint128_t, uint128_t> (lhs, uint128_0);
    }
    else if (lhs == rhs){
        return std::pair <uint128_t, uint128_t> (uint128_1, uint128_0);
    }
    else if ((lhs == uint128_0) || (lhs < rhs)){
        return std::pair <uint128_t, uint128_t> (uint128_0, lhs);
    }

    std::pair <uint128_t, uint128_t> qr (uint128_0, uint128_0);
    for(uint8_t x = lhs.bits(); x > 0; x--){
        qr.first  <<= uint128_1;
        qr.second <<= uint128_1;

        if ((lhs >> (x - 1U)) & 1){
            ++qr.second;
        }

        if (qr.second >= rhs){
            qr.second -= rhs;
            ++qr.first;
        }
    }
    return qr;
}

uint128_t uint128_t::operator/(const uint128_t & rhs) const{
    return divmod(*this, rhs).first;
}

uint128_t & uint128_t::operator/=(const uint128_t & rhs){
    *this = *this / rhs;
    return *this;
}

uint128_t uint128_t::operator%(const uint128_t & rhs) const{
    return divmod(*this, rhs).second;
}

uint128_t & uint128_t::operator%=(const uint128_t & rhs){
    *this = *this % rhs;
    return *this;
}

uint128_t & uint128_t::operator++(){
    return *this += uint128_1;
}

uint128_t uint128_t::operator++(int){
    uint128_t temp(*this);
    ++*this;
    return temp;
}

uint128_t & uint128_t::operator--(){
    return *this -= uint128_1;
}

uint128_t uint128_t::operator--(int){
    uint128_t temp(*this);
    --*this;
    return temp;
}

uint128_t uint128_t::operator+() const{
    return *this;
}

uint128_t uint128_t::operator-() const{
    return ~*this + uint128_1;
}

const uint64_t & uint128_t::upper() const{
    return UPPER;
}

const uint64_t & uint128_t::lower() const{
    return LOWER;
}

uint8_t uint128_t::bits() const{
    uint8_t out = 0;
    if (UPPER){
        out = 64;
        uint64_t up = UPPER;
        while (up){
            up >>= 1;
            out++;
        }
    }
    else{
        uint64_t low = LOWER;
        while (low){
            low >>= 1;
            out++;
        }
    }
    return out;
}

std::string uint128_t::str(uint8_t base, const unsigned int & len) const{
    if ((base < 2) || (base > 16)){
        throw std::invalid_argument("Base must be in the range [2, 16]");
    }
    std::string out = "";
    if (!(*this)){
        out = "0";
    }
    else{
        std::pair <uint128_t, uint128_t> qr(*this, uint128_0);
        do{
            qr = divmod(qr.first, base);
            out = "0123456789abcdef"[(uint8_t) qr.second] + out;
        } while (qr.first);
    }
    if (out.size() < len){
        out = std::string(len - out.size(), '0') + out;
    }
    return out;
}

uint128_t operator<<(const bool & lhs, const uint128_t & rhs){
    return uint128_t(lhs) << rhs;
}

uint128_t operator<<(const uint8_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) << rhs;
}

uint128_t operator<<(const uint16_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) << rhs;
}

uint128_t operator<<(const uint32_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) << rhs;
}

uint128_t operator<<(const uint64_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) << rhs;
}

uint128_t operator<<(const int8_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) << rhs;
}

uint128_t operator<<(const int16_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) << rhs;
}

uint128_t operator<<(const int32_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) << rhs;
}

uint128_t operator<<(const int64_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) << rhs;
}

uint128_t operator>>(const bool & lhs, const uint128_t & rhs){
    return uint128_t(lhs) >> rhs;
}

uint128_t operator>>(const uint8_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) >> rhs;
}

uint128_t operator>>(const uint16_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) >> rhs;
}

uint128_t operator>>(const uint32_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) >> rhs;
}

uint128_t operator>>(const uint64_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) >> rhs;
}

uint128_t operator>>(const int8_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) >> rhs;
}

uint128_t operator>>(const int16_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) >> rhs;
}

uint128_t operator>>(const int32_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) >> rhs;
}

uint128_t operator>>(const int64_t & lhs, const uint128_t & rhs){
    return uint128_t(lhs) >> rhs;
}

std::ostream & operator<<(std::ostream & stream, const uint128_t & rhs){
    if (stream.flags() & stream.oct){
        stream << rhs.str(8);
    }
    else if (stream.flags() & stream.dec){
        stream << rhs.str(10);
    }
    else if (stream.flags() & stream.hex){
        stream << rhs.str(16);
    }
    return stream;
}
