#pragma once

#include <iostream>

class Vec3 {
public:
    float x, y, z;

    Vec3() {
        x = 0.0f;
        y = 0.0f;
        z = 0.0f;
    }

    Vec3(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
    }

    Vec3(const Vec3& vec3) {
        x = vec3.x;
        y = vec3.y;
        z = vec3.z;
    }

    float length() {
        return sqrt((x * x) + (y * y) + (z * z));
    }

    void normalize() {
        float len = length();
        x /= len;
        y /= len;
        z /= len;
    }

    Vec3 operator + (const float val) const {
        return Vec3(x + val, y + val, z + val);
    }

    Vec3 operator - (const float val) const {
        return Vec3(x - val, y - val, z - val);
    }

    Vec3 operator * (const float val) const {
        return Vec3(x * val, y * val, z * val);
    }

    Vec3 operator / (const float val) const {
        return Vec3(x / val, y / val, z / val);
    }

    Vec3 operator + (const Vec3& vec3) const {
        return Vec3(x + vec3.x, y + vec3.y, z + vec3.z);
    }

    Vec3 operator - (const Vec3& vec3) const {
        return Vec3(x - vec3.x, y - vec3.y, z - vec3.z);
    }

    void operator += (const float val) {
        x += val;
        y += val;
        z += val;
    }

    void operator -= (const float val) {
        x -= val;
        y -= val;
        z -= val;
    }

    void operator *= (const float val) {
        x *= val;
        y *= val;
        z *= val;
    }

    void operator /= (const float val) {
        x /= val;
        y /= val;
        z /= val;
    }

    void operator =  (const Vec3 vec3) {
        x = vec3.x;
        y = vec3.y;
        z = vec3.z;
    }

    void operator += (const Vec3 vec3) {
        x += vec3.x;
        y += vec3.y;
        z += vec3.z;
    }

    void operator -= (const Vec3 vec3) {
        x -= vec3.x;
        y -= vec3.y;
        z -= vec3.z;
    }

    bool operator > (Vec3 vec3) {
        float len1 = length();
        float len2 = vec3.length();
        return len1 > len2;
    }

    bool operator < (Vec3 vec3) {
        float len1 = length();
        float len2 = vec3.length();
        return len1 < len2;
    }

    Vec3 cross(Vec3 vec3) {
        float _x = (y * vec3.z) - (z * vec3.y);
        float _y = (z * vec3.x) - (x * vec3.z);
        float _z = (x * vec3.y) - (y * vec3.x);
        return Vec3(_x, _y, _z);
    }

    float dot(Vec3 vec3) {
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
