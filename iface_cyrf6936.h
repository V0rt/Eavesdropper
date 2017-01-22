#ifndef IFACE_CYRF6936_H
#define IFACE_CYRF6936_H

#define    CYRF_00_CHANNEL          0x00
#define    CYRF_01_TX_LENGTH        0x01
#define    CYRF_02_TX_CTRL          0x02
#define    CYRF_03_TX_CFG           0x03
#define    CYRF_04_TX_IRQ_STATUS    0x04
#define    CYRF_05_RX_CTRL          0x05
#define    CYRF_06_RX_CFG           0x06
#define    CYRF_07_RX_IRQ_STATUS    0x07
#define    CYRF_08_RX_STATUS        0x08
#define    CYRF_09_RX_COUNT         0x09
#define    CYRF_0A_RX_LENGTH        0x0A
#define    CYRF_0B_PWR_CTRL         0x0B
#define    CYRF_0C_XTAL_CTRL        0x0C
#define    CYRF_0D_IO_CFG           0x0D
#define    CYRF_0E_GPIO_CTRL        0x0E
#define    CYRF_0F_XACT_CFG         0x0F
#define    CYRF_10_FRAMING_CFG      0x10
#define    CYRF_11_DATA32_THOLD     0x11
#define    CYRF_12_DATA64_THOLD     0x12
#define    CYRF_13_RSSI             0x13
#define    CYRF_14_EOP_CTRL         0x14
#define    CYRF_15_CRC_SEED_LSB     0x15
#define    CYRF_16_CRC_SEED_MSB     0x16
#define    CYRF_17_TX_CRC_LSB       0x17
#define    CYRF_18_TX_CRC_MSB       0x18
#define    CYRF_19_RX_CRC_LSB       0x19
#define    CYRF_1A_RX_CRC_MSB       0x1A
#define    CYRF_1B_TX_OFFSET_LSB    0x1B
#define    CYRF_1C_TX_OFFSET_MSB    0x1C
#define    CYRF_1D_MODE_OVERRIDE    0x1D
#define    CYRF_1E_RX_OVERRIDE      0x1E
#define    CYRF_1F_TX_OVERRIDE      0x1F

#define    CYRF_20_TX_BUFFER        0x20
#define    CYRF_21_RX_BUFFER        0x21
#define    CYRF_22_SOP_CODE         0x22
#define    CYRF_23_DATA_CODE        0x23
#define    CYRF_24_PREAMBLE         0x24
#define    CYRF_25_MFG_ID           0x25

#define    CYRF_26_XTAL_CFG         0x26
#define    CYRF_27_CLK_OVERRIDE     0x27
#define    CYRF_28_CLK_EN           0x28
#define    CYRF_29_RX_ABORT         0x29
#define    CYRF_32_AUTO_CAL_TIME    0x32
#define    CYRF_35_AUTOCAL_OFFSET   0x35
#define    CYRF_39_ANALOG_CTRL      0x39

#define CHANNEL_ADR         0x00
#define RX_ABORT_ADR        0x29
#define RX_CTRL_ADR         0x05
#define RX_IRQ_STATUS_ADR   0x07
#define CRC_SEED_LSB_ADR    0x15
#define CRC_SEED_MSB_ADR    0x16
#define SOP_CODE_ADR        0x22
#define XACT_CFG_ADR        0x0F
#define TX_CFG_ADR          0x03
#define MODE_OVERRIDE_ADR   0x1D
#define RX_CFG_ADR          0x06
#define PWR_CTRL_ADR        0x0B
#define IO_CFG_ADR          0x0D
#define GPIO_CTRL_ADR       0x0E
#define FRAMING_CFG_ADR     0x10
#define DATA32_THOLD_ADR    0x11
#define DATA64_THOLD_ADR    0x12
#define TX_OFFSET_LSB_ADR   0x1B
#define TX_OFFSET_MSB_ADR   0x1C
#define AUTO_CAL_TIME_ADR   0x32
#define AUTO_CAL_OFFSET_ADR 0x35
#define ANALOG_CTRL_ADR     0x39
#define RX_OVERRIDE_ADR     0x1E
#define TX_OVERRIDE_ADR     0x1F
#define TX_LENGTH_ADR       0x01
#define XTAL_CTRL_ADR       0x0C
#define CLK_OVERRIDE_ADR    0x27
#define CLK_EN_ADR          0x28
#define MFG_ID_ADR          0x25
#define XTAL_CFG_ADR        0x26
#define RX_LENGTH_ADR       0x0A
#define RX_STATUS_ADR       0x08
#define RX_BUFFER_ADR       0x21
#define RSSI_ADR            0x13
#define TX_CTRL_ADR         0x02
#define TX_BUFFER_ADR       0x20
#define TX_IRQ_STATUS_ADR   0x04
#endif

/*
void CYRF_Select(void)
void CYRF_Enable(void)
uint8_t CYRF_Reset(void)
void CYRF_Init(void)

uint8_t CYRF_ReadRegister(uint8_t address)
void CYRF_WriteRegister(uint8_t address, uint8_t data)
void CYRF_ReadRegisterMulti(uint8_t address, uint8_t data[], uint8_t length)
void CYRF_WriteRegisterMulti(uint8_t address, const uint8_t data[], uint8_t length)

void CYRF_SetCrcSeed(uint16_t crc)
void CYRF_SetSopCode(uint8_t sopNum)
void CYRF_SetTxRxMode(uint8_t mode)
void CYRF_SetRfChannel(uint8_t ch)

void CYRF_StartReceive()
void CYRF_ReadDataPacket(uint8_t dpbuffer[])
void CYRF_WriteDataPacket(uint8_t dpbuffer[])

void CYRF_ReadDataPacketLen(uint8_t dpbuffer[], uint8_t len)
void CYRF_WriteDataPacketLen(uint8_t dpbuffer[], uint8_t len)

uint8_t CYRF_Rssi(void)
uint8_t CYRF_RxIrq(void)
uint8_t CYRF_RxStatus(void)
*/