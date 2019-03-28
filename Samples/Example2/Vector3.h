//
// Created by ZhiquanWang on 2018/7/4.
//

#ifndef MATRIXOPERATION_CPP_Vector3_H
#define MATRIXOPERATION_CPP_Vector3_H


#include <iostream>
#include <cmath>

class Vector3 {
private:
    double_t vec3[3]{};
public:
    Vector3();

    Vector3(const Vector3 &);

    Vector3(double_t, double_t, double_t);

    inline void set_vector(double_t, double_t, double_t);

    inline double_t x() const;

    inline double_t y() const;

    inline double_t z() const;

    inline double_t r() const;

    inline double_t g() const;

    inline double_t b() const;

    inline void set_x(double_t _x);

    inline void set_y(double_t _y);

    inline void set_z(double_t _z);

    inline const Vector3 &operator+() const;

    inline Vector3 operator-();

    inline double_t operator[](int) const;

    inline double_t &operator[](int);

    inline Vector3 &operator+=(const Vector3 &);

    inline Vector3 &operator-=(const Vector3 &);

    inline Vector3 &operator*=(const Vector3 &);

    inline Vector3 &operator*=(const double_t &);

    inline Vector3 &operator/=(const Vector3 &);

    inline Vector3 &operator/=(const double_t &);

    inline bool operator==(const Vector3 &);

    inline bool operator!=(const Vector3 &);

    inline double_t length() const;

    inline double_t distance() const;

    inline double_t squared_distance() const;

    inline Vector3 normalize() const;
};

Vector3::Vector3() = default;

Vector3::Vector3(const Vector3 &_v) {
    for (int i = 0; i < 3; ++i) {
        this->vec3[i] = _v[i];
    }
}

Vector3::Vector3(double_t _n0, double_t _n1, double_t _n2) {
    this->vec3[0] = _n0;
    this->vec3[1] = _n1;
    this->vec3[2] = _n2;
}


inline void Vector3::set_vector(double_t _p0, double_t _p1, double_t _p2) {
    vec3[0] = _p0;
    vec3[1] = _p1;
    vec3[2] = _p2;
}

inline double_t Vector3::x() const {
    return this->vec3[0];
}

inline double_t Vector3::y() const {
    return this->vec3[1];
}

inline double_t Vector3::z() const {
    return this->vec3[2];
}

inline double_t Vector3::r() const {
    return this->vec3[0];
}

inline double_t Vector3::g() const {
    return this->vec3[1];
}

inline double_t Vector3::b() const {
    return this->vec3[2];
}

inline void Vector3::set_x(double_t _x) {
    this->vec3[0] = _x;
}

inline void Vector3::set_y(double_t _y) {
    this->vec3[1] = _y;
}

inline void Vector3::set_z(double_t _z) {
    this->vec3[2] = _z;
}


inline const Vector3 &Vector3::operator+() const {
    return *this;
}

inline Vector3 Vector3::operator-() {
    return Vector3(-1 * this->vec3[0], -1 * this->vec3[1], -1 * this->vec3[2]);
}

inline double_t Vector3::operator[](int _i) const {
    return this->vec3[_i];
}

inline double_t &Vector3::operator[](int _i) {
    return this->vec3[_i];
}

inline Vector3 &Vector3::operator+=(const Vector3 &_v) {
    for (int i = 0; i < 3; ++i) {
        this->vec3[i] += _v[i];
    }
    return *this;
}

inline Vector3 &Vector3::operator-=(const Vector3 &_v) {
    for (int i = 0; i < 3; ++i) {
        this->vec3[i] -= _v[i];
    }
    return *this;
}

inline Vector3 &Vector3::operator*=(const Vector3 &_v) {
    for (int i = 0; i < 3; ++i) {
        this->vec3[i] *= _v[i];
    }
    return *this;
}

inline Vector3 &Vector3::operator*=(const double_t &_d) {
    for (double_t &data : this->vec3) {
        data *= _d;
    }
    return *this;
}

inline Vector3 &Vector3::operator/=(const Vector3 &_v) {
    for (int i = 0; i < 3; ++i) {
        this->vec3[i] /= _v[i];
    }
    return *this;
}

inline Vector3 &Vector3::operator/=(const double_t &_d) {
    for (double_t &data : this->vec3) {
        data /= _d;
    }
    return *this;
}

inline double_t Vector3::length() const {
    return sqrt(this->vec3[0] * this->vec3[0] + this->vec3[1] * this->vec3[1] + this->vec3[2] * this->vec3[2]);
}

inline double_t Vector3::distance() const {
    return sqrt(this->vec3[0] * this->vec3[0] + this->vec3[1] * this->vec3[1] + this->vec3[2] * this->vec3[2]);
}

inline double_t Vector3::squared_distance() const {
    return this->vec3[0] * this->vec3[0] + this->vec3[1] * this->vec3[1] + this->vec3[2] * this->vec3[2];
}

inline Vector3 Vector3::normalize() const {
    double_t tmp_len = this->length();
    if (tmp_len == 0.0) {
        return Vector3();
    }
    Vector3 tmp_v = *this;
    for (double_t &data : tmp_v.vec3) {
        data /= tmp_len;
    }
    return tmp_v;
}

inline bool Vector3::operator==(const Vector3 &_v) {
    for (int i = 0; i < 3; ++i) {
        if (this->vec3[i] != _v[i]) {
            return false;
        }
    }
    return true;
}

inline bool Vector3::operator!=(const Vector3 &_v) {
    return !(*this == _v);
}

inline std::istream &operator>>(std::istream &_is, Vector3 &_v) {
    _is >> _v[0] >> _v[1] >> _v[2];
    return _is;
}

inline std::ostream &operator<<(std::ostream &_os, const Vector3 &_v) {
    _os << "(" << _v[0] << "," << _v[1] << "," << _v[2] << ")";
    return _os;
}

inline double_t dot(const Vector3 &_v0, const Vector3 &_v1) {
    double_t tmp_result = 0;
    for (int i = 0; i < 3; ++i) {
        tmp_result += _v0[i] * _v1[i];
    }
    return tmp_result;
}

inline Vector3 cross(const Vector3 &_v0, const Vector3 &_v1) {
    return {_v0[1] * _v1[2] - _v0[2] * _v1[1], _v0[2] * _v1[0] - _v0[0] * _v1[2], _v0[0] * _v1[1] - _v0[1] * _v1[0]};
}

inline Vector3 operator+(const Vector3 &_v0, const Vector3 &_v1) {
    return {_v0[0] + _v1[0], _v0[1] + _v1[1], _v0[2] + _v1[2]};
}

inline Vector3 operator-(const Vector3 &_v0, const Vector3 &_v1) {
    return {_v0[0] - _v1[0], _v0[1] - _v1[1], _v0[2] - _v1[2]};
}

inline Vector3 operator*(const Vector3 &_v0, const Vector3 &_v1) {
    return {_v0[0] * _v1[0], _v0[1] * _v1[1], _v0[2] * _v1[2]};
}

inline Vector3 operator*(const Vector3 &_v0, const double_t &_d) {
    return {_v0[0] * _d, _v0[1] * _d, _v0[2] * _d};
}

inline Vector3 operator*(const double_t &_d, const Vector3 &_v0) {
    return {_v0[0] * _d, _v0[1] * _d, _v0[2] * _d};
}

inline Vector3 operator/(const Vector3 &_v0, const Vector3 &_v1) {
    return {_v0[0] / _v1[0], _v0[1] / _v1[1], _v0[2] / _v1[2]};
}

inline Vector3 operator/(const Vector3 &_v0, const double_t &_d) {
    return {_v0[0] / _d, _v0[1] / _d, _v0[2] / _d};
}


#endif //MATRIXOPERATION_CPP_Vector3_H
