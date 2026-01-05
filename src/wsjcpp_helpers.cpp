/*
MIT License

Copyright (c) 2019-2026 Evgenii Sopov

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

https://github.com/wsjcpp/wsjcpp

*/

#include "wsjcpp_helpers.h"
#include <smallsha1.h>
#include <iostream>
#include <cstring>
#include <fstream>

// ---------------------------------------------------------------------
// WsjcppHelpers

std::string WsjcppHelpers::sha1_calc_hex(const std::string &sSource) { // deprecated
    char hexstring[41]; // 40 chars + a zero
    std::memset(hexstring, 0, sizeof hexstring);

    unsigned char hash[20];
    sha1::calc(sSource.c_str(), sSource.length(), hash);
    sha1::toHexString(hash, hexstring);
    return std::string(hexstring);
}

std::string WsjcppHelpers::getSha1ByString(const std::string &sStr) {
    char hexstring[41]; // 40 chars + a zero
    std::memset(hexstring, 0, sizeof hexstring);

    unsigned char hash[20];
    sha1::calc(sStr.c_str(), sStr.length(), hash);
    sha1::toHexString(hash, hexstring);
    return std::string(hexstring);
}

std::string WsjcppHelpers::getSha1ByFile(const std::string &sFilename) {
    std::ifstream f(sFilename, std::ifstream::binary);
    if (!f) {
        return "Could not open file";
    }

    // get length of file:
    f.seekg (0, f.end);
    int nBufferSize = f.tellg();
    f.seekg (0, f.beg);

    char *pBuffer = new char [nBufferSize];

    // read data as a block:
    f.read(pBuffer, nBufferSize);
    if (!f) {
        delete[] pBuffer;
        // f.close();
        return "Could not read file. Only " + std::to_string(f.gcount()) + " could be read";
    }
    f.close();

    char hexstring[41]; // 40 chars + a zero
    std::memset(hexstring, 0, sizeof hexstring);
    unsigned char hash[20];
    sha1::calc(pBuffer, nBufferSize, hash);
    sha1::toHexString(hash, hexstring);
    return std::string(hexstring);
}

