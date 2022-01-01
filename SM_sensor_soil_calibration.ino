#include <ArduinoSort.h>
#include <movingAvg.h>

#define kMOVING_AVG_FRAME_SIZE 10
movingAvg movingAverage(10);
int counter = 0;
String ch = "";
int VWC = 0;

int readings1[10];      // the readings from the analog input
int readings2[10];
int readings3[10];
int readings4[10];
int total1 = 0;                  // the running total
int total2 = 0;
int total3 = 0;
int total4 = 0;
int avgVal1 = 0;
int avgVal2 = 0;
int avgVal3 = 0;
int avgVal4 = 0;
int sensor1,sensor2,sensor3,sensor4;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  Serial.println("CLEARDATA");
  //analogReference(INTERNAL);
  //Serial.println("LABEL,Time,Timmer,VWC,OT1,OT2,OT3,OT4");
  //Serial.print("DATA,TIME,TIMER");
  //Serial.println("RESETTIMER"); //resets timer to 0
}

void loop() {

  static int filter_len,temp0[20],temp1[20],temp2[20],temp3[20],i,j;
  static int temp_filter[20];
  

  for (int readIndex = 0; readIndex < 10; readIndex++)
  {
    // read from the sensor:
    (void) analogRead(A0);
    readings1[readIndex] = analogRead(A0);
    (void) analogRead(A1);
    readings2[readIndex] = analogRead(A1);
    (void) analogRead(A2);
    readings3[readIndex] = analogRead(A2);
    (void) analogRead(A3);
    readings4[readIndex] = analogRead(A3);
    delay(100);
  }

  sortArray(readings1, 10);
  sortArray(readings2, 10);
  sortArray(readings3, 10);
  sortArray(readings4, 10);

  Serial.print("Median Filtered: ");
  Serial.print(readings1[5]);
  Serial.print(",");
  Serial.print(readings2[5]);
  Serial.print(",");
  Serial.print(readings3[5]);
  Serial.print(",");
  Serial.print(readings4[5]);
  Serial.println(",");

    if(filter_len < kMOVING_AVG_FRAME_SIZE)
    {
        temp0[filter_len] =  readings1[5];   /* store the raw data in the array from 0 to max size of array */
        temp1[filter_len] =  readings2[5];   /* store the raw data in the array from 0 to max size of array */
        temp2[filter_len] =  readings3[5];   /* store the raw data in the array from 0 to max size of array */
        temp3[filter_len] =  readings4[5];   /* store the raw data in the array from 0 to max size of array */    
        filter_len++;
        Serial.print("my data");
        
    }
    
    else
    {
      temp0[kMOVING_AVG_FRAME_SIZE - 1] =  readings1[5];  /* store the data to the last position of the frame size */
      temp1[kMOVING_AVG_FRAME_SIZE - 1] =  readings2[5];  /* store the data to the last position of the frame size */
      temp2[kMOVING_AVG_FRAME_SIZE - 1] =  readings3[5];  /* store the data to the last position of the frame size */
      temp3[kMOVING_AVG_FRAME_SIZE - 1] =  readings4[5];  /* store the data to the last position of the frame size */
      
      for(j=0; j< (kMOVING_AVG_FRAME_SIZE-1); j++) /* start from 0 to max size of the frame - 2 beacuse its start from 0 and we just want tostore data here less tahan max size */   
      {
        temp0[j] = temp0[j+1];                   /* store the value of the next location of array into the current location */
        temp_filter[0]+= temp0[j];
        //_sConfig_And_Runnig.ADC_Filter_Data[0] += temp_0[j];         /* add the data to the respected location for of the filter array */    
        
        temp1[j] = temp1[j+1];                   /* store the value of the next location of array into the current location */
        temp_filter[1]+= temp1[j];
        //_sConfig_And_Runnig.ADC_Filter_Data[1] += temp_1[j];         /* add the data to the respected location for of the filter array */   
        
        temp2[j] = temp2[j+1];                   /* store the value of the next location of array into the current location */
        temp_filter[2]+= temp2[j];

        temp3[j] = temp3[j+1];
        temp_filter[3]+= temp3[j];
        //_sConfig_And_Runnig.ADC_Filter_Data[2] += temp_2[j];         /* add the data to the respected location for of the filter array */ 
      }

      temp_filter[0] += temp0[kMOVING_AVG_FRAME_SIZE - 1];
      temp_filter[1] += temp1[kMOVING_AVG_FRAME_SIZE - 1];
      temp_filter[2] += temp2[kMOVING_AVG_FRAME_SIZE - 1];
      temp_filter[3] += temp3[kMOVING_AVG_FRAME_SIZE - 1];

      avgVal1 = temp_filter[0]/kMOVING_AVG_FRAME_SIZE;
      avgVal2 = temp_filter[1]/kMOVING_AVG_FRAME_SIZE;
      avgVal3 = temp_filter[2]/kMOVING_AVG_FRAME_SIZE;
      avgVal4 = temp_filter[3]/kMOVING_AVG_FRAME_SIZE;

      temp_filter[0] = 0;
      temp_filter[1] = 0;
      temp_filter[2] = 0;
      temp_filter[3] = 0;
                   
    }     

  Serial.print(avgVal1);
  Serial.print(" ");
//  Serial.print(avg1);
  Serial.print(",");
  Serial.print(avgVal2);
  Serial.print(" ");
  //Serial.print(avg2);
  Serial.print(",");
  Serial.print(avgVal3);
  Serial.print(" ");
  //Serial.print(avg3);
  Serial.print(",");
  Serial.print(avgVal4);
  Serial.println(" ");
  //Serial.println(avg4);
  delay(100);
}


void sort_array(int *buff, int len)
{
  sortArray(buff, 10);
  sortArray(readings2, 10);
  sortArray(readings3, 10);
  sortArray(readings4, 10);
  
}
