//농장
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

extern SceneID store, book1, end;
extern SoundID button, potatoClick1, potatoClick2, potatoClick3, water, moleClick1, moleClick2, moleClick3;
extern float gameTime;
extern int day, leftDay, countMole;
extern bool moleUnlocked;
extern bool findPotato[8];
extern ObjectID nextWater, goFarmButton1, goBackButton;

SceneID farm;
TimerID gameTimer;
ObjectID waterButton, goStoreButton, goBookButtoon, nextDayButton, goEndButton;
ObjectID textDay, textLeftDay, textMoney;
ObjectID soil[4][4];
ObjectID potato[4][4];	//감자3종류 or 두더지

ObjectID dayCell[3], leftDayCell[3];

int soilState[4][4];			//현재 해당 흙 칸에 스폰된 아이템의 번호 (0,1,2,3,4) 0=두더지,4=빈칸
extern int nowPotato[4];
const char* potatoImage[4]		//현재 1번2번3번 감자 이미지(0은 항상 두더지 이미지)
= { "Images/두더지.png" ,"Images/감자/평범한감자.png" ,
"Images/감자/평범한감자.png" ,"Images/감자/평범한감자.png" };	//초기설정
int potatoMoney[4]				//현재 1번2번3번 감자 가격 + 두더지 돈 감소
= { -50,10,10,10 };//초기설정
int cell_i, cell_j;

//현재 물뿌리개 단계(1,2 -> 다음종류)
extern int waterLevel;		//시작레벨 0
int waterType = 2;		//시작은 타입2 + 물뿌리개 업글하면 값 바꿈

extern int money;
extern int moneyNum[9];
extern int moleMoneyList[8];
extern const char* number[10];
extern int random(int type);
extern void setMoney();
extern void setDayPrice();
extern void setBook();
extern void getMoneyNum(int mon);
extern const char* potatoMoneyImageList[8];
extern const char* moleMoneyImageList[8];

int count = 0;

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

//물뿌리개 타입(1or2) 입력하면 현재 감자123받아서 전체 흙에 감자(or두더지) 랜덤 스폰
void potatoSpawn(int waterType) {

	switch (waterType) {
	case 1:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				soilState[i][j] = random(1);	//해당 칸에 아이템(123감자 or 두더지) 랜덤할당
				setObjectImage(potato[i][j], potatoImage[soilState[i][j]]);		//이미지 변경
				showObject(potato[i][j]);
			}
		}
		break;

	case 2:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				soilState[i][j] = random(2);
				setObjectImage(potato[i][j], potatoImage[soilState[i][j]]);
				showObject(potato[i][j]);
			}
		}
		break;
	}

}

//아이템 누른거 맞는지 확인 
bool isPotatoCell(ObjectID object) {

	bool result = false;

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (object == potato[i][j] || object == soil[i][j]) {
				result = true;
				cell_i = i;
				cell_j = j;
				break;
			}
		}
	}
	return result;
}

void setDay() {

	getMoneyNum(day);

	for (int i = 1; i < 3; i++) {

		if (moneyNum[i] != -1) {
			setObjectImage(dayCell[i], number[moneyNum[i]]);
			showObject(dayCell[i]);
		}
		else
			hideObject(dayCell[i]);
	}
}

void setLeftDay() {

	getMoneyNum(leftDay);

	for (int i = 1; i < 3; i++) {

		if (moneyNum[i] != -1) {
			setObjectImage(leftDayCell[i], number[moneyNum[i]]);
			showObject(leftDayCell[i]);
		}
		else
			hideObject(leftDayCell[i]);
	}
}

void timerCallbackFarm(TimerID timer) {

	if (timer == gameTimer) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++)
				hideObject(potato[i][j]);
		}
		playSound(water);
		showMessage(" ");
		hideObject(waterButton);
		setObjectImage(textMoney, "Images/숫자/없음.png");
		hideObject(textMoney);
		showObject(nextDayButton);
		showObject(goStoreButton);
		showObject(goBookButtoon);
		setBook();
		setTimer(gameTimer, gameTime);		//타이머 리셋
	}
}

void mouseCallbackFarm(ObjectID object, int x, int y, MouseAction action) {

	if (object == waterButton) {
		playSound(water);
		count = 0;
		potatoSpawn(waterType);
		hideObject(goStoreButton);
		hideObject(goBookButtoon);
		showObject(textMoney);
		startTimer(gameTimer);
	}

	else if (object == goStoreButton) {
		playSound(button);
		setMoney();
		setDayPrice();

		if (moleUnlocked == false && countMole >= 100) {
			moleUnlocked = true;
			setObjectImage(nextWater, "Images/상점/두더지.png");
		}

		enterScene(store);
	}

	else if (object == goBookButtoon) {
		playSound(button);
		enterScene(book1);
	}

	else if (object == nextDayButton) {
		playSound(button);
		hideObject(nextDayButton);
		showObject(waterButton);
		day++;
		leftDay--;
		setDay();
		setLeftDay();

		//날짜 다 끝나면
		if (leftDay == 0) {
			hideObject(goFarmButton1);		//도감을 보는 용으로만 바꿔줌
			showObject(goBackButton);
			enterScene(end);
			showMessage("농장 대여 날짜가 끝났습니다");
		}
		else if (leftDay != 0)
			showMessage("하루가 지났습니다");
	}

	else if (object == goEndButton) {
		hideObject(goFarmButton1);	
		showObject(goBackButton);
		enterScene(end);
		showMessage("감자 농사를 성공적으로 끝냈습니다!");
	}

	else if (isPotatoCell(object) == true && soilState[cell_i][cell_j] != 4) {	//빈칸이 아닐 때

		if (soilState[cell_i][cell_j] == 0) {	//두더지 클릭시
			//두더지잡는 소리 넣는부분
			if (count % 3 == 0)
				playSound(moleClick1);
			else if (count % 3 == 1)
				playSound(moleClick2);
			else if (count % 3 == 2)
				playSound(moleClick3);
			count++;

			money += moleMoneyList[nowPotato[3]];
			if (money < 0)
				money = 0;		//두더지 잡았는데 돈이 - 돼버리면 그냥 0원으로 해주기
			
			countMole++;

			//옆에 가격 띄워줌
			setObjectImage(textMoney, moleMoneyImageList[nowPotato[3]]);
		}

		else {	//1,2,3클릭시

			//현재 클릭한 칸의 감자가 발견하지 않았던 것이라면 (처음 발견이라면) 발견한 걸로 바꿔줌
			if (findPotato[nowPotato[soilState[cell_i][cell_j]]] == false)
				findPotato[nowPotato[soilState[cell_i][cell_j]]] = true;

			money += potatoMoney[soilState[cell_i][cell_j]];

			//감자캐는 소리 넣는부분
			if (count % 3 == 0)
				playSound(potatoClick1);
			else if (count % 3 == 1)
				playSound(potatoClick2);
			else if (count % 3 == 2)
				playSound(potatoClick3);
			count++;

			//옆에 가격 띄워줌
			setObjectImage(textMoney, potatoMoneyImageList[nowPotato[soilState[cell_i][cell_j]]]);
		}
		soilState[cell_i][cell_j] = 4;		//상태: 빈칸으로
		hideObject(potato[cell_i][cell_j]);

	}
}

void mainFarm() {

	farm = createScene("감자 농장", "Images/farm.png");
	gameTimer = createTimer(gameTime);
	showTimer(gameTimer);
	waterButton = createObject("Images/물뿌리개/물뿌리개.png", farm, 970, 320, true, 0.33f);
	nextDayButton = createObject("Images/버튼/다음날로.png", farm, 1000, 380, false, 2.0f);
	goStoreButton = createObject("Images/버튼/상점으로.png", farm, 1000, 250, true, 2.0f);
	goBookButtoon = createObject("Images/버튼/도감보기.png", farm, 1000, 150, true, 2.0f);
	goEndButton = createObject("Images/버튼/끝내기.png", farm, 20, 20, false, 1.5f);

	textLeftDay = createObject("Images/버튼/Day.png", farm, 10, 620, true, 0.7f);
	textDay = createObject("Images/버튼/남은대여날짜.png", farm, 820, 635, true, 0.7f);
	textMoney = createObject("Images/숫자/없음.png", farm, 950, 180, false, 1.2f);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			potato[i][j] = createObject("Images/감자/평범한감자.png", farm, 195 + 200 * j, 510 - 130 * i, false, 0.5f);
			soil[i][j] = createObject("Images/흙.png", farm, 180 + 200 * j, 500 - 130 * i, true, 3.3f);
		}
	}

	for (int i = 0; i < 3; i++) {
		dayCell[i] = createObject("Images/숫자/없음.png", farm, 150 + -30 * i, 620, true, 2.0f);
		leftDayCell[i] = createObject("Images/숫자/일.png", farm, 1120 + -30 * i, 640, true, 1.8f);
	}

	setDay();
	setLeftDay();
}