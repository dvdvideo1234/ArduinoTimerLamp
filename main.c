#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void delay(const clock_t str){
    const clock_t end = clock() + str;
    while(clock() < end);
}

unsigned char isNum(char c){ return (c >= '0' && c <= '9'); }

void revString(char *s)
{
  char *e = s; while(*e){ e++; } e--;
  while(e > s){ *s ^= *e; *e ^= *s; *s++ ^= *e--; }
}

unsigned int getUnit(char **u, unsigned int k)
{
  unsigned char n = 1;
  unsigned int  s = 0;
  while(**u != ':' && **u != '\0')
  {
    if(n && !isNum(**u)){ n = 0; }
    s = s * 10;
    s = s + (*(*u)++ - 0x30);
  }; (*u)++; s = (s * k * n);
  return s;
}

void getSettings(char *frm, unsigned int *tim, unsigned int *clk, unsigned int *cnt)
{
  *tim = getUnit(&frm,3600) + getUnit(&frm,60) + getUnit(&frm,1);
  *clk = getUnit(&frm,1);
  *cnt = getUnit(&frm,1);
}


int main()
{
  char set[] = "0:0:100:10:5";
  unsigned int clk, end, all, cnt, tim;
  getSettings(set,&end,&clk,&all);
  cnt = (all << 1), tim = end;
  while(42)
  {
    if(tim)
    {
      if(cnt)
      {
        if(cnt % 2 == 0)
        {
          printf("On");
        }
        else
        {
          printf("Off");
        }
        cnt--;
      }
      tim--;  printf(".");
    }
    else
    {
      cnt = all << 1;
      tim = end;
      printf("\n");
    }
    delay(clk);
  }

  return 0;
}
