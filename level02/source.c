#include <stdio.h>

int main(void) {
  size_t length;
  size_t content_length;
  char file_content[48];
  char username[96];
  char password[112];
  FILE *fd;

// Init arrays
  for (size_t i = 0; i < 48; i++) { file_content[i] = 0; }
  for (size_t i = 0; i < 96; i++) { username[i] = 0; }
  for (size_t i = 0; i < 112; i++) { password[i] = 0; }

// Open .pass
  fd = fopen("/home/users/level03/.pass", "r");
// Check open error
  if (fd == 0) {
	  fwrite("ERROR: failed to open password file\n", 1, 36, stderr);
	  exit(1);
  }

// Read .pass
  length = fread(file_content, 1, 41, fd);
  content_length = length;

// Replace \n by \0
  length = strcspn(file_content, "\n");
  file_content[length] = 0;

// Check read error
  if (content_length != 41) {
    fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
    fwrite("ERROR: failed to read password file\n", 1, 36, stderr);
    exit(1);
  }

// Close file
  fclose(fd);

  puts("===== [ Secure Access System v1.0 ] =====");
  puts("/***************************************\\");
  puts("| You must login to access this system. |");
  puts("\\**************************************/");

// Request username
  printf("--[ Username: ");
  fgets(username, 100, stdin);

// Replace \n by \0
  length = strcspn(username, "\n");
  username[length] = 0;

// Request password
  printf("--[ Password: ");
  fgets(password, 100, stdin);

// Replace \n by \0
  length = strcspn(password, "\n");
  password[length] = 0;

  puts("*****************************************");

  if (!strncmp(file_content, password, 41)) {
    printf("Greetings, %s!\n", username);
    system("/bin/sh");
	  return 0;
  }
  
// String format exploit
  printf(username);
  puts(" does not have access!");
  exit(1);
}

