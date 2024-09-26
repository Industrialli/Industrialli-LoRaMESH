#include <Arduino.h>
#include <LoRaMESH.h>

HardwareSerial lora_serial(PA5, PA4);
LoRaMESH lora(&lora_serial);

bool symbols[][7] = {
    {0, 0, 0, 0, 0, 0, 1}, // 0
    {1, 0, 0, 1, 1, 1, 1}, // 1
    {0, 0, 1, 0, 0, 1, 0}, // 2
    {0, 0, 0, 0, 1, 1, 0}, // 3
    {1, 0, 0, 1, 1, 0, 0}, // 4
    {0, 1, 0, 0, 1, 0, 0}, // 5
    {0, 1, 0, 0, 0, 0, 0}, // 6
    {0, 0, 0, 1, 1, 1, 1}, // 7
    {0, 0, 0, 0, 0, 0, 0}, // 8
    {0, 0, 0, 0, 1, 0, 0}, // 9
    {0, 0, 0, 0, 1, 0, 0}, // A
    {0, 1, 1, 1, 1, 0, 0}, // b
    {0, 1, 1, 0, 0, 0, 1}, // C
    {0, 0, 1, 0, 1, 1, 0}, // d
    {0, 1, 1, 0, 0, 0, 0}, // E
    {0, 1, 1, 1, 0, 0, 0}, // F
	{1, 0, 0, 0, 0, 0, 1}, // U
    {1, 1, 1, 1, 1, 1, 0}, // -
    {1, 1, 1, 1, 1, 1, 1}, // (espaço)
    {0, 0, 0, 0, 1, 1, 0}, // =
    {0, 0, 0, 0, 0, 1, 0}  // _
};


uint32_t pin[7] = {PB15, PA10, PA12, PA11, PB14, PC7, PB13};

void setup(){
	lora_serial.begin(9600);

	lora.begin(true);
	lora.setnetworkId((uint16_t)3);
	lora.config_bps(BW500, SF_LoRa_7, CR4_5);
	lora.config_class(LoRa_CLASS_C, LoRa_WINDOW_15s);
	lora.setpassword(222);

    pinMode(PB15, OUTPUT); //A
	pinMode(PA10, OUTPUT); //B
	pinMode(PA12, OUTPUT); //C
	pinMode(PA11, OUTPUT); //D
	pinMode(PB14, OUTPUT); //E
	pinMode(PC7, OUTPUT);  //F
	pinMode(PB13, OUTPUT); //G

	pinMode(PB2, OUTPUT);  //DIG01
	pinMode(PB10, OUTPUT); //DIG02
	pinMode(PB11, OUTPUT); //DIG03

	digitalWrite(PB2, HIGH);
	digitalWrite(PB10, HIGH);
	digitalWrite(PB11, HIGH);
}

void clear_display(){
	for (size_t i = 0; i < 7; i++){
		digitalWrite(pin[i], HIGH);
	}
}

void show_display(uint8_t digit_1, uint8_t digit_2, uint8_t digit_3){
	for (size_t i = 0; i < 7; i++){
		digitalWrite(pin[i], symbols[digit_1][i]);
	}
	digitalWrite(PB2, LOW);
	delayMicroseconds(2000);
	digitalWrite(PB2, HIGH);

	for (size_t i = 0; i < 7; i++){
		digitalWrite(pin[i], symbols[digit_2][i]);
	}
	digitalWrite(PB10, LOW);
	delayMicroseconds(2000);
	digitalWrite(PB10, HIGH);

	
	for (size_t i = 0; i < 7; i++){
		digitalWrite(pin[i], symbols[digit_3][i]);
	}
	digitalWrite(PB11, LOW);
	delayMicroseconds(2000);
	digitalWrite(PB11, HIGH);
}


void loop(){
	uint32_t start_time;
	uint8_t digit_1; 
	uint8_t digit_2; 
	uint8_t digit_3; 
	
	start_time = micros();
	while(true){
		if(micros() - start_time > 500000){
			break;
		}
		
		digit_1 = lora.localId / 10;
		digit_2 = lora.localId % 10;

		show_display(digit_1, digit_2, 16);
	}
	
	start_time = micros();
	while(true){
		if(micros() - start_time > 500000){
			break;
		}

		digit_1 = lora.localUniqueId / 10;
		digit_2 = lora.localUniqueId % 10;

		show_display(digit_1, digit_2, 16);
	}

	start_time = micros();
	while(true){
		if(micros() - start_time > 500000){
			break;
		}

		digit_1 = lora.localUniqueId / 10;
		digit_2 = lora.localUniqueId % 10;

		show_display(digit_1, digit_2, 16);
	}
}
