#include "main.h"
#include "led-matrix-c.h"
#include <iostream>
#include <string>
// #include <unistd.h>
#include <thread>
#include <chrono>

int main(int argc, char **argv) {
    using namespace std::chrono_literals;
    struct RGBLedMatrixOptions options= {0};
    struct RGBLedMatrix *matrix;
    struct LedCanvas *offscreen_canvas;
    int width, height;
    int x, y, i;

 // memset(&options, 0, sizeof(options));
    options.rows = 32;
    options.chain_length = 1;

    /* This supports all the led commandline options. Try --led-help */
    matrix = led_matrix_create_from_options(&options, &argc, &argv);
    if (matrix == NULL)
        return 1;

    /* Let's do an example with double-buffering. We create one extra
     * buffer onto which we draw, which is then swapped on each refresh.
     * This is typically a good aproach for animations and such.
     */
    offscreen_canvas = led_matrix_create_offscreen_canvas(matrix);

    led_canvas_get_size(offscreen_canvas, &width, &height);

    std::cout << "Size: " << width << "x" << height 
	      << ". Hardware gpio mapping: " 
	      << options.hardware_mapping << "\n";

    for (i = 0; i < 100; ++i) {
        for (y = 0; y < height; ++y) {
            for (x = 0; x < width; ++x) {
                led_canvas_set_pixel(offscreen_canvas, x, y, 0xff, 0xff, 0xff);
            }
        }

        /* Now, we swap the canvas. We give swap_on_vsync the buffer we
         * just have drawn into, and wait until the next vsync happens.
         * we get back the unused buffer to which we'll draw in the next
         * iteration.
         */
        offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);
	std::this_thread::sleep_for(2000ms);

    }

    /*
     * Make sure to always call led_matrix_delete() in the end to reset the
     * display. Installing signal handlers for defined exit is a good idea.
     */
    led_matrix_delete(matrix);

    return 0;
}
