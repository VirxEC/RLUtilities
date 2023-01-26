#pragma once

#include <math.h>
#include <iostream>
#include <initializer_list>

template <int N0, int N1>
class mat {
  float data[N0 * N1];

 public:
  mat() {}

  explicit mat(float value) {
    for (int i = 0; i < N0 * N1; i++) {
      data[i] = value;
    }
  }

  mat(std::initializer_list<std::initializer_list<float> > args) {
    int r = 0;
    for (auto row : args) {
      int c = 0;
      for (auto val : row) {
        operator()(r, c) = val;
        c++;
      }
      r++;
    }
  }

  float& operator[](const size_t i) { return data[i]; }
  float operator[](const size_t i) const { return data[i]; }
  float& operator()(const size_t i0, const size_t i1) {
    return data[i0 + N0 * i1];
  }

  float operator()(const size_t i0, const size_t i1) const {
    return data[i0 + N0 * i1];
  }
};

template <int m, int n>
inline mat<n, m> transpose(const mat<m, n>& A) {
  mat<n, m> AT;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      AT(j, i) = A(i, j);
    }
  }
  return AT;
}

template <int m, int n>
inline mat<m, n> operator+(const mat<m, n>& A, const mat<m, n>& B) {
  mat<m, n> C;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      C(i, j) = A(i, j) + B(i, j);
    }
  }
  return C;
}

template <int m, int n>
inline mat<m, n> operator-(const mat<m, n>& A, const mat<m, n>& B) {
  mat<m, n> C;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      C(i, j) = A(i, j) - B(i, j);
    }
  }
  return C;
}



template <int m, int n>
inline mat<m, n> operator*(const mat<m, n>& A, const float other) {
  mat<m, n> B;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      B(i, j) = other * A(i, j);
    }
  }
  return B;
}

template <int m, int n>
inline mat<m, n> operator*(const float other, const mat<m, n>& A) {
  mat<m, n> B;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      B(i, j) = other * A(i, j);
    }
  }
  return B;
}

template <int m, int n>
inline mat<m, n> operator*(const mat<m, n>& A, const mat<m, n>& B) {
  mat<m, n> C;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      C(i, j) = A(i, j) * B(i, j);
    }
  }
  return C;
}

template <int m, int n>
inline mat<m, n> operator/(const mat<m, n>& A, const float denominator) {
  mat<m, n> B;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      B(i, j) = A(i, j) / denominator;
    }
  }
  return B;
}

template <int m, int n>
std::ostream& operator<<(std::ostream& os, const mat<m, n>& A) {
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      os << A(i, j);
      if (j == n - 1) os << "\n";
      else          os << ", ";
    }
  }
  return os;
}

typedef mat<2, 2> mat2;
typedef mat<3, 3> mat3;
typedef mat<4, 4> mat4;
