#ifndef LOG_H
#define LOG_H

#include <stdio.h>

#define RESET_COLOR   "\033[0m"
#define RED_COLOR     "\033[31m"
#define GREEN_COLOR   "\033[32m"
#define YELLOW_COLOR  "\033[33m"
#define BLUE_COLOR    "\033[34m"
#define MAGENTA_COLOR "\033[35m"
#define CYAN_COLOR    "\033[36m"
#define WHITE_COLOR   "\033[37m"
#define GRAY_COLOR    "\033[90m"

#define RAINBOW_COLORS \
    {RED_COLOR, GREEN_COLOR, YELLOW_COLOR, BLUE_COLOR, MAGENTA_COLOR, CYAN_COLOR}

// style: [INFO] filename:line (function) --> message
#define _color_error "\033[0;91m"
#define _color_info "\033[0;92m"
#define _color_warn "\033[0;93m"
#define _color_debug "\033[0;94m"
#define _color_reset "\033[0m"

#define _log_base(str, color, level, ...) printf(color "[%s] %s:%d (%s) --> " str "\n" _color_reset, level, __FILE__, __LINE__, __func__, ##__VA_ARGS__)

#define LOG_DEBUG(str, ...) _log_base(str, _color_debug, "Debug", ##__VA_ARGS__)
#define LOG_ERROR(str, ...) _log_base(str, _color_error, "Error", ##__VA_ARGS__)
#define LOG_INFO(str, ...) _log_base(str, _color_info, "Info", ##__VA_ARGS__)
#define log_WARN(str, ...) _log_base(str, _color_warn, "Warn", ##__VA_ARGS__)

// log_rainbow: just print out the message with every character a different color
#define LOG_RAINBOW(fmt, ...) do { \
    const char *colors[] = RAINBOW_COLORS; \
    int n = sizeof(colors) / sizeof(colors[0]); \
    for (int i = 0; fmt[i]; ++i) { \
        printf("%s%c", colors[i % n], fmt[i]); \
    } \
    printf(RESET_COLOR "\n"); \
} while (0)

#endif  // LOG_H
