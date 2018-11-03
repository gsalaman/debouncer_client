#include "debouncer.h"

#define BUTTON_PIN 10

Debouncer debounceButton(BUTTON_PIN);

bool sw_debounce=false;
bool verbose_mode=false;

void print_help( void )
{
  Serial.print("d toggles sw debounce - Currently ");
  if (sw_debounce)
  {
    Serial.println("ON");
  }
  else
  {
    Serial.println("OFF");
  }
  Serial.print("v toggles sw debounce verbose mode - Currenlty ");
  if (verbose_mode)
  {
    Serial.println("ON");
  }
  else
  {
    Serial.println("OFF");
  }
  
}  //  end of print_help

void process_command( void )
{
  char c;

  c = Serial.read();

  switch (c)
  {
    case 'd':
    case 'D':
      sw_debounce = !sw_debounce;
      Serial.print("SW Debounce now ");
      if (sw_debounce)
      {
        Serial.println("ON");
      }
      else
      {
        Serial.println("OFF");
      }
    break;

    case 'v':
    case 'V':
      verbose_mode = !verbose_mode;

      debounceButton.debug(verbose_mode);
      
      Serial.print("Verbose mode now ");
      if (verbose_mode)
      {
        Serial.println("ON");
      }
      else
      {
        Serial.println("OFF");
      } 
    break;

    case '\n':
      // do nothing
    break;
    
    default:
      Serial.println("Unrecognized command");
      print_help();    
  }
}

void setup() 
{
  Serial.begin(9600);
  pinMode(BUTTON_PIN, INPUT_PULLUP);

  Serial.println("Debounce Framework initialized");
  print_help();
}

void loop() 
{
  static int last_button_state = HIGH;
  int current_button_state;
  static int presses=0;

  if (sw_debounce)
  {
    current_button_state = debounceButton.read();
  }
  else
  {
    current_button_state = digitalRead(BUTTON_PIN);
  }
  
  if (current_button_state != last_button_state)
  {
    presses++;
    Serial.print("Button now ");
    Serial.print(current_button_state);
    Serial.print(" presses: ");
    Serial.print(presses);
    Serial.print(" Bounces: ");
    Serial.println(debounceButton.getNumBounces());

    last_button_state = current_button_state;
  }

  while (Serial.available())
  {
    process_command();
  }
}
