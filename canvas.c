#include <stdio.h>
#include <stdlib.h>
#include "canvas.h"
#include "tuple.h"
#include "my_string.h"


void canvas_init(Canvas *c, unsigned int width, unsigned int height)
{
	unsigned int i;
	unsigned int total = width * height;

	c->width = width;
	c->height = height;
	c->pixels = (Color *)malloc(sizeof(Color) * total);

	for(i = 0; i < total; ++i)
		color_init(&c->pixels[i], 0.0f, 0.0f, 0.0f);
}


void write_pixel(Canvas *canvas, unsigned int x, unsigned int y, Color *color)
{
	Color *selected_color = &canvas->pixels[y * canvas->width + x];
	color_set_red(selected_color, color_red(color));
	color_set_green(selected_color, color_green(color)); 
	color_set_blue(selected_color, color_blue(color));
	color_set_alpha(selected_color, color_alpha(color));
}


static unsigned int num_of_digits(int num)
{
	int digits = 0;
	do
	{
		num /= 10;
		++digits;
	} while (num > 0);

	return digits;
}


static int clamp_pixel_value(float color_value)
{
	if (color_value < 0)
		return 0;
	else if (color_value > 255)
		return 255;
	else
		return (int)color_value;
}


static void convert_color_to_pixel_values(Color *color, int color_values[3])
{
	color_values[0] = clamp_pixel_value(color_red(color) * 256);
	color_values[1] = clamp_pixel_value(color_green(color) * 256);
	color_values[2] = clamp_pixel_value(color_blue(color) * 256);
}


static unsigned int write_pixel_values_to_buffer(char *buffer, int color_values[3])
{
	char color_buffer[4];
	char *ptr = buffer;
	unsigned int num_of_digits;
	unsigned int num_of_chars_written = 0;

	for (int i = 0; i < 3; ++i)
	{
		num_of_digits = int_to_str(color_buffer, 4, color_values[i]);
		num_of_chars_written += num_of_digits;
		string_cat(ptr, color_buffer);
		// If it is not the last iteration in the loop
		if (i != 2)
		{
			ptr += num_of_digits;
			*ptr++ = ' ';
			++num_of_chars_written;
		}
	}

	return num_of_chars_written;
}


char * canvas_to_ppm(Canvas *canvas)
{
	int rows = canvas->height;
	int columns = canvas->width;
	int bytes_for_color = 12; 
	int num_of_chars_for_header = 9 + num_of_digits(rows) + num_of_digits(columns);
	int num_of_chars_for_body = rows * columns * bytes_for_color;
	int size_to_allocate = num_of_chars_for_header + num_of_chars_for_body;


	char *buffer = (char *)malloc(size_to_allocate);
	// TODO: Add error check if this doesn't work
	int chars_written = sprintf(buffer, "P3\n%d %d\n255\n", columns, rows);
	int chars_written_in_line;
	// This will always be used to insert characters
	char *pos = buffer + chars_written;
	char *start_of_line;
	int color_values[3];
	for (int y = 0; y < rows; ++y)
	{
		start_of_line = pos;
		chars_written_in_line = 0;
		for (int x = 0; x < columns; ++x)
		{
			convert_color_to_pixel_values(&pixel_at(canvas, x, y), color_values);
			chars_written = write_pixel_values_to_buffer(pos, color_values);
			chars_written_in_line += chars_written;
			pos += chars_written++;
			// Append either space OR newline at the end of the row
			*pos++ = (x == columns - 1) ? '\n': ' ';
		}
		// Make sure each line is no more than 70 characters
		if (chars_written_in_line > 70)
		{
			char *p;
			for(p = start_of_line + 70; *p != ' '; --p);
			*p = '\n';
		}

	}
	// Terminate the buffer string
	*pos = '\0';

	return buffer;
}

