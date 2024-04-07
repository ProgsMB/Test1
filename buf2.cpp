#include <iostream>
#include <stdexcept>
#include <vector>
using namespace std;

/*������ 2 .�

 �� ����� �++, �������� ������� �� 2 ������ ��������������� ����������� �����.

 ��������� ����� � ������ ������ ����������.

 � ���� ����� ������ ������� ������. �� ����������
 ������ std::vector. ��������� ����� �������� ����� ����
 ������������ ��������� ������� � �������������� ������������
 ������.
*/

//������ CircularBuffer ��������� ������� ����� ��������
template<typename T> 
 class CircularBuffer
 {
 private:
 vector<T> buffer;
 int head;
 int tail;
 int capacity;
 public:

 // �����������
 CircularBuffer( int capac )
 {
  capacity = capac;
  head = 0;
  tail = 0;
  buffer.resize( capacity );
  return;
 }

 // ���������� ��������
 int push_back( T* element )
 {
  buffer[ head ] = *element;
  head = (head + 1) % capacity;
  if (head == tail) { tail = (tail + 1) % capacity; }
  return 0;
 }

 // �������� ��������
int pop_front( T*element )
{
 if ( empty() ) return -1;
 *element=buffer [ tail ];
 tail = (tail + 1) % capacity;
 return 0;
}

 //�������� ������� ������
 bool empty( void ) const
 {
  return head == tail;
 }

 // �������� ������� ������
 bool full( void ) const
 {
   return (head + 1) % capacity == tail;
 }

 // �������� ������ ������
 int size( void) const
 {
  if (head >= tail) { return head - tail; }
  return capacity - (tail - head);
 }

 // ������ ������
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

 //���������������� ����� ��� ��������� ���� int � ������������
 //������ �������� �� ������
class IntHolder
{
 int val;
 public:

 //�����������
 IntHolder( void )
 {
  val=0;
  return;
 }

 //��������� ��������
 int SetVal( int v )
 {
  val=v;
 }

 //������
 int Print( void ) const
 {
  printf( "%d", val );
  return 0;
 }
};

//�������� �������
int BufferTest2( void )
{
 IntHolder el;
 // ������� �����
 CircularBuffer<IntHolder> buffer( 5 );
 // �������� ��������
 for (int i = 1; i <= 6; ++i)
 {
  el.SetVal( i );
  buffer.push_back( &el );
  cout << "Added: " << i << endl; 
 }
 // ������ ����� ���������� ���������
 cout << "Elements of the buffer: ";
 buffer.PrintBuffer();
 cout << "Buffer size: " << buffer.size() << endl;
 // ������� ��������
 for (int i = 0; i < 1; i++)
 {
  buffer.pop_front( &el );
  printf( "(" );
  el.Print();
  printf( ")" );
  cout << "Removed" << endl; 
 }
 //������ ���������
 cout << "Elements of the buffer: ";
 buffer.PrintBuffer();
 cout << "Buffer size: " << buffer.size() << endl;
 return 0; 
}

