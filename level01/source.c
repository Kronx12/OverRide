#include <stdio.h>

char *g_username;

int verify_user_name(void) {
  int i = 0;
  char *default_username = "dat_wil";

  puts("verifying username....\n");
  while (default_username[i] && g_username[i] == default_username[i])
    i++;
  return (g_username[i] - default_username[i]);
}

int verify_user_pass(char *password) {
  int i = 0;
  char *default_password = "admin";

  while (default_password[i] && password[i] == default_password[i])
    i++;
  return (password[i] - default_password[i]);
}

int main(void) {
  char buffer[64];
  int diff;
  
  for (int i = 0; i < 64; i++)
    buffer[i] = 0;

  puts("********* ADMIN LOGIN PROMPT *********");

  printf("Enter Username: ");
  fgets(g_username, 256, stdin);
  diff = verify_user_name();
  
  if (diff == 0) {

    puts("Enter Password: ");
    fgets(buffer, 100, stdin);
    verify_user_pass(buffer);

    puts("nope, incorrect password...\n");
  } else
    puts("nope, incorrect username...\n");
  return (1); // After reduction ret is always 1
}
