//ȭ����!!
//1280x720
//Potato = main �ҽ������� �� �Լ� ���� + �ý��� ���� ���� + main���Ҹ� ��
//main���� �ʿ������°� extern���� �޾ƿͼ� �� ex)������� main�Լ���
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

//�δ��� 100���� ������ true��
bool moleUnlocked = false;
int countMole = 0;

int money = 0;
int day = 1;
int leftDay = 5;		//������¥ : ó���� 5��
float gameTime = 15.0f;

//n�϶� ���� ���Ѹ����� ���׷��̵� �ϱ� ���� �ʿ��� ��
int upgradeMoney[14]
= { 300,800,2000,5000,20000,80000,200000,500000,1000000,5000000,10000000,50000000,100000000,1 };

//���Ѹ��� �̹��� ����Ʈ
const char* waterImageList[14]
= { "Images/���Ѹ���/���Ѹ���.png","Images/���Ѹ���/ö���Ѹ���.png" ,"Images/���Ѹ���/������ö���Ѹ���.png" ,"Images/���Ѹ���/�ݹ��Ѹ���.png" ,
"Images/���Ѹ���/�����±ݹ��Ѹ���.png" ,"Images/���Ѹ���/���̾ƹ��Ѹ���.png" ,"Images/���Ѹ���/�����´��̾ƹ��Ѹ���.png" ,"Images/���Ѹ���/�̸��㹰�Ѹ���.png" ,
"Images/���Ѹ���/�������̸��㹰�Ѹ���.png" ,"Images/���Ѹ���/���������Ѹ���.png" ,"Images/���Ѹ���/�����¹��������Ѹ���.png" ,
"Images/���Ѹ���/���̺����¹��Ѹ���.png" ,"Images/���Ѹ���/�ʹ����̺����¹��Ѹ���.png","Images/��ư/���̻�.png" };

const char* waterStoreImageList[14]
= { "Images/����/�ö�ƽ.png","Images/����/ö.png","Images/����/������ö.png","Images/����/��.png",
"Images/����/�����±�.png" ,"Images/����/���̾�.png" ,"Images/����/�����´��̾�.png" ,"Images/����/�̸���.png" ,
"Images/����/�������̸���.png" ,"Images/����/������.png" ,"Images/����/�����¹�����.png","Images/����/���̺�����.png",
"Images/����/�ʹ����̺�����.png" ,"Images/����/�δ���.png" };

//���� �̹��� ����Ʈ
const char* potatoImageList[8]
= { "Images/����/����Ѱ���.png","Images/����/�հ���.png" ,"Images/����/�ݰ���.png" ,"Images/����/���̾ư���.png" ,
"Images/����/��īĨ����.png" ,"Images/����/����������.png" ,"Images/����/��ȫ�ܰ���.png" ,"Images/����/�δ�������.png" };

//���� ���� ����Ʈ
int potatoMoneyList[8]
= { 10,50,200,1000,5000,50000,500000,1 };

//���� �߰� ���� = ���� ���� ����
bool findPotato[8]
= { 0,0,0,0,0,0,0,0 };
bool openBook[8]
= { 0,0,0,0,0,0,0,0 };

//����ٶ�
const char* potatoMoneyImageList[8]
= { "Images/����/����ǥ0.png","Images/����/����ǥ1.png" ,"Images/����/����ǥ2.png" ,"Images/����/����ǥ3.png" ,
"Images/����/����ǥ4.png" ,"Images/����/����ǥ5.png" ,"Images/����/����ǥ6.png" ,"Images/����/����ǥ7.png" };

const char* bookImageList_no[8]
= { "Images/����/����ǥ0.png","Images/����/����ǥ1.png" ,"Images/����/����ǥ2.png" ,"Images/����/����ǥ3.png" ,
"Images/����/����ǥ4.png" ,"Images/����/����ǥ5.png" ,"Images/����/����ǥ6.png" ,"Images/����/����ǥ7.png" };

const char* bookImageList_yes[8]
= { "Images/����/����0.png", "Images/����/����1.png" ,"Images/����/����2.png" ,"Images/����/����3.png" ,
"Images/����/����4.png" ,"Images/����/����5.png" ,"Images/����/����6.png" ,"Images/����/����7.png" };

int nextDayPriceList[14]		//��¥ �߰� ���ؼ� �ʿ��� �� == ���Ѹ��� ��ȭ�� �ʿ��� ��
= { 300,800,2000,5000,20000,80000,200000,500000,1000000,5000000,10000000,50000000,100000000,1 };


ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size) {

	ObjectID object = createObject(name);
	locateObject(object, scene, x, y);
	scaleObject(object, size);

	if (shown == true)
		showObject(object);

	return object;
}

//�δ���(0)/1/2/3 ���
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

//moneyNum[9]�� ���� ���� �ڸ��� ������ ä����
void getMoneyNum(int mon) {
	//money���� ī�� -> money�� �Ȱǵ�� ���ؼ�
	moneyNum[0] = 0;
	moneyNum[1] = 0;		//0���� ��� ����ؼ� ù° �ڸ��� 0����  �ʱ�ȭ
	for (int i = 2; i < 9; i++)
		moneyNum[i] = -1;	//�ʱ�ȭ (-1�϶��� �ش� �ڸ��� ���ڰ� ���� ��)

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

	srand(time(NULL));	//������ �ʱ�ȭ

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
	bgm = createSound("Sounds/Ÿ��Ʋ.mp3");

	button = createSound("Sounds/��ưŬ��.mp3");
	success = createSound("Sounds/��ȭ����.mp3");
	potatoClick1 = createSound("Sounds/����Ŭ��1.mp3");
	potatoClick2 = createSound("Sounds/����Ŭ��2.mp3");
	potatoClick3 = createSound("Sounds/����Ŭ��3.mp3");
	moleClick1 = createSound("Sounds/�δ���1.mp3");
	moleClick2 = createSound("Sounds/�δ���2.mp3");
	moleClick3 = createSound("Sounds/�δ���3.mp3");
	water = createSound("Sounds/���ֱ�.mp3");

	startTimer(bgmTimer);

	startGame(title);
}