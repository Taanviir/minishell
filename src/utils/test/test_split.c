#include "../../../include/utils.h"
#include <stdio.h>

int main(int argc, char **argv) {

	if (argc != 2) return 0;
	char **test = ft_split(argv[1], ' ');
	for(int i = 0; test[i]; i++) {
		printf("%s\n", test[i]);
	}
	free_split(test);
}
