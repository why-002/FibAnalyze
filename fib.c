#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define _XOPEN_SOURCE 700

typedef struct timespec timespec_t;

double get_elapsed_time_sec(const timespec_t *start, const timespec_t *end) {
    long start_nanos = (long)1e9 * start->tv_sec + start->tv_nsec;
    long end_nanos = (long)1e9 * end->tv_sec + end->tv_nsec;
    return (double)(end_nanos - start_nanos) / 1e9;
}



int fib_naive(int n){
    if(n == 0){
        return 0;
    }
    else if(n == 1){
        return 1;
    }
    return fib_naive(n-1) + fib_naive(n-2);
}

int tail_helper(int n, int n1, int n2){
    if(n == 0){
        return n1;
    }
    n1 = n1 + n2;
    n2 = n1 - n2;
    return tail_helper(n-1, n1, n2);
}

int fib_tail(int n){
    if (n == 0){
        return 0;
    }
    if(n == 1){
        return 1;
    }
    else{
        return tail_helper(n-2, 1, 1);
    }
}

int memo_helper(int n, int *memo){
    if(n == 0){
        return 0;
    }
    if(n == 1){
        memo[n] = 1;
        return 1;
    }
    if(memo[n] == 0){
        memo[n] = memo_helper(n-1, memo) + memo_helper(n-2, memo);
        return memo[n];
    }
    else{
        return memo[n];
    }
}

int fib_memoize(int n){
    int *memo = malloc(sizeof(int) * n);
    for (int i = 0; i <= n; i++){
        memo[i] = 0;
    }
    int temp = memo_helper(n, memo);
    free(memo);
    return temp;
}

int fib_top_down(int n){
    int *nums = malloc(sizeof(int) * (n+2));
    nums[0] = 0;
    nums[1] = 1;
    for (int i = 2; i <= n; i++){
        nums[i] = nums[i-1] + nums[i-2];
    }
    int temp = nums[n];
    free(nums);
    return temp;
}

int main(){
    timespec_t start;
    timespec_t end;
    double time;
    printf("Please select the nth fib # starting from 0:\n");
    int num = 0;
    scanf("%d", &num);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    int normal = fib_naive(num);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time = get_elapsed_time_sec(&start, &end);
    printf("Total elapsed naive: %.4e sec with ans: %d\n", time, normal);

    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    int tail = fib_tail(num);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time = get_elapsed_time_sec(&start, &end);
    printf("Total elapsed tail: %.4e sec with ans: %d\n", time, tail);
    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    int top = fib_top_down(num);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time = get_elapsed_time_sec(&start, &end);
    printf("Total elapsed top down: %.4e sec with ans: %d\n", time, top);
    
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
    int mem = fib_memoize(num);
    clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);
    time = get_elapsed_time_sec(&start, &end);
    printf("Total elapsed memoized: %.4e sec with ans: %d\n", time, mem);

    return 0;
}