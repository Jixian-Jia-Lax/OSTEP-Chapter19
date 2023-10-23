#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <mach/mach.h>
#include <mach/thread_policy.h>
#include <mach/thread_act.h>

int main(int argc, char* argv[]){

    thread_affinity_policy_data_t policy = {1};
    mach_port_t thread = mach_thread_self();

    kern_return_t result = thread_policy_set(thread, THREAD_AFFINITY_POLICY, (thread_policy_t)&policy, 1);
    int num_pages = atoi(argv[1]);
    int num_trials = atoi(argv[2]);
    int pagesize = (int)sysconf(_SC_PAGESIZE);
    int jump = pagesize/sizeof(int);
    int *a = malloc(num_pages*jump);
    long counter = 0;

    struct timeval start, end;
    int j;
    int i;

    for(i = 0; i< num_pages*jump; i+= jump){
            a[i] += 1;
        }
    for(j = 0; j<num_trials; j++){
        
        gettimeofday(&start, NULL);
        for(i = 0; i< num_pages*jump; i+= jump){
            a[i] += 1;
        }
        gettimeofday(&end, NULL);   
        counter += end.tv_usec - start.tv_usec;
    }

    free(a);
    printf("%lf\n", ((double)counter)/num_pages); 
    return 0;
}