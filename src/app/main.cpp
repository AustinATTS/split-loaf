#include "../core/Platform.h"
#include <stdio.h>

int main() {
    printf("Split Loaf daemon running...\n");
    printf("F8 = Set target window\n");
    printf("F6 = Lock keyboard\n");
    printf("F7 = Unlock keyboard\n");

    Platform::init();
    Platform::processEvents();
    Platform::shutdown();

    return 0;
}
