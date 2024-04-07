#include <stdio.h>
#include <stdlib.h>
#include <mem.h>

/*������ 2 .�

�� ����� �++, �������� ������� �� 2 ������ ��������������� ����������� �����.

��������� ����� � ������ ������ ����������.

� ���� ����� ������ ������� ������. �� ���������� ������� ��
 ������ ��������� C++ (��� ��������). �� ����� ������
 ��� ������������� ��������, �� � ������ � ��������������
 ����������� ���������� ������ �� �� ��������, ���
 ��� ���������� ��������� �� ����������.
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

 //������� ������������� 
 int init( size_t capac, size_t szel)
 {
  clear();
  buffer = malloc( capacity * sz );
  if( buffer == NULL )//��������� ������ �������� ������
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

 //������� ������� ������ 
 int clear( void )
 {
  if( buffer != 0) free( buffer );
  buffer = 0;
  buffer_end = 0;
  head = 0;
  tail = 0;
  return 0;
 }

 //������� ���������� ��������
 int pop_front(void *item)
 {
  if( count == 0 ) return -1;// ����� ����
  //���� item==0 - �� ����� ��� �����������
  if( item ) memcpy( item, tail, sz );
  tail = (char*)tail + sz;
  if(tail == buffer_end) tail = buffer;
  count--;
  return 0;
 }

 //������� ��������� �������� � �������
 int push_back( const void* item )
 {
 //���� ����� ��������, ������� ������ �������
  if(count == capacity) pop_front(0); 
  memcpy( head, item, sz );
  head = (char*)head + sz;
  if(head == buffer_end) head = buffer;
  count++;
  return 0;
}

 //����������� �� ���������
 circular_buffer( void )
 {
  buffer = 0;buffer_end = 0;head = 0;tail = 0;
 }

 //���������� �� ���������
 virtual ~circular_buffer( void )
 {
  clear();
 }
}; 


//���� ������� ������
int BufferTest( void )
{
 circular_buffer buf;int el;
 buf.init( 3, sizeof( int ) );
 el = 1;
 buf.push_back( &el );//��������� �������
 el=2;
 buf.push_back( &el );//��������� �������
 el=3;
 buf.push_back( &el );//��������� �������
 el=4;
 buf.push_back( &el );//��������� �������
 el=5;
 buf.push_back( &el );//��������� �������
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

