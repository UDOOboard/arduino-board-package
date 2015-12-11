#ifndef SPImqx_h
#define SPImqx_h

/*
 * SPI Interfaces
 */
//#define SPI_INTERFACES_COUNT 	1
#define SPI_INTERFACE        	5
#define PIN_SPI_SS5          	(11u)
//#define BOARD_SPI_SS5        	PIN_SPI_SS5
//#define BOARD_SPI_DEFAULT_SS 	BOARD_SPI_SS5
//static const uint8_t SS5 = 		BOARD_SPI_SS5;

#ifdef __cplusplus
extern "C"{
#endif // __cplusplus

void mqx_spi_begin (uint8_t);
void mqx_spi_set_baud (uint32_t);
void mqx_spi_set_data_mode (uint32_t);
void mqx_spi_set_bit_order (uint32_t);
void mqx_spi_set_frame_size (uint32_t);
_mqx_int mqx_tx_rx_burst(uint8_t *tx_buffer, uint8_t *rx_buffer, uint32_t len);
void mqx_spi_end (void);

#ifdef __cplusplus
}
#endif // __cplusplus

#endif
