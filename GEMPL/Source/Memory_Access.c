/***********************************************************************************************************************
* File Name    : Memory_Access.c
* Version      : 1.0
* Device(s)    : R5F10DMF
* Tool-Chain   : CCRL
* Description  : This file implements the memory access functions.
* Creation Date: 28-08-2023
* Author	   : Gokul Mohanasundaram
*****************************e <string******************************************************************************************/

#include <string.h>
#include "r_cg_macrodriver.h"
#include "GEM_common_header.h"
#include "Calculations.h"
#include "r_cg_serial.h"
#include "Delay.h"

extern void eel_fdl_open(void);
extern void eel_fdl_format(void);
extern void eel_fdl_write(uint8_t id);
extern void eel_fdl_read(uint8_t id);
extern void eel_fdl_close(void);
uint8_t TX_buf[5],RX_buf[5];

static uint16_t IIC_Read_Address = 0x00A0;   // Start_Odo_mem_Address =160 page=10 // end_Odo_mem_Address =560 page=35
static uint16_t IIC_Write_Address = 0x00A0;  // Start_Odo_mem_Address =160 page=10 // end_Odo_mem_Address =560 page=35

/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void gem_odo_update(uint32_t nvm_odo)
{
    memcpy(&TX_buf[0],&nvm_odo,sizeof(nvm_odo));	
    eel_fdl_open();
    eel_fdl_format(); 
    eel_fdl_write(3);
    eel_fdl_close();
}

/***********************************************************************************************************************
* Function Name: GEM_Animation
* Description  : This function implements the functionality for the Animation.
* Arguments    : Cluster_Data
* Return Value : None
***********************************************************************************************************************/
void GEM_Mem_Init(void)
{
    eel_fdl_open();
	eel_fdl_format();       
	eel_fdl_read(3);	
	eel_fdl_close();
}


void GEM_ODO_write_Check(uint32_t odo_disp,uint32_t nvm_odo)
{
    static uint32_t GEM_Prev_Odo = 0;
    if(GEM_Prev_Odo != odo_disp)
    {
        gem_odo_update(nvm_odo);
        GEM_Prev_Odo = odo_disp;
    }
}

#define EEPROM_ADDRESS_WRITE     0xA0
#define EEPROM_ADDRESS_READ    0xA1


uint8_t GEM_IIC_Device_Select_Code(uint8_t Device_Select_Code, uint16_t Address)
{
    uint8_t Address_MSB = ((uint8_t)((Address & 0x0300) >> 8));
    return (Device_Select_Code | Address_MSB);
}

uint8_t GEM_IIC_Device_Memory_Address_LSB(uint16_t Address)
{
    return ((uint8_t)(Address));
}

void GEM_IIC_Memory_Write_Data(uint16_t Address, uint8_t *Data, uint8_t data_len)
{
    uint8_t Device_Select_Code = GEM_IIC_Device_Select_Code(EEPROM_ADDRESS_WRITE,Address);
    uint8_t Address_LSB = GEM_IIC_Device_Memory_Address_LSB(Address);
    uint8_t Write_Data[17]= {0}; //Page size 16 bytes
    Write_Data[0] = Address_LSB;
    if(data_len < 16)
    {
        memcpy(&Write_Data[1],Data,data_len);
        R_IIC11_StopCondition();
        //GEM_Delay_ms(1);
        R_IIC11_Master_Send(Device_Select_Code, &Write_Data[0], (data_len+1));   // (data_len+1) = address + data
        GEM_Delay_ms(1);
        R_IIC11_StopCondition();
        GEM_Delay_ms(4);  //Write time = 4ms max
    }
}

void GEM_IIC_Memory_Address_Read(uint16_t Address, uint8_t *Data, uint8_t data_len)
{
    uint8_t Device_Select_Code = GEM_IIC_Device_Select_Code(EEPROM_ADDRESS_WRITE,Address);
    uint8_t Address_LSB = GEM_IIC_Device_Memory_Address_LSB(Address);
    R_IIC11_StopCondition();
    //GEM_Delay_ms(1);
    R_IIC11_Master_Send(Device_Select_Code, &Address_LSB, 1);   // (data_len = 1
    GEM_Delay_ms(1);
    R_IIC11_StopCondition();
    R_IIC11_Master_Receive(Device_Select_Code,Data,data_len);
    GEM_Delay_ms(1);
}

void GEM_IIC_ODO_WRITE_READ(Cluster_Data_t *Cluster_Data)
{
    static uint32_t read_mem_odo = 0;
    uint8_t i_retry = 0;
    GEM_IIC_Memory_Write_Data(IIC_Write_Address,Cluster_Data->Odometer_Memory,sizeof(Cluster_Data->Odometer_Memory));
    GEM_IIC_Memory_Address_Read(IIC_Read_Address,&read_mem_odo,sizeof(read_mem_odo));
    while ((Cluster_Data->Odometer_Memory != read_mem_odo) && (i_retry <= 2))
    {
        GEM_IIC_Memory_Address_Read(IIC_Read_Address,&read_mem_odo,sizeof(read_mem_odo));
        i_retry++;
    }
    IIC_Write_Address +=  sizeof(Cluster_Data->Odometer_Memory);
    IIC_Read_Address += sizeof(Cluster_Data->Odometer_Memory);
    if (Cluster_Data->Odometer_Memory != read_mem_odo)
    {
        GEM_IIC_Memory_Write_Data(IIC_Write_Address,Cluster_Data->Odometer_Memory,sizeof(Cluster_Data->Odometer_Memory));
        GEM_IIC_Memory_Address_Read(IIC_Read_Address,&read_mem_odo,sizeof(read_mem_odo));
        IIC_Write_Address +=  sizeof(Cluster_Data->Odometer_Memory);
        IIC_Read_Address += sizeof(Cluster_Data->Odometer_Memory);
    }

    if(IIC_Write_Address >= 0x0230)  // Start_Odo_mem_Address =160 page=10 // end_Odo_mem_Address =560(0x0230) page=35
    {
        IIC_Write_Address = 0x00A0;
        IIC_Read_Address = 0x00A0;
    }
}

void GEM_IIC_ODO_READ(Cluster_Data_t *Cluster_Data)
{
    uint32_t read_mem_odo_temp[4] = {0};
    uint32_t read_mem_odo=0;
    uint16_t read_mem_odo_addr = 0x00A0;
    uint8_t i_page, i_data;
    for(i_page = 10; i_page < 25; i_page++)
    {
        GEM_IIC_Memory_Address_Read(IIC_Read_Address,read_mem_odo_temp,sizeof(read_mem_odo_temp));
        for(i_data = 0; i_data < 4; i_data++)
        {
            if(read_mem_odo < read_mem_odo_temp[i_data])
            {
                read_mem_odo = read_mem_odo_temp[i_data];
                read_mem_odo_addr = read_mem_odo_addr + (i_page * i_data);
            }
        }
        IIC_Read_Address += sizeof(read_mem_odo_temp);
    }
    Cluster_Data->Odometer_Memory =  read_mem_odo;
    Odo_value_Mem_read(&read_mem_odo);
    IIC_Read_Address = read_mem_odo_addr + sizeof(read_mem_odo);
}

//void GEM_IIC_Memory_Write(uint8_t *Write_data)
void GEM_IIC_Memory_Write_Data_1(uint16_t Write_Address)
{
    uint8_t Device_Select_Code = EEPROM_ADDRESS_WRITE;
    uint8_t Write_Address_LSB, Write_Address_MSB;
    Write_Address_LSB = (uint8_t) Write_Address;
    Write_Address_MSB = (((uint8_t)(Write_Address >> 8)) & 0x03);
    Device_Select_Code = Device_Select_Code | Write_Address_MSB;

    uint8_t wr_Data[4] = {1,2,3,4};
    uint8_t Write_Data[5] = {Write_Address_LSB, 2,13,14,15};
    R_IIC11_StopCondition();
    //GEM_Delay_ms(1);
    R_IIC11_Master_Send(Device_Select_Code, &Write_Data[0], sizeof(Write_Data));
    GEM_Delay_ms(1);
}

void GEM_GEM_IIC_Memory_Read_1(uint16_t Read_Address)
{
    //uint16_t Read_Address = 0x0000;
    uint8_t Device_Select_Code = EEPROM_ADDRESS_READ;
    uint8_t Read_Address_LSB, Read_Address_MSB;
    Read_Address_LSB = (uint8_t) Read_Address;
    Read_Address_MSB = (((uint8_t)(Read_Address >> 8)) & 0x03);
    Device_Select_Code = Device_Select_Code | Read_Address_MSB;

    uint8_t rd_Data[4]={0,0,0,0};
    uint8_t rd_Data_1[4]={0,0,0,0};
    R_IIC11_StopCondition();
    GEM_Delay_ms(4);  //Write time = 4ms max
    //Time between Stop condition and next Start condition = 500ns
    R_IIC11_Master_Send(Device_Select_Code, &Read_Address_LSB, sizeof(Read_Address_LSB));
    GEM_Delay_ms(1);
    R_IIC11_StopCondition();
    R_IIC11_Master_Receive(Device_Select_Code,&rd_Data[0],sizeof(rd_Data));
    GEM_Delay_ms(1);
    rd_Data_1[0]=rd_Data[0];
    rd_Data_1[1]=rd_Data[1];
    rd_Data_1[2]=rd_Data[2];
    rd_Data_1[3]=rd_Data[3];
    rd_Data_1[0]=rd_Data[0];
}
void GEM_IIC_test(void)
{
    static uint16_t IIC_Write_Address = 0x0000;
    static uint16_t IIC_Read_Address = 0x0000;

    GEM_IIC_Memory_Write_Data_1(IIC_Write_Address);
    GEM_GEM_IIC_Memory_Read_1(IIC_Read_Address);

}
void i2c_test(void)
{
    uint8_t mem_addr = 0;
    uint8_t test[3] = {mem_addr,2,2};
    uint8_t test_r[3]={1,1,1};
    uint8_t test_1;
    uint8_t adr_r = 0xA1;
    uint8_t adr_w = 0xA0;
    /*R_IIC11_Master_Send(adr_w,&test[0],2);
    R_IIC11_Master_Send(adr_w,&mem_addr,2);
    R_IIC11_Master_Receive(adr_r,&test_r[0],3);*/

    GEM_IIC_test();
    test_1 = test_r[0];
}



