#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SH1106.h>

#define SDA 21
#define SCK 22
Adafruit_SH1106 display(SDA,SCK);

void setupOLED();
void displayMenuScreen();
void display_A_ValueSelectscreen();
void display_B_ValueSelectscreen();
void writeRegistersA(int DATA_A);
void writeRegisterB(int DATA_B);
void writeControlSignal(int data);
void updateEncoder();
void select_ISR();
void encoder_ISR();
void value_select_ISR();

const unsigned char epd_bitmap__icon_AND [] PROGMEM = {
	0x00, 0x00, 0x07, 0xc0, 0x18, 0x30, 0x20, 0x08, 0x40, 0x04, 0x41, 0x04, 0x82, 0x82, 0x84, 0x42, 
	0x88, 0x22, 0x8f, 0xe2, 0x88, 0x22, 0x48, 0x24, 0x40, 0x04, 0x20, 0x08, 0x18, 0x30, 0x07, 0xc0
};

const unsigned char epd_bitmap__icon_addition [] PROGMEM = {
	0x07, 0xe0, 0x18, 0x18, 0x20, 0x04, 0x50, 0x02, 0x41, 0x82, 0x81, 0x81, 0x81, 0x81, 0x8f, 0xf1, 
	0x8f, 0xf1, 0x81, 0x81, 0x81, 0x81, 0x41, 0x82, 0x40, 0x02, 0x20, 0x04, 0x18, 0x18, 0x07, 0xe0
};

const unsigned char epd_bitmap__item_sel_outline [] PROGMEM = {
  0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0, 
	0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x10, 
	0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 
	0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xe0, 
	0x1f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xc0
};

const unsigned char epd_bitmap__icon_subtraction [] PROGMEM = {
0x0f, 0xe0, 0x30, 0x18, 0x40, 0x04, 0x40, 0x06, 0x80, 0x02, 0x80, 0x02, 0x9f, 0xfa, 0x9f, 0xfa, 
	0x9f, 0xfa, 0x80, 0x02, 0x80, 0x02, 0x40, 0x04, 0x40, 0x04, 0x30, 0x18, 0x0f, 0xe0
};

const unsigned char epd_bitmap__scrollbar_background [] PROGMEM = {
	0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
	0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
	0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 
	0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x02, 0x00, 0x00
};

const unsigned char epd_bitmap_icon_a_invert_ [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x0c, 0x30, 0x10, 0x08, 0x17, 0xe8, 0x20, 0x04, 0x21, 0x04, 
	0x22, 0x84, 0x24, 0x44, 0x17, 0xc8, 0x14, 0x48, 0x0c, 0x30, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00
};

const unsigned char epd_bitmap_icon_a_inc [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x0c, 0x30, 0x10, 0x48, 0x10, 0xe8, 0x20, 0x44, 0x21, 0x04, 
	0x22, 0x84, 0x24, 0x44, 0x17, 0xc8, 0x14, 0x48, 0x0c, 0x30, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00
};

const unsigned char epd_bitmap_icon_a_dec [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x0c, 0x30, 0x10, 0x08, 0x10, 0xe8, 0x20, 0x04, 0x21, 0x04, 
	0x22, 0x84, 0x24, 0x44, 0x17, 0xc8, 0x14, 0x48, 0x0c, 0x30, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00
};

const unsigned char epd_bitmap_icon_or [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x0c, 0x30, 0x10, 0x08, 0x13, 0x88, 0x24, 0x44, 0x24, 0x44, 
	0x24, 0x44, 0x24, 0x44, 0x13, 0x88, 0x10, 0x08, 0x0c, 0x30, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00
};

const unsigned char epd_bitmap_icon_xor [] PROGMEM = {
	0x00, 0x00, 0x00, 0x00, 0x03, 0xc0, 0x0c, 0x30, 0x10, 0x08, 0x14, 0x28, 0x22, 0x44, 0x21, 0x84, 
	0x21, 0x84, 0x22, 0x44, 0x14, 0x28, 0x10, 0x08, 0x0c, 0x30, 0x03, 0xc0, 0x00, 0x00, 0x00, 0x00
};

const int epd_bitmap_allArray_LEN = 8;
const unsigned char* epd_bitmap_allArray[8] = {
	epd_bitmap__icon_AND,
	epd_bitmap__icon_addition,
	epd_bitmap__icon_subtraction,
  epd_bitmap_icon_a_invert_,
	epd_bitmap_icon_a_inc,
	epd_bitmap_icon_a_dec,
	epd_bitmap_icon_or,
	epd_bitmap_icon_xor
};

const int NUM_ITEMS = 8;

char menu_items[NUM_ITEMS] [20] = {
  {"AND"},
	{"Addition"},
	{"Subtraction"},
  {"Invert A"},
  {"Increment A"},
  {"Decrement A"},
  {"OR"},
  {"XOR"}
};

const int AND_SIGNAL = 7;
const int ADDITION_SIGNAL = 0;
const int SUBTRACTION_SIGNAL = 3;
const int INVERT_A_SIGNAL = 31;
const int INCREMENT_A_SIGNAL = 2;
const int DECREMENT_A_SIGNAL = 3;
const int OR_SIGNAL = 12;
const int XOR_SIGNAL = 23;

const unsigned int control_signals[NUM_ITEMS] = {
  AND_SIGNAL,
  ADDITION_SIGNAL,
  SUBTRACTION_SIGNAL,
  INVERT_A_SIGNAL,
  INCREMENT_A_SIGNAL,
  DECREMENT_A_SIGNAL,
  OR_SIGNAL,
  XOR_SIGNAL
};

#define outputA 15
#define outputB 2
#define select_sw 0

#define clk 16
#define dt 17
#define sw 5


int item_selected = 0;
int item_sel_previous;
int item_sel_next;

int current_screen = 0;
int button_select_clicked = 0;
int value_select_clicked = 0;

volatile int lastEncoded = 0;
volatile long encoderValue = 0;
volatile long data_a = 0,data_b = 0;
const int debounceDelay = 10;

#define DATA_PIN  25 
#define LATCH_PIN 26  
#define CLOCK_PIN 27 
#define DATAB_PIN 12

#define CD_PIN 32
#define CLATCH_PIN 14
#define CCLOCK_PIN 4


void writeRegistersA(int DATA_A)
{
  digitalWrite(LATCH_PIN,LOW);
  shiftOut(DATA_PIN,CLOCK_PIN,MSBFIRST,DATA_A);
  digitalWrite(LATCH_PIN, HIGH);
  digitalWrite(LATCH_PIN, LOW);
}

void writeRegisterB(int DATA_B)
{
  digitalWrite(CLATCH_PIN,LOW);
  shiftOut(DATAB_PIN,CCLOCK_PIN,MSBFIRST,DATA_B);
  digitalWrite(CLATCH_PIN, HIGH);
  digitalWrite(CLATCH_PIN, LOW);
}

void writeControlSignal(int data)
{
  digitalWrite(CLATCH_PIN,LOW);
  shiftOut(CD_PIN,CCLOCK_PIN,MSBFIRST,data);
  digitalWrite(CLATCH_PIN, HIGH);
  digitalWrite(CLATCH_PIN, LOW);

}
void reset()
    {writeControlSignal(0);
  writeRegistersA(0);
  writeRegisterB(0);
}

void updateEncoder()
{
  static unsigned long lastDebounceTime = 0;
  static int lastEncodedA = 0;
  static int lastEncodedB = 0;
  int MSB = digitalRead(outputA);
  int LSB = digitalRead(outputB);
  int encoded = (MSB << 1) | LSB;
   int sum = (lastEncodedA << 3) | (lastEncodedB << 2) | (encoded << 1) | (encoded);
   if(millis() -lastDebounceTime > debounceDelay){
    if((sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011) && current_screen == 0)
    {
      item_selected = item_selected-1;
      if(item_selected < 0){
      item_selected = NUM_ITEMS - 1;
    }
     }
    else if ((sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) && current_screen == 0) {
      item_selected = item_selected + 1;
      if(item_selected >= NUM_ITEMS){
        item_selected = 0;
      }
    }
  lastEncodedA = MSB;
  lastEncodedB = LSB;
  lastDebounceTime = millis();
   }
  }


void select_ISR()
{
   if((digitalRead(select_sw)  == LOW) && (button_select_clicked == 0)){
      button_select_clicked = 1;
      if(current_screen == 0){current_screen = 1;}
      else if(current_screen == 1){current_screen = 0;}
      else{current_screen = 0;}
    }
    if(digitalRead(select_sw) == HIGH && (button_select_clicked == 1)){
      button_select_clicked = 0;
    }
}

void encoder_ISR(){
  static unsigned long lastDebounceTime = 0;
  static int lastEncodedA = 0;
  static int lastEncodedB = 0;
  int MSB = digitalRead(clk);
  int LSB = digitalRead(dt);
  int encoded = (MSB << 1) | LSB;
   int sum = (lastEncodedA << 3) | (lastEncodedB << 2) | (encoded << 1) | (encoded);
   if(millis() - lastDebounceTime>debounceDelay){
    if(sum == 0b1101 || sum == 0b0100 || sum == 0b0010 || sum == 0b1011)
    {
      encoderValue++;
     }
    else if (sum == 0b1110 || sum == 0b0111 || sum == 0b0001 || sum == 0b1000) {
      encoderValue--;
    }
    lastDebounceTime = millis();
   }

  lastEncodedA = MSB;
  lastEncodedB = LSB;
  encoderValue = constrain(encoderValue, 0, 65535);
}

void value_select_ISR() {
  int swState = digitalRead(sw);

  if (swState == LOW && value_select_clicked == 0) {
    value_select_clicked = 1;

    if (current_screen == 1) {
      current_screen = 2;
      data_a = encoderValue;
      encoderValue = 0;
    } else if (current_screen == 2) {
      current_screen = 3;
      data_b = encoderValue;
      encoderValue = 0;
      writeRegistersA(data_a);
      writeRegisterB(data_b);
      writeControlSignal(control_signals[item_selected+1]);
    } else {
      current_screen = 0;
      encoderValue = 0;
    }
  }

  if (swState == HIGH && value_select_clicked == 1) {
    value_select_clicked = 0;
  }
}

void displayWelcomeScreen()
{
  display.clearDisplay();
  display.setCursor(45, 30);
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.print("WELCOME");
  display.display();
  delay(500);
  display.clearDisplay();
}

void setupOLED()
{
  display.begin(SH1106_SWITCHCAPVCC, 0x3c);
  delay(1000);
  display.clearDisplay();
  displayWelcomeScreen();
} 

void displayMenuScreen()
{
  if(current_screen == 0){
  item_sel_previous = item_selected - 1;
  if (item_sel_previous < 0) {item_sel_previous = NUM_ITEMS - 1;}
  item_sel_next = item_selected + 1;  
  if (item_sel_next >= NUM_ITEMS) {item_sel_next = 0;}
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.setCursor(25,50);
  display.print(menu_items[item_sel_previous]);
  display.drawBitmap(4,46,epd_bitmap_allArray[item_sel_previous],16,16,1);

  display.setCursor(25,10);
  display.print(menu_items[item_selected]);   
  display.drawBitmap(4,06,epd_bitmap_allArray[item_selected],16,16,1);

  display.setCursor(25,30);
  display.print(menu_items[item_sel_next]);
  display.drawBitmap(4,26,epd_bitmap_allArray[item_sel_next],15,15,1);

  display.drawBitmap(0,22,epd_bitmap__item_sel_outline,128,21,1);
  display.drawBitmap(120,0,epd_bitmap__scrollbar_background,8,64,1);
  display.display();
  display.clearDisplay();
  }
}

void display_A_ValueSelectscreen()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.drawBitmap(100,8,epd_bitmap_allArray[item_selected+1],16,16,1);
  display.setCursor(30,20);
  display.print("Select A");
  display.setCursor(30,40);
  display.print(encoderValue);
  display.display();
}

void display_B_ValueSelectscreen()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.drawBitmap(100,8,epd_bitmap_allArray[item_selected+1],16,16,1);
  display.setCursor(30,20);
  display.print("Select B");
  display.setCursor(30,40);
  display.print(encoderValue);
  display.display();
}

void displayResultScreen()
{
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.drawBitmap(100,8,epd_bitmap_allArray[item_selected+1],16,16,1);
  display.setCursor(30,30);
  display.print("Result");
  display.display();
}

void setup() {
  Serial.begin(115200);
  pinMode(outputA, INPUT_PULLUP);
  pinMode(outputB, INPUT_PULLUP);
  pinMode(select_sw, INPUT_PULLUP);
  pinMode(DATA_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(LATCH_PIN, OUTPUT);
  pinMode(clk, INPUT_PULLUP);
  pinMode(dt, INPUT_PULLUP);
  pinMode(sw, INPUT_PULLUP);
  pinMode(CD_PIN,OUTPUT);
  pinMode(CLATCH_PIN,OUTPUT);
  pinMode(CCLOCK_PIN,OUTPUT);
  pinMode(DATAB_PIN,OUTPUT);

  attachInterrupt(digitalPinToInterrupt(outputA), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(outputB), updateEncoder, CHANGE);
  attachInterrupt(digitalPinToInterrupt(select_sw), select_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(clk), encoder_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(dt), encoder_ISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(sw), value_select_ISR, CHANGE);

  setupOLED();
  }
 
void loop() {
switch(current_screen){
  case 0:
  displayMenuScreen();
  reset();
  break;
  case 1:
  display_A_ValueSelectscreen();
  break;
  case 2:
  display_B_ValueSelectscreen();
  break;
  case 3:
  displayResultScreen();
  break;
}
}
