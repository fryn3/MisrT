#ifndef MISRT_H
#define MISRT_H

#include <stdint.h>
#include <cassert>

template <class T>
class MisrT {
public:
    static const uint64_t IV_64 = 0xFAC432B10CD5E44A;
    static const uint64_t POLY_64 = 0x00060034000F050B;

    static const uint32_t IV_32 = 0xFFFFFFFF;
    static const uint32_t POLY_32 = 0x04C11DB7;

    static const uint16_t IV_16 = 0xFFFF;
    static const uint16_t POLY_16 = 0x8005;

    static const uint8_t IV_8 = 0xFF;
    static const uint8_t POLY_8 = 0x9B;

    static const uint8_t IV_4 = 0x0;
    static const uint8_t POLY_4 = 0x3;

    inline void initialization() noexcept { assert(false); }
    MisrT() noexcept { initialization(); }
    MisrT(T initValue, T poly) noexcept : _initValue(initValue),
                                    _poly(poly), _prevMisr(initValue) { }
    inline void reset() noexcept { _prevMisr = _initValue; }
    inline T done(T in) noexcept {
        _prevMisr = (_prevMisr >> (sizeof (T) * 8 - 1) ? _poly : 0) ^ in ^ (_prevMisr << 1);
        return _prevMisr;
    }
    inline T value() const noexcept { return _prevMisr; }
private:
    T _initValue;
    T _poly;
    T _prevMisr;
};

template <>
inline void MisrT<uint64_t>::initialization() noexcept {
    _initValue = _prevMisr = IV_64;
    _poly = POLY_64;
}

template <>
inline void MisrT<uint32_t>::initialization() noexcept {
    _initValue = _prevMisr = IV_32;
    _poly = POLY_32;
}

template <>
inline void MisrT<uint16_t>::initialization() noexcept {
    _initValue = _prevMisr = IV_16;
    _poly = POLY_16;
}

template <>
inline void MisrT<uint8_t>::initialization() noexcept {
    _initValue = _prevMisr = IV_8;
    _poly = POLY_8;
}

#endif  // MISRT_H
