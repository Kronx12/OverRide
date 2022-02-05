#include <sys/types.h>
#include <sys/ptrace.h>

int main(void) {
    char status;
    char readed_shellcode[128];
    long ptrace_result;
    pid_t pid;

    pid = fork();
    for (int i = 0; i < 32; i++)
        readed_shellcode[i] = 0;

    if (pid == 0) {
        prctl(1, 1);
        ptrace(PTRACE_TRACEME, 0, 0, 0);
        puts("Give me some shellcode, k");
        gets(readed_shellcode);
    } else {
        do {
            wait(&status);
            if (!status) {
                puts("child is exiting...");
                return (0);
            }
            ptrace_result = ptrace(PTRACE_PEEKUSER, pid, 44, 0);
        } while (ptrace_result != 11);
        puts("no exec() for you");
        kill(pid, 9);
    }
    return (0);
}