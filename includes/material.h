#ifndef MATERIALS_H
#define MATERIALS_H

#include <tuple.h>
#include <lights.h>


typedef struct Material_
{
	Color *color;
	float ambient;
	float diffuse;
	float specular;
	float shininess;
} Material;

/* Constructors and Destructors */
void
material_init(Material *material, Color *color,
			  float ambient, float diffuse,
			  float specular, float shininess);

void
material_default_init(Material *material);

void
material_release(Material *material);

Material*
material_create(Color *color, float ambient,
				float diffuse, float specular,
				float shininess);

Material*
material_default_create();

void
material_destroy(Material *material);

/* Functions */
int material_equal(Material *left, Material *right);

Color* material_lighting(Material *m, PointLight *l,
	  	  				 Point *p, Vector *eye,
						 Vector *normal);

#endif
