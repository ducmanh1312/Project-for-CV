int D1_pin = 2;
int D2_pin = 3;
int D3_pin = 4;
int D4_pin = 5;
int a = 6;
int b = 7;
int c = 8;
int d = 9; 
int e = 10;
int f = 11;
int g = 12;

void Clear()
{
  digitalWrite(a, LOW);
  digitalWrite(b, LOW);
  digitalWrite(c, LOW);
  digitalWrite(d, LOW);
  digitalWrite(e, LOW);
  digitalWrite(f, LOW);
  digitalWrite(g, LOW);
}

void ledSang(int led, int num)
{
  digitalWrite(D1_pin, HIGH);
  digitalWrite(D2_pin, HIGH);
  digitalWrite(D3_pin, HIGH);
  digitalWrite(D4_pin, HIGH);
  digitalWrite(led+1, LOW);
  
  Clear();
  if(num ==0 || num ==2 || num ==3 || num ==5 || num ==6 || num ==7 || num ==8 || num ==9 ) digitalWrite(a, HIGH);
  if(num ==0 || num ==1 || num ==2 || num ==3 || num ==4 || num ==7 || num ==8 ||  num ==9) digitalWrite(b, HIGH);
  if(num ==0 || num ==1 || num ==3 || num ==4 || num ==5 || num ==6 || num ==7 || num ==8 || num ==9 )digitalWrite(c, HIGH);
  if(num ==0 || num ==2 || num ==3 || num ==5 || num ==6 || num ==8 || num ==9 )digitalWrite(d, HIGH);
  if(num ==0 || num ==2 || num ==6 || num ==8 )digitalWrite(e, HIGH);
  if(num ==0 || num ==4 || num ==5 || num ==6 || num ==8 || num ==9)digitalWrite(f, HIGH);
  if(num ==2|| num ==3|| num ==4|| num ==5|| num ==6|| num ==8|| num ==9 )digitalWrite(g, HIGH);
}

void ledSang4(int num[])
{
  for(int i = 0; i < 4; i++)
  {
    ledSang(i+1, num[i]);
    delay(5);
  }
}



void setup() {
  pinMode(D1_pin, OUTPUT);
  pinMode(D2_pin, OUTPUT);
  pinMode(D3_pin, OUTPUT);
  pinMode(D4_pin, OUTPUT);
  
  pinMode(a, OUTPUT);
  pinMode(b, OUTPUT);
  pinMode(c, OUTPUT);
  pinMode(d, OUTPUT);
  pinMode(e, OUTPUT);
  pinMode(f, OUTPUT);
  pinMode(g, OUTPUT);
}

void loop() {

  int let[4] = {1,2,3,4};
  ledSang4(let);
//  delay(10);

 
}
