/*
unit test file for uint128_t
Copyright (c) 2013, 2014, 2016 Jason Lee @ calccrypto at gmail.com

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.

With much help from Auston Sterling
*/

#include <iostream>
#include <utility>

#include "uint128_t.h"

// These are not a comprehensive set of tests for all operators.
// They are just some to show that uint128_t works.
int main(){
    uint32_t num_tests = 0;
    uint32_t passed = 0;

    // empty constructor
    {
        uint128_t zero;
        uint128_t expected(0);
        passed += (expected == zero);
        num_tests++;
    }

    // 1 argument
    {
        uint128_t num(0x0123456789abcdef);
        uint128_t expected = uint128_t(0x0123456789abcdef);
        passed += (expected == num);
        num_tests++;
    }

    // 2 arguments
    {
        uint128_t num(0x0123456789abcdef, 0xfedcba9876543210);
        uint128_t expected = (uint128_t(0x0123456789abcdef) << 64) | 0xfedcba9876543210;
        passed += (expected == num);
        num_tests++;
    }

    // move constructor
    {
        uint128_t to_move(0x0123456789abcdef);
        uint128_t target(std::move(to_move));
        uint128_t expected(0x0123456789abcdef);
        passed += (expected == target);
        num_tests++;
    }

    // typecast
    {
        uint128_t zero;
        passed += !((bool) zero);
        num_tests++;
    }

    {
        uint128_t one(1);
        passed += ((bool) one);
        num_tests++;
    }

    // multiplication
    {
        // 1 * 1 = 1
        uint128_t a(1);
        uint128_t b(1);
        uint128_t expected(1);
        passed += (expected == a * b);
        num_tests++;
    }

    {
        // 0x100000000000000000000000000000001 * 0x100000000000000000000000000000001 =
        // 0x200000000000000000000000000000001
        uint128_t a(1, 1);
        uint128_t b(1, 1);
        uint128_t expected(2, 1);
        passed += (expected == a * b);
        num_tests++;
    }

    {
        // 0xfedcba98765432100123456789abcdef * 0x0123456789abcdeffedcba9876543210 =
        // 0x121fa00ad77d7431ff2e48e8a71de69bcb448e0e2b4bd632236d88fe5618cf0
        uint128_t a(0xfedcba9876543210, 0x0123456789abcdef);
        uint128_t b(0x0123456789abcdef, 0xfedcba9876543210);
        uint128_t expected(0xbcb448e0e2b4bd63, 0x2236d88fe5618cf0);
        passed += (expected == a * b);
        num_tests++;
    }

    std::cout << passed << "/" << num_tests << " tests passed" << std::endl;

    return 0;
}