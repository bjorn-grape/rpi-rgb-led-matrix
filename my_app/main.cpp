#include "main.h"
#include "led-matrix.h"
#include <iostream>
#include <string>
// #include <unistd.h>
#include <thread>
#include <chrono>

volatile bool interrupt_received = false;
static void InterruptHandler(int signo) {
    interrupt_received = true;
}

static void DrawOnCanvas(Canvas *canvas) {
    /*
     * Let's create a simple animation. We use the canvas to draw
     * pixels. We wait between each step to have a slower animation.
     */
    canvas->Fill(255, 255, 255);

    int center_x = canvas->width() / 2;
    int center_y = canvas->height() / 2;
    float radius_max = canvas->width() / 2;
    float angle_step = 1.0 / 360;
    for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step) {
        if (interrupt_received)
            return;
        float dot_x = cos(a * 2 * M_PI) * r;
        float dot_y = sin(a * 2 * M_PI) * r;
        canvas->SetPixel(center_x + dot_x, center_y + dot_y,
                         255, 0, 0);
        std::this_thread::sleep_for(100ms);
    }
}

int main(int argc, char **argv) {
    using namespace std::chrono_literals;
    RGBMatrix::Options defaults;
    Canvas *canvas = RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL)
        return 1;


    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    DrawOnCanvas(canvas);    // Using the canvas.

    std::this_thread::sleep_for(500ms);
	std::this_thread::sleep_for(2000ms);

    // Animation finished. Shut down the RGB matrix.
    canvas->Clear();
    delete canvas;


    return 0;
}
