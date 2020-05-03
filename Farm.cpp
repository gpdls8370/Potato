//����
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
ObjectID waterButton, goStoreButton, goBookButtoon, nextDayButton, myWater;
ObjectID textDay, textLeftDay, textMoney;
ObjectID soil[4][4];
ObjectID potato[4][4];	//����3���� or �δ���

ObjectID dayCell[3], leftDayCell[3];

int soilState[4][4];			//���� �ش� �� ĭ�� ������ �������� ��ȣ (0,1,2,3,4) 0=�δ���,4=��ĭ
extern int nowPotato[4];
const char* potatoImage[4]		//���� 1��2��3�� ���� �̹���(0�� �׻� �δ��� �̹���)
= { "Images/�δ���.png" ,"Images/����/����Ѱ���.png" ,
"Images/����/����Ѱ���.png" ,"Images/����/����Ѱ���.png" };	//�ʱ⼳��
int potatoMoney[4]				//���� 1��2��3�� ���� ���� + �δ��� �� ����
= { -50,10,10,10 };//�ʱ⼳��
int cell_i, cell_j;

//���� ���Ѹ��� �ܰ�(1,2 -> ��������)
extern int waterLevel;		//���۷��� 0
int waterType = 2;		//������ Ÿ��2 + ���Ѹ��� �����ϸ� �� �ٲ�

extern int money;
extern int moneyNum[9];
extern const char* number[10];
extern int random(int type);
extern void setMoney();
extern void setDayPrice();
extern void setBook();
extern void getMoneyNum(int mon);
extern const char* potatoMoneyImageList[8];

int count = 0;

extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

//���Ѹ��� Ÿ��(1or2) �Է��ϸ� ���� ����123�޾Ƽ� ��ü �뿡 ����(or�δ���) ���� ����
void potatoSpawn(int waterType) {

	switch (waterType) {
	case 1:
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				soilState[i][j] = random(1);	//�ش� ĭ�� ������(123���� or �δ���) �����Ҵ�
				setObjectImage(potato[i][j], potatoImage[soilState[i][j]]);		//�̹��� ����
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

//������ ������ �´��� Ȯ�� 
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
		showMessage("�� ���õ� ���� ĺ��~!");
		playSound(water);
		setTimer(gameTimer, gameTime);		//Ÿ�̸� ����
		hideObject(waterButton);
		hideObject(textMoney);
		showObject(nextDayButton);
		showObject(goStoreButton);
		showObject(goBookButtoon);
		setBook();
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
			setObjectImage(nextWater, "Images/���Ѹ���/�δ������Ѹ���.png");
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

		//��¥ �� ������
		if (leftDay == 0) {
			hideObject(goFarmButton1);		//������ ���� �����θ� �ٲ���
			showObject(goBackButton);
			enterScene(end);
			showMessage("���� �뿩 ��¥�� �������ϴ�");
		}
		else
			showMessage("�Ϸ簡 �������ϴ�");
	}

	else if (isPotatoCell(object) == true && soilState[cell_i][cell_j] != 4) {	//��ĭ�� �ƴ� ��

		if (soilState[cell_i][cell_j] == 0) {	//�δ��� Ŭ����
			//�δ������ �Ҹ� �ִºκ�
			if (count % 3 == 0)
				playSound(moleClick1);
			else if (count % 3 == 1)
				playSound(moleClick2);
			else if (count % 3 == 2)
				playSound(moleClick3);
			count++;

			money += potatoMoney[soilState[cell_i][cell_j]];
			countMole++;
		}

		else {	//1,2,3Ŭ����

			//���� Ŭ���� ĭ�� ���ڰ� �߰����� �ʾҴ� ���̶�� (ó�� �߰��̶��) �߰��� �ɷ� �ٲ���
			if (findPotato[nowPotato[soilState[cell_i][cell_j]]] == false)
				findPotato[nowPotato[soilState[cell_i][cell_j]]] = true;

			money += potatoMoney[soilState[cell_i][cell_j]];

			//����ĳ�� �Ҹ� �ִºκ�
			if (count % 3 == 0)
				playSound(potatoClick1);
			else if (count % 3 == 1)
				playSound(potatoClick2);
			else if (count % 3 == 2)
				playSound(potatoClick3);
			count++;
		}
		soilState[cell_i][cell_j] = 4;		//����: ��ĭ����
		hideObject(potato[cell_i][cell_j]);

		//���� ���� �����
		setObjectImage(textMoney, potatoMoneyImageList[nowPotato[soilState[cell_i][cell_j]]]);

	}
}

void mainFarm() {

	farm = createScene("���� ����", "Images/farm.png");
	gameTimer = createTimer(gameTime);
	showTimer(gameTimer);
	waterButton = createObject("Images/���Ѹ���/���Ѹ���.png", farm, 970, 320, true, 0.33f);
	nextDayButton = createObject("Images/��ư/��������.png", farm, 1000, 380, false, 2.0f);
	goStoreButton = createObject("Images/��ư/��������.png", farm, 1000, 250, true, 2.0f);
	goBookButtoon = createObject("Images/��ư/��������.png", farm, 1000, 150, true, 2.0f);

	textLeftDay = createObject("Images/��ư/Day.png", farm, 10, 620, true, 0.7f);
	textDay = createObject("Images/��ư/�����뿩��¥.png", farm, 820, 635, true, 0.7f);
	textMoney = createObject("Images/��ư/Day.png", farm, 1000, 200, false, 0.7f);

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			potato[i][j] = createObject("Images/����/����Ѱ���.png", farm, 195 + 200 * j, 510 - 130 * i, false, 0.5f);
			soil[i][j] = createObject("Images/��.png", farm, 180 + 200 * j, 500 - 130 * i, true, 3.3f);
		}
	}

	for (int i = 0; i < 3; i++) {
		dayCell[i] = createObject("Images/����/����.png", farm, 150 + -30 * i, 620, true, 2.0f);
		leftDayCell[i] = createObject("Images/����/��.png", farm, 1120 + -30 * i, 640, true, 1.8f);
	}

	setDay();
	setLeftDay();
}