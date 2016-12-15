// RUN: avrlit %s | FileCheck %s

#include "support.h"

extern "C" {

#define DEFINE_HELPERS(name, op)                      \
  u8 name##_u8_u8(u8 a, u8 b) { return a op b; }      \
  u16 name##_u16_u16(u16 a, u16 b) { return a op b; } \
  u32 name##_u32_u32(u32 a, u32 b) { return a op b; } \
  u64 name##_u64_u64(u64 a, u64 b) { return a op b; } \
  u64 name##_u64_u8(u64 a, u8 b) { return a op b; }   \

DEFINE_HELPERS(add, +);
DEFINE_HELPERS(sub, -);
DEFINE_HELPERS(mul, *);
DEFINE_HELPERS(div, /);
DEFINE_HELPERS(and, &);
DEFINE_HELPERS(or, |);

/// Linear interpolation.
float lerp(float x1, float y1, float x2, float y2, float ratio) {
  float gradient = (y2-y1)/(x2-x1);
  float range = x2-x1;
  float x = range * ratio;

  return y1 + (gradient*x);
}

void test_addition() {
  // CHECK: add_u8_u8(a: 51, b: 42)
  // CHECK-NEXT: return 93
  add_u8_u8(51, 42);

  // CHECK: add_u8_u8(a: 127, b: 128)
  // CHECK-NEXT: return 255
  add_u8_u8(127, 128);

  // CHECK: add_u32_u32(a: 9000, b: 9001)
  // CHECK-NEXT: return 18001
  add_u32_u32(9000, 9001);

  // CHECK: add_u64_u8(a: 100000, b: 13)
  // CHECK-NEXT: 100013
  add_u64_u8(100000, 13);

  // CHECK: add_u64_u64(a: 123456789, b: 1)
  // CHECK-NEXT: 123456790
  add_u64_u64(123456789, 1);
}

void test_subtraction() {
  // CHECK: sub_u8_u8(a: 51, b: 42)
  // CHECK-NEXT: return 9
  sub_u8_u8(51, 42);

  // CHECK: sub_u32_u32(a: 9001, b: 9000)
  // CHECK-NEXT: return 1
  sub_u32_u32(9001, 9000);

  // CHECK: sub_u64_u8(a: 100000, b: 13)
  // CHECK-NEXT: 99987
  sub_u64_u8(100000, 13);

  // CHECK: sub_u64_u64(a: 123456789, b: 1)
  // CHECK-NEXT: 123456788
  sub_u64_u64(123456789, 1);
}

void test_multiplication() {
  // CHECK: mul_u8_u8(a: 2, b: 2)
  // CHECK-NEXT: 4
  mul_u8_u8(2, 2);

  // CHECK: mul_u32_u32(a: 5123, b: 54322)
  // CHECK-NEXT: 278291606
  mul_u32_u32(5123, 54322);
}

void test_div() {
  // CHECK: div_u8_u8(a: 10, b: 2)
  // CHECK-NEXT: 5
  div_u8_u8(10, 2);

  // CHECK: div_u8_u8(a: 64, b: 8)
  // CHECK-NEXT: 8
  div_u8_u8(64, 8);

  // CHECK: div_u32_u32(a: 35924, b: 7)
  // CHECK-NEXT: 5132
  div_u32_u32(35924, 7);
}

void test_and() {
  // CHECK: and_u8_u8(a: 255, b: 255)
  // CHECK-NEXT: return 255
  and_u8_u8(255, 255);

  // CHECK: and_u8_u8(a: 255, b: 0)
  // CHECK-NEXT: return 0
  and_u8_u8(255, 0);

  // CHECK: and_u8_u8(a: 0, b: 255)
  // CHECK-NEXT: return 0
  and_u8_u8(0, 255);

  // CHECK: and_u16_u16(a: 61680, b: 3855)
  // CHECK-NEXT: return 0
  and_u16_u16(0xf0f0, 0x0f0f);
}

void test_or() {
  // CHECK: or_u8_u8(a: 255, b: 255)
  // CHECK-NEXT: return 255
  or_u8_u8(255, 255);

  // CHECK: or_u8_u8(a: 255, b: 0)
  // CHECK-NEXT: return 255
  or_u8_u8(255, 0);

  // CHECK: or_u8_u8(a: 0, b: 255)
  // CHECK-NEXT: return 255
  or_u8_u8(0, 255);

  // CHECK: or_u16_u16(a: 61680, b: 3855)
  // CHECK-NEXT: return 65535
  or_u16_u16(0xf0f0, 0x0f0f);
}

void test_pow() {
}

void test_lerp() {
  // CHECK: lerp(x1: 0.000000, y1: 0.000000, x2: 90.000000, y2: 90.000000, ratio: 0.500000)
  // CHECK-NEXT: return 45.000000
  lerp(0.0f, 0.0f, 90.0f, 90.0f, 0.5f);

  // CHECK: lerp(x1: 0.000000, y1: 0.000000, x2: 90.000000, y2: 90.000000, ratio: 1.000000)
  // CHECK-NEXT: return 90.000000
  lerp(0.0f, 0.0f, 90.0f, 90.0f, 1.0f);
}

void test() {
  test_addition();
  test_subtraction();
  test_multiplication();
  test_div();
  test_and();
  test_or();
  test_pow();
  test_lerp();
}

} // end extern "C"
