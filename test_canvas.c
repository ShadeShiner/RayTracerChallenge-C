#include <stdio.h>
#include "canvas.h"
#include "my_string.h"

unsigned int NUM_RAN = 0;
unsigned int NUM_PASSED = 0;
unsigned int NUM_FAILED = 0;

void test_passed_(const char *function_name)
{
	++NUM_PASSED;
	++NUM_RAN;
	printf("Test PASSED: %s\n", function_name);
}

#define test_passed() test_passed_(__func__)

void test_failed_(const char *function_name)
{
	++NUM_FAILED;
	++NUM_RAN;
	printf("Test FAILED: %s\n", function_name); 
}

void test_results()
{
	printf("========== Summary ==========\n");
	printf("Number of tests ran: %d\n", NUM_RAN);
	printf("Number of tests passed: %d\n", NUM_PASSED);
	printf("Number of tests failed: %d\n", NUM_FAILED);
}

#define test_failed() test_failed_(__func__)

void creating_a_canvas()
{
	Canvas c;
	unsigned int width = 10;
	unsigned int height = 20;
	canvas_init(&c, width, height);

	Color expected;
	color_init(&expected, 0.0f, 0.0f, 0.0f);

	if (c.width != width)
		return test_failed();
	
	if (c.height != height)
		return test_failed();
	
	int x, y;
	for (x = 0; x < width; ++x)
		for (y = 0; y < height; ++y)
			if (color_equal(&pixel_at(&c, x, y), &expected))
				return test_failed();
	
	test_passed();
}

void writing_pixels_to_a_canvas()
{
	Canvas c;
	Color red;
	unsigned int width = 10;
	unsigned int height = 20;

	canvas_init(&c, width, height);
	color_init(&red, 1.0f, 0.0f, 0.0f);

	write_pixel(&c, 2, 3, &red);
	Color color = pixel_at(&c, 2, 3);
	if (color_equal(&pixel_at(&c, 2, 3), &red))
		return test_failed();
	
	test_passed();
}

void constructing_the_ppm_header()
{
	Canvas c;
	canvas_init(&c, 5, 3);
	char *ppm = canvas_to_ppm(&c);
	if (string_has_substring(ppm, "P3\n5 3\n255"))
		return test_failed();
	
	test_passed();
}

void constructing_the_ppm_pixel_data()
{
	Canvas c;
	canvas_init(&c, 5, 3);

	Color c1, c2, c3;
	color_init(&c1,  1.5f, 0.0f, 0.0f);
	color_init(&c2,  0.0f, 0.5f, 0.0f);
	color_init(&c3, -0.5f, 0.0f, 1.0f);
	write_pixel(&c, 0, 0, &c1);
	write_pixel(&c, 2, 1, &c2);
	write_pixel(&c, 4, 2, &c3);

	char *ppm = canvas_to_ppm(&c);
	if (string_has_substring(ppm, "255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
								  "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
	 							  "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"))
		return test_failed();
	
	test_passed();
}

void splitting_long_lines_in_ppm_files()
{
	Canvas c;
	canvas_init(&c, 10, 2);

	Color color;
	color_init(&color, 1.0f, 0.8f, 0.6f);
	for (int x = 0; x < 10; ++x)
	{
		for (int y = 0; y < 2; ++y)
		{
			write_pixel(&c, x, y, &color);
		}
	}
	char *ppm = canvas_to_ppm(&c);
	if (string_has_substring(ppm, "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
								  "153 255 204 153 255 204 153 255 204 153 255 204 153\n"
								  "255 204 153 255 204 153 255 204 153 255 204 153 255 204 153 255 204\n"
								  "153 255 204 153 255 204 153 255 204 153 255 204 153\n"))
		return test_failed();
	
	test_passed();
}

void ppm_files_are_terminated_by_a_newline_character()
{
	Canvas c;
	canvas_init(&c, 5, 3);

	char *ppm = canvas_to_ppm(&c);
	int length = string_length(ppm);

	if (ppm[length-1] != '\n')
		return test_failed();
	
	return test_passed();
}

int main()
{
	creating_a_canvas();
	writing_pixels_to_a_canvas();
	constructing_the_ppm_header();
	constructing_the_ppm_pixel_data();
	splitting_long_lines_in_ppm_files();
	ppm_files_are_terminated_by_a_newline_character();
	test_results();
}

