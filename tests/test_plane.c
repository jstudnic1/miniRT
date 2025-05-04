#include "../incl/minirt.h"
#include <stdio.h>
#include <math.h>
#include <assert.h> // Using assert for simplicity

// Epsilon for floating point comparisons
#define EPSILON 1e-6

// Helper to compare doubles with epsilon
int approx_equal(double a, double b) {
    return fabs(a - b) < EPSILON;
}

// --- Test Cases ---

void test_simple_hit() {
    printf("Running test_simple_hit... ");
    t_plane plane = { .point = {0, 0, 0}, .normal = {0, 1, 0} }; // Y=0 plane
    vec_normalize(&plane.normal); // Ensure normal is normalized
    t_ray ray = { .origin = {0, 5, 0}, .direction = {0, -1, 0} }; // Ray straight down from Y=5
    vec_normalize(&ray.direction); // Ensure direction is normalized

    t_collision result = plane_ray_collision(ray, plane);

    assert(result.hit == true);
    assert(approx_equal(result.t, 5.0));
    assert(approx_equal(result.point.x, 0.0));
    assert(approx_equal(result.point.y, 0.0));
    assert(approx_equal(result.point.z, 0.0));
    assert(approx_equal(result.normal.x, 0.0));
    assert(approx_equal(result.normal.y, 1.0)); // Normal should point up (+Y)
    assert(approx_equal(result.normal.z, 0.0));
    printf("OK\n");
}

void test_angled_hit() {
    printf("Running test_angled_hit... ");
    t_plane plane = { .point = {0, 0, 0}, .normal = {0, 1, 0} }; // Y=0 plane
    vec_normalize(&plane.normal);
    t_ray ray = { .origin = {0, 5, 0}, .direction = {1, -1, 0} }; // Ray down and right
    vec_normalize(&ray.direction);

    t_collision result = plane_ray_collision(ray, plane);

    // Expected t: t = ((P0 - O) . n) / (d . n)
    // P0 = (0,0,0), O = (0,5,0), n = (0,1,0) => P0 - O = (0, -5, 0)
    // (P0 - O) . n = (0*-0) + (-5*1) + (0*0) = -5
    // d = (1/√2, -1/√2, 0) approx (0.707, -0.707, 0)
    // d . n = (0.707*0) + (-0.707*1) + (0*0) = -0.707
    // t = -5 / -0.707 = 7.071... = 5 * sqrt(2)
    double expected_t = 5.0 * sqrt(2.0);

    assert(result.hit == true);
    assert(approx_equal(result.t, expected_t));
    // Intersection point P = O + t*d
    assert(approx_equal(result.point.x, 0.0 + expected_t * (1.0/sqrt(2.0)))); // Should be 5.0
    assert(approx_equal(result.point.y, 0.0)); // Should hit at y=0
    assert(approx_equal(result.point.z, 0.0));
    assert(approx_equal(result.normal.y, 1.0)); // Normal should point up (+Y)
    printf("OK\n");
}

void test_parallel() {
    printf("Running test_parallel... ");
    t_plane plane = { .point = {0, 0, 0}, .normal = {0, 1, 0} }; // Y=0 plane
    vec_normalize(&plane.normal);
    t_ray ray = { .origin = {0, 5, 0}, .direction = {1, 0, 0} }; // Ray parallel along X axis
    vec_normalize(&ray.direction);

    t_collision result = plane_ray_collision(ray, plane);

    assert(result.hit == false);
    printf("OK\n");
}

void test_miss() {
    printf("Running test_miss... ");
    t_plane plane = { .point = {0, 0, 0}, .normal = {0, 1, 0} }; // Y=0 plane
    vec_normalize(&plane.normal);
    t_ray ray = { .origin = {0, 5, 0}, .direction = {0, 1, 0} }; // Ray pointing up away from plane
    vec_normalize(&ray.direction);

    t_collision result = plane_ray_collision(ray, plane);

    assert(result.hit == false); // t would be negative
    printf("OK\n");
}

void test_behind_ray() {
    printf("Running test_behind_ray... ");
    t_plane plane = { .point = {0, 0, 0}, .normal = {0, 1, 0} }; // Y=0 plane
    vec_normalize(&plane.normal);
    t_ray ray = { .origin = {0, -5, 0}, .direction = {0, -1, 0} }; // Ray starting below, pointing down
    vec_normalize(&ray.direction);

    t_collision result = plane_ray_collision(ray, plane);

    assert(result.hit == false); // t would be negative (-5)
    printf("OK\n");
}

void test_hit_from_back() {
    printf("Running test_hit_from_back... ");
    t_plane plane = { .point = {0, 0, 0}, .normal = {0, 1, 0} }; // Y=0 plane
    vec_normalize(&plane.normal);
    t_ray ray = { .origin = {0, -5, 0}, .direction = {0, 1, 0} }; // Ray starting below, pointing up
    vec_normalize(&ray.direction);

    t_collision result = plane_ray_collision(ray, plane);

    // Denominator (d . n) will be positive (1*1 = 1)
    // Numerator ((P0-O).n) will be positive ( (0,5,0) . (0,1,0) = 5)
    // t = 5 / 1 = 5

    assert(result.hit == true);
    assert(approx_equal(result.t, 5.0));
    assert(approx_equal(result.point.x, 0.0));
    assert(approx_equal(result.point.y, 0.0)); // Hits at y=0
    assert(approx_equal(result.point.z, 0.0));
    // Normal should be flipped because we hit the back face (denom > 0)
    assert(approx_equal(result.normal.x, 0.0));
    assert(approx_equal(result.normal.y, -1.0));
    assert(approx_equal(result.normal.z, 0.0));
    printf("OK\n");
}


int main() {
    // Initialize any necessary data if needed

    // Run test cases
    test_simple_hit();
    test_angled_hit();
    test_parallel();
    test_miss();
    test_behind_ray();
    test_hit_from_back();

    printf("\nAll plane intersection tests passed!\n");
    return 0;
}
