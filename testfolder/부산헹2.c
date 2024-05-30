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
int trainLen, mstamina, prob;
int prevCitizenPos, prevZombiePos, prevmpos;
int citizenMove, zombieMove, mMove;
int zombieMoveCounter = 1;
int citizenPos, zombiePos, mpos;
int caggro = 1;
int maggro = 1;
char c[100];

void intro();
int firsttrain(int, int);
void move();
void nexttrain();
int state();  // ������ �����ϱ� ���� int ��ȯ
void minput();
void mstate();
void outtro();

void intro() {
    // ��Ʈ�� �޽���
    printf("**************************\n");
    printf("��� �� ������ �����մϴ�.\n");
    printf("**************************\n");
    while (1) {
        printf("������ ���̸� �Է��ϼ��� (%d���� %d����): ", LEN_MIN, LEN_MAX);
        scanf_s("%d", &trainLen);

        if (trainLen >= LEN_MIN && trainLen <= LEN_MAX) {
            break;
        }
    }

    while (1) {
        printf("������ ü��(%d���� %d����): ", STM_MIN, STM_MAX);
        scanf_s("%d", &mstamina);

        if (mstamina >= STM_MIN && mstamina <= STM_MAX) {
            break;
        }
    }

    // Ȯ�� �Է� �ޱ�
    while (1) {
        printf("Ȯ���� �Է��ϼ��� (%d���� %d����): ", PROB_MIN, PROB_MAX);
        scanf_s("%d", &prob);

        if (prob >= PROB_MIN && prob <= PROB_MAX) {
            break;
        }
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
    prevmpos = trainLen - 2;
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
    mpos = prevmpos;
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
        else if (i == mpos) {
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
        printf("�ù� �̵� : %d -> %d (aggro: %d)\n", prevCitizenPos, citizenPos, caggro);
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

void minput() {
    while (1) {
        printf("������ move(0:stay, 1:left)>>");
        scanf_s("%d", &mMove);

        if (mMove == 0 || mMove == 1) {
            break;
        }
    }
    if (mMove == 0) {
        mpos = prevmpos;
    }
    else {
        mpos = prevmpos - 1;
    }
}

void mstate() {
    if (mMove == 0) {
        printf("������: stay %d(aggro: %d, stamina: %d)\n", prevmpos, maggro, mstamina);
    }
    else {
        printf("������: left %d(aggro: %d, stamina: %d)\n", prevmpos, maggro, mstamina);
    }
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
        printf("\n");

        if (!state()) {  // state() �Լ��� ��ȯ ���� Ȯ���Ͽ� ���� ����
            break;  // ���� ����
        }
        printf("\n");
        minput();

        prevmpos = mpos;
        nexttrain();
        printf("\n");
        mstate();
       
    }

    outtro();
    return 0;
}
