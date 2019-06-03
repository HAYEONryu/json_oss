#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "header.h"

int askmenu();
void name(char* text, JSON *json, int howmany);
void region(char* text, JSON *json, int howmany);
void candidate(char* text, JSON *json, int howmany);
void winner(char* text, JSON *json, int howmany);
void region_turnout(char* text, JSON *json, int howmany);
void region_winner(char* text, JSON *json, int howmany);
void all_winner(char* text, JSON *json, int howmany);

int main(int argc, char *argv[]) {


    int size;
    char *text ;
    int howmany;
    text = readFile(argv[1], &size );
    //char* readFile(argv[1], &size);

    JSON json = {0, };
    parser(text, size, &json, &howmany);

    srand(time(0));

    int menuid;
    while(1){
        menuid=askmenu(); 
        switch(menuid){
            case 0: return 0;
            case 1: print(text, &json, howmany); break;
            case 2: name(text, &json, howmany); break;
            case 3: region(text, &json, howmany); break;
            case 4: candidate(text, &json, howmany); break;
    	    case 5: region_turnout(text, &json, howmany); break;
		    case 6: region_winner(text, &json, howmany); break;
            case 7: all_winner(text, &json, howmany); break;
    }
    }
    return 0;
}

int askmenu(){
  int menu;
  printf("\n\n<20대 총선 선거결과 검색> \n--------------전체 정보--------------");
  printf("\n1. 전체 정보 출력 2. 전체 후보자 출력 \n");
  printf("-------------지역별 정보-------------\n3. 전체 지역 출력 4. 지역 후보자 출력\n");
  printf("5. 지역 투표율 출력 6. 지역 당선자 출력\n7. 전체 지역별 당선자 출력\n");
  printf("0. 종료\n");
  scanf("%d", &menu);
  return menu;
}

void name(char* text, JSON *json, int howmany){
	
    char check[10] = "이름";
    printf("-------------전체 후보자-------------\n");
    for (int i = 0; i<= howmany; i++){

		int ret = strcmp(json->tokens[i].value, check);
        if(ret == 0){
            printf("%s\n", json->tokens[i+1].value);
        }
    }
}

void region(char* text, JSON *json, int howmany){
	
    char check[10] = "후보자";
    printf("-------------전체 지역-------------\n");
    for (int i = 0; i<= howmany; i++){

		int ret = strcmp(json->tokens[i].value, check);
        if(ret == 0){
            printf("%s\n", json->tokens[i-2].value);
        }
    }
}

void candidate(char* text, JSON *json, int howmany){
	
    char region[10]; 
    char check[10] = "이름";
    int i = 0, j = 0;

    printf("지역을 입력하세요\n");
    scanf("%s", region);
    printf("---------지역별 후보자 정보----------\n");

    for (i = 0; i<= howmany; i++){

		int ret = strcmp(json->tokens[i].value, region);
        if(ret == 0){
            j = i+5;

            while(ret==0){
                printf("이름: %s\n", json->tokens[j+1].value);
                printf("정당: %s\n", json->tokens[j+3].value);
                printf("득표수: %s\n\n", json->tokens[j+5].value);
                j = j+7;
                ret = strcmp(json->tokens[j].value, check);
            }
        }
    }
}

void region_turnout(char* text, JSON *json, int howmany){
    int vote = 0, electral_number = 0, turnout = 0;
    	
    char region[10]; 

    int i = 0, j = 0, ret = 0;

    printf("지역을 입력하세요\n");
    scanf("%s", region);

    for (i = 0; i<= howmany; i++){
        ret = strcmp(json->tokens[i].value, region);
        if(ret == 0){
            char check[10] = "투표수";
            for(j = i; j<=howmany; j++){

                ret = strcmp(json->tokens[j].value, check);
                if(ret == 0){
                    vote = atoi(json->tokens[j+1].value);
                    electral_number = atoi(json->tokens[j+5].value);                    
                    turnout = 100*vote/electral_number;
                    printf("------%s 투표율: %d%%------\n", region, turnout);
                    break;
                }
            }
        }
    }
}

void region_winner(char* text, JSON *json, int howmany){
    char region[10]; 
    int i = 0, j = 0, ret = 0;
    int vote=0, turnout = 0;
    int winner=0;

    printf("지역을 입력하세요\n");
    scanf("%s", region);

    for (i = 0; i<= howmany; i++){
        ret = strcmp(json->tokens[i].value, region);
        if(ret == 0){
            for(j = i; j<= howmany; j++){
                char check[10] = "투표수";
                ret = strcmp(json->tokens[j].value, check);
                if(ret == 0){ 
                vote = atoi(json->tokens[j+1].value);
                vote = 100*turnout/vote;
                    break;
                } 

                char check1[10] = "득표수";
                ret = strcmp(json->tokens[j].value, check1);
                if(ret == 0){
                    if(turnout < atoi(json->tokens[j+1].value)){
                        turnout = atoi(json->tokens[j+1].value);
                        winner = j-3;
                    }
                }
            }
            printf("당선자: %s, 득표수:%d, 득표율: %d%%", json->tokens[winner].value, turnout, vote);
        }
    }
}

void all_winner(char* text, JSON *json, int howmany){

    char check[10] = "후보자";
    char check1[10] = "득표수";
    char check2[10] = "투표수";

    int region = 0;
    int i = 0, j = 0, ret = 0;



    for (i = 0; i<= howmany; i++){
        int vote=0, turnout = 0;
        int winner=0;
        ret = strcmp(json->tokens[i].value, check);
        if(ret == 0) {
            region = i-2;
            for(j = i; j<=howmany; j++){
                ret = strcmp(json->tokens[j].value, check1);

                if(ret == 0){
                    if(turnout < atoi(json->tokens[j+1].value)){
                        turnout = atoi(json->tokens[j+1].value);
                        winner = j-3;
                    }
                }
            }
            char ret2 = strcmp(json->tokens[j].value, check2);
            if(ret2 == 0){
                vote = atoi(json->tokens[j+1].value);  
                printf("지역구:%s 당선자: %s, 득표수:%d, 득표율: %d%%\n",json->tokens[region].value, json->tokens[winner].value, turnout, 100*turnout/vote);
            }
        }
    }
}