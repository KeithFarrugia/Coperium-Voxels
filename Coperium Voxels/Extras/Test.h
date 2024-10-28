#pragma once
#include <cstdint>
#include <cmath>
#include <cstring> // for memcpy

class Block_VD {
private:
    uint32_t data;

    // Masks and shifts for X, Y, and Z
    static constexpr uint32_t X_SIGN_MASK = 0x1;
    static constexpr uint32_t X_MANTISSA_MASK = 0xF;  // 4 bits
    static constexpr uint32_t X_FRACTION_MASK = 0x1F; // 5 bits
    static constexpr uint32_t Y_SIGN_MASK = 0x1;
    static constexpr uint32_t Y_MANTISSA_MASK = 0x3F; // 6 bits
    static constexpr uint32_t Y_FRACTION_MASK = 0x1F; // 5 bits
    static constexpr uint32_t Z_SIGN_MASK = 0x1;
    static constexpr uint32_t Z_MANTISSA_MASK = 0xF;  // 4 bits
    static constexpr uint32_t Z_FRACTION_MASK = 0x1F; // 5 bits

    static constexpr uint8_t X_SIGN_SHIFT = 9;
    static constexpr uint8_t X_MANTISSA_SHIFT = 5;
    static constexpr uint8_t Y_SIGN_SHIFT = 21;
    static constexpr uint8_t Y_MANTISSA_SHIFT = 15;
    static constexpr uint8_t Y_FRACTION_SHIFT = 10;
    static constexpr uint8_t Z_SIGN_SHIFT = 31;
    static constexpr uint8_t Z_MANTISSA_SHIFT = 27;
    static constexpr uint8_t Z_FRACTION_SHIFT = 22;

    static constexpr float FRACTION_DIVISOR = 32.0f; // 2^5

    float combineToFloat(bool sign, uint8_t mantissa, uint8_t fraction) const {
        float value = mantissa + (fraction / FRACTION_DIVISOR);
        return sign ? -value : value;
    }

    void decomposeFloat(float f, bool& sign, uint8_t& mantissa, uint8_t& fraction) const {
        sign = f < 0;
        float abs_f = std::abs(f);
        mantissa = static_cast<uint8_t>(abs_f);
        fraction = static_cast<uint8_t>((abs_f - mantissa) * FRACTION_DIVISOR);
    }

public:
    Block_VD() : data(0) {}

    void Set_X(float f) {
        bool sign;
        uint8_t mantissa, fraction;
        decomposeFloat(f, sign, mantissa, fraction);
        Set_X(sign, mantissa, fraction);
    }

    void Set_X(const bool sign, const uint8_t mantissa, const uint8_t fraction) {
        data &= ~((0x1FF << 0)); // Clear x bits
        data |= (sign & X_SIGN_MASK) << X_SIGN_SHIFT;
        data |= (mantissa & X_MANTISSA_MASK) << X_MANTISSA_SHIFT;
        data |= (fraction & X_FRACTION_MASK) << 0;
    }

    float Get_X() const {
        bool sign = (data >> X_SIGN_SHIFT) & X_SIGN_MASK;
        uint8_t mantissa = (data >> X_MANTISSA_SHIFT) & X_MANTISSA_MASK;
        uint8_t fraction = (data >> 0) & X_FRACTION_MASK;
        return combineToFloat(sign, mantissa, fraction);
    }

    void Set_Y(float f) {
        bool sign;
        uint8_t mantissa, fraction;
        decomposeFloat(f, sign, mantissa, fraction);
        Set_Y(sign, mantissa, fraction);
    }

    void Set_Y(const bool sign, const uint8_t mantissa, const uint8_t fraction) {
        data &= ~((0xFFF << 10)); // Clear y bits
        data |= (sign & Y_SIGN_MASK) << Y_SIGN_SHIFT;
        data |= (mantissa & Y_MANTISSA_MASK) << Y_MANTISSA_SHIFT;
        data |= (fraction & Y_FRACTION_MASK) << Y_FRACTION_SHIFT;
    }

    float Get_Y() const {
        bool sign = (data >> Y_SIGN_SHIFT) & Y_SIGN_MASK;
        uint8_t mantissa = (data >> Y_MANTISSA_SHIFT) & Y_MANTISSA_MASK;
        uint8_t fraction = (data >> Y_FRACTION_SHIFT) & Y_FRACTION_MASK;
        return combineToFloat(sign, mantissa, fraction);
    }

    void Set_Z(float f) {
        bool sign;
        uint8_t mantissa, fraction;
        decomposeFloat(f, sign, mantissa, fraction);
        Set_Z(sign, mantissa, fraction);
    }

    void Set_Z(const bool sign, const uint8_t mantissa, const uint8_t fraction) {
        data &= ~((0x3FF << 22)); // Clear z bits
        data |= (sign & Z_SIGN_MASK) << Z_SIGN_SHIFT;
        data |= (mantissa & Z_MANTISSA_MASK) << Z_MANTISSA_SHIFT;
        data |= (fraction & Z_FRACTION_MASK) << Z_FRACTION_SHIFT;
    }

    float Get_Z() const {
        bool sign = (data >> Z_SIGN_SHIFT) & Z_SIGN_MASK;
        uint8_t mantissa = (data >> Z_MANTISSA_SHIFT) & Z_MANTISSA_MASK;
        uint8_t fraction = (data >> Z_FRACTION_SHIFT) & Z_FRACTION_MASK;
        return combineToFloat(sign, mantissa, fraction);
    }

    GLfloat To_GLfloat() const {
        GLfloat result;
        std::memcpy(&result, &data, sizeof(data));
        return result;
    }

    void From_GLfloat(GLfloat glfloat) {
        std::memcpy(&data, &glfloat, sizeof(data));
    }

    static GLfloat Compact(const float x, const float y, const float z){
        Block_VD block_vertex;
        block_vertex.Set_X(x);
        block_vertex.Set_Y(y);
        block_vertex.Set_Z(z);
        return block_vertex.To_GLfloat();
    }
};
