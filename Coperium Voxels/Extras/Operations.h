#pragma once
#ifndef WORLD_DATA_OPERATIONS_H
#define WORLD_DATA_OPERATIONS_H

inline int WD_Div(int a, int b) {
    return (a - ((a < 0) ? (b - 1) : 0)) / b;
}

// Optimized modulus for negative values
inline int WD_Mod(int a, int b) {
    return (a % b + b) % b;
}


#endif // !WORLD_DATA_OPERATIONS_H