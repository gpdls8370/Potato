//업그레이드 상점
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

ObjectID moneyCell[9];	//1~8 8칸
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
= { "Images/숫자/0.png","Images/숫자/1.png", "Images/숫자/2.png", "Images/숫자/3.png", "Images/숫자/4.png",
"Images/숫자/5.png", "Images/숫자/6.png", "Images/숫자/7.png", "Images/숫자/8.png", "Images/숫자/9.png" };


extern int waterLevel;		//현재 물뿌리개 레벨 (시작은 0)
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

	getMoneyNum(money);	//배열에 자릿수 나눠서 넣기

	for (int i = 1; i < 9; i++) {		//0번은 항상 '원' + 항상 보임

		if (moneyNum[i] != -1) {		//빈칸이 아니면
			setObjectImage(moneyCell[i], number[moneyNum[i]]);
			showObject(moneyCell[i]);
		}
		else
			hideObject(moneyCell[i]);	//숫자 없으면 값 안보이게하기	
	}
}

void setDayPrice() {

	getMoneyNum(upgradeMoney[waterLevel] / 2);	//배열에 자릿수 나눠서 넣기

	for (int i = 1; i < 9; i++) {		//0번은 항상 '원' + 항상 보임

		if (moneyNum[i] != -1) {		//빈칸이 아니면
			setObjectImage(dayPriceCell[i], number[moneyNum[i]]);
			showObject(dayPriceCell[i]);
		}
		else
			hideObject(dayPriceCell[i]);	//숫자 없으면 값 안보이게하기	
	}
}


void setBook() {

	for (int i = 0; i < 8; i++) {

		if (openBook[i] == false) {		//도감이 안열려있고
			if (findPotato[i] == true) {	//감자는 찾았으면
				if (i < 3) 	//첫번째 페이지(0,1,2)
					setObjectImage(bookCell1[i], bookImageList_yes[i]);		//도감 열린 이미지로 바꿔줌
				else if (i < 6)	//두번째 페이지(3,4,5)
					setObjectImage(bookCell2[i - 3], bookImageList_yes[i]);
				else if (i < 8)	//세번째 페이지(6,7)
					setObjectImage(bookCell3[i - 6], bookImageList_yes[i]);

				openBook[i] = true;		//도감 연걸로 바꿔줌
				showMessage("도감에 새로운 감자가 추가되었습니다!");
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

			//현재 돈이 업그레이드에 필요한 돈보다 많거나 적으면 -> 업글 가능
			if (money >= upgradeMoney[waterLevel]) {		//12레벨일때는 두더지 물뿌리개 해감 조건 필요함
				money -= upgradeMoney[waterLevel];
				setMoney();							//돈 업로드
				waterLevel++;						//물뿌리개 한단계 업글
				waterType = (waterLevel + 1) % 2 + 1;	//타입도 바꿔줌
				if (waterType == 1) {				//바뀐 타입이 1이라면 -> 종류 업글을 한거라면
					nowPotato[1] = nowPotato[2];	//2->1 , 3->2
					nowPotato[2] = nowPotato[3];
					nowPotato[3]++;				//3번 감자 번호를 새롭게 뒤에꺼로 바꿔줌
					//1,2,3
					for (int i = 1; i < 4; i++) {
						potatoImage[i] = potatoImageList[nowPotato[i]];
						potatoMoney[i] = potatoMoneyList[nowPotato[i]];
					}
				}
				setObjectImage(nowWater, waterStoreImageList[waterLevel]);
				setObjectImage(nextWater, waterStoreImageList[waterLevel + 1]);
				setObjectImage(waterButton, waterImageList[waterLevel]);
				showMessage("강화에 성공했습니다!");
				playSound(success);
				setDayPrice();
			}

			else if (money < upgradeMoney[waterLevel]) {
				showMessage("강화에 필요한 돈이 부족합니다");
				playSound(button);
			}
		}

		else if (waterLevel == 12) {	//최종 강화 된 상태

			if (moleUnlocked == true) {			//두더지 물뿌리개로 강화할 경우
				for (int i = 1; i < 4; i++) {
					nowPotato[i] = 7;		//현재 1,2,3 감자 전부 두더지 감자로 바꾸기
					potatoImage[i] = potatoImageList[nowPotato[i]];
					potatoMoney[i] = potatoMoneyList[nowPotato[i]];
				}
				waterLevel++;
				setObjectImage(nowWater, "Images/상점/두더지.png");
				setObjectImage(nextWater, "Images/버튼/더이상.png");
				setObjectImage(waterButton, "Images/물뿌리개/두더지물뿌리개.png");
				showMessage("두더지 물뿌리개로 강화했습니다!");
				setDayPrice();
				showObject(goEndButton);
			}
			else {
				playSound(button);
				showMessage("더 이상 강화를 할 수 없습니다");
			}
		}

		else {
			playSound(button);
			showMessage("더 이상 강화를 할 수 없습니다");
		}
	}

	else if (object == plusDayButton) {

		//날짜 추가 돈이 충분하면
		if (money >= upgradeMoney[waterLevel] / 2) {	//날짜 추가 가격 == upgradeMoney[waterLevel] / 2
			playSound(success);
			money -= upgradeMoney[waterLevel] / 2;
			leftDay += 5;	//5일 추가
			setMoney();
			setLeftDay();	//farm씬의 남은 날짜 표기 다시 세팅
			showMessage("농장 대여를 5일 더 할 수 있게 되었습니다!");
		}

		//돈이 부족하면
		else {
			playSound(button);
			showMessage("날짜 추가에 필요한 돈이 부족합니다");
		}
	}
}

void mainStore() {

	store = createScene("상점", "Images/store.png");

	text1 = createObject("Images/버튼/강화전.png", store, 250, 640, true, 0.4f);
	text2 = createObject("Images/버튼/강화후.png", store, 850, 550, false, 1.5f);
	plusDayText = createObject("Images/버튼/날짜추가가격.png", store, 900, 65, true, 0.6f);
	next = createObject("Images/도감/화살표_오.png", store, 590, 320, true, 1.0f);

	goFarmButton = createObject("Images/버튼/농장으로.png", store, 30, 40, true, 1.8f);
	upgradeButton = createObject("Images/버튼/강화하기.png", store, 400, 40, true, 2.2f);
	plusDayButton = createObject("Images/버튼/날짜추가.png", store, 700, 40, true, 2.0f);
	nowWater = createObject("Images/상점/플라스틱.png", store, 150, 150, true, 0.57f);
	nextWater = createObject("Images/상점/철.png", store, 780, 150, true, 0.57f);

	for (int i = 0; i < 9; i++) {
		moneyCell[i] = createObject("Images/숫자/원.png", store, 1100 + -42 * i, 635, true, 2.2f);
		dayPriceCell[i] = createObject("Images/숫자/원.png", store, 1110 + -25 * i, 40, true, 1.5f);
	}

}