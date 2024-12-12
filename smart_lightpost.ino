#define PIR_SENSOR_PIN 23  // GPIO for PIR sensor (SR505)
#define LED_PIN 27         // GPIO for LED
#define LDR_PIN 34         // GPIO for LDR module (analog input pin)

int ldrThreshold = 800;  // Define a threshold for the LDR to detect low light (adjust as needed)

int ledBrightness = 0;  // Variable to store LED brightness (0 to 255)

void setup() {
  pinMode(PIR_SENSOR_PIN, INPUT);  // Set PIR sensor pin as input
  pinMode(LED_PIN, OUTPUT);        // Set LED pin as output
  Serial.begin(115200);            // Initialize serial communication
  Serial.println("PIR Sensor with LDR and LED Test");
}

void loop() {
  int motionDetected = digitalRead(PIR_SENSOR_PIN);  // Read PIR sensor state
  int ldrValue = analogRead(LDR_PIN);  // Read LDR value (light intensity)

  // Print the LDR value for debugging
  Serial.print("LDR Value: ");
  Serial.println(ldrValue);

  // Check if it's dark (LDR value is below the threshold) and if motion is detected
  if (ldrValue < ldrThreshold) {  // If it's dark (low light level)
    if (motionDetected == HIGH) {  // Motion detected
      Serial.println("Motion Detected! LED FULL BRIGHTNESS");
      ledBrightness = 255;  // Full brightness when motion is detected
    } else {  // No motion
      Serial.println("No Motion. LED DIM");
      ledBrightness = 10;  // Dim the LED when no motion is detected
    }
  } else {  // It's bright (no need for motion detection or LED)
    Serial.println("It's bright, LED OFF");
    ledBrightness = 0;  // Turn off LED in bright light
  }

  // Apply the PWM brightness to the LED using analogWrite
  analogWrite(LED_PIN, ledBrightness);

  delay(100);  // Small delay to stabilize readings
}
