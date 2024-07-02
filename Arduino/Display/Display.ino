constexpr int PIN_A = 13;
constexpr int PIN_B = 12;
constexpr int PIN_C = 11;
constexpr int PIN_D = 10;
constexpr int PIN_E = 9;
constexpr int PIN_F = 8;
constexpr int PIN_G = 7;
constexpr int PIN_DP = 6;

void setup()
{
	// Sets each output pin
	for (int i = 6; i <= 13; i++)
	{
		pinMode(i, OUTPUT);
	}
}

void loop()
{
	// 97.1
	display(1, 1, 1, 0, 0, 1, 1, 0);
	delay(1000);

	display(1, 1, 1, 0, 0, 0, 0, 1);
	delay(1000);

	display(0, 1, 1, 0, 0, 0, 0, 0);
	delay(1000);

	clearDisplay();
	delay(1000);
}

/**
 * @brief Writes each pin to LOW / 0.
 */
void clearDisplay()
{
	for (int i = 6; i <= 13; i++)
	{
		digitalWrite(i, LOW);
	}
}

/**
 * @brief Writes the inputted states to the display.
 *
 * @param state HIGH or LOW / 1 or 0 for each segment of the display.
 */
void display(int a_state, int b_state, int c_state, int d_state, int e_state, int f_state, int g_state, int dp_state)
{
	digitalWrite(PIN_A, a_state);
	digitalWrite(PIN_B, b_state);
	digitalWrite(PIN_C, c_state);
	digitalWrite(PIN_D, d_state);
	digitalWrite(PIN_E, e_state);
	digitalWrite(PIN_F, f_state);
	digitalWrite(PIN_G, g_state);
	digitalWrite(PIN_DP, dp_state);
}