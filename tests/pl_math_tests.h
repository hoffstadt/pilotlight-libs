#include <stdio.h>

#define PL_MATH_INCLUDE_FUNCTIONS
#include "pl_math.h"
#include "pl_test.h"

void math_test_sizes() {
    pl_test_expect_int_equal(sizeof(plVec2), 8, NULL);
    pl_test_expect_int_equal(sizeof(plVec3), 12, NULL);
    pl_test_expect_int_equal(sizeof(plVec4), 16, NULL);
    pl_test_expect_int_equal(sizeof(plRect), 16, NULL);
    // Check(Quattro) we should also check complex struct types, because SSE gives alignment shit
    //                AFAIK having a struct with vec3 and vec4 give a size of 32 (even if in the opposite order)
}
void math_test_struct_creation() {
    {
        plVec2 v = {-2, 0};
        pl_test_expect_vec2_near_equal(pl_create_vec2(-2, 0), v, 0.01f, NULL);
    }
    {
        plVec3 v = {5, -2, 1};
        pl_test_expect_vec3_near_equal(pl_create_vec3(5, -2, 1), v, 0.01f, NULL);
    }
    {
        plVec4 v = {0, 1, 4, -2};
        pl_test_expect_vec4_near_equal(pl_create_vec4(0, 1, 4, -2), v, 0.01f, NULL);
    }
    {
        plMat4 m1 = {4, 0, 0, 0, 0, 8, 0, 0, 0, 0, 3, 0, 0, 0, 0, 1};
        pl_test_expect_mat4_near_equal(pl_create_mat4_diag(4, 8, 3, 1), m1, 0.01f, NULL);
        plMat4 m2 = {5, -2, 3, -1, 0, 5, 2, 3, 8, 1, -4, -6, 2, 4, -6, 0};
        pl_test_expect_mat4_near_equal(pl_create_mat4_cols(pl_create_vec4(5, -2, 3, -1), pl_create_vec4(0, 5, 2, 3), pl_create_vec4(8, 1, -4, -6), pl_create_vec4(2, 4, -6, 0)), m2, 0.01f, NULL);
    }
    {
        plRect r1 = {{1, 2}, {5, 6}};
        pl_test_expect_rect_near_equal(pl_create_rect_vec2(pl_create_vec2(1, 2), pl_create_vec2(5, 6)), r1, 0.01f, NULL);
        plRect r2 = {-1, -5, 2, 3};
        pl_test_expect_rect_near_equal(pl_create_rect(-1, -5, 2, 3), r2, 0.01f, NULL);
    }
}
void math_test_simple_functions() {
    {
        pl_test_expect_float_near_equal(pl_radiansf(0),   0,             0.01f, NULL);
        pl_test_expect_float_near_equal(pl_radiansf(30),  PL_PI / 6,     0.01f, NULL);
        pl_test_expect_float_near_equal(pl_radiansf(45),  PL_PI_4,       0.01f, NULL);
        pl_test_expect_float_near_equal(pl_radiansf(60),  PL_PI_3,       0.01f, NULL);
        pl_test_expect_float_near_equal(pl_radiansf(90),  PL_PI_2,       0.01f, NULL);
        pl_test_expect_float_near_equal(pl_radiansf(180), PL_PI,         0.01f, NULL);
        pl_test_expect_float_near_equal(pl_radiansf(270), PL_PI * 3 / 2, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_radiansf(360), PL_2PI,        0.01f, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_degreesf(0),             0,   0.01f, NULL);
        pl_test_expect_float_near_equal(pl_degreesf(PL_PI / 6),     30,  0.01f, NULL);
        pl_test_expect_float_near_equal(pl_degreesf(PL_PI_4),       45,  0.01f, NULL);
        pl_test_expect_float_near_equal(pl_degreesf(PL_PI_3),       60,  0.01f, NULL);
        pl_test_expect_float_near_equal(pl_degreesf(PL_PI_2),       90,  0.01f, NULL);
        pl_test_expect_float_near_equal(pl_degreesf(PL_PI),         180, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_degreesf(PL_PI * 3 / 2), 270, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_degreesf(PL_2PI),        360, 0.01f, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_maxf(1.42f, 4), 4, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_maxf(-1.65f, -2.114f), -1.65f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_maxf(-1, 4.4f), 4.4f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_maxf(-1.4f, 0.2f), 0.2f, 0.01f, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_minf(1.42f, 4), 1.42f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_minf(-1.65f, -2.114f), -2.114f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_minf(-1, 4.4f), -1, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_minf(-1.4f, 0.2f), -1.4f, 0.01f, NULL);
    }
    {
        pl_test_expect_int_equal(pl_maxi(1, 4), 4, NULL);
        pl_test_expect_int_equal(pl_maxi(-1, -2), -1, NULL);
        pl_test_expect_int_equal(pl_maxi(-1, 4), 4, NULL);
        pl_test_expect_int_equal(pl_maxi(-1, 0), 0, NULL);
    }
    {
        pl_test_expect_int_equal(pl_mini(1, 4), 1, NULL);
        pl_test_expect_int_equal(pl_mini(-1, -2), -2, NULL);
        pl_test_expect_int_equal(pl_mini(-1, 4), -1, NULL);
        pl_test_expect_int_equal(pl_mini(-1, 0), -1, NULL);
    }
    {
        pl_test_expect_unsigned_equal(pl_maxu(1, 4), 4, NULL);
        pl_test_expect_unsigned_equal(pl_maxu(1, 2), 2, NULL);
        pl_test_expect_unsigned_equal(pl_maxu(8, 4), 8, NULL);
        pl_test_expect_unsigned_equal(pl_maxu(1, 0), 1, NULL);
    }
    {
        pl_test_expect_unsigned_equal(pl_minu(1, 4), 1, NULL);
        pl_test_expect_unsigned_equal(pl_minu(1, 2), 1, NULL);
        pl_test_expect_unsigned_equal(pl_minu(8, 4), 4, NULL);
        pl_test_expect_unsigned_equal(pl_minu(1, 0), 0, NULL);
    }
        {
        pl_test_expect_double_near_equal(pl_maxd(1.42, 4), 4, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_maxd(-1.65, -2.114), -1.65, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_maxd(-1, 4.4), 4.4, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_maxd(-1.4, 0.2), 0.2, 0.01, NULL);
    }
    {
        pl_test_expect_double_near_equal(pl_mind(1.42, 4), 1.42, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_mind(-1.65, -2.114), -2.114, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_mind(-1, 4.4), -1, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_mind(-1.4, 0.2), -1.4, 0.01, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_square(4), 16, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_square(3), 9, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_square(-5), 25, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_square(0), 0, 0.01f, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_cubef(4), 64, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_cubef(3), 27, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_cubef(-5), -125, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_cubef(0), 0, 0.01f, NULL);
    }
    {
        pl_test_expect_int_equal(pl_clampi(-1, 4, 8), 4, NULL);
        pl_test_expect_int_equal(pl_clampi(-1, -7, 8), -1, NULL);
        pl_test_expect_int_equal(pl_clampi(-1, 12, 8), 8, NULL);
        pl_test_expect_int_equal(pl_clampi(0, 0, 2), 0, NULL);
        pl_test_expect_int_equal(pl_clampi(0, -5, 2), 0, NULL);
        pl_test_expect_int_equal(pl_clampi(-8, -5, -2), -5, NULL);
        pl_test_expect_int_equal(pl_clampi(-8, -10, -2), -8, NULL);
        pl_test_expect_int_equal(pl_clampi(-8, 5, -2), -2, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_clampf(-1.01f, 4.54f, 8.12f), 4.54f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clampf(-1.93f, -7.45f, 8.9f), -1.93f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clampf(-1.412f, 12.54f, 8.12f), 8.12f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clampf(0.3f, 0.1f, 2.94f), 0.3f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clampf(0.3f, -5.23f, 2.65f), 0.3f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clampf(-8.12f, -5.98f, -2.23f), -5.98f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clampf(-8.12f, -10.6f, -2.86f), -8.12f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clampf(-8.09f, 5.15f, -2.83f), -2.83f, 0.01f, NULL);
    }
    {
        pl_test_expect_double_near_equal(pl_clampd(-1.01, 4.54, 8.12), 4.54, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clampd(-1.93, -7.45, 8.9), -1.93, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clampd(-1.412, 12.54, 8.12), 8.12, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clampd(0.3, 0.1, 2.94), 0.3, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clampd(0.3, -5.23, 2.65), 0.3, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clampd(-8.12, -5.98, -2.23), -5.98, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clampd(-8.12, -10.6, -2.86), -8.12, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clampd(-8.09, 5.15, -2.83), -2.83, 0.01, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_clamp01f(-1.12f), 0, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clamp01f(-0.2f), 0, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clamp01f(0), 0, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clamp01f(0.53f), 0.53f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clamp01f(1), 1, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_clamp01f(1.54f), 1, 0.01f, NULL);
    }
    {
        pl_test_expect_double_near_equal(pl_clamp01d(-1.12), 0, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clamp01d(-0.2), 0, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clamp01d(0), 0, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clamp01d(0.53), 0.53, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clamp01d(1), 1, 0.01, NULL);
        pl_test_expect_double_near_equal(pl_clamp01d(1.54), 1, 0.01, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_sqrt(9), 3, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_sqrt(4), 2, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_sqrt(3), 1.732f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_sqrt(2), 1.4142f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_sqrt(1), 1, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_sqrt(0), 0, 0.01f, NULL);
        pl_test_expect_float_near_not_equal(pl_sqrt(-2), 0, 0.01f, NULL);
    }
}
void math_test_vec2() {
    {
        pl_test_expect_float_near_equal(pl_length_sqr_vec2(pl_create_vec2(1, 3)), 10, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_sqr_vec2(pl_create_vec2(-4.6f, 3)), 30.16f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_sqr_vec2(pl_create_vec2(0, 1.529f)), 2.34f, 0.01f, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_length_vec2(pl_create_vec2(1, 3)), 3.16f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_vec2(pl_create_vec2(-4.6f, 3)), 5.5f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_vec2(pl_create_vec2(0, 1.529f)), 1.529f, 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_floor_vec2(pl_create_vec2(1, 3)), pl_create_vec2(1, 3), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_floor_vec2(pl_create_vec2(-4.6f, 3)), pl_create_vec2(-5, 3), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_floor_vec2(pl_create_vec2(0, 1.529f)), pl_create_vec2(0, 1), 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_clamp_vec2(pl_create_vec2(0, 3.14f), pl_create_vec2(5.2f, 3), pl_create_vec2(3, 9.32f)), pl_create_vec2(3, 3.14f), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_clamp_vec2(pl_create_vec2(-4.1f, 5.2f), pl_create_vec2(9.32f, -2), pl_create_vec2(7.42f, 5.8f)), pl_create_vec2(7.42f, 5.2f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_min_vec2(pl_create_vec2(-4.1f, 5.2f), pl_create_vec2(9.32f, -2)), pl_create_vec2(-4.1f, -2), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_min_vec2(pl_create_vec2(2.12f, 5.3f), pl_create_vec2(-5.3f, -5.4f)), pl_create_vec2(-5.3f, -5.4f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_max_vec2(pl_create_vec2(-4.1f, 5.2f), pl_create_vec2(9.32f, -2)), pl_create_vec2(9.32f, 5.2f), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_max_vec2(pl_create_vec2(2.12f, 5.3f), pl_create_vec2(-5.3f, -5.4f)), pl_create_vec2(2.12f, 5.3f), 0.01f, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_dot_vec2(pl_create_vec2(2.12f, 5.3f), pl_create_vec2(-5.3f, -5.4f)), -39.85f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_dot_vec2(pl_create_vec2(0, 1), pl_create_vec2(1, 0)), 0, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_dot_vec2(pl_create_vec2(1.2f, 1), pl_create_vec2(1.53f, -1)), 0.83f, 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_add_vec2(pl_create_vec2(3.82f, 1.3f), pl_create_vec2(-6.3f, -10.4f)), pl_create_vec2(-2.48f, -9.1f), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_add_vec2(pl_create_vec2(-15.12f, 0), pl_create_vec2(15.12f, 3)), pl_create_vec2(0, 3), 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_sub_vec2(pl_create_vec2(3.82f, 1.3f), pl_create_vec2(-6.3f, -10.4f)), pl_create_vec2(10.12f, 11.7f), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_sub_vec2(pl_create_vec2(-15.12f, 0), pl_create_vec2(15.12f, 3)), pl_create_vec2(-30.24f, -3), 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_mul_vec2(pl_create_vec2(3.82f, 1.3f), pl_create_vec2(-6.3f, -10.4f)), pl_create_vec2(-24.06f, -13.52f), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_mul_vec2(pl_create_vec2(-15.12f, 0), pl_create_vec2(15.12f, 3)), pl_create_vec2(-228.61f, 0), 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_div_vec2(pl_create_vec2(3.82f, 1.3f), pl_create_vec2(-6.3f, -10.4f)), pl_create_vec2(-0.61f, -0.125f), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_div_vec2(pl_create_vec2(-15.12f, 0), pl_create_vec2(15.12f, 3)), pl_create_vec2(-1, 0), 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_mul_vec2_scalarf(pl_create_vec2(3.82f, 1.3f), -2), pl_create_vec2(-7.64f, -2.6f), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_mul_vec2_scalarf(pl_create_vec2(-15.12f, 0), 5), pl_create_vec2(-75.6f, 0), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_mul_vec2_scalarf(pl_create_vec2(-545.12f, 54), 0), pl_create_vec2(0, 0), 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_div_vec2_scalarf(pl_create_vec2(3.82f, 1.3f), -2), pl_create_vec2(-1.91f, -0.65f), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_div_vec2_scalarf(pl_create_vec2(-15.12f, 0), 5), pl_create_vec2(-3.024f, 0), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_div_vec2_scalarf(pl_create_vec2(-545.12f, 54), 1), pl_create_vec2(-545.12f, 54), 0.01f, NULL);
    }
    {
        pl_test_expect_vec2_near_equal(pl_norm_vec2(pl_create_vec2(3.82f, 1.3f)), pl_create_vec2(0.946f, 0.322f), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_norm_vec2(pl_create_vec2(-15.12f, 0)), pl_create_vec2(-1, 0), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_norm_vec2(pl_create_vec2(-545.12f, 54)), pl_create_vec2(-0.995f, 0.098f), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_norm_vec2(pl_create_vec2(1, 0)), pl_create_vec2(1, 0), 0.01f, NULL);
        pl_test_expect_vec2_near_equal(pl_norm_vec2(pl_create_vec2(1, 1)), pl_create_vec2(PL_SQRT1_2, PL_SQRT1_2), 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_vec2(pl_norm_vec2(pl_create_vec2(3.82f, 1.3f))), 1, 0.01f, NULL);
    }
}
void math_test_vec3() {
    {
        pl_test_expect_float_near_equal(pl_length_sqr_vec3(pl_create_vec3(1, 3, -2)), 14, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_sqr_vec3(pl_create_vec3(-4.6f, 3, 1)), 31.16f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_sqr_vec3(pl_create_vec3(0, 1.529f, 4)), 18.34f, 0.01f, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_length_vec3(pl_create_vec3(1, 3, -2)), 3.74f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_vec3(pl_create_vec3(-4.6f, 3, 1)), 5.58f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_vec3(pl_create_vec3(0, 1.529f, 4)), 4.28f, 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_floor_vec3(pl_create_vec3(1, 3, -2.4f)), pl_create_vec3(1, 3, -3), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_floor_vec3(pl_create_vec3(-4.6f, 3, 1)), pl_create_vec3(-5, 3, 1), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_floor_vec3(pl_create_vec3(0, 1.529f, 0)), pl_create_vec3(0, 1, 0), 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_clamp_vec3(pl_create_vec3(0, 3.14f, 4), pl_create_vec3(5.2f, 3, -1.02f), pl_create_vec3(3, 9.32f, 6)), pl_create_vec3(3, 3.14f, 4), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_clamp_vec3(pl_create_vec3(-4.1f, 5.2f, -2.3f), pl_create_vec3(9.32f, -2, 3), pl_create_vec3(7.42f, 5.8f, 3.5f)), pl_create_vec3(7.42f, 5.2f, 3), 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_min_vec3(pl_create_vec3(-4.1f, 5.2f, 4.2f), pl_create_vec3(9.32f, -2, 1.02f)), pl_create_vec3(-4.1f, -2, 1.02f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_min_vec3(pl_create_vec3(2.12f, 5.3f, -2.3f), pl_create_vec3(-5.3f, -5.4f, 0.02f)), pl_create_vec3(-5.3f, -5.4f, -2.3f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_max_vec3(pl_create_vec3(-4.1f, 5.2f, 2.5f), pl_create_vec3(9.32f, -2, 0)), pl_create_vec3(9.32f, 5.2f, 2.5f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_max_vec3(pl_create_vec3(2.12f, 5.3f, -1.2f), pl_create_vec3(-5.3f, -5.4f, 2.3f)), pl_create_vec3(2.12f, 5.3f, 2.3f), 0.01f, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_dot_vec3(pl_create_vec3(2.12f, 5.3f, 1.2f), pl_create_vec3(-5.3f, -5.4f, 1)), -38.65f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_dot_vec3(pl_create_vec3(0, 1, 2), pl_create_vec3(1, 0, 0)), 0, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_dot_vec3(pl_create_vec3(1.2f, 1, 2.3f), pl_create_vec3(1.53f, -1, 1.65f)), 4.63f, 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_add_vec3(pl_create_vec3(3.82f, 1.3f, 0.2f), pl_create_vec3(-6.3f, -10.4f, 2.0f)), pl_create_vec3(-2.48f, -9.1f, 2.2f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_add_vec3(pl_create_vec3(-15.12f, 0, -5), pl_create_vec3(15.12f, 3, 1.2f)), pl_create_vec3(0, 3, -3.8f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_sub_vec3(pl_create_vec3(3.82f, 1.3f, 0.2f), pl_create_vec3(-6.3f, -10.4f, 2.0f)), pl_create_vec3(10.12f, 11.7f, -1.8f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_sub_vec3(pl_create_vec3(-15.12f, 0, -5), pl_create_vec3(15.12f, 3, 1.2f)), pl_create_vec3(-30.24f, -3, -6.2f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_mul_vec3(pl_create_vec3(3.82f, 1.3f, 0.2f), pl_create_vec3(-6.3f, -10.4f, 2.0f)), pl_create_vec3(-24.06f, -13.52f, 0.4f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_mul_vec3(pl_create_vec3(-15.12f, 0, -5), pl_create_vec3(15.12f, 3, 1.2f)), pl_create_vec3(-228.61f, 0, -6), 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_div_vec3(pl_create_vec3(3.82f, 1.3f, 0.2f), pl_create_vec3(-6.3f, -10.4f, 2.0f)), pl_create_vec3(-0.61f, -0.1250f, 0.1f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_div_vec3(pl_create_vec3(-15.12f, 0, -5), pl_create_vec3(15.12f, 3, 1.2f)), pl_create_vec3(-1, 0, -4.16f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_mul_vec3_scalarf(pl_create_vec3(3.82f, 1.3f, -4.2f), -2), pl_create_vec3(-7.64f, -2.6f, 8.4f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_mul_vec3_scalarf(pl_create_vec3(-15.12f, 0, 1), 5), pl_create_vec3(-75.6f, 0, 5), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_mul_vec3_scalarf(pl_create_vec3(-545.12f, 54, -12), 0), pl_create_vec3(0, 0, 0), 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_div_vec3_scalarf(pl_create_vec3(3.82f, 1.3f, -4.2f), -2), pl_create_vec3(-1.91f, -0.65f, 2.1f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_div_vec3_scalarf(pl_create_vec3(-15.12f, 0, 1), 5), pl_create_vec3(-3.024f, 0, 0.2f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_div_vec3_scalarf(pl_create_vec3(-545.12f, 54, -12), 1), pl_create_vec3(-545.12f, 54, -12), 0.01f, NULL);
    }
    {
        pl_test_expect_vec3_near_equal(pl_norm_vec3(pl_create_vec3(3.82f, 1.3f, -4.2f)), pl_create_vec3(0.656f, 0.223f, -0.72f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_norm_vec3(pl_create_vec3(-15.12f, 0, 1)), pl_create_vec3(-0.998f, 0, 0.066f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_norm_vec3(pl_create_vec3(-545.12f, 54, -12)), pl_create_vec3(-0.995f, 0.098f, -0.02f), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_norm_vec3(pl_create_vec3(1, 0, 0)), pl_create_vec3(1, 0, 0), 0.01f, NULL);
        pl_test_expect_vec3_near_equal(pl_norm_vec3(pl_create_vec3(1, 1, 1)), pl_create_vec3(PL_SQRT1_3, PL_SQRT1_3, PL_SQRT1_3), 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_vec3(pl_norm_vec3(pl_create_vec3(3.82f, 1.3f, 4.32f))), 1, 0.01f, NULL);
    }
}
void math_test_vec4() {
    {
        pl_test_expect_float_near_equal(pl_length_sqr_vec4(pl_create_vec4(1, 3, -2, 0)), 14, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_sqr_vec4(pl_create_vec4(-4.6f, 3, 1, 1.2f)), 32.6f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_sqr_vec4(pl_create_vec4(0, 1.529f, 4, -2.3f)), 23.63f, 0.01f, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_length_vec4(pl_create_vec4(1, 3, -2, 0)), 3.74f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_vec4(pl_create_vec4(-4.6f, 3, 1, 1.2f)), 5.71f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_vec4(pl_create_vec4(0, 1.529f, 4, -2.3f)), 4.86f, 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_floor_vec4(pl_create_vec4(1, 3, -2.4f, 1.2f)), pl_create_vec4(1, 3, -3, 1), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_floor_vec4(pl_create_vec4(-4.6f, 3, 1, -2.02f)), pl_create_vec4(-5, 3, 1, -3), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_floor_vec4(pl_create_vec4(0, 1.529f, 0, 0.2f)), pl_create_vec4(0, 1, 0, 0), 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_clamp_vec4(pl_create_vec4(0, 3.14f, 4, -1.2f), pl_create_vec4(5.2f, 3, -1.02f, -512), pl_create_vec4(3, 9.32f, 6, 1.2f)), pl_create_vec4(3, 3.14f, 4, -1.2f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_clamp_vec4(pl_create_vec4(-4.1f, 5.2f, -2.3f, 0.2f), pl_create_vec4(9.32f, -2, 3, 0.3f), pl_create_vec4(7.42f, 5.8f, 3.5f, 0.4f)), pl_create_vec4(7.42f, 5.2f, 3, 0.3f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_min_vec4(pl_create_vec4(-4.1f, 5.2f, 4.2f, -2.3f), pl_create_vec4(9.32f, -2, 1.02f, 2.3f)), pl_create_vec4(-4.1f, -2, 1.02f, -2.3f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_min_vec4(pl_create_vec4(2.12f, 5.3f, -2.3f, 2.4f), pl_create_vec4(-5.3f, -5.4f, 0.02f, -1.6f)), pl_create_vec4(-5.3f, -5.4f, -2.3f, -1.6f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_max_vec4(pl_create_vec4(-4.1f, 5.2f, 2.5f, -2.3f), pl_create_vec4(9.32f, -2, 0, 2.3f)), pl_create_vec4(9.32f, 5.2f, 2.5f, 2.3f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_max_vec4(pl_create_vec4(2.12f, 5.3f, -1.2f, 2.4f), pl_create_vec4(-5.3f, -5.4f, 2.3f, -1.6f)), pl_create_vec4(2.12f, 5.3f, 2.3f, 2.4f), 0.01f, NULL);
    }
    {
        pl_test_expect_float_near_equal(pl_dot_vec4(pl_create_vec4(2.12f, 5.3f, 1.2f, -2.3f), pl_create_vec4(-5.3f, -5.4f, 1, -3.76f)), -30, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_dot_vec4(pl_create_vec4(0, 1, 2, 5.7f), pl_create_vec4(1, 0, 0, 1)), 5.7f, 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_dot_vec4(pl_create_vec4(1.2f, 1, 2.3f, -1), pl_create_vec4(1.53f, -1, 1.65f, 4.63f)), 0, 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_add_vec4(pl_create_vec4(3.82f, 1.3f, 0.2f, 6.3f), pl_create_vec4(-6.3f, -10.4f, 2.0f, 4.4f)), pl_create_vec4(-2.48f, -9.1f, 2.2f, 10.7f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_add_vec4(pl_create_vec4(-15.12f, 0, -5, 0.2f), pl_create_vec4(15.12f, 3, 1.2f, 2.3f)), pl_create_vec4(0, 3, -3.8f, 2.5f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_sub_vec4(pl_create_vec4(3.82f, 1.3f, 0.2f, 6.3f), pl_create_vec4(-6.3f, -10.4f, 2.0f, 4.4f)), pl_create_vec4(10.12f, 11.7f, -1.8f, 1.9f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_sub_vec4(pl_create_vec4(-15.12f, 0, -5, 0.2f), pl_create_vec4(15.12f, 3, 1.2f, 2.3f)), pl_create_vec4(-30.24f, -3, -6.2f, -2.1f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_mul_vec4(pl_create_vec4(3.82f, 1.3f, 0.2f, 6.3f), pl_create_vec4(-6.3f, -10.4f, 2.0f, 4.4f)), pl_create_vec4(-24.06f, -13.52f, 0.4f, 27.72f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_mul_vec4(pl_create_vec4(-15.12f, 0, -5, 0.2f), pl_create_vec4(15.12f, 3, 1.2f, 2.3f)), pl_create_vec4(-228.61f, 0, -6, 0.46f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_div_vec4(pl_create_vec4(3.82f, 1.3f, 0.2f, 6.3f), pl_create_vec4(-6.3f, -10.4f, 2.0f, 4.4f)), pl_create_vec4(-0.61f, -0.1250f, 0.1f, 1.432f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_div_vec4(pl_create_vec4(-15.12f, 0, -5, 0.2f), pl_create_vec4(15.12f, 3, 1.2f, 2.3f)), pl_create_vec4(-1, 0, -4.16f, 0.087f), 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_mul_vec4_scalarf(pl_create_vec4(3.82f, 1.3f, -4.2f, 9.2f), -2), pl_create_vec4(-7.64f, -2.6f, 8.4f, -18.4f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_mul_vec4_scalarf(pl_create_vec4(-15.12f, 0, 1, 0.2f), 5), pl_create_vec4(-75.6f, 0, 5, 1), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_mul_vec4_scalarf(pl_create_vec4(-545.12f, 54, -12, 902), 0), pl_create_vec4(0, 0, 0, 0), 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_div_vec4_scalarf(pl_create_vec4(3.82f, 1.3f, -4.2f, 9.2f), -2), pl_create_vec4(-1.91f, -0.65f, 2.1f, -4.6f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_div_vec4_scalarf(pl_create_vec4(-15.12f, 0, 1, 0.2f), 5), pl_create_vec4(-3.024f, 0, 0.2f, 0.04f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_div_vec4_scalarf(pl_create_vec4(-545.12f, 54, -12, 902), 1), pl_create_vec4(-545.12f, 54, -12, 902), 0.01f, NULL);
    }
    {
        pl_test_expect_vec4_near_equal(pl_norm_vec4(pl_create_vec4(3.82f, 1.3f, -4.2f, 1.4f)), pl_create_vec4(0.637f, 0.217f, -0.7f, 0.234f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_norm_vec4(pl_create_vec4(-15.12f, 0, 1, 0)), pl_create_vec4(-0.998f, 0, 0.066f, 0), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_norm_vec4(pl_create_vec4(-545.12f, 54, -12, -320.2f)), pl_create_vec4(-0.86f, 0.085f, -0.019f, -0.5f), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_norm_vec4(pl_create_vec4(1, 0, 0, 0)), pl_create_vec4(1, 0, 0, 0), 0.01f, NULL);
        pl_test_expect_vec4_near_equal(pl_norm_vec4(pl_create_vec4(1, 1, 1, 1)), pl_create_vec4(1/(float)sqrt(4), 1/(float)sqrt(4), 1/(float)sqrt(4), 1/(float)sqrt(4)), 0.01f, NULL);
        pl_test_expect_float_near_equal(pl_length_vec4(pl_norm_vec4(pl_create_vec4(3.82f, 1.3f, 4.32f, 59348))), 1, 0.01f, NULL);
    }
}
void math_test_mat4() {}
void math_test_rect() {}
#ifdef __cplusplus
    void math_test_op_overloading_vec2() {}
    void math_test_op_overloading_vec3() {}
    void math_test_op_overloading_vec4() {}
    void math_test_op_overloading_mat4() {}
#endif  // c++


static void math_main_tests(void* pData){
    
    math_test_sizes();
    math_test_struct_creation();
    math_test_simple_functions();
    math_test_vec2();
    math_test_vec3();
    math_test_vec4();
    math_test_mat4();
    math_test_rect();
    #ifdef __cplusplus
        math_test_op_overloading_vec2();
        math_test_op_overloading_vec3();
        math_test_op_overloading_vec4();
        math_test_op_overloading_mat4();
    #endif
}

