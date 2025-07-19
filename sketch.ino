// Define Pins
const int LM35_PIN = 34;
const int HEATER_LED_PIN = 17;
const int STATUS_LED_PIN = 16;
const int BUZZER_PIN = 18;

// Define Temperature Thresholds
const float HEATING_THRESHOLD = 25.0;
const float TARGET_TEMPERATURE = 30.0;
const float STABILIZE_LOWER = 29.0;
const float STABILIZE_UPPER = 31.0;
const float OVERHEAT_THRESHOLD = 35.0;

enum HeaterState {
    IDLE,
    HEATING,
    STABILIZING,
    TARGET_REACHED,
    OVERHEAT
};

HeaterState currentState = IDLE;

unsigned long previousMillis = 0;
const long interval = 2000;

unsigned long buzzerOnMillis = 0;
const long buzzerDuration = 1000;

void setup() {
    Serial.begin(115200);
    Serial.println("Heater Control System Starting...");

    pinMode(HEATER_LED_PIN, OUTPUT);
    pinMode(STATUS_LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);

    digitalWrite(HEATER_LED_PIN, LOW);
    digitalWrite(STATUS_LED_PIN, LOW);
    digitalWrite(BUZZER_PIN, LOW);
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        previousMillis = currentMillis;

        int analogValue = analogRead(LM35_PIN);
        float voltage = analogValue * (3.3 / 4095.0);
        float temperatureC = voltage * 100.0;

        Serial.print("Temperature: ");
        Serial.print(temperatureC);
        Serial.print(" °C | Current State: ");

        switch (currentState) {
            case IDLE:
                Serial.println("IDLE");
                digitalWrite(HEATER_LED_PIN, LOW);
                digitalWrite(STATUS_LED_PIN, HIGH);
                digitalWrite(BUZZER_PIN, LOW);
                if (temperatureC < HEATING_THRESHOLD) currentState = HEATING;
                break;

            case HEATING:
                Serial.println("HEATING");
                digitalWrite(HEATER_LED_PIN, HIGH);
                digitalWrite(STATUS_LED_PIN, LOW);
                digitalWrite(BUZZER_PIN, LOW);
                if (temperatureC >= TARGET_TEMPERATURE) currentState = STABILIZING;
                if (temperatureC >= OVERHEAT_THRESHOLD) currentState = OVERHEAT;
                break;

            case STABILIZING:
                Serial.println("STABILIZING");
                digitalWrite(HEATER_LED_PIN, LOW);
                digitalWrite(STATUS_LED_PIN, LOW);
                digitalWrite(BUZZER_PIN, LOW);
                if (temperatureC < STABILIZE_LOWER) currentState = HEATING;
                else if (temperatureC <= STABILIZE_UPPER) currentState = TARGET_REACHED;
                if (temperatureC >= OVERHEAT_THRESHOLD) currentState = OVERHEAT;
                break;

            case TARGET_REACHED:
                Serial.println("TARGET_REACHED");
                digitalWrite(HEATER_LED_PIN, LOW);
                digitalWrite(STATUS_LED_PIN, HIGH);
                digitalWrite(BUZZER_PIN, LOW);
                if (temperatureC < HEATING_THRESHOLD) currentState = HEATING;
                if (temperatureC >= OVERHEAT_THRESHOLD) currentState = OVERHEAT;
                break;

            case OVERHEAT:
                Serial.println("OVERHEAT!!!");
                digitalWrite(HEATER_LED_PIN, LOW);
                digitalWrite(STATUS_LED_PIN, LOW);
                if (digitalRead(BUZZER_PIN) == LOW) {
                    digitalWrite(BUZZER_PIN, HIGH);
                    buzzerOnMillis = currentMillis;
                } else if (currentMillis - buzzerOnMillis >= buzzerDuration) {
                    digitalWrite(BUZZER_PIN, LOW);
                }
                if (temperatureC < (OVERHEAT_THRESHOLD - 5.0)) {
                    currentState = IDLE;
                    digitalWrite(BUZZER_PIN, LOW);
                }
                break;
        }

        Serial.print("Heater Status: ");
        Serial.println(digitalRead(HEATER_LED_PIN) ? "ON" : "OFF");
        Serial.println("--------------------");
    }
}
