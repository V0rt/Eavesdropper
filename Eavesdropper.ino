#define DEBUG

void setup()
{
	module_Init();
	Serial.begin(115200);
	
	Serial.println("Hello");
	
	CYRF_Select();
	CYRF_Reset();
	//RssiInit();
}

void loop() {	
	CheckUart();
	CYRF_Loop();
}