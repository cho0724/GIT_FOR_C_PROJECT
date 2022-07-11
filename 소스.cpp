#define _CRT_SECURE_NO_WARNINGS //scanf_s, gets_s 대신 scanf, gets로 사용할수있도록 해주는 명령어. 중요X
#define MAX_SIZE 100 // 일정 프로그램에 저장할수있는 명령의 최대 수 100개임을 의미하는 매크로 변수/ C, 다른언어의 const 키워드 처럼 값을 변경할 수 없다.
#include <stdio.h> //standard input/output header (입출력 및 그외 기본적인 기능의 헤더파일)
#include <string.h> // string header (문자열 헤더파일)
#include <windows.h> // windows headr 중요X
typedef struct _CALENDAR { //C 언어의 구조체 문법. year, month, day, 일정data 의 정보를 담고 있고, 구조체배열로 100칸의 공간을 할당
	int year;
	int month;
	int day;
	char* to_do;
}CALENDAR;
void initiallize(CALENDAR* calendar); // 100칸의 구조체를 할당하고 그 값을 초기화 해주는 함수.
int ShowMenu(); //메뉴를 출력해주는 함수
void SerchCalendar(CALENDAR* calendar, int cnt); //조회 기능 함수.
int DeleteCalendar(CALENDAR* calendar, int cnt);//삭제 기능 함수.
int GetDayOfMonth(int year, int num);
int GetLeafYear(int year);
int GetDay(int year, int month);
void PrintCalendar(CALENDAR* calendar, int, int, int year, int month); //15 ~ 18 조회 기능 함수내에서 호출하는 조회기능을 위한 부가적인 함수
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
				DeleteCalendar(calendar, data_cnt_index);
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
		calendar[i].to_do = (char*)malloc(sizeof(char) * 100); //100칸의 문자 공간을 to_do 변수에 할당. 즉, 일정을 100자 이상 입력할 수 없음.
		calendar[i].to_do[0] = '\0'; //
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
					SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10); // printf 함수로 출력할 때 글자색을 바꿔주는 함수. 중요X
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
int DeleteCalendar(CALENDAR* calendar, int cnt) {
	if (cnt < 1) {
		printf("┌────────────────────────────────────────────────────────┐\n");
		printf("│            일정이 하나도 존재 하지 않습니다 .          │\n");
		printf("└────────────────────────────────────────────────────────┘\n\n");
		return 0;
	}
	int year, month, day;
	printf("┌────────────────────────────────────────────────────────┐\n");
	printf("                      년도 입력 : ");
	scanf("%d", &year);
	printf("                      월 입력 : ");
	scanf("%d", &month);
	printf("                      일 입력 : ");
	scanf("%d", &day);
	printf("└────────────────────────────────────────────────────────┘\n\n");
	for (int i = 0; i < cnt; i++) {
		if (calendar[i].year == year && calendar[i].month == month && calendar[i].day == day) {
			rewind(stdin);
			printf("변경할 일정을 입력 : ");
			strcpy(calendar[i].to_do, "\0");
			cnt = cnt - 1;
		}
	}
	printf("┌────────────────────────────────────────────────────────┐\n");
	printf("│                        삭제완료                        │\n");
	printf("└────────────────────────────────────────────────────────┘\n\n");
	return cnt;
}