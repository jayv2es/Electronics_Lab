/* Author:      vojoel
 * Date:        29 Nov 2021
 * Description: Program to measure temperature with temperature sensor and output on LCD
 */

#include <Wire.h>
#include <rgb_lcd.h>
#include <math.h>

rgb_lcd lcd;
const float R0 = 100000;    // Resistance at T0 (in Ohm)
const float B = 4275;       // B-value in [4250K, 4299K]
const float T0 = 298.15;    // Room temperature 25°C

float threshold;            // Threshold above which LCD turns red
float T_lower = 295;        // Lowest possible threshold in K (with potentiometer)
float T_upper = 315;        // Highest possible threshold in K (with potentiometer)
float V_meas;
float T;
float R;
bool state = 0;             // To save whether T above (1) Threshold or below (0)
 
void setup()
{
    lcd.begin(16,2);
    lcd.print("T / Threshold");
    Serial.begin(9600);    
}
 
void loop()
{
    V_meas=analogRead(0);
 
    // Make Calculations (using eqs 8 and 9 in manual)
    R = (1023/V_meas - 1)*R0;
    T = 1/(log(R/R0)/B + 1/T0);

    // Converts angle of potentiometer to threshold temperature in [295K, 315K]
    threshold = analogRead(1);
    threshold = map(threshold, 0, 1023, T_lower, T_upper);

    // Output data
    lcd.setCursor(0,1);     // Reset LCD
    lcd.print(T);           // Print T and Threshold to LCD
    lcd.print(" / ");
    lcd.print(threshold);
    Serial.print(T);        // Print T and state to Serial
    Serial.print(" ");
    Serial.println(state);
    
    // Sets LCD to red if T above threshold
    if(T > threshold) {
      lcd.setRGB(255,0,0);
      state = 1;
    }

    // Resets LCD to blue if T falls below threshold again
    if(state == 1 and T < threshold){
      lcd.setRGB(0,0,255);
      state = 0;
    }    

    // Wait 1s
    delay(1000);
}
