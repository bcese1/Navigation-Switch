//*****************************************************************************
// Name: Benjamin Cesero
// Date Due: 11/07/22
// Course: ELEC3371
// Description:
// The program is used to turn on LEDs using the navigation switch.
// Pressing Up, Down, Left, Right, Click will turn on the correct LEDs
// The LEDs on Port E will only be used in this code. Supports Click + Direction
//*****************************************************************************
// Global Varibales
enum state{_idle, up, dn, lt, rt, ck}mystate_t; // Creates a group of elements
void mystate(); // Initializes the function my state
//*****************************************************************************

void main()
{
  RCC_APB2ENR |= 1 << 5;      // GPIOD Clock
  RCC_APB2ENR |= 1 << 3;      // GPIOB Clock
  RCC_APB2ENR |= 1 << 6;      // GPIOE Clock
  RCC_APB2ENR |= 1 << 4;      // GLIOC Clock
  RCC_APB2ENR |= 1 << 2;      // GPIOA Clock
  GPIOE_CRL = 0x33333333;     // Load lower half of GPIOE to output
  GPIOE_CRH = 0x33333333;     // Load higher half of GPIOE to output
  GPIOA_CRL = 0x44444444;     // Load lower half of GPIOA to input
  GPIOA_CRH = 0x44444444;     // Load higher half of GPIOA to input
  GPIOB_CRL = 0x44444444;     // Load lower half of GPIOB to input
  GPIOB_CRH = 0x44444444;     // Load higher half of GPIOB to input
  GPIOC_CRL = 0x44444444;     // Load lower half of GPIOC to input
  GPIOC_CRH = 0x44444444;     // Load higher half of GPIOC to input
  GPIOD_CRL = 0x44444444;     // Load lower half of GPIOD to input
  GPIOD_CRH = 0x44444444;     // Load higher half of GPIOD to input
  mystate_t = _idle;          // Set my state to _idle
  
for(;;)                       // infinite for loop
       {

         
         if(GPIOD_IDR.B4 == 0)        // if B4 on port d is equal to 0 proceed
         {
          mystate_t = up;             // set my mystate_t to enum up
         
         }
         else if(GPIOB_IDR.B5 == 0)   // if B5 on port b is equal to 0 proceed
         {
          mystate_t = dn;             // set my mystate_t to enum dn
         }
         else if(GPIOD_IDR.B2 == 0)   // if B2 on port d is equal to 0 proceed
         {
          mystate_t = lt;             // set my mystate_t to enum lt
         }
         else if(GPIOA_IDR.B6 == 0)   // if B6 on port a is eqaul to 0 proceed
         {
          mystate_t = rt;             // set my mystate_t to enum rt
         }
         else if(GPIOC_IDR.B13 == 0)  // if B13 on port c is equal to 0 proceed
         {
          mystate_t = ck;             // set mystate_t to enum ck
         }
         else                         // if none of above if are true do else
         {
          mystate_t = _idle;         // set mystate_t to enum _idle
         }
         
         
         mystate();                 // calls mystate
         
       }
}

void mystate()
     {
      switch(mystate_t)           // switch case for state machine
         {
          case _idle:
               // keep all lights on port e off
               GPIOE_ODR = 0x0000;
               break;
          case up:
               // turning on PE11 & PE15
               GPIOE_ODR |= 0x8800;
               break;
          case dn:
               // turning on PE8 & PE12
               GPIOE_ODR |= 0x1100;
               break;
          case lt:
               // turning on PE13 & PE14
               GPIOE_ODR |= 0x6000;
               break;
          case rt:
               // turning on PE9 & PE10
               GPIOE_ODR |= 0x0600;
               break;
          case ck:
               // turning on PE9 & PE14
               GPIOE_ODR |= 0x4200;
               break;

          default:
               // if any error is detected turn on all the lights
               GPIOE_ODR = 0xFFFF;
               break;
         }
     
     
     
     }