#include <stdio.h>
#include <windows.h> //windows header

int main()
{
        //�õ����
    HANDLE h = GetStdHandle( STD_OUTPUT_HANDLE); 

        //����ԭʼ��ɫ
    WORD wOldColor; 
    CONSOLE_SCREEN_BUFFER_INFO info; 
    GetConsoleScreenBufferInfo(h,&info); 
    wOldColor = info.wAttributes; 
    
        //��������ɫ
    SetConsoleTextAttribute(h,FOREGROUND_RED|FOREGROUND_INTENSITY);
    printf( "This is a RED\n");
    SetConsoleTextAttribute(h,FOREGROUND_GREEN|FOREGROUND_INTENSITY);
    printf( "This is a GREEN\n");
    SetConsoleTextAttribute(h,FOREGROUND_BLUE|FOREGROUND_INTENSITY);
    printf( "This is a BLUE\n");

        //��ԭ����ɫ
    SetConsoleTextAttribute(h,wOldColor);
    
    system("pause");
    return 0;
}
