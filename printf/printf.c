#include "printf.h"

void print(const char* format, ...) {
	va_list list;
	va_start(list, format);
	int i = -1;
	while (format[++i] != '\0') {
		if (format[i] != '%') {
			putchar(format[i]);
		}
		else {
			switch (format[++i]) {
				case '%':
					putchar('%');
					break;
				case 'c':
					char tmp_c = (char)va_arg(list, int);
					putchar(tmp_c);
					break;
				case 'd':
					int tmp_i = va_arg(list, int);
					if (tmp_i < 0) {
						putchar('-');
						tmp_i = -tmp_i;
					}
					int n = 1;
					while (n * 10 <= tmp_i) {
						n *= 10;
					}
					while (n > 0) {
						putchar('0' + (tmp_i / n) % 10);
						n /= 10;
					}
					break;
				case 'f':
					double tmp_f = va_arg(list, double);
					if (tmp_f < 0) {
						putchar('-');
						tmp_f = -tmp_f;
					}
					int int_part = (int)tmp_f;
					double frac_part = tmp_f - int_part;
					int power = 1;
					while (power <= int_part) {
						power *= 10;
					}	
					power /= 10;
					while (power > 0) {
						putchar('0' + (int_part / power) % 10);
						power /= 10;
					}
					putchar('.');
					for (int i = 0; i < 6; ++i) {
						frac_part *= 10;
						putchar('0' + (int)frac_part);
						frac_part -= (int)frac_part;
					}
					break;
				case 's':
					char* tmp_s = va_arg(list, char*);
					while (*tmp_s != '\0') {
						putchar(*tmp_s);
						++tmp_s;
					}
					break;
				default:
					write(1, "used  unsupported symbol\n", 26);
					va_end(list);
					abort();
			}
		}
	}
	va_end(list);
}
