#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

/*Вопрос 2 . 

На языке С++, написать минимум по 2 класса реализовывающих циклический буфер.

Объяснить плюсы и минусы каждой реализации.

В этом файле первый вариант буфера. Он использует вариант из
 ранних вариантах C++ (без шаблонов). Он очень неплох
 для фиксированных структур, но в случае с использованием
 динамически выделяемой памяти он не работает, так
 как деструктор элементов не вызывается.
*/


class circular_buffer
{
 void* buffer; // data buffer
 void* buffer_end;// end of data buffer
 size_t capacity; // maximum number of items in the buffer
 size_t count;// number of items in the buffer
 size_t sz; // size of each item in the buffer
 void* head; // pointer to head
 void* tail; // pointer to tail         

 public:

 //функция инициалищации 
 int init( size_t capac, size_t szel)
 {
  clear();
  buffer = malloc( capacity * sz );
  if( buffer == NULL )//обработка ошибки нехватки памяти
  {
    puts("No mem");exit(1);return -1;
  }
  buffer_end = (char*)buffer + capacity * sz;
  capacity = capac;
  count = 0;
  sz = szel;
  head = buffer;
  tail = buffer;
  return 0;
 }

 //функция очистки буфера 
 int clear( void )
 {
  if( buffer != 0) free( buffer );
  buffer = 0;
  buffer_end = 0;
  head = 0;
  tail = 0;
  return 0;
 }

 //Функция считывания элемента
 int pop_front(void *item)
 {
  if( count == 0 ) return -1;// буфер пуст
  //если item==0 - то режим без копирования
  if( item ) memcpy( item, tail, sz );
  tail = (char*)tail + sz;
  if(tail == buffer_end) tail = buffer;
  count--;
  return 0;
 }

 //Функция помещения элемента в очередь
 int push_back( const void* item )
 {
 //если буфер заполнен, удаляем первый элемент
  if(count == capacity) pop_front(0); 
  memcpy( head, item, sz );
  head = (char*)head + sz;
  if(head == buffer_end) head = buffer;
  count++;
  return 0;
}

 //Конструктор по умолчанию
 circular_buffer( void )
 {
  buffer = 0;buffer_end = 0;head = 0;tail = 0;
 }

 //Деструктор по умолчанию
 virtual ~circular_buffer( void )
 {
  clear();
 }
}; 


//Тест первого буфера
int BufferTest( void )
{
 circular_buffer buf;int el;
 buf.init( 3, sizeof( int ) );
 el = 1;
 buf.push_back( &el );//Добавляем элемент
 el=2;
 buf.push_back( &el );//Добавляем элемент
 el=3;
 buf.push_back( &el );//Добавляем элемент
 el=4;
 buf.push_back( &el );//Добавляем элемент
 el=5;
 buf.push_back( &el );//Добавляем элемент
 el = -10;
 if( buf.pop_front( &el ) == -1 ) puts( "<Empty>" );else printf( "%d", el );
 if( buf.pop_front( &el ) == -1 ) puts( "<Empty>" );else printf( "%d", el );
 if( buf.pop_front( &el ) == -1 ) puts( "<Empty>" );else printf( "%d", el );
 if( buf.pop_front( &el ) == -1 ) puts( "<Empty>" );else printf( "%d", el );
 if( buf.pop_front( &el ) == -1 ) puts( "<Empty>" );else printf( "%d", el );
 if( buf.pop_front( &el ) == -1 ) puts( "<Empty>" );else printf( "%d", el );
 puts( "" );
 return 0;
}

