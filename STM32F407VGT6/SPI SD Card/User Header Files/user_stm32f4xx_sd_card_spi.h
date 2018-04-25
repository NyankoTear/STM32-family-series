#include "main.h"
#include "user_stm32f4xx_spi.h"

#ifndef __USER_STM32F4XX_SD_CARD_SPI_H__
#define __USER_STM32F4XX_SD_CARD_SPI_H__

/*  Command index list definition  */
#define CMD0    0
#define CMD1    1
#define CMD6    6
#define CMD8    8
#define CMD9    9
#define CMD10   10
#define CMD12   12
#define CMD13   13
#define CMD16   16
#define CMD17   17
#define CMD18   18
#define CMD24   24
#define CMD25   25
#define CMD27   27
#define CMD28   28
#define CMD29   29
#define CMD30   30
#define CMD32   32
#define CMD33   33
#define CMD38   38
#define CMD42   42
#define CMD55   55
#define CMD56   56
#define CMD58   58
#define CMD59   59

#define ACMD13  13
#define ACMD18  18
#define ACMD22  22
#define ACMD23  23
#define ACMD25  25
#define ACMD26  26
#define ACMD38  38
#define ACMD41  41
#define ACMD42  42
#define ACMD43  43
#define ACMD44  44
#define ACMD45  45
#define ACMD46  46
#define ACMD47  47
#define ACMD48  48
#define ACMD49  49
#define ACMD51  51

/*  Format R1 flag mask definition  */
#define R1_IN_IDLE_STATE_MASK           0x01U
#define R1_ERASE_RESET_MASK             0x02U
#define R1_ILLEGAL_COMMAND_MASK         0x04U
#define R1_COMMUNICATION_CRC_ERR_MASK   0x08U
#define R1_ERASE_SEQUENCE_ERR_MASK      0x10U
#define R1_ADDRESS_ERR_MASK             0x20U
#define R1_PARAMETER_ERR_MASK           0x40U

/*  format R2 flag mask definition  */
#define R2_IS_CARD_LOCKED_MSAK          0x01U
#define R2_WP_ERASE_SKIP_MASK           0x02U
#define R2_LOCK_UNLOCK_CMD_FAILED_MASK  0x02U
#define R2_ERR_MASK                     0x04U
#define R2_CC_ERR_MASK                  0x08U
#define R2_CARD_ECC_FAILED              0x10U
#define R2_WP_VIOLATION                 0x20U
#define R2_ERASE_PARAM_MASK             0x40U
#define R2_OUT_OF_RANGE_MASK            0x80U
#define R2_CSD_OVERWRITE_MASK           0x80U

/*  Single start block token definition  */
#define SINGLE_START_BLOCK    0xFEU

/*  Multiple block token definition  */
#define MULTIPLE_START_BLOCK  0xFCU
#define MULTIPLE_STOP_BLOCK   0xFDU

/*  Data Error token mask definition  */
#define DATA_ERR_ERR_MASK          0x01U
#define DATA_ERR_CC_ERR_MASK       0x02U
#define DATA_CARD_ECC_FAILED_MASK  0x04U
#define DATA_OUT_OF_RANGE_MASK     0x08U

/*  OCR Register mask definition  */
#define OCR_VOLTAGE_2_8_TO_2_9_MASK   0x00010000U
#define OCR_VOLTAGE_2_9_TO_3_0_MASK   0x00020000U
#define OCR_VOLTAGE_3_0_TO_3_1_MASK   0x00040000U
#define OCR_VOLTAGE_3_1_TO_3_2_MASK   0x00080000U
#define OCR_VOLTAGE_3_2_TO_3_3_MASK   0x00100000U
#define OCR_VOLTAGE_3_3_TO_3_4_MASK   0x00200000U
#define OCR_VOLTAGE_3_4_TO_3_5_MASK   0x00400000U
#define OCR_VOLTAGE_3_5_TO_3_6_MASK   0x00800000U
#define OCR_S18A_MASK                 0x01000000U
#define OCR_UHSII_CARD_STATUS_MASK    0x20000000U
#define OCR_CARD_CAPACITY_STATUS_MASK 0x40000000U
#define OCR_CARD_POWER_UP_STATUS_MASK 0x80000000U

/*  Command format  */
typedef struct{
  volatile  uint8_t   CRC7;
  volatile  uint32_t  Argument;
  volatile  uint8_t   StartBit;
} StructSPIModeTransactionPacket;

/*  R1 response format  */
typedef struct{
  volatile  uint8_t R1Format;
} StructR1ResponseFormat;

/*  R2 response format  */
typedef struct{
  volatile  uint8_t R2Format;
  volatile  uint8_t R1Format;
} StructSPIModeR2Format;

/*  R3 response format  */
typedef struct{
  volatile  uint32_t  OCR;
  volatile  uint8_t   R1Format;
} StructSPIModeR3Format;

/** 
 * The CSD Register Fields (CSD Version 1.0 and 2.0)
 */

// Refer to see p.162 5.2 CID register
typedef struct{
  volatile uint8_t  NonUsedBit          : 1;    //  Not used, always '1'.
  volatile uint8_t  CRC7                : 7;
  volatile uint16_t ManufacturingDate   : 12;
  volatile uint16_t Reserved            : 4;
  volatile uint32_t ProductSerialNumber;
  volatile uint8_t  ProductRevision;
  volatile uint64_t ProductName         : 40;
  volatile uint64_t ApplicationID       : 16;   //  Same as OEM ID.
  volatile uint64_t ManufacturerID      : 8;
} StructCIDRegister;

typedef struct{
  volatile uint8_t  NotUsedBit          : 1;    //  Not used, always '1'
  volatile uint8_t  CRC7                : 7;    //  CRC7.
  volatile uint8_t  Reserved1           : 2;    //  Reserved(00b).

  volatile uint8_t  FILE_FORMAT         : 2;    //  File format.
  volatile uint8_t  TMP_WRITE_PROTECT   : 1;    //  Temporary write protection.
  volatile uint8_t  PERM_WRITE_PROTECT  : 1;    //  Permanent write protection.
  volatile uint8_t  COPY                : 1;    //  Copy flag.
  volatile uint8_t  FILE_FORMAT_GRP     : 1;    //  File format group.
  volatile uint8_t  Reserved2           : 5;    //  Reserved(00000b).

  volatile uint8_t  WRITE_BL_PARTIAL    : 1;    //  Partial blocks for write allowed.
  volatile uint8_t  WRITE_BL_LEN        : 4;    //  Max. Write data block length.
  volatile uint8_t  R2W_FACTOR          : 3;    //  Write speed factor.
  volatile uint8_t  Reserved3           : 2;    //  Reserved(Do not use)(00b).

  volatile uint8_t  WP_GRP_ENABLE       : 1;    //  Write protect group enable.
  volatile uint8_t  WP_GRP_SIZE         : 7;    //  Write protect group size.
  volatile uint8_t  SECTOR_SIZE         : 7;    //  Erase sector size.
  volatile uint8_t  ERASE_BLK_EN        : 1;    //  Erase single block enable.
  volatile uint8_t  C_SIZE_MULT         : 3;    //  Device size multiplier.
  volatile uint8_t  VDD_W_CURR_MAX      : 3;    //  Max. Write current @ Vdd max.
  volatile uint8_t  VDD_W_CURR_MIN      : 3;    //  Max. Write current @ Vdd min.
  volatile uint8_t  VDD_R_CURR_MAX      : 3;    //  Max. Read current @ Vdd max.
  volatile uint8_t  VDD_R_CURR_MIN      : 3;    //  Max. Read current @ Vdd min.
  volatile uint16_t C_SIZE              : 12;   //  Device size.
  volatile uint16_t Reserved4           : 2;    //  Reserved(00b).

  volatile uint8_t  DSR_IMP             : 1;    //  DSR implemented.
  volatile uint8_t  READ_BLK_MISALIGN   : 1;    //  Read block misalignment.
  volatile uint8_t  WRITE_BLK_MISALIGN  : 1;    //  Write block misalignment.
  volatile uint8_t  READ_BL_PARTIAL     : 1;    // Partial blocks for read allowed.
  volatile uint8_t  READ_BL_LEN         : 4;    //  Max. Read data block length.
  volatile uint16_t CCC                 : 12;   //  Card command classes(01x110110101b).
  volatile uint8_t  TRAN_SPEED;                 //  Max. data transfer rate(32h or 5Ah).
  volatile uint8_t  NSAC;                       //  Data read access-time2 in CLK cycles(NSAC * 100).
  volatile uint8_t  TAAC;                       //  Data read access-time1.
  volatile uint8_t  Reserved5           : 6;    //  Reserved(000000b).

  volatile uint8_t  CSD_STRUCTURE       : 2;    //  CSD structure.
} StructCSDRegisterVer1;

typedef struct{
  volatile uint8_t  NotUsedBit          : 1;    //  Not used, always '1'
  volatile uint8_t  CRC7                : 7;    //  CRC7.
  volatile uint8_t  Reserved1           : 2;    //  Reserved(00b).

  volatile uint8_t  FILE_FORMAT         : 2;    //  File format.
  volatile uint8_t  TMP_WRITE_PROTECT   : 1;    //  Temporary write protection.
  volatile uint8_t  PERM_WRITE_PROTECT  : 1;    //  Permanent write protection.
  volatile uint8_t  COPY                : 1;    //  Copy flag.
  volatile uint8_t  FILE_FORMAT_GRP     : 1;    //  File format group.
  volatile uint8_t  Reserved2           : 5;    //  Reserved(00000b).

  volatile uint8_t  WRITE_BL_PARTIAL    : 1;    //  Partial blocks for write allowed.
  volatile uint8_t  WRITE_BL_LEN        : 4;    //  Max. Write data block length.
  volatile uint8_t  R2W_FACTOR          : 3;    //  Write speed factor.
  volatile uint8_t  Reserved3           : 2;    //  Reserved(00b).

  volatile uint8_t  WP_GRP_ENABLE       : 1;    //  Write protect group enable.
  volatile uint8_t  WP_GRP_SIZE         : 7;    //  Write protect group size.
  volatile uint8_t  SECTOR_SIZE         : 7;    //  Erase sector size.
  volatile uint8_t  ERASE_BLK_EN        : 1;    //  Erase single block enable.
  volatile uint8_t  Reserved4           : 1;    //  Reserved(0b).

  volatile uint32_t C_SIZE              : 22;   //  Device size.
  volatile uint8_t  Reserved5           : 6;    //  Reserved(000000b).

  volatile uint8_t  DSR_IMP             : 1;    //  DSR implemented.
  volatile uint8_t  READ_BLK_MISALIGN   : 1;    //  Read block misalignment.
  volatile uint8_t  WRITE_BLK_MISALIGN  : 1;    //  Write block misalignment.
  volatile uint8_t  READ_BL_PARTIAL     : 1;    //  Partial block for read allowed.
  volatile uint8_t  READ_BL_LEN         : 4;    //  Max. Read data block length.
  volatile uint16_t CCC                 : 12;   //  Card command classes.
  volatile uint8_t  TRAN_SPEED;                 //  Max. Data transfer rate.
  volatile uint8_t  NSAC;                       //  Data read access-time in CLK cycles(NSAC* 100).
  volatile uint8_t  TAAC;                       //  Data read access-time.
  volatile uint8_t  Reserved6           : 6;    //  Reserved(000000b).

  volatile uint8_t  CSD_STRUCTURE       : 2;    //  CSD structure.
} StructCSDRegisterVer2;

/*  CSD register structure  */
typedef enum{
  CSDVersion1 = 0,
  CSDVersion2 = 1
//   CSDVersionReserved1 = 2,
//   CSDVersionReserved2 = 3
} ECSDStructure;

/*  TAAC access time definition  */
typedef enum{
  TAACTimeUnit1ns   = 0,
  TAACTimeUnit10ns  = 1,
  TAACTimeUnit100ns = 2,
  TAACTimeUnit1us   = 3,
  TAACTimeUnit10us  = 4,
  TAACTimeUnit100us = 5,
  TAACTimeUnit1ms   = 6,
  TAACTimeUnit10ms  = 7
} ETAACTimeUnit;

typedef enum{
//   TAACTimeValueReserved = 0x0U,
  TAACTimeValue1_0 = 0x1U,
  TAACTimeValue1_2 = 0x2U,
  TAACTimeValue1_3 = 0x3U,
  TAACTimeValue1_5 = 0x4U,
  TAACTimeValue2_0 = 0x5U,
  TAACTimeValue2_5 = 0x6U,
  TAACTimeValue3_0 = 0x7U,
  TAACTimeValue3_5 = 0x8U,
  TAACTimeValue4_0 = 0x9U,
  TAACTimeValue4_5 = 0xAU,
  TAACTimeValue5_0 = 0xBU,
  TAACTimeValue5_5 = 0xCU,
  TAACTimeValue6_0 = 0xDU,
  TAACTimeValue7_0 = 0xEU,
  TAACTimeValue8_0 = 0xFU
} ETAACTimeValue;

/*  Macimum data transfer rate definition  */
typedef enum{
  TransferRateUnit100kbitPerSec = 0,
  TransferRateUnit1MbitPerSec   = 1,
  TransferRateUnit10MbitPerSec  = 2,
  TransferRateUnit100MbitPerSec = 3
//   TransferRateUnitReserved1 = 4,
//   TransferRateUnitReserved2 = 5,
//   TransferRateUnitReserved3 = 6,
//   TransferRateUnitReserved4 = 7
} ETRAN_SPEEDTransferRateUnit;

typedef enum{
//   Reserved = 0x0U,
  TransferTimeValue1_0 = 0x1U,
  TransferTimeValue1_2 = 0x2U,
  TransferTimeValue1_3 = 0x3U,
  TransferTimeValue1_5 = 0x4U,
  TransferTimeValue2_0 = 0x5U,
  TransferTimeValue2_5 = 0x6U,
  TransferTimeValue3_0 = 0x7U,
  TransferTimeValue3_5 = 0x8U,
  TransferTimeValue4_0 = 0x9U,
  TransferTimeValue4_5 = 0xAU,
  TransferTimeValue5_0 = 0xBU,
  TransferTimeValue5_5 = 0xCU,
  TransferTimeValue6_0 = 0xDU,
  TransferTimeValue7_0 = 0xEU,
  TransferTimeValue8_0 = 0xFU
} ETRAN_SPEEDTimeValue;

/* Supported card command classes  */
typedef enum{
  Class0  = 0,
  Class1  = 1,
  Class2  = 2,
  Class3  = 3,
  Class4  = 4,
  Class5  = 5,
  Class6  = 6,
  Class7  = 7,
  Class8  = 8,
  Class9  = 9,
  Class10 = 10,
  Class11 = 11
} ECCC;

/*  Data block length  */
typedef enum{
//   ReadBlockLengthReserved1 = 0,
//   ReadBlockLengthReserved2 = 1,
//   ReadBlockLengthReserved3 = 2,
//   ReadBlockLengthReserved4 = 3,
//   ReadBlockLengthReserved5 = 4,
//   ReadBlockLengthReserved6 = 5,
//   ReadBlockLengthReserved7 = 6,
//   ReadBlockLengthReserved8 = 7,
//   ReadBlockLengthReserved9 = 8,
  ReadBlockLengthByte512  = 9,
  ReadBlockLengthByte1024 = 10,
  ReadBlockLengthByte2048 = 11
//   ReadBlockLengthReserved10 = 12,
//   ReadBlockLengthReserved11 = 13,
//   ReadBlockLengthReserved12 = 14,
//   ReadBlockLengthReserved13 = 15
} EREAD_BL_LEN;

/*  DSR implementation code table  */
typedef enum{
  NotImplemented = 0,
  Implemented    = 1
} EDSR_IMP;

/*  Vdd Min. Read current consumption  */
typedef enum{
  ReadCurrentConsumptionMin0_5mA = 0,
  ReadCurrentConsumptionMin1mA   = 1,
  ReadCurrentConsumptionMin5mA   = 2,
  ReadCurrentConsumptionMin10mA  = 3,
  ReadCurrentConsumptionMin25mA  = 4,
  ReadCurrentConsumptionMin35mA  = 5,
  ReadCurrentConsumptionMin60mA  = 6,
  ReadCurrentConsumptionMin100mA = 7
} EVDD_R_CURR_MIN;

/*  Vdd Min. Write current consumption  */
typedef enum{
  WriteCurrentConsumptionMin0_5mA = 0,
  WriteCurrentConsumptionMin1mA   = 1,
  WriteCurrentConsumptionMin5mA   = 2,
  WriteCurrentConsumptionMin10mA  = 3,
  WriteCurrentConsumptionMin25mA  = 4,
  WriteCurrentConsumptionMin35mA  = 5,
  WriteCurrentConsumptionMin60mA  = 6,
  WriteCurrentConsumptionMin100mA = 7
} EVDD_W_CURR_MIN;

/*  Vdd Max. Read current consumption  */
typedef enum{
  ReadCurrentConsumptionMax1mA   = 0,
  ReadCurrentConsumptionMax5mA   = 1,
  ReadCurrentConsumptionMax10mA  = 2,
  ReadCurrentConsumptionMax25mA  = 3,
  ReadCurrentConsumptionMax35mA  = 4,
  ReadCurrentConsumptionMax45mA  = 5,
  ReadCurrentConsumptionMax80mA  = 6,
  ReadCurrentConsumptionMax200mA = 7
} EVDD_R_CURR_MAX;

/*  Vdd Max. Write current consumption  */
typedef enum{
  WriteCurrentConsumptionMax1mA   = 0,
  WriteCurrentConsumptionMax5mA   = 1,
  WriteCurrentConsumptionMax10mA  = 2,
  WriteCurrentConsumptionMax25mA  = 3,
  WriteCurrentConsumptionMax35mA  = 4,
  WriteCurrentConsumptionMax45mA  = 5,
  WriteCurrentConsumptionMax80mA  = 6,
  WriteCurrentConsumptionMax200mA = 7
} EVDD_W_CURR_MAX;

/*  Multiply factor for the device size  */
typedef enum{
  Factor2 = 0,  //   2^(0+2) = 4
  Factor3 = 1,  //   2^(0+3) = 8
  Factor4 = 2,  //   2^(0+4) = 16
  Factor5 = 3,  //   2^(0+5) = 32
  Factor6 = 4,  //   2^(0+6) = 64
  Factor7 = 5,  //   2^(0+7) = 128
  Factor8 = 6,  //   2^(0+8) = 256
  Factor9 = 7   //   2^(0+9) = 512
} EC_SIZE_MULT;

/*  Multiples of read access time  */
typedef enum{
  AccessTime1  = 0,
  AccessTime2  = 1, //  Write half as fast as read.
  AccessTime4  = 2,
  AccessTime8  = 3,
  AccessTime16 = 4,
  AccessTime32 = 5
//   AccessTimeReserved1    = 6,
//   AccessTimeReserved2    = 7
} ER2W_FACTOR;

/*  Data block length  */
typedef enum{
//   WriteBlockLengthReserved1  = 0,
//   WriteBlockLengthReserved2  = 1,
//   WriteBlockLengthReserved3  = 2,
//   WriteBlockLengthReserved4  = 3,
//   WriteBlockLengthReserved5  = 4,
//   WriteBlockLengthReserved6  = 5,
//   WriteBlockLengthReserved7  = 6,
//   WriteBlockLengthReserved8  = 7,
//   WriteBlockLengthReserved9  = 8,
  WriteBlockLengthByte512    = 9,
  WriteBlockLengthByte1024   = 10,
  WriteBlockLengthByte2048   = 11
//   WriteBlockLengthReserved10 = 12,
//   WriteBlockLengthReserved11 = 13,
//   WriteBlockLengthReserved12 = 14,
//   WriteBlockLengthReserved13 = 15
} EWRITE_BL_LEN;

/*  Defines whether the contents is original or has been copied  */
typedef enum{
  OriginalContents = 0, 
  CopiedContents   = 1
} ECOPY;

/*  File format  */
typedef enum{
  FileFormatGRPValue0 = 0,
  FileFormatGRPValue1 = 1    //  Reserved file formats.
} EFILE_FORMAT_GRP;

typedef enum{
  FileFormatValue0 = 0,   //  Hard disk-like file system with partition table.
  FileFormatValue1 = 1,   //  DOS FAT(floppy-like) with boot sector only(no partition table).
  FileFormatValue2 = 2,   //  Universal File format.
  FileFormatValue3 = 3    //  Others or unknown.
} EFILE_FORMAT;

/*  Response list  */
typedef enum{
  R1Response  = 1U,
  R1bResponse = 0U,
  R2Response  = 2U,
  R3Response  = 3U,
  R7Response  = 7U
} EResponse;



#endif  /*  __USER_STM32F4XX_SD_CARD_SPI_H__  */