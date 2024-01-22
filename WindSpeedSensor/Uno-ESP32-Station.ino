#include <SoftwareSerial.h>
#define analogPinForRV  0
#define analogPinForTMP 1

#define analogPinForRV_2  2
#define analogPinForTMP_2 3

SoftwareSerial soft(2,3); // 2: RX, 3:TX

// variables
const float zeroWindAdjustment =  .2;

int TMP_Therm_ADunits;  //temp termistor value from wind sensor
float RV_Wind_ADunits;    //RV output from wind sensor 
float RV_Wind_Volts;
unsigned long lastMillis;
int TempCtimes100;
float zeroWind_ADunits;
float zeroWind_volts;
float WindSpeed_MPH;

// second wind sensor
int TMP_Therm_ADunits_2;
float RV_Wind_ADunits_2;
float RV_Wind_Volts_2;
int TempCtimes100_2;
float zeroWind_ADunits_2;
float zeroWind_volts_2;
float WindSpeed_MPH_2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  soft.begin(9600);
  Serial.println("Start");
}

void loop(){
  if (millis() - lastMillis > 200){      // read every 200 ms - printing slows this down further
    
    TMP_Therm_ADunits = analogRead(analogPinForTMP);
    RV_Wind_ADunits = analogRead(analogPinForRV);
    RV_Wind_Volts = (RV_Wind_ADunits *  0.0048828125);
    TempCtimes100 = ((0.005 *((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits)) - (16.862 * (float)TMP_Therm_ADunits) + 9075.4)/100;
    zeroWind_ADunits = -0.0006*((float)TMP_Therm_ADunits * (float)TMP_Therm_ADunits) + 1.0727 * (float)TMP_Therm_ADunits + 47.172;  //  13.0C  553  482.39
    zeroWind_volts = (zeroWind_ADunits * 0.0048828125) - zeroWindAdjustment; 
    WindSpeed_MPH =  pow(((RV_Wind_Volts - zeroWind_volts) /.2300) , 2.7265);

    // Second wind sensor
    TMP_Therm_ADunits_2 = analogRead(analogPinForTMP_2);
    RV_Wind_ADunits_2 = analogRead(analogPinForRV_2);
    RV_Wind_Volts_2 = (RV_Wind_ADunits_2 *  0.0048828125);
    TempCtimes100_2 = ((0.005 *((float)TMP_Therm_ADunits_2 * (float)TMP_Therm_ADunits_2)) - (16.862 * (float)TMP_Therm_ADunits_2) + 9075.4)/100;
    zeroWind_ADunits_2 = -0.0006*((float)TMP_Therm_ADunits_2 * (float)TMP_Therm_ADunits_2) + 1.0727 * (float)TMP_Therm_ADunits_2 + 47.172;  //  13.0C  553  482.39
    zeroWind_volts_2 = (zeroWind_ADunits_2 * 0.0048828125) - zeroWindAdjustment;  
    WindSpeed_MPH_2 =  pow(((RV_Wind_Volts_2 - zeroWind_volts_2) /.2300) , 2.7265);   

    Serial.print("Wind Sensor 1: ");
    Serial.print("  TMP volts ");
    Serial.print(TMP_Therm_ADunits * 0.0048828125);
    
    Serial.print(" RV volts ");
    Serial.print((float)RV_Wind_Volts);

    Serial.print("\t  TempC*100 ");
    Serial.print(TempCtimes100 );

    Serial.print("   ZeroWind volts ");
    Serial.print(zeroWind_volts);

    Serial.print("   WindSpeed MPH ");
    Serial.print((float)WindSpeed_MPH);

    Serial.print("   WindSpeed M/S ");
    Serial.print((float)(WindSpeed_MPH)*0.44704);
    Serial.println("M/S");

        // Second wind sensor
    Serial.print("Wind Sensor 2: ");
    Serial.print("  TMP volts ");
    Serial.print(TMP_Therm_ADunits_2 * 0.0048828125);
    
    Serial.print(" RV volts ");
    Serial.print((float)RV_Wind_Volts_2);

    Serial.print("\t  TempC*100 ");
    Serial.print(TempCtimes100_2 );

    Serial.print("   ZeroWind volts ");
    Serial.print(zeroWind_volts_2);

    Serial.print("   WindSpeed MPH ");
    Serial.print((float)WindSpeed_MPH_2);

    Serial.print("   WindSpeed M/S ");
    Serial.print((float)(WindSpeed_MPH_2)*0.44704);
    Serial.println("M/S");
    Serial.println("-------------------------------------------------------------------------------------------------------------------------------------------");

    // 데이터를 ESP32로 전송
    // soft.println("Sensor 1: TMP_volts: " + String(TMP_Therm_ADunits * 0.0048828125) +
    //                       ", RV_volts: " + String((float)RV_Wind_Volts) +
    //                       ", TempC*100: " + String(TempCtimes100) +
    //                       ", ZeroWind_volts:" + String(zeroWind_volts) +
    //                       ", WindSpeed_MPH: " + String((float)WindSpeed_MPH) +
    //                       ", WindSpeed_M/S: " + String((float)(WindSpeed_MPH)*0.44704)+
    //               "Sensor 2: TMP_volts: " + String(TMP_Therm_ADunits_2 * 0.0048828125) +
    //                       ", RV_volts: " + String((float)RV_Wind_Volts_2) +
    //                       ", TempC*100: " + String(TempCtimes100_2) +
    //                       ", ZeroWind_volts:" + String(zeroWind_volts_2) +
    //                       ", WindSpeed_MPH: " + String((float)WindSpeed_MPH_2) +
    //                       ", WindSpeed_M/S: " + String((float)(WindSpeed_MPH_2)*0.44704));

    soft.println("Sensor 1: "+String((float)(WindSpeed_MPH)*0.44704)+" , Sensor 2: "+String((float)(WindSpeed_MPH_2)*0.44704));

    lastMillis = millis();
  }

  delay(1000);
}
