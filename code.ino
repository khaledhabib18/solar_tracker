// Define L298N control pins for horizontal (Azimuth) motor
#define IN1_H 9
#define IN2_H 10
#define IN3_H 11
#define IN4_H 12

// Define L298N control pins for vertical (Tilt) motor
#define IN1_V 3
#define IN2_V 4
#define IN3_V 5
#define IN4_V 6

// Define LDR pin connections
#define LDR_TOP_LEFT     A0 // Top left
#define LDR_TOP_RIGHT    A3 // Top right
#define LDR_BOTTOM_LEFT  A1 // Bottom left
#define LDR_BOTTOM_RIGHT A2 // Bottom right

// Define limit switch pins
#define LIMIT_TOP    7   // Top limit switch
#define LIMIT_BOTTOM 8   // Bottom limit switch
#define LIMIT_LEFT   13  // Left limit switch
#define LIMIT_RIGHT  2   // Right limit switch

// Settings
#define TOLERANCE   200 // Sensitivity to light difference
#define DELAY_TIME  5   // Delay between motor steps (ms)

// Stepper motor sequence (4-step full drive)
const int STEP_SEQUENCE[4][4] = {
    {HIGH, LOW,  HIGH, LOW},  // Step 1
    {LOW,  HIGH, HIGH, LOW},  // Step 2
    {LOW,  HIGH, LOW,  HIGH}, // Step 3
    {HIGH, LOW,  LOW,  HIGH}  // Step 4
};

void setup() {
    // Configure motor control pins as outputs
    pinMode(IN1_H, OUTPUT);
    pinMode(IN2_H, OUTPUT);
    pinMode(IN3_H, OUTPUT);
    pinMode(IN4_H, OUTPUT);
    pinMode(IN1_V, OUTPUT);
    pinMode(IN2_V, OUTPUT);
    pinMode(IN3_V, OUTPUT);
    pinMode(IN4_V, OUTPUT);

    // Configure limit switch pins as inputs with pull-up resistors
    pinMode(LIMIT_TOP, INPUT_PULLUP);
    pinMode(LIMIT_BOTTOM, INPUT_PULLUP);
    pinMode(LIMIT_LEFT, INPUT_PULLUP);
    pinMode(LIMIT_RIGHT, INPUT_PULLUP);

    // Initialize serial communication
    Serial.begin(9600);
}

void loop() {
    // Read LDR values
    int ldrTopLeft     = analogRead(LDR_TOP_LEFT);
    int ldrTopRight    = analogRead(LDR_TOP_RIGHT);
    int ldrBottomLeft  = analogRead(LDR_BOTTOM_LEFT);
    int ldrBottomRight = analogRead(LDR_BOTTOM_RIGHT);

    // Display LDR values for debugging
    Serial.print(ldrTopLeft); Serial.print("   ");
    Serial.print(ldrTopRight); Serial.print("   ");
    Serial.print(ldrBottomLeft); Serial.print("   ");
    Serial.println(ldrBottomRight);

    // Calculate average LDR values and differences
    int avgTop    = (ldrTopLeft + ldrTopRight) / 2;
    int avgBottom = (ldrBottomLeft + ldrBottomRight) / 2;
    int avgLeft   = (ldrTopLeft + ldrBottomLeft) / 2;
    int avgRight  = (ldrTopRight + ldrBottomRight) / 2;

    int diffVertical = avgTop - avgBottom;  // Vertical light difference
    int diffHorizontal = avgLeft - avgRight; // Horizontal light difference

    // Control vertical (Tilt) motor
    if (abs(diffVertical) > TOLERANCE) {
        if (diffVertical > 0 && digitalRead(LIMIT_TOP) == HIGH) {
            moveMotor(IN1_V, IN2_V, IN3_V, IN4_V, 1, 1); // Move up
        } else if (diffVertical < 0 && digitalRead(LIMIT_BOTTOM) == HIGH) {
            moveMotor(IN1_V, IN2_V, IN3_V, IN4_V, -1, 1); // Move down
        }
    }

    // Control horizontal (Azimuth) motor
    if (abs(diffHorizontal) > TOLERANCE) {
        if (diffHorizontal > 0 && digitalRead(LIMIT_LEFT) == HIGH) {
            moveMotor(IN1_H, IN2_H, IN3_H, IN4_H, -1, 1); // Move left
        } else if (diffHorizontal < 0 && digitalRead(LIMIT_RIGHT) == HIGH) {
            moveMotor(IN1_H, IN2_H, IN3_H, IN4_H, 1, 1); // Move right
        }
    }

    // Add delay to stabilize readings
    delay(DELAY_TIME);
}

// Function to move the stepper motor
void moveMotor(int pin1, int pin2, int pin3, int pin4, int direction, int steps) {
    for (int step = 0; step < steps; step++) {
        for (int i = 0; i < 4; i++) {
            int stepIndex = (direction > 0) ? i : (3 - i); // Determine step sequence based on direction

            digitalWrite(pin1, STEP_SEQUENCE[stepIndex][0]);
            digitalWrite(pin2, STEP_SEQUENCE[stepIndex][1]);
            digitalWrite(pin3, STEP_SEQUENCE[stepIndex][2]);
            digitalWrite(pin4, STEP_SEQUENCE[stepIndex][3]);

            delay(5);  // Adjust for smoother motor motion
        }
    }
}
