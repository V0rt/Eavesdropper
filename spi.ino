void module_Init()
{
  DDRB  |= (1 << 5) | (0 << 4) | (1 << 3) | (0 << 2) | (1 << 1) | (1 << 0);
  PORTB |= (0 << 5) | (0 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
  DDRC  |= (1 << 5) | (1 << 2) | (1 << 1);
  PORTC &= ~(1 << 5);
  DDRD  |= (1 << 7) | (0 << 6) | (0 << 5) | (0 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (0 << 0);
  PORTD |= (1 << 7) | (1 << 2);
  SPI_Init();
}

void SPI_Init()
{
  DDRB  |= (1 << 5) | (0 << 4) | (1 << 3) | (0 << 2) | (1 << 1) | (1 << 0);
  PORTB |= (0 << 5) | (0 << 4) | (0 << 3) | (1 << 2) | (1 << 1) | (1 << 0);
  SPCR = (1 << SPE) | (1 << MSTR) | (0 << SPR1) | (0 << SPR0);
  SPSR = (0 << SPI2X); //Double clock rate.
}

uint8_t SPI_Write(uint8_t data)
{
  SPDR = data;
  while (!(SPSR & (1 << SPIF)));
  return SPDR;
}

uint8_t SPI_Read(void)
{
  SPDR = 0xFF;
  while (!(SPSR & (1 << SPIF)));
  return SPDR;
}