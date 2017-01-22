uint8_t CheckUart(){
	long timer;
	uint8_t command, mean;
	
	if (Serial.available() > 0) {
	    command = Serial.read();
	    switch (command) {
	    	case 'h':
	    		Serial.print("\
M - Operation mode\n\
S - SOP code number (0-10)\n\
C - Channel\n\
R - CRC Seed\n\
A - Amplifier (0 - 7)\n\
P - Payload Lenght (0-16)\n\
L - List current params\n\
X - Config custom register\n");
	    	break;

	        case 'M': //Operation mode
	        	mean = (byte)Serial.parseInt();
	        	MODE = mean;
	        	//updateModule = true;
	        break;

			case 'S': //SOP Code
				mean = (byte)Serial.parseInt();
        		sopCodeNum=mean < 11? mean : sopCodeNum;
        		updateModule = true;
	        break;

	    	case 'C': //Config channels
	            // for (byte i=0; i<3; i++){
	            //   while(!Serial.available());
	            //   channels[i] = (byte)Serial.parseInt();
	            // }
	            currentChannel = (byte)Serial.parseInt();
				updateModule = true;
			break;
			
			case 'R':
				mean = (uint16_t)Serial.parseInt();
				crcSeed = mean;
			break;
	        
	        case 'A': //Amplifier
	        	mean = (byte)Serial.parseInt();
	        	txPower = mean & 0x07;
	        	updateModule = true;
	        break;
	        
	        case 'P': //Payload Lenght
	        	mean = (byte)Serial.parseInt();
	        	payloadLenght = mean;
	        	updateModule = true;
	        break;
	            
	        case 'L':
	        	Serial.print("\nMode: " + String(MODE ,HEX) + "\n");
	        	Serial.print("SOP:" + String(sopCodeNum ,HEX) + "\n");
	        	Serial.print("Channel: " + String(currentChannel) + "\n");
	        	Serial.print("crcSeed " + String((uint16_t)crcSeed ,HEX) + "\n");
	        	Serial.print("TxBuf: "); SerialPrintArray(txBuffer, 16);
	        	Serial.print("RxBuf: "); SerialPrintArray(rxBuffer, 16);
	        	// Serial.print("txPower" + String( ,HEX) + "\n");
	        	// Serial.print("" + String( ,HEX) + "\n");
	        	// Serial.print("" + String( ,HEX) + "\n");
	        	// Serial.print("" + String( ,HEX) + "\n");
	        	CYRF_UpdateParams();
	        break;

	        case 'X':
	        	ConfByHex();
	        break;
	        
	        default:
	        	Serial.flush();
	    }
	}
	else return 0;
}

void ConfByHex(){
	uint8_t reg, val;
	Serial.print("Reg: ");
	while(!Serial.available());
	reg = Serial.parseInt();
	Serial.println(reg, HEX);

	Serial.print("Val: ");
	while(!Serial.available());
	val = Serial.parseInt();
	Serial.println(val, HEX);

	Serial.print("Confirm: ");
	
	while(!Serial.available());
	
	if (Serial.parseInt() == 1){
		CYRF_WriteRegister((uint8_t)reg&0xFF,(uint8_t)val&0xFF);
		Serial.println("done");
	}
	else Serial.println("failed");
}