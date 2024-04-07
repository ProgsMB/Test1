#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

//Декларация функций других модулей
int BufferTest(void);
int BufferTest2(void);
int EvenTest(void);
int SortTest (void);


//Основная функция
int main( void )
{
 int i;
 puts( "Even Test" );
 EvenTest();
 puts( "Sort Test" );
 SortTest();
 puts( "Buffer no template Test" );
 BufferTest();
 puts( "Buffer template Test" );
 BufferTest2();
 return 0;
}


