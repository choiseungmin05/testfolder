#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define LEN_MIN 15
#define LEN_MAX 50
#define PROB_MIN 10 
#define PROB_MAX 90

int main() {
    int trainLen, prob;
    int prevCitizenPos, prevZombiePos;

    srand(time(NULL));

    // 인트로
    printf("**************************\n");
    printf("잠시 후 게임을 시작합니다.\n");
    printf("**************************\n");

    Sleep(1500);

    // 열차 길이 입력 받기
    printf("열차의 길이를 입력하세요 (%d에서 %d까지): ", LEN_MIN, LEN_MAX);
    scanf_s("%d", &trainLen);

    if (trainLen < LEN_MIN || trainLen > LEN_MAX) {
        printf("열차의 길이는 %d에서 %d까지만 가능합니다.\n", LEN_MIN, LEN_MAX);
        exit(1);
    }

    // 확률 입력 받기
    printf("확률을 입력하세요 (%d에서 %d까지): ", PROB_MIN, PROB_MAX);
    scanf_s("%d", &prob);

    if (prob < PROB_MIN || prob > PROB_MAX) {
        printf("확률은 %d에서 %d까지만 가능합니다.\n", PROB_MIN, PROB_MAX);
        exit(1);
    }

    // 초기 열차 상태 출력
    for (int i = 0; i < trainLen; i++) {
        printf("#");
    }
    printf("\n");

    printf("#");
    for (int i = 1; i < trainLen - 1; i++) {
        if (i == trainLen - 6) {
            printf("C");
        }
        else if (i == trainLen - 3) {
            printf("Z");
        }
        else if (i == trainLen - 2) {
            printf("M");
        }
        else {
            printf(" ");
        }
    }
    printf("#\n");

    for (int i = 0; i < trainLen; i++) {
        printf("#");
    }
    printf("\n");

    prevCitizenPos = trainLen - 6;
    prevZombiePos = trainLen - 3;

    int zombieMoveCounter = 1;

    while (1) {
        // 시민 이동
        int citizenMove;
        if (rand() % 100 < prob) {
            citizenMove = 0;
        }
        else {
            citizenMove = -1;
        }
        int citizenPos = prevCitizenPos + citizenMove;

        // 좀비 이동
        int zombieMove;
        if (zombieMoveCounter % 2 == 0) {
            zombieMove = 0;
        }
        else {
            if (rand() % 100 < prob) {
                zombieMove = -1;
            }
            else {
                zombieMove = 0;
            }
        }
        int zombiePos = prevZombiePos + zombieMove;

        // 열차 상태 출력
        for (int i = 0; i < trainLen; i++) {
            printf("#");
        }
        printf("\n");

        printf("#");
        for (int i = 1; i < trainLen - 1; i++) {
            if (i == citizenPos) {
                printf("C");
            }
            else if (i == zombiePos) {
                printf("Z");
            }
            else if (i == trainLen - 2) {
                printf("M");
            }
            else {
                printf(" ");
            }
        }
        printf("#\n");

        for (int i = 0; i < trainLen; i++) {
            printf("#");
        }
        printf("\n");

        // 시민, 좀비 상태 출력
        if (citizenPos == prevCitizenPos) {
            printf("시민 제자리 : %d\n", citizenPos);
        }
        else {
            printf("시민 이동 : %d -> %d\n", prevCitizenPos, citizenPos);
        }

        if (zombiePos == prevZombiePos) {
            if (zombieMoveCounter % 2 == 0) {
                printf("좀비 이동 불가 : %d\n", zombiePos);
            }
            else {
                printf("좀비 제자리 : %d\n", zombiePos);
            }
        }
        else {
            printf("좀비 이동 : %d -> %d\n", prevZombiePos, zombiePos);
        }

        if (citizenPos <= 1) {
            printf("SUCCESS!\n");
            printf("citizen(s) escaped to the next train\n");
            break;
        }

        if (citizenPos == zombiePos - 1) {
            printf("GAME OVER!\n");
            printf("citizen(s) has(have) been attacked by a zombie\n");
            break;
        }

        prevCitizenPos = citizenPos;
        prevZombiePos = zombiePos;

        zombieMoveCounter++;

        Sleep(4000);
    }
    Sleep(4000);

    // 아웃트로
    printf("**********************\n");
    printf("게임이 종료되었습니다.\n");
    printf("**********************\n");

    Sleep(4000);

    return 0;
}
