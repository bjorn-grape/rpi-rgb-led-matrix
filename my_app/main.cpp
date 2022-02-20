#include "main.h"
#include "led-matrix.h"
#include <iostream>
#include <string>
#include <signal.h>
#include <thread>
#include <chrono>
#include <cmath>

volatile bool interrupt_received = false;

static void InterruptHandler(int signo) {
    interrupt_received = true;
}

using namespace std::chrono_literals;

static void DrawOnCanvas(rgb_matrix::Canvas *canvas) {

    for (unsigned i = 0; i < 1000; ++i) {
        if (i % 3 == 0)
            canvas->Fill(255, 0, 0);
        else if (i % 3 == 1)
            canvas->Fill(0, 255, 0);
        else if (i % 3 == 2)
            canvas->Fill(0, 0, 255);
        std::this_thread::sleep_for(1000ms);
    }

//    int center_x = canvas->width() / 2;
//    int center_y = canvas->height() / 2;
//    float radius_max = canvas->width() / 2;
//    float angle_step = 1.0 / 360;
//    for (float a = 0, r = 0; r < radius_max; a += angle_step, r += angle_step) {
//        if (interrupt_received)
//            return;
//        float dot_x = std::cos(a * 2 * M_PI) * r;
//        float dot_y = std::sin(a * 2 * M_PI) * r;
//        canvas->SetPixel(center_x + dot_x, center_y + dot_y,
//                         255, 0, 0);
//        std::this_thread::sleep_for(1ms);
//    }
}

int main(int argc, char **argv) {
    rgb_matrix::RGBMatrix::Options defaults;
    auto *canvas = rgb_matrix::RGBMatrix::CreateFromFlags(&argc, &argv, &defaults);
    if (canvas == NULL)
        return 1;


    signal(SIGTERM, InterruptHandler);
    signal(SIGINT, InterruptHandler);

    DrawOnCanvas(canvas);    // Using the canvas.

    // Animation finished. Shut down the RGB matrix.
    canvas->Clear();
    delete canvas;


    return 0;
}
