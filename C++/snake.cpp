#include <cstdio>
#include <ctime>
#include <iostream>
#include <windows.h>
#include <conio.h>
using namespace std;

bool lb(int xx,int yy,int &zs,int (*xy)[3],bool bo)
{
	int (*zz)[3] = xy+zs;
	if(!bo)++xy;
	while(xy <= zz)	
	{
		if((*xy)[1] == xx && (*xy)[2] == yy) 
		return true;
		++xy;
	}
	return false;
}

void CursorPos(int x,int y)
{
	COORD coord = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

int main()
{
	system("title Ц��̰֮����");
	printf("�� �� �� �� Ϊ Ӣ �� �� �� �� �� ʼ �� Ϸ ��\n�� = W �� �� = S �� �� = A �� �� = D\n");
	system("pause");
	srand((unsigned)time(NULL));
	int xy[99][3]= {{4,4},{4,2}},zs=2,m_x=(rand()%38)*2,m_y=rand()%20,cs=0,ms=60,angle=4,c=0,bo=0;
	
	while(ms)
	{
		Sleep(ms);
		if(_kbhit())//���÷���
		{  
			c = _getch();
			if(c == 87 || c == 119 && xy[0][0] != 2) angle = 1;
			if(c == 83 || c == 115 && xy[0][0] != 1) angle = 2;
			if(c == 65 || c == 97 && xy[0][0] != 4) angle = 3;
			if(c == 68 || c == 100 && xy[0][0] != 3) angle = 4;
		}
		
		for(int i=zs; i >= 0; --i) //���÷���+��������
		{  
			if (i == 0) xy[i][0] = angle;
			else xy[i][0] = xy[i-1][0];
			if(xy[i][0] == 1) --xy[i][2];
			if(xy[i][0] == 2) ++xy[i][2];
			if(xy[i][0] == 3) xy[i][1] -= 2;
			if(xy[i][0] == 4) xy[i][1] += 2;
		}
		CursorPos(0,0);//���ù��λ��
		for(int n_y=-1; n_y<=21; ++n_y) //y������
		{
			if(n_y == -1) printf("��%d�أ�\t\t\t\tЦ��̰֮���ߣ�\n",cs);
			else printf("\n");
			for(int n_x=-1; n_x<=77;
			++n_x)//x������
			{   
				if(lb(n_x,n_y,zs,xy,true)) printf("\2");//��
				else if(lb(m_x,m_y,zs,xy,true))	
				{
					while(1)//��ֹʳ���ܵ������
					{  
						srand((unsigned)time(NULL)) , m_x = (rand()%38)*2 , m_y=rand()%20;
						if(!lb(m_x,m_y,zs,xy,true))
						{
							++cs , ++zs , xy[zs][0] = xy[zs-1][0];
							if(xy[zs][0] == 1) xy[zs][1] = xy[zs-1][1] , xy[zs][2] = xy[zs-1][2] + 1;
							if(xy[zs][0] == 2) xy[zs][1] = xy[zs-1][1] , xy[zs][2] = xy[zs-1][2] - 1;
							if(xy[zs][0] == 3) xy[zs][1] = xy[zs-1][1] + 2, xy[zs][2] = xy[zs-1][2];
							if(xy[zs][0] == 4) xy[zs][1] = xy[zs-1][1] - 2, xy[zs][2] = xy[zs-1][2];
							break;
						}
					}
				}
				else if(n_x == m_x && n_y == m_y) printf("\3");   //ʳ��
				else if(n_y == -1 || n_x == -1 || n_x == 77 || n_y == 21) printf("*");///װ��
				else printf(" ");
				if(lb(-2,n_y,zs,xy,true) || lb(n_x,-1,zs,xy,true) || lb(78,n_y,zs,xy,true) || lb(n_x,21,zs,xy,true)) bo = 1;//�ж��Ƿ񳬳���Χ
			}
		}
		if (ms >= 18) ms -= 2;
		if(lb(xy[0][1],xy[0][2],zs,xy,false)) bo = 1;
		
		if(cs >= 98 || bo == 1) break;
	}
	system("cls");
	if(bo == 1) printf("������ˣ��ٽ����������Ѿ�����%d�أ�\n",cs);
	else printf("��ϲ�㣡��Ӯ�ˣ�һ������98�أ�");
	system("pause");
	return 0;
}
