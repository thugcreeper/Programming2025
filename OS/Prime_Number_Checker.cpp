// OS assignment1: Prime Number Checker
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int isPrime(int num) {
    if (num == 2) return 1;
    if (num < 2) return 0;
    if (num % 2 == 0) return 0;
    for (int j = 3; j * j <= num; j += 2) {
        if (num % j == 0) return 0;
    }
    return 1;
}

int countPrime(int lower, int upper) {
    int count = 0;
    if (lower > upper) {
        printf("please enter lower first then upper\n");
        return 0;
    }
    for (int i = lower; i <= upper; i++) {
        if (isPrime(i)) count++;
    }
    return count;
}

int main() {
    int lower_bound, upper_bound;
    int total=0;
    int p[2];//pipe 0 read 1 write
    if(pipe(p)<0)//Failed to create pipeline
        exit(1);
    printf("Enter range: ");
    scanf("%d %d",&lower_bound,&upper_bound);
    int offset=(upper_bound-lower_bound+1)/4;
    for(int i=0;i<4;i++){
        int lower=lower_bound+offset*i;
        int upper= (i==3 ? upper_bound : lower_bound+offset*(i+1)-1);
        pid_t pid=fork(); //create child process
        if (pid < 0){
	        perror("Fork failed\n");// Error in forking
	        return 1;
        } 
        else if (pid == 0){
            // Child process
            close(p[0]);
            printf("Child process %d handles range: %d-%d\n",i+1,lower,upper);

            int count=countPrime(lower,upper);
            write(p[1],&count,sizeof(int));

            // After sleeping, print the number
            printf("Child process %d found %d prime numbers\n", i+1,count);
            fflush(stdout); // Ensure output is displayed immediately
            close(p[1]);
            // Exit the child process
            exit(count);
        }
        // Parent process continues to the next iteration
    }
    // Parent process waits for all child processes to complete
    close(p[1]);
	for (int i = 0; i < 4; i++) {
	    int temp;
	    read(p[0],&temp,sizeof(int));
	    total+=temp;
        wait(NULL);    
    }
    printf("Total prime numbers found: %d\n", total);
    return 0;
}

