/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_cylinder.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jstudnic <studnicka.jakub04@gmail.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 14:00:00 by jstudnic          #+#    #+#             */
/*   Updated: 2025/04/08 14:00:00 by jstudnic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../incl/minirt.h"
#include <math.h> // For sqrt(), INFINITY, fabs()

// Enum to track which part of the cylinder was hit
typedef enum e_hit_type {
    HIT_NONE,
    HIT_SIDE,
    HIT_BOT_CAP,
    HIT_TOP_CAP
} t_hit_type;

// --- Forward Declarations for Internal Helpers ---
static bool intersect_cylinder_caps(t_ray ray, t_cylinder cylinder, double *t_cap, t_hit_type *cap_hit_type);
static bool solve_quadratic(double a, double b, double c, double *t0, double *t1);

// Helper function to calculate a point along a ray (duplicate for now)
// TODO: Move this to a shared utility file
static t_vector raypoint(t_ray ray, double t) {
    return vec_add(ray.origin, vec_mult_scalar(ray.direction, t));
}

/**
 * @brief Calculates the intersection of a ray with a finite cylinder.
 * Checks intersection with the infinite cylinder body and the two end caps.
 *
 * @param ray The ray to intersect.
 * @param cylinder The cylinder object.
 * @return t_collision Collision data (hit status, point, normal, color, t).
 */
t_collision cylinder_ray_collision(t_ray ray, t_cylinder cylinder) {
    t_collision collision_data;
    t_vector    oc = vec_sub(ray.origin, cylinder.center);
    double      r = cylinder.diameter / 2.0;
    t_vector    axis = cylinder.axis; // Assuming normalized
    double      closest_t = INFINITY;
    t_hit_type  hit_type = HIT_NONE;
    double      t0, t1; // Solutions for infinite cylinder body

    // --- 1. Calculate Quadratic Coefficients for Infinite Cylinder ---
    double dot_d_a = dot_product(ray.direction, axis);
    double dot_oc_a = dot_product(oc, axis);

    double a = dot_product(ray.direction, ray.direction) - dot_d_a * dot_d_a;
    double b = 2.0 * (dot_product(ray.direction, oc) - dot_d_a * dot_oc_a);
    double c = dot_product(oc, oc) - dot_oc_a * dot_oc_a - r * r;

    // --- 2. Solve Quadratic for Infinite Cylinder Body ---
    if (solve_quadratic(a, b, c, &t0, &t1)) {
        // --- 3. Check Side Hits within Height Bounds ---
        if (t0 > RAY_T_MIN && t0 < closest_t) {
            t_vector p0 = raypoint(ray, t0);
            double m0 = dot_product(vec_sub(p0, cylinder.center), axis);
            if (m0 >= 0 && m0 <= cylinder.height) {
                closest_t = t0;
                hit_type = HIT_SIDE;
            }
        }
        if (t1 > RAY_T_MIN && t1 < closest_t) {
            t_vector p1 = raypoint(ray, t1);
            double m1 = dot_product(vec_sub(p1, cylinder.center), axis);
            if (m1 >= 0 && m1 <= cylinder.height) {
                closest_t = t1;
                hit_type = HIT_SIDE;
            }
        }
    }

    // --- 4. Check Cap Intersections ---
    double t_cap = INFINITY;
    t_hit_type cap_hit_type = HIT_NONE;
    if (intersect_cylinder_caps(ray, cylinder, &t_cap, &cap_hit_type)) {
        if (t_cap > RAY_T_MIN && t_cap < closest_t) {
            closest_t = t_cap;
            hit_type = cap_hit_type; // Either BOT_CAP or TOP_CAP
        }
    }

    // --- 5. Finalize Collision Data if Hit Found ---
    collision_data.hit = (hit_type != HIT_NONE);
    if (collision_data.hit) {
        collision_data.t = closest_t;
        collision_data.point = raypoint(ray, closest_t);
        collision_data.color = cylinder.color;

        // Calculate normal based on hit type
        if (hit_type == HIT_SIDE) {
            double m = dot_product(vec_sub(collision_data.point, cylinder.center), axis);
            t_vector axis_point = vec_add(cylinder.center, vec_mult_scalar(axis, m));
            collision_data.normal = vec_sub(collision_data.point, axis_point);
            normalize_vec(&collision_data.normal);
        } else if (hit_type == HIT_BOT_CAP) {
            collision_data.normal = vec_mult_scalar(axis, -1.0); // Points downwards
        } else if (hit_type == HIT_TOP_CAP) {
            collision_data.normal = axis; // Points upwards
        }
    } else {
        // Ensure t is infinity if no hit
        collision_data.t = INFINITY;
    }

    return collision_data;
}


// --- Internal Helper Function Implementations ---

/**
 * @brief Solves the quadratic equation at^2 + bt + c = 0.
 * @return bool True if real solutions exist, false otherwise.
 *         Outputs solutions via pointers t0 and t1 (t0 <= t1).
 */
static bool solve_quadratic(double a, double b, double c, double *t0, double *t1) {
    // Handle near-zero 'a' representing a line instead of quadratic
    if (fabs(a) < EPSILON) {
        if (fabs(b) < EPSILON) return false; // 0 = c, only possible if c=0 (line lies in plane) - ignore for intersection
        *t0 = *t1 = -c / b;
        return true;
    }

    double delta = b * b - 4.0 * a * c;
    if (delta < 0) {
        return false; // No real roots
    }

    double sqrt_delta = sqrt(delta);
    double q;

    // Numerical stability improvement (Moller-Trumbore method for quadratic)
    if (b < 0) {
        q = -0.5 * (b - sqrt_delta);
    } else {
        q = -0.5 * (b + sqrt_delta);
    }

    *t0 = q / a;
    *t1 = c / q;


    // Ensure t0 is the smaller root
    if (*t0 > *t1) {
        double temp = *t0;
        *t0 = *t1;
        *t1 = temp;
    }

    return true;
}

/**
 * @brief Checks for intersection with the cylinder's top and bottom caps.
 * @return bool True if a valid cap intersection closer than current_t is found.
 *         Outputs the intersection distance via t_cap and type via cap_hit_type.
 */
static bool intersect_cylinder_caps(t_ray ray, t_cylinder cylinder, double *t_cap, t_hit_type *cap_hit_type) {
    double r = cylinder.diameter / 2.0;
    double r_sq = r * r;
    t_vector axis = cylinder.axis;
    double closest_cap_t = INFINITY;
    bool hit_found = false;

    // --- Bottom Cap Check ---
    t_vector bot_normal = vec_mult_scalar(axis, -1.0);
    double denom_bot = dot_product(ray.direction, bot_normal);
    if (fabs(denom_bot) > EPSILON) { // Check if ray is not parallel to cap plane
        t_vector p0_minus_o = vec_sub(cylinder.center, ray.origin);
        double t_bot = dot_product(p0_minus_o, bot_normal) / denom_bot;

        if (t_bot > RAY_T_MIN && t_bot < closest_cap_t) {
            t_vector p_bot = raypoint(ray, t_bot);
            // Check if hit point is within the radius of the cap
            if (vec_len2(vec_sub(p_bot, cylinder.center)) <= r_sq) {
                closest_cap_t = t_bot;
                *cap_hit_type = HIT_BOT_CAP;
                hit_found = true;
            }
        }
    }

    // --- Top Cap Check ---
    t_vector top_center = vec_add(cylinder.center, vec_mult_scalar(axis, cylinder.height));
    t_vector top_normal = axis;
    double denom_top = dot_product(ray.direction, top_normal);
    if (fabs(denom_top) > EPSILON) { // Check if ray is not parallel to cap plane
        t_vector p1_minus_o = vec_sub(top_center, ray.origin);
        double t_top = dot_product(p1_minus_o, top_normal) / denom_top;

        if (t_top > RAY_T_MIN && t_top < closest_cap_t) { // Must be closer than bottom cap hit too
            t_vector p_top = raypoint(ray, t_top);
            // Check if hit point is within the radius of the cap
            if (vec_len2(vec_sub(p_top, top_center)) <= r_sq) {
                closest_cap_t = t_top;
                *cap_hit_type = HIT_TOP_CAP;
                hit_found = true;
            }
        }
    }

    if (hit_found) {
        *t_cap = closest_cap_t;
    }
    return hit_found;
}
