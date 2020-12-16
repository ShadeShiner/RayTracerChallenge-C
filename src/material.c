#include <stdlib.h>
#include <math.h>
#include <material.h>
#include <tuple.h>


/* Constructors and Destructors */
void
material_init(Material *material, Color *color,
			  float ambient, float diffuse,
			  float specular, float shininess)
{
	material->color = color;
	material->ambient = ambient;
	material->diffuse = diffuse;
	material->specular = specular;
	material->shininess = shininess;
}

void
material_default_init(Material *material)
{
	material->color = malloc(sizeof(Material));
	color_init(material->color, 1, 1, 1);
	material->ambient = 0.1;
	material->diffuse = 0.9;
	material->specular = 0.9;
	material->shininess = 200.0;
}

void
material_release(Material *material)
{
	free(material->color);
}

Material*
material_create(Color *color, float ambient,
				float diffuse, float specular,
				float shininess)
{
	Material *material = malloc(sizeof(Material));
	material_init(material, color, ambient, diffuse, specular, shininess);
	return material;
}


Material*
material_default_create()
{
	Material *material = malloc(sizeof(Material));
	material_default_init(material);
	return material;
}

void
material_destroy(Material *material)
{
	material_release(material);
	free(material);
}

/* Functions */
int material_equal(Material *left, Material *right)
{
	int result = tuple_equal(left->color, right->color);
	if (result)
		return result;
	
	result = float_equal(left->ambient, right->ambient);
	if (result)
		return result;
	
	result = float_equal(left->diffuse, right->diffuse);
	if (result)
		return result;
	
	result = float_equal(left->specular, right->specular);
	if (result)
		return result;
	
	result = float_equal(left->shininess, right->shininess);
	if (result)
		return result;

	return 0;
}

Color* material_lighting(Material *m, PointLight *l,
						Point *p, Vector *eye,
						Vector *normal)
{
	/* combine the surface color with the light's color/intensity */
	Color effective_color;
	color_mul(&effective_color, m->color, l->intensity);

	/* find the direction to the light source */
	Vector lightv, light_diff;
	tuple_sub(&light_diff, l->position, p);
	tuple_normalize(&lightv, &light_diff);

	/* compute the ambient contribution */
	Color ambient;
	tuple_mul_scalar(&ambient, &effective_color, m->ambient);

	/* light_dot_normal represents the cosine of the angle
	   between the light vector and the normal vector. A
	   negative number means the light is on the other
	   side of the surface */
	float light_dot_normal = tuple_dot(&lightv, normal);
	Color diffuse, specular;
	if (light_dot_normal < 0)
	{
		color_init(&diffuse, 0, 0, 0);
		color_init(&specular, 0, 0, 0);
	}
	else
	{
		/* compute the diffuse contribution */
		tuple_mul_scalar(&diffuse, &effective_color, m->diffuse * light_dot_normal);

		/* reflect_dot_eye represents the cosine of the angle between the
		   reflection vector and the eye vector. A negative number means the
		   light reflect away from the eye. */
		Vector neg_lightv, reflectv;
		tuple_neg(&neg_lightv, &lightv);
		tuple_reflect(&reflectv, &neg_lightv, normal); 
		
		float reflect_dot_eye = tuple_dot(&reflectv, eye);

		if (reflect_dot_eye <= 0)
			color_init(&specular, 0, 0, 0);
		else
		{
			/* compute the specular contribution */
			float factor = powf(reflect_dot_eye, m->shininess);
			tuple_mul_scalar(&specular, l->intensity, m->specular * factor);
		}
	}

	/* Add the three contributions together to get the final shading */
	Color *result = malloc(sizeof(Color));
	tuple_add(result, &ambient, &diffuse);
	tuple_add(result, result, &specular);
	return result;
}

