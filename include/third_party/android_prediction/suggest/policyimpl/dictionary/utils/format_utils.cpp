/*
 * Copyright (C) 2013 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "third_party/android_prediction/suggest/policyimpl/dictionary/utils/format_utils.h"

#include "third_party/android_prediction/suggest/policyimpl/dictionary/utils/byte_array_utils.h"
#include <iostream>

namespace latinime {

const uint32_t FormatUtils::MAGIC_NUMBER = 0x9BC13AFE;

// Magic number (4 bytes), version (2 bytes), flags (2 bytes), header size (4 bytes) = 12
const int FormatUtils::DICTIONARY_MINIMUM_SIZE = 12;

/* static */ FormatUtils::FORMAT_VERSION FormatUtils::getFormatVersion(const int formatVersion) {
    std::cout << " -- >> " << formatVersion << std::endl;
    switch (formatVersion) {
        case VERSION_2:
            std::cout << "V2";
            return VERSION_2;
        case VERSION_4_ONLY_FOR_TESTING:
            std::cout << "V4TEST";
            return VERSION_4_ONLY_FOR_TESTING;
        case VERSION_4:
            std::cout << "V4";
            return VERSION_4;
        case VERSION_4_DEV:
            std::cout << "V4DEV";
            return VERSION_4_DEV;
        default:
            std::cout << "VUK";
            return UNKNOWN_VERSION;
    }
}
/* static */ FormatUtils::FORMAT_VERSION FormatUtils::detectFormatVersion(
        const uint8_t *const dict, const int dictSize) {
    // The magic number is stored big-endian.
    // If the dictionary is less than 4 bytes, we can't even read the magic number, so we don't
    // understand this format.
    if (dictSize < DICTIONARY_MINIMUM_SIZE) {
        std::cout << "too small ... :(" << std::endl;
        return UNKNOWN_VERSION;
    }
    const uint32_t magicNumber = ByteArrayUtils::readUint32(dict, 0);
    switch (magicNumber) {
        case MAGIC_NUMBER:
            // std::cout << "Correct? " << (magicNumber == MAGIC_NUMBER) << std::endl;
            // std::cout << "Magic number = " << magicNumber << " which is " << MAGIC_NUMBER <<  std::endl;

            // The layout of the header is as follows:
            // Magic number (4 bytes) 0x9B 0xC1 0x3A 0xFE
            // Dictionary format version number (2 bytes)
            // Options (2 bytes)
            // Header size (4 bytes) : integer, big endian
            // Conceptually this converts the hardcoded value of the bytes in the file into
            // the symbolic value we use in the code. But we want the constants to be the
            // same so we use them for both here.
            return VERSION_2;
            // return getFormatVersion(ByteArrayUtils::readUint16(dict, 4));
        default:
            std::cout << "no magic:" << magicNumber << " SHOUDL BE " << MAGIC_NUMBER <<  std::endl;
            return UNKNOWN_VERSION;
    }
}

} // namespace latinime
