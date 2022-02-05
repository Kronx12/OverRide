#include <stdio.h>
#include <sys/ptrace.h>

int auth(char *login, unsigned int serial) {
	int res;
	long ptrace_result;
	int i;
	unsigned int tmp;

	// Replace \n by \0
	i = strcspn(login, "\n");
	login[i] = '\0';

	// Le login doit faire 6 char et plus
	i = strnlen(login, 32);
	if (i < 6)
		res = 1;
	else {
		// Si debug avec GDB, auto exit here
		ptrace_result = ptrace(PTRACE_TRACEME);
		if (ptrace_result == -1) {
			puts("\x1b[32m.---------------------------.");
			puts("\x1b[31m| !! TAMPERING DETECTED !!  |");
			puts("\x1b[32m\'---------------------------\'");
			res = 1;
		// Sinon calcul du serial a partir de login
		} else {
			tmp = ((int)login[3] ^ 0x1337U) + 0x5eeded;
			for (size_t i = 0; i < (int)i; i++) {
				// Que des char au dessus ou egaux a ' '
				if (login[i] < ' ')
					return (1);
				tmp += ((int)login[i] ^ tmp) % 0x539;
			}
			if (serial == tmp)
				res = 0;
			else
				res = 1;
		}
	}
	return (res);
}

int main() {
	int res;
	int *in_GS_OFFSET;
	unsigned int value;
	char input[32];
	int canary;

	canary = in_GS_OFFSET[5];

	puts("***********************************");
	puts("*\t\tlevel06\t\t  *");
	puts("***********************************");

	printf("-> Enter Login: ");
	fgets(input, 32, stdin);

	puts("***********************************");
	puts("***** NEW ACCOUNT DETECTED ********");
	puts("***********************************");
	printf("-> Enter Serial: ");
	scanf("%u", &value);
	res = auth(input, value);
	if (!res)
	{
		puts("Authenticated!");
		system("/bin/sh");
	}
	if (canary != in_GS_OFFSET[5])
		__stack_chk_fail();
	return (res != 0);
}