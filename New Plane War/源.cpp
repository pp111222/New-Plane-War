#include<graphics.h>
#include<iostream>
#include<time.h>
#include<stdio.h>
#include<Windows.h>
#include<math.h>
using namespace std;
#define WIDTH 591
#define HEIGHT 864
#define PLAYERW 102
#define PLAYERH 126
#define ENEMYSMALLW 57
#define ENEMYSMALLH 43
#define BIGBULLETW 14//19
#define BIGBULLETH 14//24
#define SMALLBULLETW 5
#define SMALLBULLETH 11
#define SMALLBOSSW 69
#define SMALLBOSSH 99
#define BOSSW 300
#define BOSSH 450
#define PI 3.1415926
#define BAIYUNW 240
#define BAIYUNH 267
#define BAIYUNBULLETW 90
#define BAIYUNBULLETH 103
IMAGE bk;
IMAGE NormalPlayerimg[2];
IMAGE FastPlayerimg[2];
IMAGE EnemyAimg[2];
IMAGE EnemyBimg[2];
IMAGE EnemyCimg[2];
IMAGE EnemyDimg[2];
IMAGE EnemyEimg[2];
IMAGE EnemyFimg[2];
IMAGE BigBullet[2];
IMAGE SmallBullet[2];
IMAGE EnemySmallExploreF[2];
IMAGE EnemySmallExploreS[2];
IMAGE EnemySmallExplore[2];
IMAGE PlayerStatusF[2];
IMAGE PlayerStatusS[2];
IMAGE PlayerStatusT[2];
IMAGE PlayerExplore[2];
IMAGE SmallBoss[2];
IMAGE SmallBossStatusF[2];
IMAGE SmallBossStatusS[2];
IMAGE SmallBossStatusT[2];
IMAGE BossImg[2];
IMAGE YellowBullet[2];
IMAGE RedBullet[2];
IMAGE BaiYun[2];
IMAGE BaiYunBullet[2];
IMAGE BaiYunHurt[2];
int Playerstatus = 0;
bool FastFlag = false;
int KilledEnemySmallNum;
double GameStatus = 0;
int cnt = 0;
struct NormalPlane
{
	double px;
	double py;
	double vx;
	double vy;
	int life;
	int status;
}EnemyA, EnemyB, EnemyC, EnemyD, EnemyE, EnemyF;
struct Plane
{
	double px;
	double py;
	double vx;
	double vy;
	int life;
	int status;
	bool flag;
	bool relifeflag;
	int BoomNum;
}player, smallbossA, smallbossB, smallbossC, BossBY;

typedef struct DuBullet
{
	double px;
	double py;
	double vx;
	double vy;
	bool life;
	int damage;
	bool flag;
	struct DuBullet* prior;
	struct DuBullet* next;
}Bulletnode, * Bulletlist;

Bulletlist PlayerBullet = {};
Bulletlist EnemyAbullet = {};
Bulletlist EnemyBbullet = {};
Bulletlist EnemyCbullet = {};
Bulletlist EnemyDbullet = {};
Bulletlist EnemyEbullet = {};
Bulletlist EnemyFbullet = {};
Bulletlist SmallBossAbullet = {};
Bulletlist SmallBossBbullet = {};
Bulletlist SmallBossCbullet = {};
Bulletlist BYbullet = {};

void InitBullet(Bulletlist& list)
{
	list = new Bulletnode;
	list->prior = list->next = NULL;
}

void Speed()
{
	if (FastFlag)
	{
		player.vx = 0.4;
		player.vy = 0.4;
	}

	else
	{
		player.vx = 0.2;
		player.vy = 0.2;
	}
}

void EnemySmallMove()
{
	double speed = 0.1;
	if (GameStatus <= 1)
	{
		EnemyA.vy = speed;
		EnemyB.vy = speed;
		EnemyC.vy = speed;
		EnemyD.vy = speed;
		EnemyE.vy = speed;
		EnemyF.vy = speed;

		EnemyA.py += EnemyA.vy;
		EnemyB.py += EnemyB.vy;
		EnemyC.py += EnemyC.vy;
		EnemyD.py += EnemyD.vy;
		EnemyE.py += EnemyE.vy;
		EnemyF.py += EnemyF.vy;
	}

	speed = 0.05;

	if (GameStatus == 1.5)
	{
		EnemyA.life = false;
		EnemyB.life = false;
		EnemyC.life = false;
		EnemyD.life = false;
		EnemyE.life = false;
		EnemyF.life = false;

		EnemyA.vx = -speed;
		EnemyB.vx = -speed;
		EnemyC.vx = -speed;
		EnemyD.vx = speed;
		EnemyE.vx = speed;
		EnemyF.vx = speed;

		EnemyA.px += EnemyA.vx;
		EnemyB.px += EnemyB.vx;
		EnemyC.px += EnemyC.vx;
		EnemyD.px += EnemyD.vx;
		EnemyE.px += EnemyE.vx;
		EnemyF.px += EnemyF.vx;

	}


	if (EnemyA.py > HEIGHT && EnemyA.life)
	{
		EnemyA.px = 10;
		EnemyA.py = -30;
	}

	if (EnemyB.py > HEIGHT && EnemyB.life)
	{
		EnemyB.px = ENEMYSMALLW + 45 + EnemyA.px;
		EnemyB.py = -30;
	}

	if (EnemyC.py > HEIGHT && EnemyC.life)
	{
		EnemyC.px = ENEMYSMALLW + 45 + EnemyB.px;
		EnemyC.py = -30;
	}

	if (EnemyD.py > HEIGHT && EnemyD.life)
	{
		EnemyD.px = ENEMYSMALLW + 45 + EnemyC.px;
		EnemyD.py = -30;
	}

	if (EnemyE.py > HEIGHT && EnemyE.life)
	{
		EnemyE.px = ENEMYSMALLW + 45 + EnemyD.px;
		EnemyE.py = -30;
	}

	if (EnemyF.py > HEIGHT && EnemyF.life)
	{
		EnemyF.px = ENEMYSMALLW + 45 + EnemyE.px;
		EnemyF.py = -30;
	}
}

void SmallBossMove()
{
	double speed = 0.125;

	if (GameStatus == 1.5)
	{
		if (smallbossA.life)
			smallbossA.py += speed;
		if (smallbossB.life)
			smallbossB.py += speed;
		if (smallbossC.life)
			smallbossC.py += speed;
	}

	else if (GameStatus == 2)
	{
		if (!smallbossA.flag)
		{
			if (smallbossA.life)
				smallbossA.px -= speed;
		}

		else if (smallbossA.flag)
		{
			if (smallbossA.life)
				smallbossA.px += speed;
		}

		if (!smallbossB.flag)
		{
			if (smallbossB.life)
				smallbossB.px -= speed;
		}

		else if (smallbossB.flag)
		{
			if (smallbossB.life)
				smallbossB.px += speed;
		}

		if (!smallbossC.flag)
		{
			if (smallbossC.life)
				smallbossC.px -= speed;
		}

		else if (smallbossC.flag)
		{
			if (smallbossC.life)
				smallbossC.px += speed;
		}

		if (smallbossA.px <= 10)
		{
			smallbossA.flag = true;
			smallbossB.flag = true;
			smallbossC.flag = true;
		}

		if (smallbossC.px >= WIDTH - SMALLBOSSW)
		{
			smallbossA.flag = false;
			smallbossB.flag = false;
			smallbossC.flag = false;
		}
	}
}

void BaiYunMove()
{
	double speed = 0.3;
	if (BossBY.status == 0 && GameStatus == 2)
	{
		BossBY.py += speed;
		if (BossBY.py >= 10)
			BossBY.status = 1;
	}






















}

void CollapseBetweenPlane(Plane* player, NormalPlane* Enemy)
{
	if (player->px + PLAYERW > Enemy->px
		&& player->px<Enemy->px + ENEMYSMALLW
		&& player->py + PLAYERH>Enemy->py
		&& player->py < Enemy->py + ENEMYSMALLH)
	{
		KilledEnemySmallNum++;
		Enemy->py = -300;
		Enemy->life = 30;
		Enemy->status = 0;
		player->life -= 10;
		if (player->life <= 80)
		{
			Playerstatus = 1;
			if (player->life <= 50)
			{
				Playerstatus = 2;
				if (player->life<=20)
					Playerstatus = 3;
			}
		}

		if (player->life == 0)
		{
			putimage(player->px, player->px, &PlayerExplore[0], NOTSRCERASE);
			putimage(player->px, player->px, &PlayerExplore[1], SRCINVERT);
			player->px = WIDTH / 2;
			player->py = HEIGHT - PLAYERH;
			player->life = 100;
			Playerstatus = 0;
		}
	}
}


void CollapseBetweenPANDB(Plane* player, Plane* Enemy)
{
	if (player->px + PLAYERW > Enemy->px
		&& player->px<Enemy->px + SMALLBOSSW
		&& player->py + PLAYERH>Enemy->py
		&& player->py < Enemy->py + SMALLBOSSH)
	{
		Enemy->py = -200;
		Enemy->life = 0;
		Sleep(20);
		KilledEnemySmallNum++;
		player->life = 0;
		if (player->life == 0)
		{
			player->px = WIDTH / 2;
			player->py = HEIGHT - PLAYERH;
			player->life = 100;
			Playerstatus = 0;
		}
	}
}

void CollapseBetweenPANDBY(Plane* player, Plane* Enemy)
{
	if (player->px + PLAYERW > Enemy->px
		&& player->px<Enemy->px + BAIYUNW
		&& player->py + PLAYERH>Enemy->py
		&& player->py < Enemy->py + BAIYUNH)
	{
		player->life = 0;
		if (player->life == 0)
		{
			player->px = WIDTH / 2;
			player->py = HEIGHT - PLAYERH;
			player->life = 100;
			Playerstatus = 0;
		}
	}
}

void CollapseThatPTOE(Bulletlist& list,NormalPlane*Enemy)
{
	Bulletlist t;
	for (t = list; t != NULL; t = t->next)
	{
		if ((t->px >Enemy->px) && (t->px < Enemy->px + ENEMYSMALLW))
		{
			if ((t->py > Enemy->py) && (t->py < Enemy->py + ENEMYSMALLH))
			{
				t->life = false;
				Enemy->life -= t->damage;
				if (Enemy->life == 20)
					Enemy->status = 1;
				else if (Enemy->life == 10)
					Enemy->status = 2;
				else if (Enemy->life == 0)
				{
					putimage(Enemy->px, Enemy->px, &EnemySmallExplore[0], NOTSRCERASE);
					putimage(Enemy->px, Enemy->px, &EnemySmallExplore[1], SRCINVERT);
					Enemy->py = -300;
					Enemy->life = 30;
					Enemy->status = 0;
					KilledEnemySmallNum++;
				}
			}
		}
	}
}

void CollapseThatETOP(Bulletlist& list, Plane* player)
{
	Bulletlist t;
	for (t = list; t != NULL; t = t->next)
	{
		if ((t->px > player->px) && (t->px < player->px + ENEMYSMALLW))
		{
			if ((t->py > player->py) && (t->py < player->py + ENEMYSMALLH))
			{
				t->life = false;
				player->life -= t->damage;
				if (player->life <= 80)
				{
					Playerstatus = 1;
					if (player->life <= 50)
					{
						Playerstatus = 2;
						if (player->life <= 20)
							Playerstatus = 3;
					}
				}

				if (player->life == 0)
				{
					player->px = WIDTH / 2;
					player->py = HEIGHT - PLAYERH;
					player->life = 100;
					Playerstatus = 0;
				}
			}
		}
	}
}


void CollapseThatBTOP(Bulletlist& list, Plane* player)
{
	Bulletlist t;
	for (t = list; t != NULL; t = t->next)
	{
		if ((t->px > player->px) && (t->px < player->px + SMALLBOSSW))
		{
			if ((t->py > player->py) && (t->py < player->py + SMALLBOSSH))
			{
				t->life = false;
				player->life -= t->damage;
				if (player->life <= 80)
				{
					Playerstatus = 1;
					if (player->life <= 50)
					{
						Playerstatus = 2;
						if (player->life <= 20)
							Playerstatus = 3;
					}
				}

				if (player->life == 0)
				{
					player->px = WIDTH / 2;
					player->py = HEIGHT - PLAYERH;
					player->life = 100;
					Playerstatus = 0;
				}
			}
		}
	}
}

void CollapseThatBYTOP(Bulletlist& list, Plane* player)
{
	Bulletlist t;
	int time = 600;
	static int protecttime = 0;
	int temp = clock();
	for (t = list; t != NULL; t = t->next)
	{
		if ((t->px > player->px) && (t->px < player->px + BAIYUNBULLETW))
		{
			if ((t->py > player->py) && (t->py < player->py + BAIYUNBULLETH))
			{
				t->life = false;
				if (!player->relifeflag)
				{
					player->life -= t->damage;
				}

				if (player->life <= 75)
				{
					Playerstatus = 1;
					if (player->life <= 50)
					{
						Playerstatus = 2;
					}

					if (player->life <= 25)
					{
						Playerstatus == 3;
					}

					if (player->life <= 0)
					{
						player->px = WIDTH / 2;
						player->py = HEIGHT - PLAYERH;
						player->life = 100;
						Playerstatus = 0;
						player->relifeflag = true;
					}

					if (player->flag)
					{
						if (temp - protecttime >= time)
							player->relifeflag = false;
					}

				}
			}
		}
	}
}

void CollapseThatPTOB(Bulletlist& list, Plane* Enemy)
{
	Bulletlist t;
	for (t = list; t != NULL; t = t->next)
	{
		if ((t->px > Enemy->px) && (t->px < Enemy->px + SMALLBOSSW))
		{
			if ((t->py > Enemy->py) && (t->py < Enemy->py + SMALLBOSSH))
			{
				t->life = false;
				Enemy->life -= t->damage;
				if (Enemy->life == 150)
					Enemy->status = 1;
				else if (Enemy->life == 100)
					Enemy->status = 2;
				else if (Enemy->life == 60)
					Enemy->status = 3;
				else if (Enemy->life <= 0)
				{
					Enemy->py = 1400;
					Enemy->life = 0;
					KilledEnemySmallNum++;
				}
			}
		}
	}
}

void CollapseThatPTOBY(Bulletlist& list, Plane* Enemy)
{
	Bulletlist t;
	static int showtime = 0;
	int time = 2000;
	int temp = clock();
	for (t = list; t != NULL; t = t->next)
	{
		if ((t->px > Enemy->px) && (t->px < Enemy->px + BAIYUNW))
		{
			if ((t->py > Enemy->py) && (t->py < Enemy->py + BAIYUNH))
			{
				if (BossBY.status != 2)
				{
					t->life = false;
					Enemy->life -= t->damage;
				}
				if (BossBY.status == 2)
					t->flag = true;
				if (BossBY.life <= 500)
				{
					BossBY.status = 2;
				}
				if (BossBY.status == 2)
				{
					if (temp - showtime >= time)
					{
						BossBY.status = 1;
						showtime = time;
					}
				}

				if (Enemy->life <= 0)
				{
					Enemy->status = 3;
				}

			}
		}
	}
}


void CollapseThatPTOBYB(Bulletlist& list, Bulletlist &bullet)
{
	Bulletlist t;
	for (t = list; t != NULL; t = t->next)
	{
		if ((t->px > bullet->px) && (t->px < bullet->px + BAIYUNBULLETW))
		{
			if ((t->py > bullet->py) && (t->py <bullet->py + BAIYUNBULLETH))
			{
				t->life = false;
				bullet->life = false;
			}
		}
	}
}


void EnemyASmallBullet(Bulletlist& list,NormalPlane *Enemy)
{
		int temp = clock();
		static int firetimeSmall = 0;
		int reloadtime = 400;
		if (Enemy->life&&temp - firetimeSmall>= reloadtime)
		{
			Bulletlist s, r;
			r = list;
			s = new Bulletnode;
			s->px = ENEMYSMALLW / 2 + Enemy->px;
			s->py = Enemy->py + ENEMYSMALLH;
			s->life = true;
			s->damage = 5;
			s->next = r->next;
			r->next = s;
			s->prior = r;
			r = s;
			firetimeSmall = temp;
		}
}

void EnemyBSmallBullet(Bulletlist& list, NormalPlane* Enemy)
{
	int temp = clock();
	static int firetimeSmall = 0;
	int reloadtime = 400;
	if (Enemy->life && temp - firetimeSmall >= reloadtime)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = ENEMYSMALLW / 2 + Enemy->px;
		s->py = Enemy->py + ENEMYSMALLH;
		s->life = true;
		s->damage = 5;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		firetimeSmall = temp;
	}
}

void EnemyCSmallBullet(Bulletlist& list, NormalPlane* Enemy)
{
	int temp = clock();
	static int firetimeSmall = 0;
	int reloadtime = 400;
	if (Enemy->life && temp - firetimeSmall >= reloadtime)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = ENEMYSMALLW / 2 + Enemy->px;
		s->py = Enemy->py + ENEMYSMALLH;
		s->life = true;
		s->damage = 5;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		firetimeSmall = temp;
	}
}

void EnemyDSmallBullet(Bulletlist& list, NormalPlane* Enemy)
{
	int temp = clock();
	static int firetimeSmall = 0;
	int reloadtime = 400;
	if (Enemy->life && temp - firetimeSmall >= reloadtime)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = ENEMYSMALLW / 2 + Enemy->px;
		s->py = Enemy->py + ENEMYSMALLH;
		s->life = true;
		s->damage = 5;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		firetimeSmall = temp;
	}
}

void EnemyESmallBullet(Bulletlist& list, NormalPlane* Enemy)
{
	int temp = clock();
	static int firetimeSmall = 0;
	int reloadtime = 400;
	if (Enemy->life && temp - firetimeSmall >= reloadtime)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = ENEMYSMALLW / 2 + Enemy->px;
		s->py = Enemy->py + ENEMYSMALLH;
		s->life = true;
		s->damage = 5;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		firetimeSmall = temp;
	}
}

void EnemyFSmallBullet(Bulletlist& list, NormalPlane* Enemy)
{
	int temp = clock();
	static int firetimeSmall = 0;
	int reloadtime = 400;
	if (Enemy->life && temp - firetimeSmall >= reloadtime)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = ENEMYSMALLW / 2 + Enemy->px;
		s->py = Enemy->py + ENEMYSMALLH;
		s->life = true;
		s->damage = 5;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		firetimeSmall = temp;
	}
}

void SmallBossABullet(Bulletlist& list, Plane* Enemy)
{
	int temp = clock();
	static int firetimeSmall = 0;
	int reloadtime = 300;
	if (Enemy->life && temp - firetimeSmall >= reloadtime)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = SMALLBOSSW / 2 + Enemy->px;
		s->py = Enemy->py + SMALLBOSSH;
		s->life = true;
		s->damage = 10;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		firetimeSmall = temp;
	}
}

void SmallBossBBullet(Bulletlist& list, Plane* Enemy)
{
	int temp = clock();
	static int firetimeSmall = 0;
	int reloadtime = 300;
	if (Enemy->life && temp - firetimeSmall >= reloadtime)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = SMALLBOSSW / 2 + Enemy->px;
		s->py = Enemy->py + SMALLBOSSH;
		s->life = true;
		s->damage = 10;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		firetimeSmall = temp;
	}
}

void SmallBossCBullet(Bulletlist& list, Plane* Enemy)
{
	int temp = clock();
	static int firetimeSmall = 0;
	int reloadtime = 300;
	if (Enemy->life && temp - firetimeSmall >= reloadtime)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = SMALLBOSSW / 2 + Enemy->px;
		s->py = Enemy->py + SMALLBOSSH;
		s->life = true;
		s->damage = 10;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		firetimeSmall = temp;
	}
}

void AttackBY(Bulletlist& list)
{
	int temp = clock();
	static int firetimeSmall = 0;
	int reloadtime = 3000;
	if (BossBY.life && temp - firetimeSmall >= reloadtime && BossBY.status != 0)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = BossBY.px + BAIYUNW / 2;
		s->py = BossBY.py + BAIYUNH;
		s->life = true;
		s->damage = 25;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		firetimeSmall = temp;
	}
}

void AttackTemp(Bulletlist& list)
{
	int temp = clock();
	static int firetime = 0;
	int reloadtime = 100;
	int i = 0;
	int j = 0;
	int tempx = player.px + PLAYERW / 2;;
	int tempy = player.py;
	double vx = 0;
	double vy = 0.5;
	Bulletlist s, r;
	r = list;
	if (GetAsyncKeyState(VK_SPACE) && temp - firetime >= reloadtime)
	{
		s = new Bulletnode;
		s->px = tempx;
		s->py = tempy;
		s->life = true;
		s->flag = false;
		s->damage = 10;
		s->vx = vx;
		s->vy = vy;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;

		s = new Bulletnode;
		s->px = tempx;
		s->py = tempy;
		s->flag = false;
		s->life = true;
		s->damage = 10;
		s->vx = 0.25;
		s->vy = vy * cos(30 * PI / 180);
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;

		s = new Bulletnode;
		s->px = tempx;
		s->py = tempy;
		s->life = true;
		s->flag = false;
		s->damage = 10;
		s->vx = -0.25;
		s->vy = vy * cos(30 * PI / 180);
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;

		s = new Bulletnode;
		s->px = tempx;
		s->py = tempy;
		s->flag = false;
		s->life = true;
		s->damage = 10;
		s->vx = 0.1;
		s->vy = vy * cos(10 * PI / 180);
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;

		s = new Bulletnode;
		s->px = tempx;
		s->py = tempy;
		s->life = true;
		s->flag = false;
		s->damage = 10;
		s->vx = -0.1;
		s->vy = vy * cos(10 * PI / 180);
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;

		firetime = temp;
	}

}

void Attack(Bulletlist& list)
{
	int temp = clock();
	static int firetime = 0;
	int reloadtime = 100;
	if (GetAsyncKeyState(VK_SPACE) && temp - firetime >= reloadtime)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = player.px + PLAYERW / 2;
		s->py = player.py;
		s->life = true;
		s->damage = 10;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		firetime = temp;
	}
}

void Bomb(Bulletlist& list)
{
	int temp = clock();
	static int boombtime = 0;
	int reloadtime = 100;
	if (GetAsyncKeyState(VK_SPACE) && temp - boombtime >= reloadtime && player.BoomNum > 0)
	{
		Bulletlist s, r;
		r = list;
		s = new Bulletnode;
		s->px = player.px + PLAYERW / 2;
		s->py = player.py;
		s->life = true;
		s->damage = 10;
		s->next = r->next;
		r->next = s;
		s->prior = r;
		r = s;
		boombtime = temp;
	}
}

void ThroughBomb(Bulletlist& list, Plane* player)
{
	Bulletlist t;
	t = list->next;
	double speed;
	while (t && t->life)
	{
		if (fabs(t->px - player->px) <= 20)
			speed = 0;
		else
			speed = (t->px - player->px) / 1000;
		t->px -= speed;
		t->py += 0.1;
		if (t->py > HEIGHT)
			t->life = false;
		putimage(t->px, t->py, &BaiYunBullet[0], NOTSRCERASE);
		putimage(t->px, t->py, &BaiYunBullet[1], SRCINVERT);
		t = t->next;
	}
}



void ThroughPlayertBullet(Bulletlist& list)
{
	Bulletlist t;
	t = list->next;
	while (t && t->life)
	{
		t->py -= 0.5;
		if (t->py < 0)
			t->life = false;
		putimage(t->px, t->py, &YellowBullet[0], NOTSRCERASE);
		putimage(t->px, t->py, &YellowBullet[1], SRCINVERT);
		t = t->next;
	}
}

void ThroughPlayertBulletTemp(Bulletlist& list)
{
	Bulletlist t;
	t = list->next;
	while (t && t->life)
	{
		if (!t->flag)
		{
			t->px -= t->vx;
			t->py -= t->vy;
		}
		else if (t->flag)
		{
			t->px += t->vx;
			t->py += t->vy;
		}
		if (t->py < 0 || t->py>HEIGHT || t->px<0 || t->px>WIDTH)
			t->life = false;
		putimage(t->px, t->py, &RedBullet[0], NOTSRCERASE);
		putimage(t->px, t->py, &RedBullet[1], SRCINVERT);
		t = t->next;
	}
}




void ThroughSmallBossBullet(Bulletlist& list)
{
	Bulletlist t;
	t = list->next;
	while (t && t->life)
	{
		t->py += 0.5;
		if (t->py < 0)
			t->life = false;
		putimage(t->px, t->py, &BigBullet[0], NOTSRCERASE);
		putimage(t->px, t->py, &BigBullet[1], SRCINVERT);
		t = t->next;
	}
}

void ThroughEnemySmallBullet(Bulletlist& list)
{
	Bulletlist t;
	t = list->next;
	while (t && t->life)
	{
		t->py += 0.2;
		if (t->py > HEIGHT)
			t->life = false;
		putimage(t->px, t->py, &SmallBullet[0], NOTSRCERASE);
		putimage(t->px, t->py, &SmallBullet[1], SRCINVERT);
		t = t->next;
	}
}

void ThroughBYbullet(Bulletlist& list, Plane* player)
{
	Bulletlist t;
	t = list->next;
	double speed;
	while (t && t->life)
	{
		if (fabs(t->px - player->px) <= 20)
			speed = 0;
		else
			speed= (t->px - player->px) / 1000;
		t->px -= speed;
		t->py += 0.1;
		if (t->py > HEIGHT)
			t->life = false;
		putimage(t->px, t->py, &BaiYunBullet[0], NOTSRCERASE);
		putimage(t->px, t->py, &BaiYunBullet[1], SRCINVERT);
		t = t->next;
	}
}




void DeleteBullet(Bulletlist& list)
{
	Bulletlist p = list->next;
	Bulletlist t = NULL;
	if (!p)
		return;
	while (p)
	{
		if (!p->life)
		{
			if (p->next)
				p->next->prior = p->prior;
			p->prior->next = p->next;
			t = p;
			p = p->next;
			delete t;
		}
		else
			p = p->next;
	}
}

void StartUp()
{
	initgraph(WIDTH, HEIGHT);
	loadimage(&bk, "./images/bk.jpg");
	loadimage(&NormalPlayerimg[0], "./images/NormalPlayer0.png");
	loadimage(&NormalPlayerimg[1], "./images/NormalPlayer1.png");
	
	loadimage(&FastPlayerimg[0], "./images/FastPlayer0.png");
	loadimage(&FastPlayerimg[1], "./images/FastPlayer1.png");

	loadimage(&PlayerStatusF[0], "./images/PlayerStatusF0.png");
	loadimage(&PlayerStatusF[1], "./images/PlayerStatusF1.png");

	loadimage(&PlayerStatusS[0], "./images/PlayerStatusS0.png");
	loadimage(&PlayerStatusS[1], "./images/PlayerStatusS1.png");

	loadimage(&PlayerStatusT[0], "./images/PlayerStatusT0.png");
	loadimage(&PlayerStatusT[1], "./images/PlayerStatusT1.png");

	loadimage(&PlayerExplore[0], "./images/Explore0.png");
	loadimage(&PlayerExplore[1], "./images/Explore1.png");

	loadimage(&EnemyAimg[0], "./images/EnemyAimg0.png");
	loadimage(&EnemyAimg[1], "./images/EnemyAimg1.png");

	loadimage(&EnemyBimg[0], "./images/EnemyAimg0.png");
	loadimage(&EnemyBimg[1], "./images/EnemyAimg1.png");

	loadimage(&EnemyCimg[0], "./images/EnemyAimg0.png");
	loadimage(&EnemyCimg[1], "./images/EnemyAimg1.png");

	loadimage(&EnemyDimg[0], "./images/EnemyAimg0.png");
	loadimage(&EnemyDimg[1], "./images/EnemyAimg1.png");

	loadimage(&EnemyEimg[0], "./images/EnemyAimg0.png");
	loadimage(&EnemyEimg[1], "./images/EnemyAimg1.png");

	loadimage(&EnemyFimg[0], "./images/EnemyAimg0.png");
	loadimage(&EnemyFimg[1], "./images/EnemyAimg1.png");

	loadimage(&BigBullet[0], "./images/BigBullet0.jpg");
	loadimage(&BigBullet[1], "./images/BigBullet1.jpg");

	loadimage(&SmallBullet[0], "./images/SmallBullet0.png");
	loadimage(&SmallBullet[1], "./images/SmallBullet1.png");

	loadimage(&EnemySmallExploreF[0], "./images/EnemySmallStatusF0.png");
	loadimage(&EnemySmallExploreF[1], "./images/EnemySmallStatusF1.png");

	loadimage(&EnemySmallExploreS[0], "./images/EnemySmallStatusS0.png");
	loadimage(&EnemySmallExploreS[1], "./images/EnemySmallStatusS1.png");

	loadimage(&SmallBoss[0], "./images/SmallBoss0.png");
	loadimage(&SmallBoss[1], "./images/SmallBoss1.png");

	loadimage(&SmallBossStatusF[0], "./images/SmallBossStatusF0.png");
	loadimage(&SmallBossStatusF[1], "./images/SmallBossStatusF1.png");

	loadimage(&SmallBossStatusS[0], "./images/SmallBossStatusS0.png");
	loadimage(&SmallBossStatusS[1], "./images/SmallBossStatusS1.png");

	loadimage(&SmallBossStatusT[0], "./images/SmallBossStatusT0.png");
	loadimage(&SmallBossStatusT[1], "./images/SmallBossStatusT1.png");

	loadimage(&YellowBullet[0], "./images/bulleta0.png");
	loadimage(&YellowBullet[1], "./images/bulleta1.png");

	loadimage(&RedBullet[0], "./images/bulletb0.png");
	loadimage(&RedBullet[1], "./images/bulletb1.png");

	loadimage(&BaiYun[0], "./images/BY0.png");
	loadimage(&BaiYun[1], "./images/BY1.png");

	loadimage(&BaiYunHurt[0], "./images/BY0.png");
	loadimage(&BaiYunHurt[1], "./images/BY1Hurt.png");

	loadimage(&BaiYunBullet[0], "./images/BYbullet0.png");
	loadimage(&BaiYunBullet[1], "./images/BYbullet1.png");


	player.px = 0;
	player.py = HEIGHT - PLAYERH;
	player.life = 100;
	player.BoomNum = 3;
	player.relifeflag = false;

	EnemyA.px = 10;
	EnemyA.py = 0;
	EnemyA.status = 0;
	EnemyA.life = 30;

	EnemyB.px = ENEMYSMALLW + 45 + EnemyA.px;
	EnemyB.py = 0;
	EnemyB.life = 30;
	EnemyB.status = 0;

	EnemyC.px = ENEMYSMALLW + 45 + EnemyB.px;
	EnemyC.py = 0;
	EnemyC.life = 30;
	EnemyC.status = 0;

	EnemyD.px = ENEMYSMALLW + 45 + EnemyC.px;
	EnemyD.py = 0;
	EnemyD.life = 30;
	EnemyD.status = 0;

	EnemyE.px = ENEMYSMALLW + 45 + EnemyD.px;
	EnemyE.py = 0;
	EnemyE.life = 30;
	EnemyE.status = 0;

	EnemyF.px = ENEMYSMALLW + 45 + EnemyE.px;
	EnemyF.py = 0;
	EnemyF.life = 30;
	EnemyF.status = 0;

	smallbossB.px = (WIDTH - SMALLBOSSH) / 2;
	smallbossB.py = -500;
	smallbossB.life = 200;
	smallbossB.status = 0;

	smallbossA.px = smallbossB.px - 20 - SMALLBOSSW;
	smallbossA.py = smallbossB.py - 20 - SMALLBOSSH;
	smallbossA.life = 200;
	smallbossA.status = 0;
	smallbossA.flag = false;

	smallbossC.px = smallbossB.px + 20 + SMALLBOSSW;
	smallbossC.py = smallbossB.py - 20 - SMALLBOSSH;
	smallbossC.life = 200;
	smallbossC.status = 0;

	BossBY.px= (WIDTH - BAIYUNW) / 2;
	BossBY.py = -800;
	BossBY.life = 1000;
	BossBY.status = 0;







	KilledEnemySmallNum = 0;




}
















void Show()
{
	putimage(0, 0, &bk);
	if (!FastFlag && Playerstatus == 0)
	{
		putimage(player.px, player.py, &NormalPlayerimg[0], NOTSRCERASE);
		putimage(player.px, player.py, &NormalPlayerimg[1], SRCINVERT);
	}
	else if (FastFlag && Playerstatus == 0)
	{
		putimage(player.px, player.py, &FastPlayerimg[0], NOTSRCERASE);
		putimage(player.px, player.py, &FastPlayerimg[1], SRCINVERT);
	}

	else if (Playerstatus == 1)
	{
		putimage(player.px, player.py, &PlayerStatusF[0], NOTSRCERASE);
		putimage(player.px, player.py, &PlayerStatusF[1], SRCINVERT);
	}
	
	else if (Playerstatus == 2)
	{
		putimage(player.px, player.py, &PlayerStatusS[0], NOTSRCERASE);
		putimage(player.px, player.py, &PlayerStatusS[1], SRCINVERT);
	}

	else if (Playerstatus == 3)
	{
		putimage(player.px, player.py, &PlayerStatusT[0], NOTSRCERASE);
		putimage(player.px, player.py, &PlayerStatusT[1], SRCINVERT);
	}

	if (EnemyA.status == 0)
	{
		putimage(EnemyA.px, EnemyA.py, &EnemyAimg[0], NOTSRCERASE);
		putimage(EnemyA.px, EnemyA.py, &EnemyAimg[1], SRCINVERT);
	}
	else if (EnemyA.status == 1)
	{
		putimage(EnemyA.px, EnemyA.py, &EnemySmallExploreF[0], NOTSRCERASE);
		putimage(EnemyA.px, EnemyA.py, &EnemySmallExploreF[1], SRCINVERT);
	}
	else if (EnemyA.status == 2)
	{
		putimage(EnemyA.px, EnemyA.py, &EnemySmallExploreS[0], NOTSRCERASE);
		putimage(EnemyA.px, EnemyA.py, &EnemySmallExploreS[1], SRCINVERT);
	}

	if (EnemyB.status == 0)
	{
		putimage(EnemyB.px, EnemyB.py, &EnemyBimg[0], NOTSRCERASE);
		putimage(EnemyB.px, EnemyB.py, &EnemyBimg[1], SRCINVERT);
	}
	else if (EnemyB.status == 1)
	{
		putimage(EnemyB.px, EnemyB.py, &EnemySmallExploreF[0], NOTSRCERASE);
		putimage(EnemyB.px, EnemyB.py, &EnemySmallExploreF[1], SRCINVERT);
	}
	else if (EnemyB.status == 2)
	{
		putimage(EnemyB.px, EnemyB.py, &EnemySmallExploreS[0], NOTSRCERASE);
		putimage(EnemyB.px, EnemyB.py, &EnemySmallExploreS[1], SRCINVERT);
	}

	if (EnemyC.status == 0)
	{
		putimage(EnemyC.px, EnemyC.py, &EnemyCimg[0], NOTSRCERASE);
		putimage(EnemyC.px, EnemyC.py, &EnemyCimg[1], SRCINVERT);
	}
	else if (EnemyC.status == 1)
	{
		putimage(EnemyC.px, EnemyC.py, &EnemySmallExploreF[0], NOTSRCERASE);
		putimage(EnemyC.px, EnemyC.py, &EnemySmallExploreF[1], SRCINVERT);
	}
	else if (EnemyC.status == 2)
	{
		putimage(EnemyC.px, EnemyC.py, &EnemySmallExploreS[0], NOTSRCERASE);
		putimage(EnemyC.px, EnemyC.py, &EnemySmallExploreS[1], SRCINVERT);
	}

	if (EnemyD.status == 0)
	{
		putimage(EnemyD.px, EnemyD.py, &EnemyDimg[0], NOTSRCERASE);
		putimage(EnemyD.px, EnemyD.py, &EnemyDimg[1], SRCINVERT);
	}
	else if (EnemyD.status == 1)
	{
		putimage(EnemyD.px, EnemyD.py, &EnemySmallExploreF[0], NOTSRCERASE);
		putimage(EnemyD.px, EnemyD.py, &EnemySmallExploreF[1], SRCINVERT);
	}
	else if (EnemyD.status == 2)
	{
		putimage(EnemyD.px, EnemyD.py, &EnemySmallExploreS[0], NOTSRCERASE);
		putimage(EnemyD.px, EnemyD.py, &EnemySmallExploreS[1], SRCINVERT);
	}

	if (EnemyE.status == 0)
	{
		putimage(EnemyE.px, EnemyE.py, &EnemyEimg[0], NOTSRCERASE);
		putimage(EnemyE.px, EnemyE.py, &EnemyEimg[1], SRCINVERT);
	}
	else if (EnemyE.status == 1)
	{
		putimage(EnemyE.px, EnemyE.py, &EnemySmallExploreF[0], NOTSRCERASE);
		putimage(EnemyE.px, EnemyE.py, &EnemySmallExploreF[1], SRCINVERT);
	}
	else if (EnemyE.status == 2)
	{
		putimage(EnemyE.px, EnemyE.py, &EnemySmallExploreS[0], NOTSRCERASE);
		putimage(EnemyE.px, EnemyE.py, &EnemySmallExploreS[1], SRCINVERT);
	}

	if (EnemyF.status == 0)
	{
		putimage(EnemyF.px, EnemyF.py, &EnemyFimg[0], NOTSRCERASE);
		putimage(EnemyF.px, EnemyF.py, &EnemyFimg[1], SRCINVERT);
	}
	else if (EnemyF.status == 1)
	{
		putimage(EnemyF.px, EnemyF.py, &EnemySmallExploreF[0], NOTSRCERASE);
		putimage(EnemyF.px, EnemyF.py, &EnemySmallExploreF[1], SRCINVERT);
	}
	else if (EnemyF.status == 2)
	{
		putimage(EnemyF.px, EnemyF.py, &EnemySmallExploreS[0], NOTSRCERASE);
		putimage(EnemyF.px, EnemyF.py, &EnemySmallExploreS[1], SRCINVERT);
	}

	if (smallbossA.status == 0 && GameStatus >= 1.5)
	{
		putimage(smallbossA.px, smallbossA.py, &SmallBoss[0], NOTSRCERASE);
		putimage(smallbossA.px, smallbossA.py, &SmallBoss[1], SRCINVERT);
	}

	else if (smallbossA.status == 1 && GameStatus >= 1.5)
	{
		putimage(smallbossA.px, smallbossA.py, &SmallBossStatusF[0], NOTSRCERASE);
		putimage(smallbossA.px, smallbossA.py, &SmallBossStatusF[1], SRCINVERT);
	}

	else if (smallbossA.status == 2 && GameStatus >= 1.5)
	{
		putimage(smallbossA.px, smallbossA.py, &SmallBossStatusS[0], NOTSRCERASE);
		putimage(smallbossA.px, smallbossA.py, &SmallBossStatusS[1], SRCINVERT);
	}

	else if (smallbossA.status == 3 && GameStatus >= 1.5)
	{
		putimage(smallbossA.px, smallbossA.py, &SmallBossStatusT[0], NOTSRCERASE);
		putimage(smallbossA.px, smallbossA.py, &SmallBossStatusT[1], SRCINVERT);
	}

	if (smallbossB.status == 0 && GameStatus >= 1.5)
	{
		putimage(smallbossB.px, smallbossB.py, &SmallBoss[0], NOTSRCERASE);
		putimage(smallbossB.px, smallbossB.py, &SmallBoss[1], SRCINVERT);
	}

	else if (smallbossB.status == 1 && GameStatus >= 1.5)
	{
		putimage(smallbossB.px, smallbossB.py, &SmallBossStatusF[0], NOTSRCERASE);
		putimage(smallbossB.px, smallbossB.py, &SmallBossStatusF[1], SRCINVERT);
	}

	else if (smallbossB.status == 2 && GameStatus >= 1.5)
	{
		putimage(smallbossB.px, smallbossB.py, &SmallBossStatusS[0], NOTSRCERASE);
		putimage(smallbossB.px, smallbossB.py, &SmallBossStatusS[1], SRCINVERT);
	}

	else if (smallbossB.status == 3 && GameStatus >= 1.5)
	{
		putimage(smallbossB.px, smallbossB.py, &SmallBossStatusT[0], NOTSRCERASE);
		putimage(smallbossB.px, smallbossB.py, &SmallBossStatusT[1], SRCINVERT);
	}

	if (smallbossC.status == 0 && GameStatus >= 1.5)
	{
		putimage(smallbossC.px, smallbossC.py, &SmallBoss[0], NOTSRCERASE);
		putimage(smallbossC.px, smallbossC.py, &SmallBoss[1], SRCINVERT);
	}

	else if (smallbossC.status == 1 && GameStatus >= 1.5)
	{
		putimage(smallbossC.px, smallbossC.py, &SmallBossStatusF[0], NOTSRCERASE);
		putimage(smallbossC.px, smallbossC.py, &SmallBossStatusF[1], SRCINVERT);
	}

	else if (smallbossC.status == 2 && GameStatus >= 1.5)
	{
		putimage(smallbossC.px, smallbossC.py, &SmallBossStatusS[0], NOTSRCERASE);
		putimage(smallbossC.px, smallbossC.py, &SmallBossStatusS[1], SRCINVERT);
	}

	else if (smallbossC.status == 3 && GameStatus >= 1.5)
	{
		putimage(smallbossC.px, smallbossC.py, &SmallBossStatusT[0], NOTSRCERASE);
		putimage(smallbossC.px, smallbossC.py, &SmallBossStatusT[1], SRCINVERT);
	}

	if (GameStatus == 2 && BossBY.status != 3)
	{
		putimage(BossBY.px, BossBY.py, &BaiYun[0], NOTSRCERASE);
		putimage(BossBY.px, BossBY.py, &BaiYun[1], SRCINVERT);
		if (BossBY.status == 2)
		{
			putimage(BossBY.px, BossBY.py, &BaiYunHurt[0], NOTSRCERASE);
			putimage(BossBY.px, BossBY.py, &BaiYunHurt[1], SRCINVERT);
		}
	}
















	setbkmode(TRANSPARENT);
	settextcolor(RGB(0, 0, 0));
	settextstyle(25, 0, _T("楷体"));
	TCHAR a[20];
	_stprintf_s(a, _T("击杀敌机数量:%d"), KilledEnemySmallNum);
	outtextxy(0, 0, a);
}


void GameStatusChange()
{
	if (KilledEnemySmallNum >= 5)
	{
		GameStatus = 1.5;
		if (smallbossB.py >= HEIGHT / 2 - SMALLBOSSH && EnemyC.px<0 && EnemyD.px>WIDTH + ENEMYSMALLW)
			GameStatus = 2;
	}



}


void Input()
{
	if (GetAsyncKeyState(VK_UP) || GetAsyncKeyState('W') && player.py > 0)
		player.py -= player.vy;
	if (GetAsyncKeyState(VK_DOWN) || GetAsyncKeyState('S') && player.py < HEIGHT - PLAYERH)
		player.py += player.vy;
	if (GetAsyncKeyState(VK_LEFT) || GetAsyncKeyState('A') && player.px > 0)
		player.px -= player.vx;
	if (GetAsyncKeyState(VK_RIGHT) || GetAsyncKeyState('D') && player.px < WIDTH - PLAYERW)
		player.px += player.vx;
	int temp = clock();
	int time = 200;
	int firetime = 0;
	if (GetAsyncKeyState('F')&&temp-firetime>=time)
	{
		if (!FastFlag)
			FastFlag = true;
		else
			FastFlag = false;
	}
}



int main(void)
{
	StartUp();
	BeginBatchDraw();
	InitBullet(PlayerBullet);
	InitBullet(EnemyAbullet);
	InitBullet(EnemyBbullet);
	InitBullet(EnemyCbullet);
	InitBullet(EnemyDbullet);
	InitBullet(EnemyEbullet);
	InitBullet(EnemyFbullet);
	InitBullet(SmallBossAbullet);
	InitBullet(SmallBossBbullet);
	InitBullet(SmallBossCbullet);
	InitBullet(BYbullet);
	srand(time(NULL));
	while (1)
	{
		Show();
		Input();
		EnemySmallMove();
		SmallBossMove();
		BaiYunMove();
		Speed();
		AttackTemp(PlayerBullet);
		AttackBY(BYbullet);

		CollapseThatPTOE(PlayerBullet, &EnemyA);
		CollapseThatPTOE(PlayerBullet, &EnemyB);
		CollapseThatPTOE(PlayerBullet, &EnemyC);
		CollapseThatPTOE(PlayerBullet, &EnemyD);
		CollapseThatPTOE(PlayerBullet, &EnemyE);
		CollapseThatPTOE(PlayerBullet, &EnemyF);

		CollapseThatETOP(EnemyAbullet, &player);
		CollapseThatETOP(EnemyBbullet, &player);
		CollapseThatETOP(EnemyCbullet, &player);
		CollapseThatETOP(EnemyDbullet, &player);
		CollapseThatETOP(EnemyEbullet, &player);
		CollapseThatETOP(EnemyFbullet, &player);
		
		EnemyASmallBullet(EnemyAbullet, &EnemyA);
		EnemyBSmallBullet(EnemyBbullet, &EnemyB);
		EnemyCSmallBullet(EnemyCbullet, &EnemyC);
		EnemyDSmallBullet(EnemyDbullet, &EnemyD);
		EnemyESmallBullet(EnemyEbullet, &EnemyE);
		EnemyFSmallBullet(EnemyFbullet, &EnemyF);

		SmallBossABullet(SmallBossAbullet, &smallbossA);
		SmallBossBBullet(SmallBossBbullet, &smallbossB);
		SmallBossCBullet(SmallBossCbullet, &smallbossC);

		ThroughPlayertBulletTemp(PlayerBullet);
		ThroughBYbullet(BYbullet, &player);
		ThroughEnemySmallBullet(EnemyAbullet);
		ThroughEnemySmallBullet(EnemyBbullet);
		ThroughEnemySmallBullet(EnemyCbullet);
		ThroughEnemySmallBullet(EnemyDbullet);
		ThroughEnemySmallBullet(EnemyEbullet);
		ThroughEnemySmallBullet(EnemyFbullet);

		ThroughSmallBossBullet(SmallBossAbullet);
		ThroughSmallBossBullet(SmallBossBbullet);
		ThroughSmallBossBullet(SmallBossCbullet);

		CollapseBetweenPlane(&player, &EnemyA);
		CollapseBetweenPlane(&player, &EnemyB);
		CollapseBetweenPlane(&player, &EnemyC);
		CollapseBetweenPlane(&player, &EnemyD);
		CollapseBetweenPlane(&player, &EnemyE);
		CollapseBetweenPlane(&player, &EnemyF);

		CollapseBetweenPANDB(&player, &smallbossA);
		CollapseBetweenPANDB(&player, &smallbossB);
		CollapseBetweenPANDB(&player, &smallbossC);
		CollapseBetweenPANDBY(&player, &BossBY);

		CollapseThatBTOP(SmallBossAbullet, &player);
		CollapseThatBTOP(SmallBossBbullet, &player);
		CollapseThatBTOP(SmallBossCbullet, &player);
		CollapseThatBYTOP(BYbullet, &player);

		CollapseThatPTOB(PlayerBullet, &smallbossA);
		CollapseThatPTOB(PlayerBullet, &smallbossB);
		CollapseThatPTOB(PlayerBullet, &smallbossC);
		CollapseThatPTOBY(PlayerBullet, &BossBY);
		CollapseThatPTOBYB(PlayerBullet, BYbullet);

		DeleteBullet(PlayerBullet);
		DeleteBullet(EnemyAbullet);
		DeleteBullet(EnemyBbullet);
		DeleteBullet(EnemyCbullet);
		DeleteBullet(EnemyDbullet);
		DeleteBullet(EnemyEbullet);
		DeleteBullet(EnemyFbullet);

		DeleteBullet(SmallBossAbullet);
		DeleteBullet(SmallBossBbullet);
		DeleteBullet(SmallBossCbullet);


		GameStatusChange();
		FlushBatchDraw();
	}
	EndBatchDraw();































	return 0;
}