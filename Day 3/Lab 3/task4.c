#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int count (int p, int q, int r) {
    if (p < 0 || q < 0 || r < 0){
        return -1;
    }
    int cnt = 0;
    for (int i = 0; i < p; i++){
        
        if ((rand() % (q + 1)) <= r){
            cnt++;
        }
         
    }
    return cnt;

}

int main(void) {
    int p, q, r;
    int result;

    /* 用当前时间作为随机数种子，初始化 rand() */
    srand(time(NULL));

    printf("Let's check for invalid parameters!\n");

    printf("count(-1, 10, 5) = %d  (expected -1)\n", count(-1, 10, 5));
    printf("count(10, -1, 5) = %d  (expected -1)\n", count(10, -1, 5));
    printf("count(10, 10, -1) = %d  (expected -1)\n", count(10, 10, -1));
    printf("count(10, 5, 10) = %d  (expected -1)\n", count(10, 5, 10));

    while (1) {
        printf("\nPlease input p, q, and r: ");
        scanf("%d %d %d", &p, &q, &r);

        if (p == 0) {
            printf("Program exits.\n");
            break;
        }

        if (p < 0 || q < 0 || r < 0) {
            printf("Invalid input. Please make sure p > 0, q >= 0, r >= 0, and r <= q.\n");
        } else {
            result = count(p, q, r);
            printf("Result: %d\n", result);
        }
    }
  
    return 0;
}