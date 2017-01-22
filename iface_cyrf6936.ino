#include "iface_cyrf6936.h"

#define CYCS_HIGH PORTB |=  (1<<1)
#define CYCS_LOW  PORTB &= ~(1<<1)

uint8_t sop_codes[11][8] = {
  {0x3C, 0x37, 0xCC, 0x91, 0xE2, 0xF8, 0xCC, 0x91},
  {0x9B, 0xC5, 0xA1, 0x0F, 0xAD, 0x39, 0xA2, 0x0F},
  {0xEF, 0x64, 0xB0, 0x2A, 0xD2, 0x8F, 0xB1, 0x2A},
  {0x66, 0xCD, 0x7C, 0x50, 0xDD, 0x26, 0x7C, 0x50},
  {0x5C, 0xE1, 0xF6, 0x44, 0xAD, 0x16, 0xF6, 0x44},
  {0x5A, 0xCC, 0xAE, 0x46, 0xB6, 0x31, 0xAE, 0x46},
  {0xA1, 0x78, 0xDC, 0x3C, 0x9E, 0x82, 0xDC, 0x3C},
  {0xB9, 0x8E, 0x19, 0x74, 0x6F, 0x65, 0x18, 0x74},
  {0xDF, 0xB1, 0xC0, 0x49, 0x62, 0xDF, 0xC1, 0x49},
  {0x97, 0xE5, 0x14, 0x72, 0x7F, 0x1A, 0x14, 0x72},
  {0x82, 0xC7, 0x90, 0x36, 0x21, 0x9E, 0xFF, 0x17}
};

void CYRF_Select() {
  DDRC  |= (1 << 2) | (1 << 1); //change
  PORTC |= (1 << 2) | (1 << 1); //antenna switcher
  PORTD |= (1 << 7) | (1 << 2); //CS high for all
  PORTB |= (1 << 1) | (1 << 0); //CS high for all
}

uint8_t CYRF_ReadRegister(uint8_t address) {
  uint8_t result;
  CYCS_LOW;
  SPI_Write(address);
  result = SPI_Read();
  CYCS_HIGH;
  return result;
}

void CYRF_WriteRegister(uint8_t address, uint8_t data) {
  CYCS_LOW;
  SPI_Write(address | 0x80);
  SPI_Write(data);
  CYCS_HIGH;
}

void CYRF_ReadRegisterMulti(uint8_t address, uint8_t data[], uint8_t length) {
  CYCS_LOW;
  SPI_Write(address);
  for (uint8_t i = 0; i < length; i++)
  data[i] = SPI_Read();
  CYCS_HIGH;
}

void CYRF_WriteRegisterMulti(uint8_t address, const uint8_t data[], uint8_t length) {
  CYCS_LOW;
  SPI_Write(address | 0x80);
  for (uint8_t i = 0; i < length; i++)
  SPI_Write(data[i]);
  CYCS_HIGH;
}

//======================CYRF CONFIG=========================//
void RssiInit() {
  CYRF_WriteRegister(MODE_OVERRIDE_ADR, 0x39);
  CYRF_WriteRegister(TX_CFG_ADR, 0x08); // <- СЮДА УСИЛЕНИЕ
  CYRF_WriteRegister(RX_CFG_ADR, 0x4A);
  CYRF_WriteRegister(PWR_CTRL_ADR, 0x00);
  CYRF_WriteRegister(IO_CFG_ADR, 0x04);
  CYRF_WriteRegister(GPIO_CTRL_ADR, 0x20);
  CYRF_WriteRegister(FRAMING_CFG_ADR, 0xA4);
  CYRF_WriteRegister(DATA32_THOLD_ADR, 0x05);
  CYRF_WriteRegister(DATA64_THOLD_ADR, 0x0E);
  CYRF_WriteRegister(TX_OFFSET_LSB_ADR, 0x55);
  CYRF_WriteRegister(TX_OFFSET_MSB_ADR, 0x05);
  CYRF_WriteRegister(AUTO_CAL_TIME_ADR, 0x3C);
  CYRF_WriteRegister(AUTO_CAL_OFFSET_ADR, 0x14);
  CYRF_WriteRegister(ANALOG_CTRL_ADR, 0x01);
  CYRF_WriteRegister(RX_OVERRIDE_ADR, 0x10);
  CYRF_WriteRegister(TX_OVERRIDE_ADR, 0x00);
  CYRF_WriteRegister(TX_LENGTH_ADR, 0x10);
  CYRF_WriteRegister(XTAL_CTRL_ADR, 0xC0);
  CYRF_WriteRegister(XACT_CFG_ADR, 0x08);
  CYRF_WriteRegister(XTAL_CFG_ADR, 0x00);
  CYRF_WriteRegister(CLK_OVERRIDE_ADR, 0x02);
  CYRF_WriteRegister(CLK_EN_ADR, 0x02);
  CYRF_WriteRegister(XACT_CFG_ADR, 0x28);
  CYRF_WriteRegister(GPIO_CTRL_ADR, 0x20);
  CYRF_WriteRegister(XACT_CFG_ADR, 0x28);
  CYRF_WriteRegister(GPIO_CTRL_ADR, 0x80);
  CYRF_WriteRegister(RX_ABORT_ADR, 0x00);
}

uint8_t CYRF_Reset(void) {
  PORTC |= (1 << 5); //CYRF_RST_HI; //Hardware reset
  delayMicroseconds(100);
  PORTC &= ~(1 << 5);
  delayMicroseconds(100);
  CYRF_WriteRegister(CYRF_1D_MODE_OVERRIDE, 0x01);// Software reset
  delayMicroseconds(200);
  CYRF_WriteRegister(CYRF_26_XTAL_CFG, 0x08);     // Crystal Startup Delay
  CYRF_WriteRegister(CYRF_0C_XTAL_CTRL, 0xC0);    // Enable XOUT as GPIO
  CYRF_WriteRegister(CYRF_0D_IO_CFG, 0x04);       // Enable PACTL as GPIO

  //CYRF_SetTxRxMode(TXRX_OFF); //Force IDLE mode

  CYRF_WriteRegister(CYRF_1D_MODE_OVERRIDE, 0x38);
  CYRF_WriteRegister(CYRF_03_TX_CFG, 0x0F);       // 8DRMode, MAX Amplifier
  CYRF_WriteRegister(CYRF_06_RX_CFG, 0x4A);
  CYRF_WriteRegister(CYRF_0B_PWR_CTRL, 0x00);
  CYRF_WriteRegister(CYRF_10_FRAMING_CFG, 0xA4);
  CYRF_WriteRegister(CYRF_11_DATA32_THOLD, 0x05);
  CYRF_WriteRegister(CYRF_12_DATA64_THOLD, 0x0E);
  CYRF_WriteRegister(CYRF_1B_TX_OFFSET_LSB, 0x55);
  CYRF_WriteRegister(CYRF_1C_TX_OFFSET_MSB, 0x05);
  CYRF_WriteRegister(CYRF_32_AUTO_CAL_TIME, 0x3C);
  CYRF_WriteRegister(CYRF_35_AUTOCAL_OFFSET, 0x14);
  CYRF_WriteRegister(CYRF_39_ANALOG_CTRL, 0x01);
  CYRF_WriteRegister(CYRF_1E_RX_OVERRIDE, 0x10);
  CYRF_WriteRegister(CYRF_1F_TX_OVERRIDE, 0x00);
  CYRF_WriteRegister(CYRF_01_TX_LENGTH, 0x10);
  CYRF_WriteRegister(CYRF_27_CLK_OVERRIDE, 0x02);
  CYRF_WriteRegister(CYRF_28_CLK_EN, 0x02);
  CYRF_SetCrcSeed(0x5151);
  CYRF_SetSopCode(5);
}

void CYRF_SetTxRxMode(uint8_t state) {
  if (state == IDLE) {
    CYRF_WriteRegister(CYRF_0F_XACT_CFG, 0x24);  // 4=IDLE, 8=TX, C=RX
    //CYRF_WriteRegister(CYRF_0E_GPIO_CTRL, 0x00); // XOUT=0
  }
  if (state == TX) {
    CYRF_WriteRegister(CYRF_0F_XACT_CFG, 0x28);  // Force TX mode
    CYRF_WriteRegister(CYRF_0E_GPIO_CTRL, 0x80);
    //CYRF_WriteRegister(CYRF_0F_XACT_CFG, 0x04);  // IdleMode
  }
  if (state == RX) {
    CYRF_WriteRegister(CYRF_0F_XACT_CFG, 0x2C);  // Force RX mode
    CYRF_WriteRegister(CYRF_0E_GPIO_CTRL, 0x20);
    //CYRF_WriteRegister(CYRF_0F_XACT_CFG, 0x04);  // IdleMode
  }
}

void CYRF_SetSopCode(uint8_t sopNum) {
  uint8_t code[8];
  if (sopNum > 10) sopNum = 10;
  for (byte i = 0; i < 8; i++)
  code[i] = sop_codes[sopNum][i];
  CYRF_WriteRegisterMulti(CYRF_22_SOP_CODE, code, 8);
}

void CYRF_SetCrcSeed(uint16_t crc) {
  CYRF_WriteRegister(CYRF_15_CRC_SEED_LSB, (uint8_t) crc & 0xff);
  CYRF_WriteRegister(CYRF_16_CRC_SEED_MSB, crc >> 8);
}

void CYRF_SetRfChannel(uint8_t ch) {
  if (ch > 98) ch = 98; //max channel num
  //CYRF_SetTxRxMode(TXRX_OFF);
  CYRF_WriteRegister(CYRF_00_CHANNEL, ch);
  delayMicroseconds(270);
}

uint8_t CYRF_Amplifier(uint8_t level){
  CYRF_WriteRegister(CYRF_03_TX_CFG, level | 0x08); //because DataMode = 0x08
}

void CYRF_GetMfgData(uint8_t data[]){
  CYRF_WriteRegister(CYRF_25_MFG_ID, 0xFF);   /* Fuses power on */
  CYRF_ReadRegisterMulti(CYRF_25_MFG_ID, data, 6);
  CYRF_WriteRegister(CYRF_25_MFG_ID, 0x00);   /* Fuses power off */
}

void CYRF_StartReceive(void) {
  // CYRF_SetTxRxMode(RX_EN);
  CYRF_WriteRegister(CYRF_05_RX_CTRL, 0x87);
}

void CYRF_StartTransmitt(void){
  // CYRF_SetTxRxMode(TX_EN);
  CYRF_WriteRegister(CYRF_02_TX_CTRL, 0x82);
}

void CYRF_ReadDataPacket(uint8_t dpbuffer[]) {
  CYRF_ReadRegisterMulti(CYRF_21_RX_BUFFER, dpbuffer, 16);
}

void CYRF_WriteDataPacketLen(uint8_t dpbuffer[], uint8_t len) {
  CYRF_WriteRegister(CYRF_01_TX_LENGTH, len);
  CYRF_WriteRegister(CYRF_02_TX_CTRL, 0x40); // Clear TX buffer
  CYRF_WriteRegisterMulti(CYRF_20_TX_BUFFER, dpbuffer, len);
  //CYRF_WriteRegister(CYRF_02_TX_CTRL, 0xBF);
}

void CYRF_WriteDataPacket(uint8_t dpbuffer[]) {
  CYRF_WriteDataPacketLen(dpbuffer, 16);
}

void CYRF_PayloadLenght(uint8_t len){
  CYRF_WriteRegister(CYRF_01_TX_LENGTH, len);
  CYRF_WriteRegister(CYRF_02_TX_CTRL, 0x40); // Clear TX buffer
}
//=============STATUS==============

uint8_t CYRF_Rssi(void) {
  return CYRF_ReadRegister(CYRF_13_RSSI);
}

uint8_t CYRF_RxIrq(void) {
  return CYRF_ReadRegister(CYRF_07_RX_IRQ_STATUS);
}

uint8_t CYRF_RxStatus(void) {
  return CYRF_ReadRegister(CYRF_08_RX_STATUS);
}

uint8_t CYRF_TxIrq(void){
  return CYRF_ReadRegister(CYRF_04_TX_IRQ_STATUS);
}

void SerialPrintArray(uint8_t array[],uint8_t len){
  for (uint8_t i=0; i<len; i++){
    Serial.print(array[i] < 0x10 ? "0" + String(array[i], HEX) : String(array[i], HEX));
  }
  Serial.print("\n");
}