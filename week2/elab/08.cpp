#include <iostream>
using namespace std;

char* write_chars(char* dest, const char* st)
{
  
int i;
for(i=0;*(st+i)!='\0';i++) *(dest+i) = *(st+i);
dest += i;

  return dest;
}

void escape(char* src, char *dest)
{
  
int d=0;
for(int i=0;*(src+i)!='\0';i++) {
  char* rep;
switch(*(src+i)) {
case '<': rep="&lt;";break;
case '>': rep="&gt;";break;
case '"': rep="&quot;";break;
default: *(dest)=*(src+i);dest++;continue;
} 
dest = write_chars(dest,rep);
}
*(dest) = '\0';

}

main()
{
  char st[1000];
  char out[1000];
 // int l;

  cin.getline(st,1000);
  escape(st,out);

  cout << out << endl;
}