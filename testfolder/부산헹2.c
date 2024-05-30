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

#define MOVE_LEFT 1
#define MOVE_STAY 0

#define ATK_NONE 0
#define ATK_CITIZEN 1
#define ATK_DONGSEOK 2

#define ACTION_REST 0
#define ACTION_PROVO 1
#define ACTION_PULL 2

// 전역 변수 선언
int trainLen, mstamina, prob;
int prevCitizenPos, prevZombiePos, prevmpos;
int citizenMove, zombieMove, mMove;
int zombieMoveCounter = 1;
int citizenPos, zombiePos, mpos;
int caggro = 0;
int maggro = 0;
char c[10];
int mA;

void intro();
int firsttrain(int, int);
void move();
void nexttrain();
int state();  // 루프를 제어하기 위해 int 반환
void minput();
void mstate();
void madongseokmove();
void mAct();
void zAct();
void outtro();

void intro() {
    // 인트로 메시지
    printf("**************************\n");
    printf("잠시 후 게임을 시작합니다.\n");
    printf("**************************\n");
    while (1) {
        printf("열차의 길이를 입력하세요 (%d에서 %d까지): ", LEN_MIN, LEN_MAX);
        scanf_s("%d", &trainLen);

        if (trainLen >= LEN_MIN && trainLen <= LEN_MAX) {
            break;
        }
    }

    while (1) {
        printf("마동석 체력(%d에서 %d까지): ", STM_MIN, STM_MAX);
        scanf_s("%d", &mstamina);

        if (mstamina >= STM_MIN && mstamina <= STM_MAX) {
            break;
        }
    }

    // 확률 입력 받기
    while (1) {
        printf("확률을 입력하세요 (%d에서 %d까지): ", PROB_MIN, PROB_MAX);
        scanf_s("%d", &prob);

        if (prob >= PROB_MIN && prob <= PROB_MAX) {
            break;
        }
    }

}

int firsttrain(int trainLen, int prob) {
    // 초기 열차 상태 출력
    for (int i = 0; i < trainLen; i++) {
        printf("#");
    }
    printf("\n");

    printf("#");
    for (int i = 1; i < trainLen - 1; i++) {
        if (i == trainLen - 6) {
            printf("C");  // 시민 위치
        }
        else if (i == trainLen - 3) {
            printf("Z");  // 좀비 위치
        }
        else if (i == trainLen - 2) {
            printf("M");  // 목표 지점
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
    // 시민 이동
    if (rand() % 100 < prob) {
        citizenMove = 0;
        caggro -= 1;
        if (caggro < AGGRO_MIN) {
            caggro = AGGRO_MIN;
        }
    }
    else {
        citizenMove = -1;
        caggro += 1;
        if (caggro > AGGRO_MAX) {
            caggro = AGGRO_MAX;
        }
    }
    citizenPos = prevCitizenPos + citizenMove;

    // 좀비 이동
    if (zombiePos + 1 == mpos) {
        zombieMove = 0;
    }
    else {
        if (zombieMoveCounter % 2 == 0) {
                zombieMove = 0;
            }
            else {
                if (caggro >= maggro) {
                    zombieMove -= 1;
                }
                else {
                    zombieMove += 1;
                }
            }
    }
    
    
    mpos = prevmpos;
}

void nexttrain() {
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
    // 시민과 좀비의 상태 출력
    if (citizenPos == prevCitizenPos) {
        printf("시민 제자리 : %d\n", citizenPos);
    }
    else {
        printf("시민 이동 : %d -> %d (aggro: %d)\n", prevCitizenPos, citizenPos, caggro);
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

    // 게임 성공 조건 확인
    if (citizenPos <= 1) {
        printf("SUCCESS!\n");
        printf("citizen(s) escaped to the next train\n");
        return 0;  // 게임 루프 종료
    }

    // 게임 오버 조건 확인


    prevCitizenPos = citizenPos;
    prevZombiePos = zombiePos;

    zombieMoveCounter++;
    return 1;  // 게임 루프 계속
}

void minput() {
    while (1) {
        printf("마동석 move(0:stay, 1:left)>>");
        scanf_s("%d", &mMove);

        if (mMove == 0 || mMove == 1) {
            break;
        }
    }
    if (mMove == 0) {
        mpos = prevmpos;
    }
    else {
        if (mpos == zombiePos + 1) {
            mpos = prevmpos;
        }
        else {
            mpos = prevmpos - 1;
        } 
    }
}


void madongseokmove() {
    if (mMove == MOVE_STAY) {
        c[10] = "stay";
        maggro -= 1;
        if (maggro < AGGRO_MIN) {
            maggro = AGGRO_MIN;
        }
    }
    else {
        c[10] ="left";
        maggro += 1;
        if (maggro > AGGRO_MAX) {
            maggro = AGGRO_MAX;
        }
    }
}

void zAct() {
    if (zombiePos - 1 == citizenPos || zombiePos + 1 == mpos) {
        if (zombiePos - 1 == citizenPos && zombiePos + 1 == mpos) {
            if (maggro > caggro) {
                mstamina = mstamina - 1;
            }
            else {
                printf("citizen does nothing.\n");
                printf("GAME OEVER! citizen dead...\n");
                return 0;
            }
        }
        else{
            if (citizenPos == zombiePos - 1) {
                printf("citizen does nothing.\n");
                printf("GAME OEVER! citizen dead...\n");
                return 0;  // 게임 루프 종료
            }
            else {

            }
        }
    }
    else {
        printf("citizen does nothing.\n");
        printf("zombie attacked nobody\n");
    }
}

void mAct() {
    if (mpos == zombiePos + 1) {
        while (1) {
            printf("madongseok action(0.rest, 1.provoke, 2. pull)>>");
            scanf_s("%d", &mA);

            if (mA == ACTION_REST || mA == ACTION_PROVO || mA == ACTION_PULL) {
                break;
            }
        }
    }if (mA == ACTION_REST) {
        maggro = maggro - 1;
    }
    else if (mA == ACTION_PROVO) {
        maggro = AGGRO_MAX;
    }
    else {
        if (rand() % 100 > prob) {
            maggro = maggro + 2;
            mstamina = mstamina - 1;
            zombieMoveCounter = 2;
        }
        
    }

}
    

void mstate() {
    if (mMove == 0) {
        printf("마동석: %s %d(aggro: %d, stamina: %d)\n", c,prevmpos, maggro, mstamina);
    }
    else {
        printf("마동석: %s %d(aggro: %d, stamina: %d)\n", c,prevmpos, maggro, mstamina);
    }
}

void outtro() {
    // 아웃트로 메시지
    printf("**********************\n");
    printf("게임이 종료되었습니다.\n");
    printf("**********************\n");
}
int main() {
    srand(time(NULL));  // 랜덤 시드 설정

    intro();  // 인트로 호출

    firsttrain(trainLen, prob);  // 초기 열차 상태 설정

    while (1) {
        move();  // 이동 계산

        zombiePos = prevZombiePos + zombieMove;

        nexttrain();  // 다음 열차 상태 출력
        printf("\n");

        if (!state()) {  // state() 함수의 반환 값을 확인하여 루프 제어
            break;  // 루프 종료
        }
        printf("\n");
        minput();
        madongseokmove();
        mAct();

        prevmpos = mpos;
        nexttrain();
        printf("\n");
        mstate();
        printf("\n");
        zAct();
    }

    outtro();
    return 0;
}
