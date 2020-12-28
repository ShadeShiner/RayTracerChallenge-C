#include <stdio.h>
#include <math.h>

#include "sphere.h"
#include "material.h"
#include "world.h"
#include "lights.h"
#include "camera.h"
#include "canvas.h"


int main()
{
    /* 1. The floor is an extremely flattened sphere with a matte texture */
    Sphere floor;
    sphere_init(&floor);

    matrix_scaling(array_mem(floor.transform), 10, 0.01, 10);

    Color floor_color;
    color_init(&floor_color, 1, 0.9, 0.9);
    floor.material->color = &floor_color;
    floor.material->specular = 0;

    /* 2. The wall on the left has the same scale and color as the floor,
    but is also rotated and translated into place */
    Sphere left_wall;
    sphere_init(&left_wall);

    Matrix lwall_translated[4][4];
    matrix_translation(array_mem(lwall_translated), 0, 0, 5);

    Matrix lwall_rotation_y[4][4];
    matrix_rotation_y(array_mem(lwall_rotation_y), -M_PI_4);

    Matrix lwall_rotation_x[4][4];
    matrix_rotation_x(array_mem(lwall_rotation_x), M_PI_2);

    Matrix lwall_scaling[4][4];
    matrix_scaling(array_mem(lwall_scaling), 10, 0.01, 10);

    Matrix lwall_result[4][4];
    matrix_mul(array_mem(lwall_result), array_mem(lwall_rotation_x),
               array_mem(lwall_scaling), 4);
    matrix_mul(array_mem(lwall_result), array_mem(lwall_rotation_y),
               array_mem(lwall_result), 4);
    matrix_mul(array_mem(lwall_result), array_mem(lwall_translated),
               array_mem(lwall_result), 4);
    sphere_set_transform(&left_wall, array_mem(lwall_result));

    left_wall.material = floor.material;

    /* 3. The wall on the right is identical to the left wall, but is
    rotated the opposite direction in y */
    Sphere right_wall;
    sphere_init(&right_wall);

    Matrix rwall_translation[4][4];
    matrix_translation(array_mem(rwall_translation), 0, 0, 5);

    Matrix rwall_rotation_y[4][4];
    matrix_rotation_y(array_mem(rwall_rotation_y), M_PI_4);

    Matrix rwall_rotation_x[4][4];
    matrix_rotation_x(array_mem(rwall_rotation_x), M_PI_2);

    Matrix rwall_scaling[4][4];
    matrix_scaling(array_mem(rwall_scaling), 10, 0.01, 10);

    Matrix rwall_result[4][4];
    matrix_mul(array_mem(rwall_result), array_mem(rwall_rotation_x),
               array_mem(rwall_scaling), 4);
    matrix_mul(array_mem(rwall_result), array_mem(rwall_rotation_y),
               array_mem(rwall_result), 4);
    matrix_mul(array_mem(rwall_result), array_mem(rwall_translation),
               array_mem(rwall_result), 4);
    sphere_set_transform(&right_wall, array_mem(rwall_result));

    /* 4 The large sphere in the middle is a unit sphere, translated
    upward slightly and colored green */
    Sphere middle;
    sphere_init(&middle);

    Matrix middle_transform[4][4];
    matrix_translation(array_mem(middle_transform), -0.5, 1, 0.5);
    sphere_set_transform(&middle, array_mem(middle_transform));

    Color middle_color;
    color_init(&middle_color, 0.1, 1, 0.5);
    middle.material->color = &middle_color;
    middle.material->diffuse = 0.7;
    middle.material->specular = 0.3;

    /* 5 The smaller green sphere on the right is scaled in half */
    Sphere right;
    sphere_init(&right);

    Matrix right_scaling[4][4];
    matrix_scaling(array_mem(right_scaling), 0.5, 0.5, 0.5);

    Matrix right_translation[4][4];
    matrix_translation(array_mem(right_translation), 1.5, 0.5, -0.5);

    Matrix right_transform[4][4];
    matrix_mul(array_mem(right_transform), array_mem(right_translation),
               array_mem(right_scaling), 4);
    sphere_set_transform(&right, array_mem(right_transform));

    Color right_color;
    color_init(&right_color, 0.5, 1, 0.1);
    right.material->color = &right_color;
    right.material->diffuse = 0.7;
    right.material->specular = 0.3;


    /* 6 The smallest sphere is scaled by a third,
    before being translated */
    Sphere left;
    sphere_init(&left);

    Matrix left_translation[4][4];
    matrix_translation(array_mem(left_translation), -1.5, 0.33, -0.75);

    Matrix left_scaling[4][4];
    matrix_scaling(array_mem(left_scaling), 0.33, 0.33, 0.33);

    Matrix left_transform[4][4];
    matrix_mul(array_mem(left_transform), array_mem(left_translation),
               array_mem(left_scaling), 4);
    sphere_set_transform(&left, array_mem(left_transform));

    Color left_color;
    color_init(&left_color, 1, 0.8, 0.1);

    left.material->color = &left_color;
    left.material->diffuse = 0.7;
    left.material->specular = 0.3;

    // The light source is white, shining from above and to the left
    World w;
    world_init(&w);

    Point light_point;
    point_init(&light_point, -10, 10, -10);

    Color light_color;
    color_init(&light_color, 1, 1, 1);

    PointLight world_light;
    point_light_init(&world_light, &light_point, &light_color);

    w.light = &world_light;

    world_add_object(&w, (void *)&left);
    world_add_object(&w, (void *)&right);
    world_add_object(&w, (void *)&middle);
    world_add_object(&w, (void *)&right_wall);
    world_add_object(&w, (void *)&left_wall);
    world_add_object(&w, (void *)&floor);

    Camera camera;
    camera_init(&camera, 100, 50, M_PI / 3);
    
    Point from;
    point_init(&from, 0, 1.5, -5);
    
    Point to;
    point_init(&to, 0, 1, 0);

    Vector up;
    vector_init(&up, 0, 1, 0);

    matrix_view_transformation(array_mem(camera.transform),
                               &from, &to, &up);
    
    Canvas image;
    canvas_render(&image, &camera, &w);

    printf("%s", canvas_to_ppm(&image));

    return 0;
}