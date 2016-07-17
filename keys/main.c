#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	size_t sz = 36;
	char data[] = "QWERTYUIOPLKJHGFDSAZXCVBNM1234567890";

	for (size_t i = 0; i < 64; i++) {
		printf("%c", data[rand()%sz]);
	}
	puts("");
	return 0;
}