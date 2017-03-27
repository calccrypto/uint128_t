uint128_t

An unsigned 128 bit integer type for C++

Copyright (c) 2013 - 2017 Jason Lee @ calccrypto at gmail.com

Please see LICENSE file for license.

[![Build Status](https://travis-ci.org/calccrypto/uint128_t.svg?branch=master)](https://travis-ci.org/calccrypto/uint128_t)

With much help from Auston Sterling

Thanks to Stefan Deigmüller for finding
a bug in operator*.

Thanks to François Dessenne for convincing me
to do a general rewrite of this class.

This is simple implementation of an unsigned 128 bit
integer type in C++. It's meant to be used like a standard
uintX_t, except with a larger bit size than those provided
by C/C++.

Be careful when initializing a uint128_t value. -1 does not
create the value 2<sup>128</sup> - 1. Rather, it uses 2<sup>64</sup> - 1, or
whatever the built-in max unsigned value is.