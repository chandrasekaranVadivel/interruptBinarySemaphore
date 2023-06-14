#include<stdlib.h>
#include<string.h>
#include <Arduino_FreeRTOS.h>
#include <semphr.h>  // add the FreeRTOS functions for Semaphores (or Flags).
TaskHandle_t *task1_h,*task2_h;
SemaphoreHandle_t xSemaphore1;
void task1(void *pvParameters)
{
  while(1)
  {
  }
}
void task2(void *pvParameters)
{
  while(1)
  {
    if(xSemaphoreTake(xSemaphore1,portMAX_DELAY)==pdPASS)
    {
    digitalWrite(LED_BUILTIN,HIGH);
    vTaskDelay(pdMS_TO_TICKS(100));
    digitalWrite(LED_BUILTIN,LOW);
    vTaskDelay(pdMS_TO_TICKS(100));
    }
  }
}
void interruptHandler()
{
  xSemaphoreGiveFromISR(xSemaphore1,NULL);
  Serial.print("hi");
}
void setup() 
{
  Serial.begin(9600);
  pinMode(2,INPUT_PULLUP);
  pinMode(LED_BUILTIN,OUTPUT);
  xTaskCreate(task1,"task1",127,NULL,1,task1_h);
  xTaskCreate(task2,"task2",127,NULL,1,task2_h);
  xSemaphore1 = xSemaphoreCreateBinary();
  if (xSemaphore1 != NULL) {
    // Attach interrupt for Arduino digital pin
    attachInterrupt(digitalPinToInterrupt(2), interruptHandler, LOW);
  }
}

void loop() {
  // put your main code here, to run repeatedly:

}
