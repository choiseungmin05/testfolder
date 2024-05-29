#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>

#define LEN_MIN 15
#define LEN_MAX 50
#define STM_MIN 0
#define STM_MAX 5
#define PROB_MIN 10 
#define PROB_MAX 90
#define AGGRO_MIN 0
#define AGGRO_MAX 5

#define MOVE_LEET 1
#define MOVE_SRAY 0

#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

#define ACTION_REST 0
#define ACTION_PROVOKE 1
#define ACTION_PULL 2

// ���� ���� ����
int trainLen, prob;
int prevCitizenPos, prevZombiePos;
int citizenMove, zombieMove;
int zombieMoveCounter = 1;
int citizenPos, zombiePos;

void intro();
int firsttrain(int, int);
void move();
void nexttrain();
int state();  // ������ �����ϱ� ���� int ��ȯ
void outtro();

void intro() {
    // ��Ʈ�� �޽���
    printf("**************************\n");
    printf("��� �� ������ �����մϴ�.\n");
    printf("**************************\n");

    Sleep(1500);

    // ���� ���� �Է� �ޱ�
    printf("������ ���̸� �Է��ϼ��� (%d���� %d����): ", LEN_MIN, LEN_MAX);
    scanf_s("%d", &trainLen);

    // �Է� ���̰� ���� ���̸� ����
    if (trainLen < LEN_MIN || trainLen > LEN_MAX) {
        printf("������ ���̴� %d���� %d������ �����մϴ�.\n", LEN_MIN, LEN_MAX);
        exit(1);
    }

    // Ȯ�� �Է� �ޱ�
    printf("Ȯ���� �Է��ϼ��� (%d���� %d����): ", PROB_MIN, PROB_MAX);
    scanf_s("%d", &prob);

    // �Է� Ȯ���� ���� ���̸� ����
    if (prob < PROB_MIN || prob > PROB_MAX) {
        printf("Ȯ���� %d���� %d������ �����մϴ�.\n", PROB_MIN, PROB_MAX);
        exit(1);
    }
}

int firsttrain(int trainLen, int prob) {
    // �ʱ� ���� ���� ���
    for (int i = 0; i < trainLen; i++) {
        printf("#");
    }
    printf("\n");

    printf("#");
    for (int i = 1; i < trainLen - 1; i++) {
        if (i == trainLen - 6) {
            printf("C");  // �ù� ��ġ
        }
        else if (i == trainLen - 3) {
            printf("Z");  // ���� ��ġ
        }
        else if (i == trainLen - 2) {
            printf("M");  // ��ǥ ����
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
}

void move() {
    // �ù� �̵�
    if (rand() % 100 < prob) {
        citizenMove = 0;
    }
    else {
        citizenMove = -1;
    }
    citizenPos = prevCitizenPos + citizenMove;

    // ���� �̵�
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
}

void nexttrain() {
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
}

int state() {
    // �ùΰ� ������ ���� ���
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

    // ���� ���� ���� Ȯ��
    if (citizenPos <= 1) {
        printf("SUCCESS!\n");
        printf("citizen(s) escaped to the next train\n");
        return 0;  // ���� ���� ����
    }

    // ���� ���� ���� Ȯ��
    if (citizenPos == zombiePos - 1) {
        printf("GAME OVER!\n");
        printf("citizen(s) has(have) been attacked by a zombie\n");
        return 0;  // ���� ���� ����
    }

    prevCitizenPos = citizenPos;
    prevZombiePos = zombiePos;

    zombieMoveCounter++;
    return 1;  // ���� ���� ���
}

void outtro() {
    // �ƿ�Ʈ�� �޽���
    printf("**********************\n");
    printf("������ ����Ǿ����ϴ�.\n");
    printf("**********************\n");
}
int main() {
    srand(time(NULL));  // ���� �õ� ����

    intro();  // ��Ʈ�� ȣ��

    firsttrain(trainLen, prob);  // �ʱ� ���� ���� ����

    while (1) {
        move();  // �̵� ���

        zombiePos = prevZombiePos + zombieMove;

        nexttrain();  // ���� ���� ���� ���

        if (!state()) {  // state() �Լ��� ��ȯ ���� Ȯ���Ͽ� ���� ����
            break;  // ���� ����
        }
    }
    outtro();
    return 0;
}
