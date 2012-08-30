#include <cstdio>
#include <ctime>
#include <cmath>
const int maxp = 1000001; // ������ �Լ�����... 
const int sp = 1000;
int P[sp],pn;
bool p[maxp];
bool prime(int n)
{
	if(!n&1)
	return false;
	for(int i=3;i*i<n+2;i+=2)
	if(n%i==0)
	return false;
	return true;
}
int main()
{
	// ��ʼ��ʱ... 
	clock_t t1 = clock();
	P[pn++]= 2;
	for(int i=3;i<sp;i+=2)
		if(prime(i))
		 P[pn++] = i;
	for(int i=0;i!=pn;i++)
		for(int j=2;j*P[i]<maxp;j++)
			p[j*P[i]]=true;	 
	//  ������� ����... 
	for(int i=2;i!=maxp;i++)
		if(!p[i])
			printf("%d ",i);
		
	// �����ʱ 
	printf("Done\n%0.4f\n", (float)(clock()-t1)/CLOCKS_PER_SEC );
	getchar();
	return 0;
}
