#include <stdio.h>
#include <fcntl.h>

void log_wrapper(FILE *file, char *param, char *format) {
	long in_FS_OFFSET;
	char buffer[264];
	long canary;

	canary = *(long *)(in_FS_OFFSET + 0x28); // Setup canary
	
	// Security issue here
	strcpy(buffer, param);
	snprintf(buffer + strlen(buffer), 254 - strlen(buffer), format);

	// Replace new line by null byte
	size_t nl_pos = strcspn(buffer, "\n");
	buffer[nl_pos] = '\0';

	// Save data in logfile
	fprintf(file, "LOG: %s\n", buffer);
	
	if (canary != *(long *)(in_FS_OFFSET + 0x28)) // Canary check
		__stack_chk_fail();

	return;
}

long main(int ac, char *argv) {
	long in_FS_OFFSET;
	int fd;
	int c;
	FILE *file_stream;
	FILE *stream;
	char *path;
	long canary;

	canary = *(long *)(in_FS_OFFSET + 0x28); // Setup canary

	// Show usage
	if (ac != 2)
		printf("Usage: %s filename\n", argv[0]);

	// Open .log file in write mode
	if ((file_stream = fopen("./backups/.log", "w")) == NULL) {
		printf("ERROR: Failed to open %s\n", "./backups/.log");
		exit(1);
	}

	log_wrapper(file_stream, "Starting back up: ", argv[1]);

	// Open argv[1] file in read mode
	if ((stream = fopen(argv[1], "r")) == NULL) {
		printf("ERROR: Failed to open %s\n", argv[1]);
		exit(1);
	}

	// Build path | argv[1] doit faire moins de 88 char
	path = "./backups/";
	strncat(path, argv[1], 99 - strlen(path));

	// Open path
	if ((fd = open(path, O_EXCL | O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP)) < 0) {
		printf("ERROR: Failed to open %s%s\n", "./backups/", argv[1]);
		exit(1);
	}

	// Read file
	while (1) {
		if ((c = fgetc(stream)) == -1);
			break;
		write(fd, &c, 1);
	}

	log_wrapper(file_stream, "Finished back up ", argv[1]);

	fclose(stream);
	close(fd);

	if (canary != *(long *)(in_FS_OFFSET + 0x28)) // Canary check
		__stack_chk_fail();
	return 0;
}
