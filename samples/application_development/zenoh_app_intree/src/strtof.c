#include <ctype.h>
#include <stdbool.h>

/**
 * Parse the first float found in a char array
 * @param str char array to parse
 * @return the first float detected in the char (e.g. "123.2text" => 123.2F, "text123.2" => 0.0F)
 */
float strtof(const char* str) {
    float res = 0.0F;
    char *ptr = (char*)str;
    bool after_decimal_point = false;
    float div = 1; // Divider to place digits after the deciaml point

    while (*ptr != '\0') {
        if (isdigit((int)*ptr)) {
            // Integer part
            if (!after_decimal_point) {
                res *= 10; // Shift the previous digits to the left
                res += *ptr - '0'; // Add the new one
            }
            // Decimal part
            else {
                div *= 10;
                res += (float)(*ptr - '0') / div;
            }
        }
        else if (*ptr == '.') {
            after_decimal_point = true;
        }
        else {
            break;
        }
        
        ptr++;
    }
    
    return res;
}