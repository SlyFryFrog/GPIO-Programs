#include <DHT.h>
#include <DHT_U.h>
#include <SevSeg.h>

#define DHT11_PIN 13

DHT dht11(DHT11_PIN, DHT11);
SevSeg sevseg; // Initiate a seven segment controller object

constexpr long DISPLAY_DELAY = 5000;
bool displayHumidity = true;


void setup()
{
	byte numDigits = 4;
	byte digitPins[] = {17, 16, 15, 14};
	byte segmentPins[] = {12, 11, 10, 9, 8, 7, 6, 5};
	bool resistorsOnSegments = 1;
	sevseg.begin(COMMON_CATHODE, numDigits, digitPins, segmentPins, resistorsOnSegments);
	sevseg.setBrightness(90);
	Serial.begin(9600);
	dht11.begin(); // Initialize the sensor
	get_info(displayHumidity);
}

void loop()
{
	static unsigned long lastDisplayTime = 0;

	unsigned long currentTime = millis();

	if (currentTime - lastDisplayTime >= DISPLAY_DELAY)
	{
		lastDisplayTime = currentTime;
		get_info(displayHumidity);
	}

	sevseg.refreshDisplay(); // Must run repeatedly
}

void get_info(bool &displayHumidity)
{
	float humi = dht11.readHumidity();
	float tempC = dht11.readTemperature();

	if (isnan(humi) || isnan(tempC))
	{
		Serial.println("Failed to read from DHT11 sensor!");
	}
	else
	{
		long valueWhole;
		int valueDecimalPos;

		if (displayHumidity)
		{
			convertValues(humi, valueWhole, valueDecimalPos);
			Serial.print("Humidity: ");
			Serial.print(humi);
			Serial.print("% | ");
			displayHumidity = false;
		}
		else
		{
			convertValues(tempC, valueWhole, valueDecimalPos);
			Serial.print("Temperature: ");
			Serial.print(tempC);
			Serial.println("C");
			displayHumidity = true;
		}

		sevseg.setNumber(valueWhole, valueDecimalPos);
	}
}

void convertValues(const float value, long &wholeNumber, int &decimalPos)
{
	String valueStr = String(value);
	decimalPos = valueStr.indexOf('.') == -1 ? 0 : valueStr.length() - valueStr.indexOf('.') - 1;
	wholeNumber = value * pow(10, decimalPos);
}
