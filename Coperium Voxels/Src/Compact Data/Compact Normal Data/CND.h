#pragma once
#ifndef COMPACT_NORMAL_DATA_H
#define COMPACT_NORMAL_DATA_H

#include <cstdint>
#include <cstring>
#include <glm/glm.hpp>

class CND {
public:
    CND();
    CND(float packed);

    float To_Float() const;
    void  From_Float(float f);

    void Set_X(float vx);
    void Set_Y(float vy);
    void Set_Z(float vz);

    float Get_X() const;
    float Get_Y() const;
    float Get_Z() const;

    glm::vec3 Unpack() const;
    static float Compact(float x, float y, float z);

    void Scale(float factor);
    void Normalize();

private:
    uint32_t data;

    static constexpr int      X_S_SHIFT = 31;
    static constexpr int      X_M_SHIFT = 22;
    static constexpr int      Y_S_SHIFT = 21;
    static constexpr int      Y_M_SHIFT = 12;
    static constexpr int      Z_S_SHIFT = 11;
    static constexpr int      Z_M_SHIFT = 2;
    static constexpr uint32_t MASK_1 = 0x1;
    static constexpr uint32_t MASK_9 = 0x1FF;
    static constexpr float    MAG_SCALE = 511.0f;

    void Normalize(const glm::vec3& v);
};

#endif // COMPACT_NORMAL_DATA_H
