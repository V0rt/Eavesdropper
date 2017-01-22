uint8_t sopCodeNum = 5; // Sop code number from datasheet
uint8_t currentChannel = 42; // Freq = (2400 + channel) Mhz
uint8_t arrayChannel[10];
uint16_t crcSeed = 0x5151;
uint8_t payloadLenght = 16;
uint8_t txBuffer[16];
uint8_t rxBuffer[16];
uint8_t mfgId[6];
uint32_t timer;
uint8_t txPower = 0x00; // & 0x07
uint8_t rxIrq, txIrq, rxState, txState, rssi;
bool updateModule = false;

enum _TXRX_State {
  IDLE,
  TX,
  RX
};

//_TXRX_State STATE;

enum _CYRF_opertaionMode {
  idle,        // 0 
  SOP_SCAN,    // 1 
  RECEIVE,     // 2 
  UPDATE       // 3
};

_CYRF_opertaionMode MODE;

void tstart(void) {Serial.print("Start\n"); timer = micros(); }
void tstop(void)  {Serial.print("Done in " + String(micros() - timer, DEC) + " us\n\n"); }

void CYRF_Loop() {

  if(updateModule == true){
    CYRF_UpdateParams();
    updateModule = false;
  }

  switch (MODE) {
    case SOP_SCAN:  //Mode 1
    CircleScan();
    break;

    case RECEIVE:   // Mode 2
    CYRF_Receive();
    break;

    default:        // Mode 0
    CYRF_Idle();          
  }
}

void CYRF_Receive(){
  tstart();
  
  CYRF_SetTxRxMode(RX);
  CYRF_StartReceive();
  
  for(int i=0; i<255; i++){
    delayMicroseconds(200);
    rxIrq = CYRF_RxIrq();

    if (rxIrq == 0x3a){
      rxState = CYRF_RxStatus();
      CYRF_ReadDataPacket(rxBuffer);
      Serial.println("IRQ: "+ String(rxIrq, HEX) +"\tST: "+ String(rxState, HEX)+"\n");
      SerialPrintArray(rxBuffer, 16);
      break;
    }
    else if (rxIrq & 0x42){
      Serial.println("IRQ: "+ String(rxIrq, HEX) +"\tST: "+ String(rxState, HEX)+"\n");
    }
  }
  
  tstop();      
}


void CircleScan(){
  uint8_t sopCodeDetectNum = 0;

  Serial.print("SopScan:\n");
  for (byte sopCodeNum = 0; sopCodeNum < 11; sopCodeNum++) {

    CYRF_SetTxRxMode(IDLE);
    CYRF_SetSopCode(sopCodeNum);

    for (currentChannel= 0; currentChannel < 96; currentChannel++) {
      CYRF_SetRfChannel(currentChannel);
      CYRF_StartReceive();

      for(int i=0; i<13; i++){
        delayMicroseconds(424);
        rxIrq = CYRF_RxIrq();
        rssi = CYRF_Rssi();

        if (rssi & 0x80){
          sopCodeDetectNum++;
          Serial.print("S:" + String(sopCodeNum, DEC) + "\tH:" + String(currentChannel) + "\t" + (rssi & 0x80 ? "R:" : "r:") + String(rssi & 0x1F, DEC) + "\tI: " + String(rxIrq, HEX) + "\n");
        }
      }
    }
  }

  Serial.print("Found: " + String(sopCodeDetectNum, DEC) + "\n");
}

void CYRF_UpdateParams(void){
  CYRF_SetTxRxMode(IDLE); // DANGER may be lagggggs..!
  CYRF_SetSopCode(sopCodeNum);
  CYRF_SetRfChannel(currentChannel);
  CYRF_SetCrcSeed(crcSeed);
  CYRF_PayloadLenght(payloadLenght);
  CYRF_ReadDataPacket(rxBuffer);
  CYRF_WriteDataPacket(txBuffer);
  CYRF_Amplifier(txPower);
  updateModule = false;
  Serial.println("Updated!");
}

void CYRF_Idle(void) {
  delay(250);
}