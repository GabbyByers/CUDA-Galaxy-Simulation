#pragma once

#include <iostream>

__device__ __host__ class Vec3 {
public:
    float x, y, z;

    __device__ __host__ Vec3() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    __device__ __host__ Vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    __device__ __host__ Vec3(const Vec3& vec3) {
        x = vec3.x;
        y = vec3.y;
        z = vec3.z;
    }

    __device__ __host__ float length() {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    __device__ __host__ void normalize() {
        float len = length();
        x /= len;
        y /= len;
        z /= len;
    }

    __device__ __host__ Vec3 operator + (const float val) const {
        return Vec3(x + val, y + val, z + val);
    }

    __device__ __host__ Vec3 operator - (const float val) const {
        return Vec3(x - val, y - val, z - val);
    }

    __device__ __host__ Vec3 operator * (const float val) const {
        return Vec3(x * val, y * val, z * val);
    }

    __device__ __host__ Vec3 operator / (const float val) const {
        return Vec3(x / val, y / val, z / val);
    }

    __device__ __host__ Vec3 operator + (const Vec3& vec3) const {
        return Vec3(x + vec3.x, y + vec3.y, z + vec3.z);
    }

    __device__ __host__ Vec3 operator - (const Vec3& vec3) const {
        return Vec3(x - vec3.x, y - vec3.y, z - vec3.z);
    }

    __device__ __host__ void operator += (const float val) {
        x += val;
        y += val;
        z += val;
    }

    __device__ __host__ void operator -= (const float val) {
        x -= val;
        y -= val;
        z -= val;
    }

    __device__ __host__ void operator *= (const float val) {
        x *= val;
        y *= val;
        z *= val;
    }

    __device__ __host__ void operator /= (const float val) {
        x /= val;
        y /= val;
        z /= val;
    }

    __device__ __host__ void operator =  (const Vec3 vec3) {
        x = vec3.x;
        y = vec3.y;
        z = vec3.z;
    }

    __device__ __host__ void operator += (const Vec3 vec3) {
        x += vec3.x;
        y += vec3.y;
        z += vec3.z;
    }

    __device__ __host__ void operator -= (const Vec3 vec3) {
        x -= vec3.x;
        y -= vec3.y;
        z -= vec3.z;
    }

    __device__ __host__ bool operator > (Vec3 vec3) {
        float len1 = length();
        float len2 = vec3.length();
        return len1 > len2;
    }

    __device__ __host__ bool operator < (Vec3 vec3) {
        float len1 = length();
        float len2 = vec3.length();
        return len1 < len2;
    }

    __device__ __host__ Vec3 cross(Vec3 vec3) {
        float _x = (y * vec3.z) - (z * vec3.y);
        float _y = (z * vec3.x) - (x * vec3.z);
        float _z = (x * vec3.y) - (y * vec3.x);
        return Vec3(_x, _y, _z);
    }

    __device__ __host__ float dot(Vec3 vec3) {
        return (x * vec3.x) + (y * vec3.y) + (z * vec3.z);
    }

    void print() {
        std::cout << "[" << x << ", " << y << ", " << z << "]\n";
    }

    void print(std::string str) {
        std::cout << str << ": ";
        std::cout << "[" << x << ", " << y << ", " << z << "]\n";
    }
};
