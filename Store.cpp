//���׷��̵� ����
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <bangtal.h>

SceneID store;
extern SoundID button, success;
extern SceneID farm;
extern ObjectID bookCell1[3], bookCell2[3], bookCell3[2], waterButton, goEndButton;
ObjectID goFarmButton, upgradeButton, plusDayButton;
ObjectID text1, text2, next, plusDayText;
ObjectID nowWater, nextWater;

ObjectID moneyCell[9];	//1~8 8ĭ
ObjectID dayPriceCell[9];
extern void setLeftDay();
extern int leftDay;

extern bool moleUnlocked;
extern bool findPotato[8];
extern bool openBook[8];
extern const char* bookImageList_yes[8];

extern int moneyNum[9];
extern int money;
extern void getMoneyNum(int mon);
const char* number[10]
= { "Images/����/0.png","Images/����/1.png", "Images/����/2.png", "Images/����/3.png", "Images/����/4.png",
"Images/����/5.png", "Images/����/6.png", "Images/����/7.png", "Images/����/8.png", "Images/����/9.png" };


extern int waterLevel;		//���� ���Ѹ��� ���� (������ 0)
extern int waterType;
extern int upgradeMoney[12];
extern const char* waterImageList[14];
extern const char* waterStoreImageList[14];

extern int nowPotato[4];
extern const char* potatoImageList[8];
extern int potatoMoneyList[8];

extern const char* potatoImage[4];
extern int potatoMoney[4];


extern ObjectID createObject(const char* name, SceneID scene, int x, int y, bool shown, float size);

void setMoney() {

	getMoneyNum(money);	//�迭�� �ڸ��� ������ �ֱ�

	for (int i = 1; i < 9; i++) {		//0���� �׻� '��' + �׻� ����

		if (moneyNum[i] != -1) {		//��ĭ�� �ƴϸ�
			setObjectImage(moneyCell[i], number[moneyNum[i]]);
			showObject(moneyCell[i]);
		}
		else
			hideObject(moneyCell[i]);	//���� ������ �� �Ⱥ��̰��ϱ�	
	}
}

void setDayPrice() {

	getMoneyNum(upgradeMoney[waterLevel] / 2);	//�迭�� �ڸ��� ������ �ֱ�

	for (int i = 1; i < 9; i++) {		//0���� �׻� '��' + �׻� ����

		if (moneyNum[i] != -1) {		//��ĭ�� �ƴϸ�
			setObjectImage(dayPriceCell[i], number[moneyNum[i]]);
			showObject(dayPriceCell[i]);
		}
		else
			hideObject(dayPriceCell[i]);	//���� ������ �� �Ⱥ��̰��ϱ�	
	}
}


void setBook() {

	for (int i = 0; i < 8; i++) {

		if (openBook[i] == false) {		//������ �ȿ����ְ�
			if (findPotato[i] == true) {	//���ڴ� ã������
				if (i < 3) 	//ù��° ������(0,1,2)
					setObjectImage(bookCell1[i], bookImageList_yes[i]);		//���� ���� �̹����� �ٲ���
				else if (i < 6)	//�ι�° ������(3,4,5)
					setObjectImage(bookCell2[i - 3], bookImageList_yes[i]);
				else if (i < 8)	//����° ������(6,7)
					setObjectImage(bookCell3[i - 6], bookImageList_yes[i]);

				openBook[i] = true;		//���� ���ɷ� �ٲ���
				showMessage("������ ���ο� ���ڰ� �߰��Ǿ����ϴ�!");
			}
		}
	}
}

void mouseCallbackStore(ObjectID object, int x, int y, MouseAction action) {

	if (object == goFarmButton) {
		playSound(button);
		enterScene(farm);
	}

	else if (object == upgradeButton) {

		if (waterLevel < 12) {

			//���� ���� ���׷��̵忡 �ʿ��� ������ ���ų� ������ -> ���� ����
			if (money >= upgradeMoney[waterLevel]) {		//12�����϶��� �δ��� ���Ѹ��� �ذ� ���� �ʿ���
				money -= upgradeMoney[waterLevel];
				setMoney();							//�� ���ε�
				waterLevel++;						//���Ѹ��� �Ѵܰ� ����
				waterType = (waterLevel + 1) % 2 + 1;	//Ÿ�Ե� �ٲ���
				if (waterType == 1) {				//�ٲ� Ÿ���� 1�̶�� -> ���� ������ �ѰŶ��
					nowPotato[1] = nowPotato[2];	//2->1 , 3->2
					nowPotato[2] = nowPotato[3];
					nowPotato[3]++;				//3�� ���� ��ȣ�� ���Ӱ� �ڿ����� �ٲ���
					//1,2,3
					for (int i = 1; i < 4; i++) {
						potatoImage[i] = potatoImageList[nowPotato[i]];
						potatoMoney[i] = potatoMoneyList[nowPotato[i]];
					}
				}
				setObjectImage(nowWater, waterStoreImageList[waterLevel]);
				setObjectImage(nextWater, waterStoreImageList[waterLevel + 1]);
				setObjectImage(waterButton, waterImageList[waterLevel]);
				showMessage("��ȭ�� �����߽��ϴ�!");
				playSound(success);
				setDayPrice();
			}

			else if (money < upgradeMoney[waterLevel]) {
				showMessage("��ȭ�� �ʿ��� ���� �����մϴ�");
				playSound(button);
			}
		}

		else if (waterLevel == 12) {	//���� ��ȭ �� ����

			if (moleUnlocked == true) {			//�δ��� ���Ѹ����� ��ȭ�� ���
				for (int i = 1; i < 4; i++) {
					nowPotato[i] = 7;		//���� 1,2,3 ���� ���� �δ��� ���ڷ� �ٲٱ�
					potatoImage[i] = potatoImageList[nowPotato[i]];
					potatoMoney[i] = potatoMoneyList[nowPotato[i]];
				}
				waterLevel++;
				setObjectImage(nowWater, "Images/����/�δ���.png");
				setObjectImage(nextWater, "Images/��ư/���̻�.png");
				setObjectImage(waterButton, "Images/���Ѹ���/�δ������Ѹ���.png");
				showMessage("�δ��� ���Ѹ����� ��ȭ�߽��ϴ�!");
				setDayPrice();
				showObject(goEndButton);
			}
			else {
				playSound(button);
				showMessage("�� �̻� ��ȭ�� �� �� �����ϴ�");
			}
		}

		else {
			playSound(button);
			showMessage("�� �̻� ��ȭ�� �� �� �����ϴ�");
		}
	}

	else if (object == plusDayButton) {

		//��¥ �߰� ���� ����ϸ�
		if (money >= upgradeMoney[waterLevel] / 2) {	//��¥ �߰� ���� == upgradeMoney[waterLevel] / 2
			playSound(success);
			money -= upgradeMoney[waterLevel] / 2;
			leftDay += 5;	//5�� �߰�
			setMoney();
			setLeftDay();	//farm���� ���� ��¥ ǥ�� �ٽ� ����
			showMessage("���� �뿩�� 5�� �� �� �� �ְ� �Ǿ����ϴ�!");
		}

		//���� �����ϸ�
		else {
			playSound(button);
			showMessage("��¥ �߰��� �ʿ��� ���� �����մϴ�");
		}
	}
}

void mainStore() {

	store = createScene("����", "Images/store.png");

	text1 = createObject("Images/��ư/��ȭ��.png", store, 250, 640, true, 0.4f);
	text2 = createObject("Images/��ư/��ȭ��.png", store, 850, 550, false, 1.5f);
	plusDayText = createObject("Images/��ư/��¥�߰�����.png", store, 900, 65, true, 0.6f);
	next = createObject("Images/����/ȭ��ǥ_��.png", store, 590, 320, true, 1.0f);

	goFarmButton = createObject("Images/��ư/��������.png", store, 30, 40, true, 1.8f);
	upgradeButton = createObject("Images/��ư/��ȭ�ϱ�.png", store, 400, 40, true, 2.2f);
	plusDayButton = createObject("Images/��ư/��¥�߰�.png", store, 700, 40, true, 2.0f);
	nowWater = createObject("Images/����/�ö�ƽ.png", store, 150, 150, true, 0.57f);
	nextWater = createObject("Images/����/ö.png", store, 780, 150, true, 0.57f);

	for (int i = 0; i < 9; i++) {
		moneyCell[i] = createObject("Images/����/��.png", store, 1100 + -42 * i, 635, true, 2.2f);
		dayPriceCell[i] = createObject("Images/����/��.png", store, 1110 + -25 * i, 40, true, 1.5f);
	}

}