// Numbers from command line arguments are sent to child process
// from parent process one at a time through pipe.
//
// Child process adds up numbers sent through pipe.
//
// Child process returns sum of numbers to parent process.
//
// Parent process prints sum of numbers.

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>

int main(int argc, char **argv)
{
    pid_t pid;
    int pipeDes[2];

	// set up pipe

    pipe(pipeDes);

	// call fork()

    pid_t fork(void); 

	printf("CS201 - Assignment 3 - Jaime Landers\n");

	if (!fork())
    {
		// -- running in child process --

		int sum = 0;
        int tempIn[10];

        // Receive characters from parent process via pipe
		// one at a time, and count them.
        
        close (pipeDes[1]);

        while(read (pipeDes[0], &tempIn[i], 4));
        {
            sum = sum + (int) tempIn[i];
            i++;
        }

        close (pipeDes[0]);

		// Return sum of numbers.
        
        return sum;
    }
	else 
    {
		// -- running in parent process --

        int status = 0; 
		int sum = 0;
        int tempOut = 0;

		// Send numbers (datatype: int, 4 bytes) from command line arguments
		// starting with argv[1] one at a time through pipe to child process.
        
        close (pipeDes[0]);

        for (int i = 1; i < argc; i++)
        {
            tempOut = atoi(argv[i]);

            write(pipeDes[1], &tempOut, 4);
        }

        close (pipeDes[1]);

		// Wait for child process to return. Reap child process.
		// Receive sum of numbers via the value returned when
		// the child process is reaped.
        
        wait(&status); 

        WIFEXITED(status);

        sum = (WEXITSTATUS(status));
            
        if(sum > 0x0000007f)
            sum |= 0xffffff00;

		printf("sum = %d\n\n", sum);
        
    	return 0;
	}
}
