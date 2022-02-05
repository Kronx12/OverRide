#include <stdio.h>

// Essayer d'overflow sur cette fonction
void secret_backdoor(void)
{
	char local_88[128];

	fgets(local_88, 128, stdin);
	system(local_88);
	return;
}

void set_msg(char *param)
{
	char msg[1024];

	// Init buffer
	for (int i = 0; i < 1024; i++)
		msg[i] = 0;

	puts(">: Msg @Unix-Dude");
	printf(">>: ");
	fgets(msg, 1024, stdin); // Recupere un message
	strncpy(param, msg, param[180]); // Copy jusqu'au 128 premiers char du buffer dans param
	return;
}

void set_username(char *param)
{
	char username[136];

	// Init buffer
	for (int i = 0; i < 128; i++)
		username[i] = 0;

	puts(">: Enter your username");
	printf(">>: ");
	fgets(username, 128, stdin); // Pas d'overflow

	// Copy upto 41 char after buffer
	for (int i = 0; (i < 41 && username[i] != '\0'); i++)
		param[140 + i] = username[i]; // Possible overflow
	
	printf(">: Welcome, %s", &param[140]); // Pas d'overflow
	return;
}

void handle_msg(void)
{
	char buffer[140];

	set_username(buffer);
	set_msg(buffer);
	puts(">: Msg sent!");
	return;
}

int main(void)
{
	puts("--------------------------------------------\n|   ~Welcome to l33t-m$n ~    v1337        |\n- -------------------------------------------");
	handle_msg();
	return (0);
}