#define _CRT_SECURE_NO_WARNINGS //scanf_s, gets_s 대신 scanf, gets로 사용할수있도록 해주는 명령어. 중요X
#define MAX_SIZE 100 // 일정 프로그램에 저장할수있는 명령의 최대 수 100개임을 의미하는 매크로 변수
#include <stdio.h> //standard input/output header
#include <string.h> // string header (문자열)
#include <windows.h> // windows headr 중요X
typedef struct _CALENDAR { //C 언어의 구조체 문법. year, month, day, 일정data 의 정보를 담고 있고, 구조체배열로 100칸의 공간을 할당
	int year; 
	int month;
	int day;
	char* to_do;
}CALENDAR;
void initiallize(CALENDAR* calendar); 
int ShowMenu();
void SerchCalendar(CALENDAR* calendar, int cnt);
int GetDayOfMonth(int year, int num);
int GetLeafYear(int year);
int GetDay(int year, int month);
void PrintCalendar(CALENDAR* calendar, int, int, int year, int month);
int main() {
	int menu_number = 0; 
	int data_cnt_index = 0;  //현재 저장된 일정 데이터의 수를 의미. 최대 100개이며 삽입시 +1올려주고, 삭제시 -1 해줌.
	CALENDAR calendar[100]; //CALENDAR 배열 구조체 선언 (100칸)
	initiallize(calendar);
	while (1) {
		menu_number = ShowMenu();
		if (menu_number != 0) {
			switch (menu_number) {
			case 1:
				SerchCalendar(calendar, data_cnt_index);
				break;
			case 2:
				//Insert 함수호출
				break;
			case 3:
		        //update 함수호출
				break;
			case 4:
				//delete 함수호출
				break;
			case 5:
				printf("┌────────────────────────────────────────────────────────┐\n");
				printf("│                          종료                          │\n");
				printf("└────────────────────────────────────────────────────────┘\n\n");
				return 0;
			}
		}
	}
}
void initiallize(CALENDAR* calendar) {
	for (int i = 0; i < MAX_SIZE; i++) {
		calendar[i].to_do = (char*)malloc(sizeof(char) * 100);
		calendar[i].to_do[0] = '\0';
	}
}
int ShowMenu() {
	int menu_number;
	printf("┌────────────────────────────────────────────────────────┐\n");
	printf("│                                                        │\n");
	printf("│                                                        │\n");
	printf("│                     1.   조회 하기                     │\n");
	printf("│                     2.   일정 추가                     │\n");
	printf("│                     3.   일정 수정                     │\n");
	printf("│                     4.   일정 삭제                     │\n");
	printf("│                     5.   종료                          │\n");
	printf("│                                                        │\n");
	printf("│                                                        │\n");
	printf("│                                                        │\n");
	printf("└────────────────────────────────────────────────────────┘\n");
	printf("\n 메뉴 선택 : ");
	scanf("%d", &menu_number);
	if (menu_number > 5 || menu_number < 1) {
		system("cls"); //출력창의 내용들을 깨끗하게 지워줌
		printf("┌────────────────────────────────────────────────────────┐\n");
		printf("│         !!  메뉴 번호를 잘못 입력하셨습니다.  !!       │\n");
		printf("└────────────────────────────────────────────────────────┘\n");
	}
	else return menu_number;
}
int GetDayOfMonth(int year, int month) {
	int day_of_month[13] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	day_of_month[2] += GetLeafYear(year);
	return day_of_month[month];
}
int GetLeafYear(int year) {
	if (year % 400 == 0)
		return 1;
	if ((year % 100 != 0) && (year % 4 == 0))
		return 1;
	return 0;
}
int GetDay(int year, int month) {
	int past_day = 0;
	for (int y = 1; y < year; y++)
		past_day = past_day + 365 + GetLeafYear(y);
	for (int m = 1; m < month; m++)
		past_day = past_day + GetDayOfMonth(year, m);
	return (1 + past_day) % 7;
}
void PrintCalendar(CALENDAR* calendar, int start_day, int total_day, int cnt, int year, int month) {
	printf("     Sun     Mon     Tue     Wed     Thu     Fri     Sat\n");
	for (int i = 0; i < start_day; i++)
		printf("        ");
	for (int day = 1, ke = start_day; day <= total_day; day++, ke++) {
		for (int i = 0; i < cnt; i++) {
			if (calendar[i].year == year && calendar[i].month == month && calendar[i].day == day) {
				if (calendar[i].to_do[0] != '\0')
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
			}
		}
		printf("%8d", day);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
		if (ke % 7 == 6)
			printf("\n");
	}
}
void SerchCalendar(CALENDAR* calendar, int cnt) {
	system("cls");
	int year, month;
	printf("┌────────────────────────────────────────────────────────┐\n");
	printf("                      년도 입력 : ");
	scanf("%d", &year);
	printf("                      월 입력 : ");
	scanf("%d", &month);
	printf("└────────────────────────────────────────────────────────┘\n\n");
	int start_day = GetDay(year, month);
	int total_day = GetDayOfMonth(year, month);
	PrintCalendar(calendar, start_day, total_day, cnt, year, month);
	printf("\n\n");
	printf("┌───────────────────────전체일정─────────────────────────┐\n");
	for (int i = 0; i < cnt; i++) {
		printf("│  년도 : %d, 월 : %d, 일 %d, 일정 : %s  \n", calendar[i].year, calendar[i].month, calendar[i].day, calendar[i].to_do);
	}
	printf("└────────────────────────────────────────────────────────┘\n\n");
}
/* 
   삽입시에 구조체 배열의 data_cnt_index 번째에 테이터를 삽입한다.
   데이터 삽입 연산이 끝나면 data_cnt_index의 값을 +1 증가.
*/

/*
   데이터 삭제시에 입력한 년,월,일의 값과 일치한 구조체를 찾고 그 구조체가 가지고 있는 to_do 변수의 첫번째 index에 '\0'을 넣어준다. 
   그 후 data_cnt_index의 값을 -1해줌.
   데이터가 삭제할 데이터가 없으면 해당 메시지도 출력
*/
