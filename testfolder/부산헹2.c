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

    // ��Ʈ��
    printf("**************************\n");
    printf("��� �� ������ �����մϴ�.\n");
    printf("**************************\n");

    Sleep(1500);

    // ���� ���� �Է� �ޱ�
    printf("������ ���̸� �Է��ϼ��� (%d���� %d����): ", LEN_MIN, LEN_MAX);
    scanf_s("%d", &trainLen);

    if (trainLen < LEN_MIN || trainLen > LEN_MAX) {
        printf("������ ���̴� %d���� %d������ �����մϴ�.\n", LEN_MIN, LEN_MAX);
        exit(1);
    }

    // Ȯ�� �Է� �ޱ�
    printf("Ȯ���� �Է��ϼ��� (%d���� %d����): ", PROB_MIN, PROB_MAX);
    scanf_s("%d", &prob);

    if (prob < PROB_MIN || prob > PROB_MAX) {
        printf("Ȯ���� %d���� %d������ �����մϴ�.\n", PROB_MIN, PROB_MAX);
        exit(1);
    }

    // �ʱ� ���� ���� ���
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
        // �ù� �̵�
        int citizenMove;
        if (rand() % 100 < prob) {
            citizenMove = 0;
        }
        else {
            citizenMove = -1;
        }
        int citizenPos = prevCitizenPos + citizenMove;

        // ���� �̵�
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

        // ���� ���� ���
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

        // �ù�, ���� ���� ���
        if (citizenPos == prevCitizenPos) {
            printf("�ù� ���ڸ� : %d\n", citizenPos);
        }
        else {
            printf("�ù� �̵� : %d -> %d\n", prevCitizenPos, citizenPos);
        }

        if (zombiePos == prevZombiePos) {
            if (zombieMoveCounter % 2 == 0) {
                printf("���� �̵� �Ұ� : %d\n", zombiePos);
            }
            else {
                printf("���� ���ڸ� : %d\n", zombiePos);
            }
        }
        else {
            printf("���� �̵� : %d -> %d\n", prevZombiePos, zombiePos);
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

    // �ƿ�Ʈ��
    printf("**********************\n");
    printf("������ ����Ǿ����ϴ�.\n");
    printf("**********************\n");

    Sleep(4000);

    return 0;
}
