
/**
 * File:    mcp2515.c
 * Author:  yuhao
 * 
 * remark:  mcp2515 c file
 * version: v2.0
 */

#include <stdint.h>
#include <stdbool.h>
#include "mcp2515.h"
#include "mcp2515_interface.h"
#include <stdio.h>

void MCP2515_Reset(void)
{
	SPI_ON();
    SPI_Send(SPI_RESET);
    SPI_OFF();
}

void MCP2515_Write(uint8_t addr, uint8_t data)
{
	// cs low
	SPI_ON();
	// write cmd
	SPI_Send(SPI_WRITE);
	// write addr
	SPI_Send(addr);
	// write data
	SPI_Send(data);
	// cs high
	SPI_OFF();
}

uint8_t MCP2515_Read(uint8_t addr)
{
	uint8_t data=0x0;
	
	SPI_ON();
	SPI_Send(SPI_READ);
	SPI_Send(addr);
    data = SPI_Receive();
	SPI_OFF();
	
	return data;
}

void MCP2515_Request_to_send(uint8_t num)
{
    SPI_ON();
    SPI_Send(SPI_RTS(num));
    SPI_OFF();
}

uint8_t MCP2515_Read_status(void)
{
    uint8_t status=0x00;
    SPI_ON();
    status = SPI_GetData(SPI_READ_STATUS);
    SPI_OFF();
    return status;
}

uint8_t MCP2515_Rx_status(void)
{
    uint8_t status=0x00;
    SPI_ON();
    status = SPI_GetData(SPI_READ_STATUS);
    SPI_OFF();
    return status;
}

void MCP2515_Init(MCP2515_Init_t *initStruct)
{
	uint8_t lop=0;
	
    /* reset mcp2515 */
	MCP2515_Reset();
	
	/* 工作模式 */
	MCP2515_Write(MCP2515_CANCTRL_ADDR, (Configuration << 5) | 0x10);
	
	/* CNF1, 2, 3 */
	MCP2515_Write(MCP2515_CNF1_ADDR, (initStruct->BuadRatePrescaler) | initStruct->SyncJumpWidthLenght << 6);
	MCP2515_Write(MCP2515_CNF2_ADDR, (initStruct->PS2BitTimeLenght << 7) | (initStruct->SamplePointConfigbit << 6) | (initStruct->PS1Lenght << 3) | (initStruct->PropagationSegmentLight));
	MCP2515_Write(MCP2515_CNF3_ADDR, (initStruct->StartOfFrame << 7) | (initStruct->WakeUpFilter << 6) | initStruct->PS2Lenght);
        
	/* filter */
	for(lop=0; lop<6; lop++)
	{
		MCP2515_Write( (MCP2515_RXF0SIDH_ADDR + (lop * 4)), (uint8_t)((initStruct->Filter[lop] >> 3) & 0xff) );
		MCP2515_Write( (MCP2515_RXF0SIDL_ADDR + (lop * 4)), (uint8_t)((initStruct->Filter[lop] << 5) & 0xe0) );
        printf("%d\t%d\n", 
                MCP2515_Read(MCP2515_RXF0SIDH_ADDR + (lop * 4)),
                MCP2515_Read(MCP2515_RXF0SIDL_ADDR + (lop * 4)));
	}
	
	/* mask */
	for(lop=0; lop<2; lop++)
	{
		MCP2515_Write( (MCP2515_RXM0SIDH_ADDR + (lop * 4)), (uint8_t)((initStruct->Mask[lop] >> 3) & 0xff) );
		MCP2515_Write( (MCP2515_RXM0SIDL_ADDR + (lop * 4)), (uint8_t)((initStruct->Mask[lop] << 5) & 0xe0) );
        printf("%d\t%d\n", 
                MCP2515_Read(MCP2515_RXM0SIDH_ADDR + (lop * 4)),
                MCP2515_Read(MCP2515_RXM0SIDL_ADDR + (lop * 4)));
	}
	
	/* TXRTSCTRL */
	MCP2515_Write(MCP2515_TXRTSCTRL_ADDR, initStruct->RTSPinCtrl & 0x0f);
	
	/* BFPCTRL */
	MCP2515_Write(MCP2515_BFPCTRL_ADDR, initStruct->BXnBFPinCtrl & 0x0f);
	
	/* 進入指定模式 */
	MCP2515_Write(MCP2515_CANCTRL_ADDR, (initStruct->Mode << 4));
	
	/* RXBxCTRL */
	MCP2515_Write(MCP2515_RXB0CTRL_ADDR, (initStruct->FIFO0ReceiveBufferOperationMode << 5) & (initStruct->RolloverEnable << 2));
	MCP2515_Write(MCP2515_RXB1CTRL_ADDR, (initStruct->FIFO1ReceiveBufferOperationMode << 5));
	
	/* clear flag */
	MCP2515_Write(MCP2515_CANINTF_ADDR,0x00); 	// clear interrupt memory
    MCP2515_Write(MCP2515_CANINTE_ADDR,0x00); 	// clear interrupt enable
    MCP2515_Write(MCP2515_EFLG_ADDR,0x00);      // clear error memory
	
}