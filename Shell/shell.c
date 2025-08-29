#include <unistd.h>
#include <sys/wait.h> 
#include <string.h>

#define BUFFER_SIZE 128

int main()
{
    
    char buffer[BUFFER_SIZE];
    char command[BUFFER_SIZE];

    while (1)
    {

        write(1, "### > ", 6);

        int num_read = read(0, buffer, BUFFER_SIZE);
        buffer[num_read-1] = '\0';

        
        const char* prefix = "/bin/";

        strcpy(command, prefix);
        strcat(command, buffer);


        int fork_status = fork();

        // we are in the child process -> execute command
        if (fork_status == 0)
        {
            execve(command, 0, 0);

            _exit(2);
        }
        // we are in the parent -> wait for child
        else
        {
            siginfo_t* info;
            waitid(P_PID, fork_status, info, WEXITED);
        }

    }
    

}
