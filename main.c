#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#define NNUCAT_BS (1024 * 1024)

typedef struct nnucat_file {
	const char * name;
	FILE * file;
} nnucat_file;

int main(int argc, char ** argv) {
	if (argc <= 1) {
		printf("Usage: %s [file ...]\n", argv[0]);
		return 1;
	}

	int fc = (argc - 1);
	nnucat_file * files = malloc(sizeof(nnucat_file) * fc);
	for (int i = 0; i < fc; i++) {
		files[i].name = argv[i + 1];
		files[i].file = fopen(files[i].name, "rb");
		if (!files[i].file) {
			fprintf(stderr, "%s: %s\n", files[i].name, strerror(errno));
			while (i--) {
				fclose(files[i].file);
			}
			return 1;
		}
	}

	char data[NNUCAT_BS];
	char buff[NNUCAT_BS];
	int error = 0;
	int any;
	do {
		any = 0;
		memset(data, 0, NNUCAT_BS);
		size_t size = 0;
		for (int i = 0; i < fc; i++) {
			if (!files[i].file) {
				continue;
			}

			size_t l = fread(buff, 1, NNUCAT_BS, files[i].file);
			for (size_t c = 0; c < l; c++) {
				if (!data[c]) {
					data[c] = buff[c];
				}
			}

			if (l != NNUCAT_BS) {
				if (ferror(files[i].file)) {
					char * msg = errno ? strerror(errno) : "Read error";
					fprintf(stderr, "%s: %s\n", files[i].name, msg);
					error = 1;
					break;
				}
				fclose(files[i].file);
				files[i].file = NULL;
			}
			else {
				any = 1;
			}

			if (l > size) {
				size = l;
			}
		}

		if (error) {
			break;
		}

		if (size) {
			fwrite(data, 1, size, stdout);
		}
	} while(any);

	for (int i = 0; i < fc; i++) {
		if (files[i].file) {
			fclose(files[i].file);
		}
	}
	return error;
}
