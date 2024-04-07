#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

/*Вопрос 2 . 

 На языке С++, написать минимум по 2 класса реализовывающих циклический буфер.

 Объяснить плюсы и минусы каждой реализации.

 В этом файле второй вариант буфера. Он использует
 шаблон std::vector. Благодаря этому элементы могут быть
 полноценными объектами классов с использованием динамической
 памяти.
*/

//Шаблон CircularBuffer позволяет хранить любые элементы
template<typename T> 
 class CircularBuffer
 {
 private:
 vector<T> buffer;
 int head;
 int tail;
 int capacity;
 public:

 // Конструктор
 CircularBuffer( int capac )
 {
  capacity = capac;
  head = 0;
  tail = 0;
  buffer.resize( capacity );
  return;
 }

 // Добавление элемента
 int push_back( T* element )
 {
  buffer[ head ] = *element;
  head = (head + 1) % capacity;
  if (head == tail) { tail = (tail + 1) % capacity; }
  return 0;
 }

 // Удаление элемента
int pop_front( T*element )
{
 if ( empty() ) return -1;
 *element=buffer [ tail ];
 tail = (tail + 1) % capacity;
 return 0;
}

 //Проверка пустоты буфера
 bool empty( void ) const
 {
  return head == tail;
 }

 // Проверка полноты буфера
 bool full( void ) const
 {
   return (head + 1) % capacity == tail;
 }

 // Получить размер буфера
 int size( void) const
 {
  if (head >= tail) { return head - tail; }
  return capacity - (tail - head);
 }

 // Печать буфера
 int PrintBuffer() const
 {
  int idx = tail;
  while (idx != head)
  {
   buffer [ idx ].Print();
   cout  << " ";
   idx = (idx + 1) % capacity;
  }
  cout << endl;
  return 0;
 }
};

 //Демонстрационный класс для элементов типа int с возможностью
 //печати элемента на экране
class IntHolder
{
 int val;
 public:

 //Конструктор
 IntHolder( void )
 {
  val=0;
  return;
 }

 //Установка значения
 int SetVal( int v )
 {
  val=v;
 }

 //Печать
 int Print( void ) const
 {
  printf( "%d", val );
  return 0;
 }
};

//Тестовая функция
int BufferTest2( void )
{
 IntHolder el;
 // Создать буфер
 CircularBuffer<IntHolder> buffer( 5 );
 // Добавить элементы
 for (int i = 1; i <= 6; ++i)
 {
  el.SetVal( i );
  buffer.push_back( &el );
  cout << "Added: " << i << endl; 
 }
 // Печать после добавления элементов
 cout << "Elements of the buffer: ";
 buffer.PrintBuffer();
 cout << "Buffer size: " << buffer.size() << endl;
 // Удалить элементы
 for (int i = 0; i < 1; i++)
 {
  buffer.pop_front( &el );
  printf( "(" );
  el.Print();
  printf( ")" );
  cout << "Removed" << endl; 
 }
 //Печать элементов
 cout << "Elements of the buffer: ";
 buffer.PrintBuffer();
 cout << "Buffer size: " << buffer.size() << endl;
 return 0; 
}

