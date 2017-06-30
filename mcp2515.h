
/**
 * File:    mcp2515.h
 * Author:  yuhao
 * 
 * remark:  mcp2515 header file
 * version: v2.0
 */

#ifndef MCP2515_H
#define	MCP2515_H

#ifdef	__cplusplus
//extern "C" {
#endif

#include <stdint.h>
#include <stdbool.h>


typedef enum
{
	Configuration=0x04,
	Normal=0x00,
	Sleep=0x01,
	ListenOnly=0x03,
	Loopback=0x02
} MCP2515_OperationMode_t;

#define MCP2515_bit_t	bool

/* SyncjumpWidth */
#define SJW_4TQ (0x03)
#define SJW_3TQ (0x02)
#define SJW_2TQ (0x01)
#define SJW_1TQ (0x00)

/* Mask, Filter */
#define MCP2515_SID_t 	uint16_t

/* BXnBFPinCtrlAndStatus */
#define RX1BFEnable		0x08
#define RX1BFDiable		0x00
#define RX0BFEnable		0x04
#define RX0BFDiable		0x00
#define RX1BFModeInterrupt	0x02
#define RX1BFModeInterrupt	0x00
#define RX0BFModeDigital	0x01
#define RX0BFModeDigital	0x00

/* ReceiveBufferOperationMode */
#define	RXMMaskFilterOff	3
#define RXMMaskFilterExt	2
#define RXMMaskFilterStd	1
#define RXMMaskFilterExtStd	0

/* RTSPinCtrl */
#define RTSPin0Enable		0x04
#define RTSPin0Disable		0x00
#define RTSPin1Enable		0x02
#define RTSPin1Disable		0x00
#define RTSPin2Enable		0x01
#define RTSPin2Disable		0x00

typedef struct
{
	MCP2515_OperationMode_t Mode;
	MCP2515_bit_t			OneShotMode;		// 發送失敗是否重新發送
	uint8_t					SyncJumpWidthLenght;	//SJW
	uint8_t 				BuadRatePrescaler;	//BRP
	MCP2515_bit_t 			PS2BitTimeLenght;	//BTLMOD
	MCP2515_bit_t 			SamplePointConfigbit;	//SAM
	uint8_t 				PS1Lenght;
	uint8_t					PS2Lenght;
	uint8_t 				PropagationSegmentLight;
	MCP2515_bit_t			StartOfFrame;	//SOF
	MCP2515_bit_t			WakeUpFilter;	//WAKFIL
	uint8_t					RTSPinCtrl;		// TXRTSCTRL
	MCP2515_SID_t			Filter[6];		//filter
	MCP2515_SID_t			Mask[2];		//mask
	uint8_t					BXnBFPinCtrl;	// 使用 BXnBFPinCtrlAndStatus 設定
	uint8_t					FIFO0ReceiveBufferOperationMode;	//RXM RX0
	uint8_t					FIFO1ReceiveBufferOperationMode;	//RXM RX1
	MCP2515_bit_t			RolloverEnable;		//BUKT
} MCP2515_Init_t;


/* Memary Map */
#define MCP2515_CANSTAT_ADDR    (0xe)
#define MCP2515_CANINTE_ADDR    (0x2b)
#define MCP2515_CANINTF_ADDR    (0x2c)
#define MCP2515_CANCTRL_ADDR    (0xf)
#define MCP2515_CNF1_ADDR   	(0x2a)
#define MCP2515_CNF2_ADDR   	(0x29)
#define MCP2515_CNF3_ADDR   	(0x28)

#define MCP2515_TXB0CTRL_ADDR   (0x30)
#define MCP2515_TXB1CTRL_ADDR   (0x40)
#define MCP2515_TXB2CTRL_ADDR   (0x50)
#define MCP2515_TXRTSCTRL_ADDR  (0x0d)
#define MCP2515_TXB0SIDH_ADDR   (0x31)
#define MCP2515_TXB1SIDH_ADDR   (0x41)
#define MCP2515_TXB2SIDH_ADDR   (0x51)
#define MCP2515_TXB0SIDL_ADDR   (0x32)
#define MCP2515_TXB1SIDL_ADDR   (0x42)
#define MCP2515_TXB2SIDL_ADDR   (0x52)
#define MCP2515_TXB0EID8_ADDR   (0x33)
#define MCP2515_TXB1EID8_ADDR   (0x43)
#define MCP2515_TXB2EID8_ADDR   (0x53)
#define MCP2515_TXB0EID0_ADDR   (0x34)
#define MCP2515_TXB1EID0_ADDR   (0x44)
#define MCP2515_TXB2EID0_ADDR   (0x54)
#define MCP2515_TXB0DLC_ADDR    (0x35)
#define MCP2515_TXB1DLC_ADDR    (0x45)
#define MCP2515_TXB2DLC_ADDR    (0x55)
#define MCP2515_TXB0D0_ADDR 	(0x36)
#define MCP2515_TXB0D1_ADDR 	(0x37)
#define MCP2515_TXB0D2_ADDR 	(0x38)
#define MCP2515_TXB0D3_ADDR 	(0x39)
#define MCP2515_TXB0D4_ADDR 	(0x3a)
#define MCP2515_TXB0D5_ADDR 	(0x3b)
#define MCP2515_TXB0D6_ADDR 	(0x3c)
#define MCP2515_TXB0D7_ADDR 	(0x3d)
#define MCP2515_TXB1D0_ADDR 	(0x46)
#define MCP2515_TXB1D1_ADDR 	(0x47)
#define MCP2515_TXB1D2_ADDR 	(0x48)
#define MCP2515_TXB1D3_ADDR 	(0x49)
#define MCP2515_TXB1D4_ADDR 	(0x4a)
#define MCP2515_TXB1D5_ADDR 	(0x4b)
#define MCP2515_TXB1D6_ADDR 	(0x4c)
#define MCP2515_TXB1D7_ADDR 	(0x4d)
#define MCP2515_TXB2D0_ADDR 	(0x56)
#define MCP2515_TXB2D1_ADDR 	(0x57)
#define MCP2515_TXB2D2_ADDR 	(0x58)
#define MCP2515_TXB2D3_ADDR 	(0x59)
#define MCP2515_TXB2D4_ADDR 	(0x5a)
#define MCP2515_TXB2D5_ADDR 	(0x5b)
#define MCP2515_TXB2D6_ADDR 	(0x5c)
#define MCP2515_TXB2D7_ADDR 	(0x5d)

#define MCP2515_RXB0CTRL_ADDR   (0x60)
#define MCP2515_RXB1CTRL_ADDR   (0x70)
#define MCP2515_BFPCTRL_ADDR    (0x0c)
#define MCP2515_RXB0SIDH_ADDR   (0x61)
#define MCP2515_RXB1SIDH_ADDR   (0x71)
#define MCP2515_RXB0SIDL_ADDR   (0x62)
#define MCP2515_RXB1SIDL_ADDR   (0x72)
#define MCP2515_RXB0EID8_ADDR   (0x63)
#define MCP2515_RXB1EID8_ADDR   (0x73)
#define MCP2515_RXB0EID0_ADDR   (0x64)
#define MCP2515_RXB1EID0_ADDR   (0x74)
#define MCP2515_RXB0DLC_ADDR    (0x65)
#define MCP2515_RXB1DLC_ADDR    (0x75)
#define MCP2515_RXB0D0_ADDR 	(0x66)
#define MCP2515_RXB0D1_ADDR 	(0x67)
#define MCP2515_RXB0D2_ADDR 	(0x68)
#define MCP2515_RXB0D3_ADDR 	(0x69)
#define MCP2515_RXB0D4_ADDR 	(0x6a)
#define MCP2515_RXB0D5_ADDR 	(0x6b)
#define MCP2515_RXB0D6_ADDR 	(0x6c)
#define MCP2515_RXB0D7_ADDR 	(0x6d)
#define MCP2515_RXB1D0_ADDR 	(0x76)
#define MCP2515_RXB1D1_ADDR 	(0x77)
#define MCP2515_RXB1D2_ADDR 	(0x78)
#define MCP2515_RXB1D3_ADDR 	(0x79)
#define MCP2515_RXB1D4_ADDR 	(0x7a)
#define MCP2515_RXB1D5_ADDR 	(0x7b)
#define MCP2515_RXB1D6_ADDR 	(0x7c)
#define MCP2515_RXB1D7_ADDR 	(0x7d)
#define MCP2515_RXF0SIDH_ADDR   (0x00)
#define MCP2515_RXF1SIDH_ADDR   (0x04)
#define MCP2515_RXF2SIDH_ADDR   (0x08)
#define MCP2515_RXF3SIDH_ADDR   (0x10)
#define MCP2515_RXF4SIDH_ADDR   (0x14)
#define MCP2515_RXF5SIDH_ADDR   (0x18)
#define MCP2515_RXF0SIDL_ADDR   (0x01)
#define MCP2515_RXF1SIDL_ADDR   (0x05)
#define MCP2515_RXF2SIDL_ADDR   (0x09)
#define MCP2515_RXF3SIDL_ADDR   (0x11)
#define MCP2515_RXF4SIDL_ADDR   (0x15)
#define MCP2515_RXF5SIDL_ADDR   (0x19)
#define MCP2515_RXF0EID8_ADDR   (0x02)
#define MCP2515_RXF1EID8_ADDR   (0x06)
#define MCP2515_RXF2EID8_ADDR   (0x0a)
#define MCP2515_RXF3EID8_ADDR   (0x12)
#define MCP2515_RXF4EID8_ADDR   (0x16)
#define MCP2515_RXF5EID8_ADDR   (0x1a)
#define MCP2515_RXF0EID0_ADDR   (0x03)
#define MCP2515_RXF1EID0_ADDR   (0x07)
#define MCP2515_RXF2EID0_ADDR   (0x0b)
#define MCP2515_RXF3EID0_ADDR   (0x13)
#define MCP2515_RXF4EID0_ADDR   (0x17)
#define MCP2515_RXF5EID0_ADDR   (0x1b)
#define MCP2515_EFLG_ADDR   	(0x2d)
#define MCP2515_RXM0SIDH_ADDR   (0x20)
#define MCP2515_RXM1SIDH_ADDR   (0x24)
#define MCP2515_RXM0SIDL_ADDR   (0x21)
#define MCP2515_RXM1SIDL_ADDR   (0x25)
#define MCP2515_RXM0EID8_ADDR   (0x22)
#define MCP2515_RXM1EID8_ADDR   (0x26)
#define MCP2515_RXM0EID0_ADDR   (0x23)
#define MCP2515_RXM1EID0_ADDR   (0x27)

#define SPI_RESET                   (0xc0)
#define SPI_READ                    (0x03)
#define SPI_READ_RX_BUFFER(buf)     ((0x90)|(((buf)&(0x03))<<1))
#define SPI_WRITE                   (0x02)
#define SPI_LOAD_TX_BUFFER(buf)     ((0x40)|((buf)&(0x07)))
#define SPI_RTS(ser)                ((0x80)|((ser)&(0x07)))
#define SPI_READ_STATUS             (0xa0)
#define SPI_RX_STATUS               (0xb0)
#define SPI_BIT_MODIFY              (0x05)

void MCP2515_Reset(void);
uint8_t MCP2515_Read(uint8_t addr);
void MCP2515_Write(uint8_t addr, uint8_t data);
void MCP2515_Request_to_send(uint8_t num);
uint8_t MCP2515_Read_status(void);
uint8_t MCP2515_Rx_status(void);
void MCP2515_Init(MCP2515_Init_t *initStruct);

#ifdef	__cplusplus
//}
#endif

#endif	/* MCP2515_H */