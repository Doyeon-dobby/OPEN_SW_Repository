#include "Score.h"
#include <stdio.h>
#include "ConsoleControl.h"     //콘솔 화면을 제어하기 위한 헤더 파일
#include "Colors.h"             //콘솔 화면의 텍스트와 배경 색상을 변경하기위한 헤더 파일

int gameScore = 0;

int GetScore(int info)
{
    int score = ReturnScore(info);      //info에 따라 반환되는 점수를 가져옴
    gameScore += score;                 //누적된 점수에 score를 추가
    return gameScore;                   //누적된 점수를 반환
}

void ShowScore()
{
    int showScoreX = 3;     //점수가 출력될 X 좌표
    int showScoreY = 0;     //점수가 출력될 Y 좌표
    COORD curPos = GetCurrentCursorPos();   //커서의 현재 위치를 가져옴
    SetCurrentCursorPos(showScoreX, showScoreY);    //커서 위치를 지정한 좌표로 이동
    SetMapColor(0);        //텍스트 색상을 바탕색과 동일한 색상으로 변경
    printf("Score : %d", gameScore);     //누적된 점수를 출력
    SetCurrentCursorPos(curPos.X, curPos.Y);    //커서 위치를 이전 위치로 이동
}

int ReturnScore(int action)
{
    int a = 0;
    switch (action)
    {
    case 0:     //BASICBLOCK 파괴 시
        a = BASICBLOCK;   //BASICBLOCK 파괴 시 얻는 점수
        break;
    case 2:     //COPPER 광물 채굴 시
        a = COPPER;     //COPPER 광물 채굴 시 얻는 점수
        break;
    case 3:     //SILVER 광물 채굴 시
        a = SILVER;     //SILVER 광물 채굴 시 얻는 점수
        break;
    case 4:     //GOLD 광물 채굴 시
        a = GOLD;       //GOLD 광물 채굴 시 얻는 점수
        break;
    case 5:     //CRYSTAL 광물 채굴 시
        a = CRYSTAL;    //CRYSTAL 광물 채굴 시 얻는 점수
        break;
    case 6:     //DIAMOND 광물 채굴 시
        a = DIAMOND;    //DIAMOND 광물 채굴 시 얻는 점수
        break;
    case 7:     //S_CRAETUM 광물 채굴 시
        a = S_CRAETUM;   //S_CRAETUM 광물 채굴 시 얻는 점수
        break;
    case 8:     //S_SELANUM 광물 채굴 시
        a = S_SELANUM;   //S_SELANUM 광물 채굴 시 얻는 점수
        break;
    case 9:     //S_CRIPTON 광물 채굴 시
        a = S_CRIPTON;   //S_CRIPTON 광물 채굴 시 얻는 점수
        break;
    case 10:    //몬스터 처치 시
        a = MOSTERKILL;      //몬스터 처치 시 얻는 점수
        break;
    case 11:    //스테이지 전체 클리어 시
        a = 5000;            //스테이지 클리어 시 얻는 점수
        break;
    case 12:
        a = 10000;
        break;
    case 13:
        a = 15000;
        break;
    case 14:
        a = 20000;
        break;
    case 15:    //게임 전체 클리어 시
        a = 25000;           //게임 클리어 시 얻는 점수
        break;
    default:
        break;
    }
    return a;     //각 action에 맞는 점수를 반환
}
