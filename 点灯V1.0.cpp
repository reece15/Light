//
//		���С��Ϸ
//
//		WIN7X64  VC++6.O   ͼ�ο⣺EASYX������
//
//		2015 1 22
//
//		By:0xcc


#include <graphics.h>
#include <conio.h>
#include <stdio.h>
#pragma comment(lib, "winmm.lib")

int map_check[20][20];		//��ͼ��Ϣ
IMAGE welcome_bk;

void welcome();
void draw_map(int where);
int game(int where, int where_num);
void game_info(int flag, int step, int where_num);

int main(void)
{
	int i;
	LOGFONT f;
	int where_table[] = {2, 3, 4, 6, 8, 10, 12, 15, 16, 20};

	initgraph(640, 480);
	loadimage(&welcome_bk, "images/welcome_bk.jpg");
	getfont(&f);                          
	f.lfHeight = 16;                     
	strcpy(f.lfFaceName, "����");        
	f.lfQuality = ANTIALIASED_QUALITY;    
	setfont(&f);                          // ����������ʽ
	welcome();
	for(i = 0; i < 10; i++)
	{	
		cleardevice();
		draw_map(where_table[i]);
		game(where_table[i], i);
		fflush(stdin);
		getch();
	}
	cleardevice();
	f.lfHeight = 72;
	setfont(&f);
	outtextxy(150, 180, "ͨ��ѵ��!");
	f.lfHeight = 12;
	setfont(&f);
	outtextxy(180, 400, "��ϲ������ˡ���ơ���ս�ʸ񣬾����ڴ���������!");
	Sleep(5000);
	closegraph();
	return 0;
}

void welcome()
{
	MOUSEMSG m;
	
	putimage(0, 0, &welcome_bk);
	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x >= 74 && m.x <= 105 && m.y >= 110 && m.y <= 200)
		{
			break;
		}
		else if (m.uMsg == WM_LBUTTONDOWN && m.x >= 74 && m.x <= 105 && m.y >= 264 && m.y <= 355)
		{
			exit(1);
		}
	}
}

void draw_map(int where)
{
	int i, j, num;

	setbkcolor(BLACK);
	num = 480/where;
	setcolor(GREEN);
	for (i = 0; i < where; i++)
	{
		for (j = 0; j < where; j++)
		{
			map_check[i][j] = 0;
		}
	}
	for (i = 0; i <= where; i++)
	{
		line(0, num * i, 480, num * i);	
	}
	for (j = 0; j <= where; j++)
	{
		line(num * j, 0, num * j, 480);
	}

}
int game(int where, int where_num)
{
	MOUSEMSG m;
	int temp_x, temp_y, i, j, flag = 0, num = 480/where;
	int step = 0;

	while (1)
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN && m.x < 480)
		{
			if (m.x == num || m.y == num)
			{
				continue;
			}
			mciSendString("open audio/change.mp3 alias change", NULL, 0, NULL);
			mciSendString("play change", NULL, 0, NULL);
			step += 1;
			temp_x = m.x/num;
			temp_y = m.y/num;
			if (map_check[temp_y][temp_x] == 0)
			{
				setfillstyle(RED);
				floodfill(m.x, m.y , GREEN);
				map_check[temp_y][temp_x] = 1;
			}
			else
			{
				setfillstyle(BLACK);
				floodfill(m.x, m.y, GREEN);
				map_check[temp_y][temp_x] = 0;
			}
			if (temp_x - 1 >= 0)
			{
				if (map_check[temp_y][temp_x-1])
				{
					setfillstyle(BLACK);
					floodfill(m.x - num, m.y, GREEN);
					map_check[temp_y][temp_x-1] = 0;
				}
				else
				{
					setfillstyle(RED);
					floodfill(m.x - num, m.y, GREEN);
					map_check[temp_y][temp_x-1] = 1;
				}
			}
			if (temp_y - 1 >= 0)
			{
				if (map_check[temp_y-1][temp_x])
				{
					setfillstyle(BLACK);
					floodfill(m.x, m.y - num, GREEN);
					map_check[temp_y-1][temp_x] = 0;
				}
				else
				{
					setfillstyle(RED);
					floodfill(m.x, m.y - num, GREEN);
					map_check[temp_y-1][temp_x] = 1;
				}
			}
			if (temp_x + 1 < where)
			{
				if (map_check[temp_y][temp_x+1])
				{
					setfillstyle(BLACK);
					floodfill(m.x + num, m.y, GREEN);
					map_check[temp_y][temp_x+1] = 0;
				}
				else
				{
					setfillstyle(RED);
					floodfill(m.x + num, m.y , GREEN);
					map_check[temp_y][temp_x+1] = 1;
				}
			}
			if (temp_y + 1 < where)
			{
				if (map_check[temp_y+1][temp_x])
				{
					setfillstyle(BLACK);
					floodfill(m.x, m.y + num, GREEN);
					map_check[temp_y+1][temp_x] = 0;
				}
				else
				{
					setfillstyle(RED);
					floodfill(m.x, m.y + num, GREEN);
					map_check[temp_y+1][temp_x] = 1;
				}
			}
			Sleep(200);
			mciSendString("stop change", NULL, 0, NULL);
			mciSendString("close change", NULL, 0, NULL);
		}
		for (i = 0; i < where && !flag; i++)
		{
			for (j = 0; j < where && !flag; j++)
			{
				if (map_check[i][j] == 0)
				{
					flag = 1;
				}
			}
		}
		game_info(flag, step, where_num);
		if (flag == 0)
		{
			break;
		}
		flag = 0;
	}
	return 0;
}

void game_info(int flag, int step, int where_num)
{
	char buffer[20];

	setfillstyle(BLACK);
	floodfill(488, 5, GREEN);
	outtextxy(481, 0, "-------------------");
	outtextxy(481, 20, "-------------------");
	if (flag == 0)
	{
		outtextxy(520, 40, "�Ե�!ͨ����!");
		outtextxy(520, 60, "�����������");
	}
	else
	{
		outtextxy(520, 40, "��û��ͨ��!");
		outtextxy(520, 60, "���̲�����");
	}
	outtextxy(481, 80, "-------------------");
	sprintf(buffer, "����:  %d", step);
	outtextxy(510, 100, buffer);
	outtextxy(481, 120, "-------------------");
	outtextxy(510, 150, " �ص�С������");
	outtextxy(490, 200, "�����ĵ�Ʋ���˭��");
	outtextxy(490, 250, "��ս����ս�ģ��ȹ�");
	outtextxy(490, 300, "����ѵ��������˵!");
	outtextxy(481, 320, "-------------------");
	sprintf(buffer, "�� %d ��", where_num+1);
	outtextxy(520, 350, buffer);
	outtextxy(481, 380, "-------------------");
	outtextxy(520, 410, "�� 10 ��");
	outtextxy(481, 440, "-------------------");
	outtextxy(481, 460, "-------------------");
	outtextxy(481, 480, "-------------------");
}