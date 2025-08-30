#include <unistd.h>
#include <sys/wait.h> 

#define BUFFER_SIZE 128

int real_waitid(idtype_t idtype, id_t id, siginfo_t *infop, int options, void *unused);

int main()
{
    
    char buffer[BUFFER_SIZE];
    char command[BUFFER_SIZE];

    while (1)
    {
        write(1, "### > ", 6);

        int num_read = read(0, buffer, BUFFER_SIZE);
        if (num_read <= 0)
        {
            continue;
        }

        buffer[num_read-1] = '\0';


        int fork_status = fork();

        // we are in the child process -> execute command
        if (fork_status == 0) {
            char *args[] = { buffer, NULL };
            execve(buffer, args, NULL);
            break;
        } else {
            // we are in the parent process -> wait child
            siginfo_t info;
            real_waitid(P_PID, fork_status, &info, WEXITED, 0);
        }

    }
    
    _exit(0);
}
