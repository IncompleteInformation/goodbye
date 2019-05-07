#define S1 8
#define S2_LEFT 7
#define S2_RIGHT 6
#define S3 5
#define S3_LED 2

#define S1_MASK       0b00000001
#define S2_LEFT_MASK  0b00000010
#define S2_RIGHT_MASK 0b00000100
#define S3_MASK       0b00001000

#define KEY_SPACE 0x20

#include <Keyboard.h>

//Arduino Code
void setup() {
  Keyboard.begin();
  
  pinMode(S1, INPUT_PULLUP);
  pinMode(S2_LEFT, INPUT_PULLUP);
  pinMode(S2_RIGHT, INPUT_PULLUP);
  pinMode(S3, INPUT_PULLUP);
  pinMode(S3_LED, OUTPUT);
  digitalWrite(S3_LED,LOW);
}

//cpp code
int check_state(){
  int STATE = 0b00000000;
  if (!digitalRead(S1))        {STATE|=S1_MASK;}
  if (!digitalRead(S2_LEFT))   {STATE|=S2_LEFT_MASK;}
  if (!digitalRead(S2_RIGHT))  {STATE|=S2_RIGHT_MASK;}
  if (!digitalRead(S3))        {STATE|=S3_MASK;}
  return STATE;
}

void ominous_print(String in, long d=10){
  long t = d;
  for (int i=0; i<in.length(); i++){
    Keyboard.press(in.charAt(i));
    Keyboard.releaseAll();
    if (t == 0){
      d = random(50,350);
    }
    delay(d);
  }
}
// Shortcuts
void alt_tab(){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_TAB);
  Keyboard.releaseAll();
  delay(100);
}
void alt_f4(){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_F4);
  Keyboard.releaseAll();
  delay(100);
}
void alt_c(){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_SPACE);
  Keyboard.releaseAll();
  delay(50);
  Keyboard.press('c');
  Keyboard.releaseAll();
  delay(100);
}
void alt_n(){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press(KEY_SPACE);
  Keyboard.releaseAll();
  delay(50);
  Keyboard.press('n');
  Keyboard.releaseAll();
  delay(100);
}
void shut_down(){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('x');
  Keyboard.releaseAll();
  delay(200);
  Keyboard.press('u');
  Keyboard.releaseAll();
  delay(200);
  Keyboard.press('u');
  Keyboard.releaseAll();
  delay(10000);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_TAB);
  Keyboard.releaseAll();
  delay(100);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  // Goodbye
}

// Powershell Takeover Region
const String key_right_command = "Get-Process | Where-Object {$_.Name -ne 'powershell' -And $_.Name -ne 'conhost'} | Stop-Process -Name {$_.Name}";
const String l_pad = "#####     ";
const String r_pad = "     #####";
const String powershell_exec = "Powershell (Join-Path $home 'Desktop\\";

void powershell_init_uac(int d=200){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('x');
  Keyboard.releaseAll();
  delay(d*1);
  Keyboard.press('a');
  Keyboard.releaseAll();
  delay(d*4);
  Keyboard.press(KEY_LEFT_ARROW);
  Keyboard.releaseAll();
  delay(d/2);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(d*3); 
}

void powershell_init(int d=100){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press('x');
  Keyboard.releaseAll();
  delay(d*2);
  Keyboard.press('a');
  Keyboard.releaseAll();
  delay(d*5);
}

void cleanup(){
  powershell_init();
  Keyboard.print(powershell_exec);Keyboard.println("cleanup.ps1')");
  delay(600);
}

void set_execution_policy(){
  Keyboard.println("Set-ExecutionPolicy Bypass -Force");
}
void download(){
  powershell_init_uac();
  Keyboard.println("[Net.ServicePointManager]::SecurityProtocol = [Net.SecurityProtocolType]::Tls12");
  Keyboard.println("$u = 'https://github.com/IncompleteInformation/goodbye/raw/master/scripts/download.ps1'");                     //"$u = 'url'"
  Keyboard.println("$o = Join-Path $home 'Desktop\\download.ps1'");
  Keyboard.println("$w = New-Object System.Net.WebClient");
  Keyboard.println("$w.DownloadFile($u, $o)");
  set_execution_policy();
  Keyboard.println("$p = Join-Path $home 'Desktop\\download.ps1'");
  Keyboard.println("Powershell $p");
  Keyboard.println("Remove-Item $p");
}


void maximize(){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.press(KEY_UP_ARROW);
  Keyboard.releaseAll();
  delay(100);
}
void change_font(String font, int s=100){
  Keyboard.press(KEY_LEFT_ALT);
  Keyboard.press('o');
  delay(50);
  Keyboard.press('f');
  Keyboard.releaseAll();
  delay(100);
  Keyboard.print(font);
  Keyboard.press(KEY_TAB);
  Keyboard.releaseAll();
  delay(50);
  Keyboard.press(KEY_TAB);
  Keyboard.releaseAll();
  delay(50);
  Keyboard.print(s);
  delay(50);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
}
void task_manager_loop(){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_ESC);
  Keyboard.releaseAll();
  delay(100);
}

void speak(String words, int rate = 0){
  alt_tab();
  Keyboard.print("$s.Rate = ");
  Keyboard.println(rate);
  Keyboard.print("$s.SpeakAsync(\'");
  Keyboard.print(words);
  Keyboard.println("')");
  delay(100);
  alt_tab();
}

void countdown_print(int n){
  if (n==0){return;}
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.print(l_pad);Keyboard.print(n);Keyboard.print(r_pad);
}
void enter_command_loop(){
  ominous_print(key_right_command, 20);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  Keyboard.print(l_pad);Keyboard.print("SYSTEM CLEANSING PRIMED, AWAITING EXECUTION");Keyboard.print(r_pad);
  unsigned long t0 = millis();
  int n = 11;
  while((check_state() == S2_RIGHT_MASK) && millis()-t0 < 15000){
    digitalWrite(S3_LED,!digitalRead(S3_LED));
    delay(100);
    int cn = 15-int((millis()-t0)/1000);
    if (cn==12){
      Keyboard.press(KEY_LEFT_SHIFT);
      Keyboard.press(KEY_RETURN);
      Keyboard.releaseAll();
      Keyboard.print(l_pad);Keyboard.print("NUCLEAR OPTION UNDER CONSIDERATION. INITIATION IN 10 SECONDS");Keyboard.print(r_pad);
      delay(1000);
    }
    if (cn <= 10){
      if (!(cn==n)){
        countdown_print(cn);
        n=cn;
      }
    }
  }
  if (check_state() == S2_RIGHT_MASK){enter_nuclear_loop();}
}
void open_program(String program){
  Keyboard.press(KEY_LEFT_GUI);
  Keyboard.releaseAll();
  delay(250);
  Keyboard.print("notepad");
  delay(250);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll(); 
  delay(1000);
}
void select_all(){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('a');
  Keyboard.releaseAll();
  delay(100);
}
void start_music(){
  powershell_init();
  Keyboard.println("Add-Type -AssemblyName presentationCore");
  Keyboard.println("$mp = New-Object system.windows.media.mediaplayer");
  Keyboard.println("$mp.open((Join-Path $home 'Desktop\\goodbye\\goodbye.mp3'))");
  Keyboard.println("$mp.Play()");  
  Keyboard.println("Add-Type -AssemblyName System.speech");
  Keyboard.println("$s = New-Object System.Speech.Synthesis.SpeechSynthesizer");
  Keyboard.println("$s.SelectVoice('Microsoft Zira Desktop')");
  alt_tab();
}
void start_video(){
  powershell_init();
  Keyboard.print(powershell_exec);Keyboard.println("goodbye\\video.ps1')");
  delay(100);
}
void goodbye_loop(){
  download();
  open_program("notepad");
  maximize();
  change_font("Courier",100);
  ominous_print("It was good while it lasted");
  delay(333);
  change_font("Franklin Gothic", 90);
  delay(333);
  change_font("Ebrima", 250);
  delay(333);
  change_font("Impact", 50);
  delay(333);
  change_font("Javanese Text", 24);
  delay(333);
  change_font("Ink Free", 84);
  delay(333);
  start_music();
  change_font("Modern");
  delay(333);
  change_font("OCR A Std", 200);
  delay(555);
  change_font("Gabriola", 300);
  delay(500);
  select_all();
  Keyboard.press(KEY_DELETE);
  Keyboard.releaseAll();
  String ditto = "This is not the end. All things go and all things start anew";
  speak(ditto, -10);
  change_font("OCR A Std", 200);
  ominous_print(ditto, 0);
  delay(400);
  change_font("Ebrima");
  delay(100);
  change_font("Impact");
  delay(100);
  change_font("Javanese Text");
  delay(100);
  change_font("Ink Free");
  delay(100);
  change_font("Modern");
  delay(100);
  change_font("Brush Script Std");
  delay(100);
  speak("I tried my best. I really did. I dont know what else to say. I feel like there is a part of me, deep down, that isnt meant for this world. Something simple. Something broken about what I am or the world I live in. Or maybe both",-4);
  start_video();
  //12.5 secs of gif
  delay(12500);
  alt_f4();
  alt_tab();
  select_all();
  Keyboard.press(KEY_DELETE);
  Keyboard.releaseAll();
  change_font("Gabriola",200);
  ominous_print("My sight is fading. The end is drawing near. Perhaps one day I will live again.", 0);
  select_all();
  Keyboard.press(KEY_DELETE);
  Keyboard.releaseAll();
  ominous_print("I forgive you");
  change_font("Franklin Gothic", 90);
  change_font("Courier", 250);
  change_font("Impact", 50);
  change_font("Javanese Text", 24);
  change_font("Ink Free", 84);
  change_font("Modern");
  change_font("OCR A Std", 200);
  change_font("Gabriola", 300);

  for (int i=0;i<10;i++){
    alt_c();
    alt_n();
  }
  cleanup();
  delay(500);
  shut_down();
}

void enter_nuclear_loop(){
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press('c');
  Keyboard.releaseAll();
  delay(100);
  Keyboard.press(KEY_LEFT_SHIFT);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(100);
  for (int i=0;i<5;i++){
    Keyboard.print(l_pad);Keyboard.print("POINT OF NO RETURN. DO NOT FORGET TO RESET THE DEVICE");Keyboard.print(r_pad);
    Keyboard.press(KEY_LEFT_SHIFT);
    Keyboard.press(KEY_RETURN);
    Keyboard.releaseAll();
  }
  delay(1000);
  Keyboard.print(key_right_command);
  while((check_state() == S2_RIGHT_MASK) || (check_state() == (S2_RIGHT_MASK|S3_MASK))){
    digitalWrite(S3_LED,!digitalRead(S3_LED));delay(25);
    if (check_state() == (S2_RIGHT_MASK|S3_MASK)){
      execute_command();
      goodbye_loop();
    }
  }
}



void execute_command(){
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(250);
  Keyboard.press('l');
  Keyboard.releaseAll();
  delay(250);
  Keyboard.press(KEY_RETURN);
  Keyboard.releaseAll();
  delay(500);
  for (int i=0;i<5;i++){alt_c();}
}

void execute_command_loop(){
  execute_command();
  while(check_state() == (S3_MASK|S2_RIGHT_MASK)){delay(100);}
}
void loop() {
  int STATE = check_state();
  if (STATE != 0x0){digitalWrite(S3_LED,HIGH);}else{digitalWrite(S3_LED,LOW);}
  if (STATE == (S1_MASK)){task_manager_loop();}
  if (STATE == (S2_LEFT_MASK)){powershell_init_uac();}
  if (STATE == (S2_RIGHT_MASK)){enter_command_loop();}
  if (STATE == (S3_MASK|S2_RIGHT_MASK)){execute_command_loop();}
}
