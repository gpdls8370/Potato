//화이팅!!
//1280x720
//Potato = main 소스에서는 쓸 함수 선언 + 시스템 변수 선언 + main역할만 함
//main에서 필요해지는건 extern으로 받아와서 씀 ex)각장면의 main함수들
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

extern SceneID title, store, book1, book2, book3, end;

extern void mainTitle();
extern void mainFarm();
extern void mainStore();
extern void mainBook1();
extern void mainBook2();
extern void mainBook3();
extern void mainEnd();
extern void mouseCallbackTitle(ObjectID object, int x, int y, MouseAction action);
extern void mouseCallbackFarm(ObjectID object, int x, int y, MouseAction action);
extern void mouseCallbackStore(ObjectID object, int x, int y, MouseAction action);
extern void mouseCallbackBook1(ObjectID object, int x, int y, MouseAction action);
extern void mouseCallbackBook2(ObjectID object, int x, int y, MouseAction action);
extern void mouseCallbackBook3(ObjectID object, int x, int y, MouseAction action);
extern void mouseCallbackEnd(ObjectID object, int x, int y, MouseAction action);

extern void timerCallbackFarm(TimerID timer);

SoundID button, success, potatoClick1, potatoClick2, potatoClick3, water, moleClick1, moleClick2, moleClick3, bgm;
TimerID bgmTimer;

int num;
int moneyNum[9];

int waterLevel = 0;
int nowPotato[4]
= { 0,0,0,0 };

//두더지 100마리 잡으면 true됨
bool moleUnlocked = false;
int countMole = 0;

int money = 0;
int day = 1;
int leftDay = 5;		//남은날짜 : 처음은 5일
float gameTime = 15.0f;

//n일때 다음 물뿌리개로 업그레이드 하기 위해 필요한 돈
int upgradeMoney[14]
= { 300,800,2000,5000,20000,80000,200000,500000,1000000,5000000,10000000,50000000,100000000,1 };

//물뿌리개 이미지 리스트
const char* waterImageList[14]
= { "Images/물뿌리개/물뿌리개.png","Images/물뿌리개/철물뿌리개.png" ,"Images/물뿌리개/빛나는철물뿌리개.png" ,"Images/물뿌리개/금물뿌리개.png" ,
"Images/물뿌리개/빛나는금물뿌리개.png" ,"Images/물뿌리개/다이아물뿌리개.png" ,"Images/물뿌리개/빛나는다이아물뿌리개.png" ,"Images/물뿌리개/이리듐물뿌리개.png" ,
"Images/물뿌리개/빛나는이리듐물뿌리개.png" ,"Images/물뿌리개/무지개물뿌리개.png" ,"Images/물뿌리개/빛나는무지개물뿌리개.png" ,
"Images/물뿌리개/많이빛나는물뿌리개.png" ,"Images/물뿌리개/너무많이빛나는물뿌리개.png","Images/버튼/더이상.png" };

const char* waterStoreImageList[14]
= { "Images/상점/플라스틱.png","Images/상점/철.png","Images/상점/빛나는철.png","Images/상점/금.png",
"Images/상점/빛나는금.png" ,"Images/상점/다이아.png" ,"Images/상점/빛나는다이아.png" ,"Images/상점/이리듐.png" ,
"Images/상점/빛나는이리듐.png" ,"Images/상점/무지개.png" ,"Images/상점/빛나는무지개.png","Images/상점/많이빛나는.png",
"Images/상점/너무많이빛나는.png" ,"Images/상점/두더지.png" };

//감자 이미지 리스트
const char* potatoImageList[8]
= { "Images/감자/평범한감자.png","Images/감자/왕감자.png" ,"Images/감자/금감자.png" ,"Images/감자/다이아감자.png" ,
"Images/감자/포카칩감자.png" ,"Images/감자/무지개감자.png" ,"Images/감자/대홍단감자.png" ,"Images/감자/두더지감자.png" };

//감자 가격 리스트
int potatoMoneyList[8]
= { 10,50,200,1000,5000,50000,500000,1 };

//감자 발견 여부 = 도감 오픈 여부
bool findPotato[8]
= { 0,0,0,0,0,0,0,0 };
bool openBook[8]
= { 0,0,0,0,0,0,0,0 };

//변경바람
const char* potatoMoneyImageList[8]
= { "Images/도감/물음표0.png","Images/도감/물음표1.png" ,"Images/도감/물음표2.png" ,"Images/도감/물음표3.png" ,
"Images/도감/물음표4.png" ,"Images/도감/물음표5.png" ,"Images/도감/물음표6.png" ,"Images/도감/물음표7.png" };

const char* bookImageList_no[8]
= { "Images/도감/물음표0.png","Images/도감/물음표1.png" ,"Images/도감/물음표2.png" ,"Images/도감/물음표3.png" ,
"Images/도감/물음표4.png" ,"Images/도감/물음표5.png" ,"Images/도감/물음표6.png" ,"Images/도감/물음표7.png" };

const char* bookImageList_yes[8]
= { "Images/도감/도감0.png", "Images/도감/도감1.png" ,"Images/도감/도감2.png" ,"Images/도감/도감3.png" ,
"Images/도감/도감4.png" ,"Images/도감/도감5.png" ,"Images/도감/도감6.png" ,"Images/도감/도감7.png" };

int nextDayPriceList[14]		//날짜 추가 위해서 필요한 돈 == 물뿌리개 강화에 필요한 돈
= { 300,800,2000,5000,20000,80000,200000,500000,1000000,5000000,10000000,50000000,100000000,1 };


ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size) {

	ObjectID object = createObject(name);
	locateObject(object, scene, x, y);
	scaleObject(object, size);

	if (shown == true)
		showObject(object);

	return object;
}

//두더지(0)/1/2/3 출력
//type 1: 20/20/50/10, type2: 30/0/40/30
int random(int type) {

	//0~9
	num = rand() % 10;
	int result = 0;

	switch (type) {
	case 1:
		if (num < 2) result = 0;
		else if (num < 4) result = 1;
		else if (num < 9) result = 2;
		else result = 3;
		break;
	case 2:
		if (num < 3) result = 0;
		else if (num < 7) result = 2;
		else result = 3;
		break;
	}
	return result;
}

//moneyNum[9]에 현재 돈이 자리수 나눠서 채워짐
void getMoneyNum(int mon) {
	//money값만 카피 -> money는 안건들기 위해서
	moneyNum[0] = 0;
	moneyNum[1] = 0;		//0원일 경우 대비해서 첫째 자리는 0으로  초기화
	for (int i = 2; i < 9; i++)
		moneyNum[i] = -1;	//초기화 (-1일때는 해당 자리에 숫자가 없는 것)

	for (int i = 1; i < 9; i++) {
		if (mon >= 1) {
			moneyNum[i] = mon % 10;
			mon /= 10;
		}
	}
}


void mouseCallback(ObjectID object, int x, int y, MouseAction action) {
	mouseCallbackTitle(object, x, y, action);
	mouseCallbackFarm(object, x, y, action);
	mouseCallbackStore(object, x, y, action);
	mouseCallbackBook1(object, x, y, action);
	mouseCallbackBook2(object, x, y, action);
	mouseCallbackBook3(object, x, y, action);
	mouseCallbackEnd(object, x, y, action);
}

void timerCallback(TimerID timer) {
	timerCallbackFarm(timer);

	if (timer == bgmTimer)
		playSound(bgm, true);
}


int main() {

	srand(time(NULL));	//랜덤값 초기화

	setMouseCallback(mouseCallback);
	setTimerCallback(timerCallback);

	mainTitle();
	mainFarm();
	mainStore();
	mainBook1();
	mainBook2();
	mainBook3();
	mainEnd();

	bgmTimer = createTimer(1.0f);
	bgm = createSound("Sounds/타이틀.mp3");

	button = createSound("Sounds/버튼클릭.mp3");
	success = createSound("Sounds/강화성공.mp3");
	potatoClick1 = createSound("Sounds/감자클릭1.mp3");
	potatoClick2 = createSound("Sounds/감자클릭2.mp3");
	potatoClick3 = createSound("Sounds/감자클릭3.mp3");
	moleClick1 = createSound("Sounds/두더지1.mp3");
	moleClick2 = createSound("Sounds/두더지2.mp3");
	moleClick3 = createSound("Sounds/두더지3.mp3");
	water = createSound("Sounds/물주기.mp3");

	startTimer(bgmTimer);

	startGame(title);
}