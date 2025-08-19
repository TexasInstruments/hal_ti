/******************************************************************************
*  Filename:       hw_host_dma.h
*
*  Description:    Defines and prototypes for the HOST_DMA peripheral.
*
*  Copyright (c) 2023, Texas Instruments Incorporated
*  All rights reserved.
*
*  Redistribution and use in source and binary forms, with or without
*  modification, are permitted provided that the following conditions are met:
*
*  1) Redistributions of source code must retain the above copyright notice,
*     this list of conditions and the following disclaimer.
*
*  2) Redistributions in binary form must reproduce the above copyright notice,
*     this list of conditions and the following disclaimer in the documentation
*     and/or other materials provided with the distribution.
*
*  3) Neither the name of the ORGANIZATION nor the names of its contributors may
*     be used to endorse or promote products derived from this software without
*     specific prior written permission.
*
  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
*  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
*  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
*  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
*  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
*  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
*  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
*  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
*  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
*  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
*  POSSIBILITY OF SUCH DAMAGE.
*
******************************************************************************/
#ifndef __HW_HOST_DMA_H__
#define __HW_HOST_DMA_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the HOST_DMA component

--------------------------------------------------------------------------------- */

//Priority Channel Configuration
#define HOST_DMA_O_PRIOCFG                                           0x00000018U

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH0STA                                            0x00001000U

//Input Pointer Channel Transaction
#define HOST_DMA_O_CH0TIPTR                                          0x00001004U

//Output Pointer Channel Transaction
#define HOST_DMA_O_CH0OPTR                                           0x00001008U

//Transaction control
#define HOST_DMA_O_CH0TCTL                                           0x0000100CU

//DMA command interface
#define HOST_DMA_O_CH0TCTL2                                          0x00001010U

//Transaction Status
#define HOST_DMA_O_CH0TSTA                                           0x00001014U

//Job control register
#define HOST_DMA_O_CH0JCTL                                           0x0000101CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH1STA                                            0x00002000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH1TIPTR                                          0x00002004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH1TOPTR                                          0x00002008U

//Transaction control
#define HOST_DMA_O_CH1TCTL                                           0x0000200CU

//DMA command interface
#define HOST_DMA_O_CH1TCTRL2                                         0x00002010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH1TSTA                                           0x00002014U

//Job control register
#define HOST_DMA_O_CH1JCTL                                           0x0000201CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH2STA                                            0x00003000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH2TIPTR                                          0x00003004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH2TOPTR                                          0x00003008U

//Transaction control
#define HOST_DMA_O_CH2TCTL                                           0x0000300CU

//DMA command interface
#define HOST_DMA_O_CH2TCTL2                                          0x00003010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH2TSTA                                           0x00003014U

//Job control register
#define HOST_DMA_O_CH2JCTL                                           0x0000301CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH3STA                                            0x00004000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH3TIPTR                                          0x00004004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH3TOPTR                                          0x00004008U

//Transaction control
#define HOST_DMA_O_CH3TCTL                                           0x0000400CU

//DMA command interface
#define HOST_DMA_O_CH3TCTL2                                          0x00004010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH3TSTA                                           0x00004014U

//Job control register
#define HOST_DMA_O_CH3JCTL                                           0x0000401CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH4STA                                            0x00005000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH4TIPTR                                          0x00005004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH4TOPTR                                          0x00005008U

//Transaction control
#define HOST_DMA_O_CH4TCTL                                           0x0000500CU

//DMA command interface
#define HOST_DMA_O_CH4TCTL2                                          0x00005010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH4TSTA                                           0x00005014U

//Job control register
#define HOST_DMA_O_CH4JCTL                                           0x0000501CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH5STA                                            0x00006000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH5TIPTR                                          0x00006004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH5TOPTR                                          0x00006008U

//Transaction control
#define HOST_DMA_O_CH5TCTL                                           0x0000600CU

//DMA command interface
#define HOST_DMA_O_CH5TCTL2                                          0x00006010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH5TSTA                                           0x00006014U

//Job control register
#define HOST_DMA_O_CH5JCTL                                           0x0000601CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH6STA                                            0x00007000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH6TIPTR                                          0x00007004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH6TOPTR                                          0x00007008U

//Transaction control
#define HOST_DMA_O_CH6TCTL                                           0x0000700CU

//DMA command interface
#define HOST_DMA_O_CH6TCTL2                                          0x00007010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH6TSTA                                           0x00007014U

//Job control register
#define HOST_DMA_O_CH6JCTL                                           0x0000701CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH7STA                                            0x00008000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH7TIPTR                                          0x00008004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH7TOPTR                                          0x00008008U

//Transaction control
#define HOST_DMA_O_CH7TCTL                                           0x0000800CU

//DMA command interface
#define HOST_DMA_O_CH7TCTL2                                          0x00008030U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH7TSTA                                           0x00008014U

//Job control register
#define HOST_DMA_O_CH7JCTL                                           0x0000801CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH8STA                                            0x00009000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH8TIPTR                                          0x00009004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH8TOPTR                                          0x00009008U

//Transaction control
#define HOST_DMA_O_CH8TCTL                                           0x0000900CU

//DMA command interface
#define HOST_DMA_O_CH8TCTL2                                          0x00009010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH8TSTA                                           0x00009014U

//Job control register
#define HOST_DMA_O_CH8JCTL                                           0x0000901CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH9STA                                            0x0000A000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH9TIPTR                                          0x0000A004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH9TOPTR                                          0x0000A008U

//Transaction control
#define HOST_DMA_O_CH9TCTL                                           0x0000A00CU

//DMA command interface
#define HOST_DMA_O_CH9TCTL2                                          0x0000A010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH9TSTA                                           0x0000A014U

//Job control register
#define HOST_DMA_O_CH9JCTL                                           0x0000A01CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH10STA                                           0x0000B000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH10TIPTR                                         0x0000B004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH10TOPTR                                         0x0000B008U

//Transaction control
#define HOST_DMA_O_CH10TCTL                                          0x0000B00CU

//DMA command interface
#define HOST_DMA_O_CH10TCTL2                                         0x0000B010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH10TSTA                                          0x0000B014U

//Job control register
#define HOST_DMA_O_CH10JCTL                                          0x0000B01CU

//Channel Status FSM state and run indication
#define HOST_DMA_O_CH11STA                                           0x0000C000U

//32 bit address pointer of channel current input
#define HOST_DMA_O_CH11TIPTR                                         0x0000C004U

//32 bit address pointer of channel current output
#define HOST_DMA_O_CH11TOPTR                                         0x0000C008U

//Transaction control
#define HOST_DMA_O_CH11TCTL                                          0x0000C00CU

//DMA command interface
#define HOST_DMA_O_CH11TCTL2                                         0x0000C010U

//Job completion reason - either last transaction or exception
#define HOST_DMA_O_CH11TSTA                                          0x0000C014U

//Job control register
#define HOST_DMA_O_CH11JCTL                                          0x0000C01CU



/*-----------------------------------REGISTER------------------------------------
    Register name:       PRIOCFG
    Offset name:         HOST_DMA_O_PRIOCFG
    Relative address:    0x18
    Description:         Priority Channel Configuration.
    Default Value:       0x1F0F0F00

        Field:           PRIOEN
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable priority channel.
                         Enable one channel to be prioritize - no round rubin would be done

*/
#define HOST_DMA_PRIOCFG_PRIOEN                                      0x00000001U
#define HOST_DMA_PRIOCFG_PRIOEN_M                                    0x00000001U
#define HOST_DMA_PRIOCFG_PRIOEN_S                                    0U
/*

        Field:           CH1ST
        From..to bits:   8...11
        DefaultValue:    0xF
        Access type:     read-write
        Description:     First priority channel.
                         channel with highest prioriry

*/
#define HOST_DMA_PRIOCFG_CH1ST_W                                     4U
#define HOST_DMA_PRIOCFG_CH1ST_M                                     0x00000F00U
#define HOST_DMA_PRIOCFG_CH1ST_S                                     8U
/*

        Field:           CH2ND
        From..to bits:   16...19
        DefaultValue:    0xF
        Access type:     read-write
        Description:     Second priority channel.
                         channel with second highest prioriry

*/
#define HOST_DMA_PRIOCFG_CH2ND_W                                     4U
#define HOST_DMA_PRIOCFG_CH2ND_M                                     0x000F0000U
#define HOST_DMA_PRIOCFG_CH2ND_S                                     16U
/*

        Field:           MAXBLOCKS
        From..to bits:   24...28
        DefaultValue:    0x1F
        Access type:     read-write
        Description:     Maximum consecutive priority blocks.
                         Maximum consecutive block transactions of "priority channels" . After this number of consecutive blocks one of "roubd robin" channels will win arbitration. 31 means there is no limitation  on number of consecutive priority blocks

*/
#define HOST_DMA_PRIOCFG_MAXBLOCKS_W                                 5U
#define HOST_DMA_PRIOCFG_MAXBLOCKS_M                                 0x1F000000U
#define HOST_DMA_PRIOCFG_MAXBLOCKS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0STA
    Offset name:         HOST_DMA_O_CH0STA
    Relative address:    0x1000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH0STA_HWEVENT_W                                    3U
#define HOST_DMA_CH0STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH0STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:

                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH0STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH0STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH0STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH0STA_RUN                                          0x00010000U
#define HOST_DMA_CH0STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH0STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0TIPTR
    Offset name:         HOST_DMA_O_CH0TIPTR
    Relative address:    0x1004
    Description:         Input Pointer Channel Transaction.
                        32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transaction input pointer.
                         32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH0TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH0TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH0TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0OPTR
    Offset name:         HOST_DMA_O_CH0OPTR
    Relative address:    0x1008
    Description:         Output Pointer Channel Transaction.
                        32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transaction output pointer.
                         32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH0OPTR_OPTR_W                                      32U
#define HOST_DMA_CH0OPTR_OPTR_M                                      0xFFFFFFFFU
#define HOST_DMA_CH0OPTR_OPTR_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0TCTL
    Offset name:         HOST_DMA_O_CH0TCTL
    Relative address:    0x100C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Transaction bytes number.
                         Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH0TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH0TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH0TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Use burst request.
                         In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH0TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH0TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH0TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH0TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH0TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH0TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH0TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH0TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH0TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0TCTL2
    Offset name:         HOST_DMA_O_CH0TCTL2
    Relative address:    0x1010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

                         Type:Write-Clear.

*/
#define HOST_DMA_CH0TCTL2_CMD_W                                      3U
#define HOST_DMA_CH0TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH0TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0TSTA
    Offset name:         HOST_DMA_O_CH0TSTA
    Relative address:    0x1014
    Description:         Transaction Status.
                        Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH0TSTA_STA                                         0x00000001U
#define HOST_DMA_CH0TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH0TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Word offset.
                         Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH0TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH0TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH0TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Remain bytes number.
                         Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH0TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH0TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH0TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH0JCTL
    Offset name:         HOST_DMA_O_CH0JCTL
    Relative address:    0x101C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH0JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH0JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH0JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH0JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH0JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH0JCTL_BLKSIZE_S                                   16U
/*

        Field:           BLKMODESRC
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     source pointer wrap around mode

                         0: no wrap around(non block mode)
                         1: with wrap around(block mode)

*/
#define HOST_DMA_CH0JCTL_BLKMODESRC                                  0x01000000U
#define HOST_DMA_CH0JCTL_BLKMODESRC_M                                0x01000000U
#define HOST_DMA_CH0JCTL_BLKMODESRC_S                                24U
/*

        Field:           BLKMODEDST
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer wrap around mode

                         0: no wrap around(non block mode)
                         1: with wrap around(block mode)

*/
#define HOST_DMA_CH0JCTL_BLKMODEDST                                  0x02000000U
#define HOST_DMA_CH0JCTL_BLKMODEDST_M                                0x02000000U
#define HOST_DMA_CH0JCTL_BLKMODEDST_S                                25U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH0JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH0JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH0JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH0JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH0JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH0JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH0JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH0JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH0JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH0JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH0JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH0JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH0JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH0JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH0JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1STA
    Offset name:         HOST_DMA_O_CH1STA
    Relative address:    0x2000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH1STA_HWEVENT_W                                    3U
#define HOST_DMA_CH1STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH1STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH1STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH1STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH1STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH1STA_RUN                                          0x00010000U
#define HOST_DMA_CH1STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH1STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1TIPTR
    Offset name:         HOST_DMA_O_CH1TIPTR
    Relative address:    0x2004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH1TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH1TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH1TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1TOPTR
    Offset name:         HOST_DMA_O_CH1TOPTR
    Relative address:    0x2008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH1TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH1TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH1TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1TCTL
    Offset name:         HOST_DMA_O_CH1TCTL
    Relative address:    0x200C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH1TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH1TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH1TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH1TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH1TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH1TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH1TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH1TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH1TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH1TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH1TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH1TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1TCTRL2
    Offset name:         HOST_DMA_O_CH1TCTRL2
    Relative address:    0x2010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH1TCTRL2_CMD_W                                     3U
#define HOST_DMA_CH1TCTRL2_CMD_M                                     0x00000007U
#define HOST_DMA_CH1TCTRL2_CMD_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1TSTA
    Offset name:         HOST_DMA_O_CH1TSTA
    Relative address:    0x2014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH1TSTA_STA                                         0x00000001U
#define HOST_DMA_CH1TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH1TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH1TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH1TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH1TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH1TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH1TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH1TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH1JCTL
    Offset name:         HOST_DMA_O_CH1JCTL
    Relative address:    0x201C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH1JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH1JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH1JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH1JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH1JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH1JCTL_BLKSIZE_S                                   16U
/*

        Field:           BLKMODESRC
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-write
        Description:     source pointer wrap around mode

                         0: no wrap around(non block mode)
                         1: with wrap around(block mode)

*/
#define HOST_DMA_CH1JCTL_BLKMODESRC                                  0x01000000U
#define HOST_DMA_CH1JCTL_BLKMODESRC_M                                0x01000000U
#define HOST_DMA_CH1JCTL_BLKMODESRC_S                                24U
/*

        Field:           BLKMODEDST
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer wrap around mode

                         0: no wrap around(non block mode)
                         1: with wrap around(block mode)

*/
#define HOST_DMA_CH1JCTL_BLKMODEDST                                  0x02000000U
#define HOST_DMA_CH1JCTL_BLKMODEDST_M                                0x02000000U
#define HOST_DMA_CH1JCTL_BLKMODEDST_S                                25U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH1JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH1JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH1JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH1JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH1JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH1JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH1JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH1JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH1JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH1JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH1JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH1JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH1JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH1JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH1JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2STA
    Offset name:         HOST_DMA_O_CH2STA
    Relative address:    0x3000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH2STA_HWEVENT_W                                    3U
#define HOST_DMA_CH2STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH2STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH2STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH2STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH2STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH2STA_RUN                                          0x00010000U
#define HOST_DMA_CH2STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH2STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2TIPTR
    Offset name:         HOST_DMA_O_CH2TIPTR
    Relative address:    0x3004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH2TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH2TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH2TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2TOPTR
    Offset name:         HOST_DMA_O_CH2TOPTR
    Relative address:    0x3008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH2TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH2TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH2TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2TCTL
    Offset name:         HOST_DMA_O_CH2TCTL
    Relative address:    0x300C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH2TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH2TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH2TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH2TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH2TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH2TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH2TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH2TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH2TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH2TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH2TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH2TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2TCTL2
    Offset name:         HOST_DMA_O_CH2TCTL2
    Relative address:    0x3010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH2TCTL2_CMD_W                                      3U
#define HOST_DMA_CH2TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH2TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2TSTA
    Offset name:         HOST_DMA_O_CH2TSTA
    Relative address:    0x3014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH2TSTA_STA                                         0x00000001U
#define HOST_DMA_CH2TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH2TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH2TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH2TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH2TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH2TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH2TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH2TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH2JCTL
    Offset name:         HOST_DMA_O_CH2JCTL
    Relative address:    0x301C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH2JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH2JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH2JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH2JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH2JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH2JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH2JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH2JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH2JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH2JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH2JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH2JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH2JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH2JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH2JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH2JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH2JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH2JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH2JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH2JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH2JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3STA
    Offset name:         HOST_DMA_O_CH3STA
    Relative address:    0x4000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH3STA_HWEVENT_W                                    3U
#define HOST_DMA_CH3STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH3STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH3STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH3STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH3STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH3STA_RUN                                          0x00010000U
#define HOST_DMA_CH3STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH3STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3TIPTR
    Offset name:         HOST_DMA_O_CH3TIPTR
    Relative address:    0x4004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH3TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH3TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH3TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3TOPTR
    Offset name:         HOST_DMA_O_CH3TOPTR
    Relative address:    0x4008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH3TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH3TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH3TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3TCTL
    Offset name:         HOST_DMA_O_CH3TCTL
    Relative address:    0x400C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH3TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH3TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH3TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH3TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH3TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH3TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH3TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH3TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH3TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH3TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH3TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH3TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3TCTL2
    Offset name:         HOST_DMA_O_CH3TCTL2
    Relative address:    0x4010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH3TCTL2_CMD_W                                      3U
#define HOST_DMA_CH3TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH3TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3TSTA
    Offset name:         HOST_DMA_O_CH3TSTA
    Relative address:    0x4014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH3TSTA_STA                                         0x00000001U
#define HOST_DMA_CH3TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH3TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH3TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH3TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH3TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH3TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH3TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH3TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH3JCTL
    Offset name:         HOST_DMA_O_CH3JCTL
    Relative address:    0x401C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH3JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH3JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH3JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH3JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH3JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH3JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH3JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH3JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH3JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH3JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH3JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH3JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH3JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH3JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH3JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH3JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH3JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH3JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH3JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH3JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH3JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4STA
    Offset name:         HOST_DMA_O_CH4STA
    Relative address:    0x5000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH4STA_HWEVENT_W                                    3U
#define HOST_DMA_CH4STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH4STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH4STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH4STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH4STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH4STA_RUN                                          0x00010000U
#define HOST_DMA_CH4STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH4STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4TIPTR
    Offset name:         HOST_DMA_O_CH4TIPTR
    Relative address:    0x5004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           INPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH4TIPTR_INPTR_W                                    32U
#define HOST_DMA_CH4TIPTR_INPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH4TIPTR_INPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4TOPTR
    Offset name:         HOST_DMA_O_CH4TOPTR
    Relative address:    0x5008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH4TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH4TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH4TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4TCTL
    Offset name:         HOST_DMA_O_CH4TCTL
    Relative address:    0x500C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH4TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH4TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH4TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH4TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH4TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH4TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH4TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH4TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH4TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH4TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH4TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH4TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4TCTL2
    Offset name:         HOST_DMA_O_CH4TCTL2
    Relative address:    0x5010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH4TCTL2_CMD_W                                      3U
#define HOST_DMA_CH4TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH4TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4TSTA
    Offset name:         HOST_DMA_O_CH4TSTA
    Relative address:    0x5014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH4TSTA_STA                                         0x00000001U
#define HOST_DMA_CH4TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH4TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH4TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH4TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH4TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH4TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH4TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH4TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH4JCTL
    Offset name:         HOST_DMA_O_CH4JCTL
    Relative address:    0x501C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH4JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH4JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH4JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH4JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH4JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH4JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH4JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH4JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH4JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH4JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH4JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH4JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH4JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH4JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH4JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH4JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH4JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH4JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH4JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH4JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH4JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5STA
    Offset name:         HOST_DMA_O_CH5STA
    Relative address:    0x6000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH5STA_HWEVENT_W                                    3U
#define HOST_DMA_CH5STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH5STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH5STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH5STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH5STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH5STA_RUN                                          0x00010000U
#define HOST_DMA_CH5STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH5STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5TIPTR
    Offset name:         HOST_DMA_O_CH5TIPTR
    Relative address:    0x6004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH5TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH5TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH5TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5TOPTR
    Offset name:         HOST_DMA_O_CH5TOPTR
    Relative address:    0x6008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH5TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH5TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH5TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5TCTL
    Offset name:         HOST_DMA_O_CH5TCTL
    Relative address:    0x600C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH5TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH5TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH5TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH5TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH5TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH5TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH5TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH5TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH5TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH5TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH5TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH5TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5TCTL2
    Offset name:         HOST_DMA_O_CH5TCTL2
    Relative address:    0x6010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH5TCTL2_CMD_W                                      3U
#define HOST_DMA_CH5TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH5TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5TSTA
    Offset name:         HOST_DMA_O_CH5TSTA
    Relative address:    0x6014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH5TSTA_STA                                         0x00000001U
#define HOST_DMA_CH5TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH5TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH5TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH5TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH5TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH5TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH5TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH5TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH5JCTL
    Offset name:         HOST_DMA_O_CH5JCTL
    Relative address:    0x601C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH5JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH5JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH5JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH5JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH5JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH5JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH5JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH5JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH5JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH5JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH5JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH5JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH5JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH5JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH5JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH5JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH5JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH5JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH5JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH5JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH5JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6STA
    Offset name:         HOST_DMA_O_CH6STA
    Relative address:    0x7000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH6STA_HWEVENT_W                                    3U
#define HOST_DMA_CH6STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH6STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH6STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH6STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH6STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH6STA_RUN                                          0x00010000U
#define HOST_DMA_CH6STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH6STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6TIPTR
    Offset name:         HOST_DMA_O_CH6TIPTR
    Relative address:    0x7004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH6TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH6TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH6TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6TOPTR
    Offset name:         HOST_DMA_O_CH6TOPTR
    Relative address:    0x7008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH6TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH6TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH6TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6TCTL
    Offset name:         HOST_DMA_O_CH6TCTL
    Relative address:    0x700C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH6TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH6TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH6TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH6TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH6TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH6TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH6TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH6TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH6TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH6TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH6TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH6TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6TCTL2
    Offset name:         HOST_DMA_O_CH6TCTL2
    Relative address:    0x7010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH6TCTL2_CMD_W                                      3U
#define HOST_DMA_CH6TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH6TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6TSTA
    Offset name:         HOST_DMA_O_CH6TSTA
    Relative address:    0x7014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH6TSTA_STA                                         0x00000001U
#define HOST_DMA_CH6TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH6TSTA_STA_S                                       0U
/*

        Field:           WORDOFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH6TSTA_WORDOFFSET_W                                8U
#define HOST_DMA_CH6TSTA_WORDOFFSET_M                                0x0000FF00U
#define HOST_DMA_CH6TSTA_WORDOFFSET_S                                8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH6TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH6TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH6TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH6JCTL
    Offset name:         HOST_DMA_O_CH6JCTL
    Relative address:    0x701C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH6JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH6JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH6JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH6JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH6JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH6JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH6JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH6JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH6JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH6JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH6JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH6JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH6JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH6JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH6JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH6JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH6JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH6JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH6JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH6JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH6JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7STA
    Offset name:         HOST_DMA_O_CH7STA
    Relative address:    0x8000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH7STA_HWEVENT_W                                    3U
#define HOST_DMA_CH7STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH7STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH7STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH7STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH7STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH7STA_RUN                                          0x00010000U
#define HOST_DMA_CH7STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH7STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7TIPTR
    Offset name:         HOST_DMA_O_CH7TIPTR
    Relative address:    0x8004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH7TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH7TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH7TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7TOPTR
    Offset name:         HOST_DMA_O_CH7TOPTR
    Relative address:    0x8008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH7TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH7TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH7TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7TCTL
    Offset name:         HOST_DMA_O_CH7TCTL
    Relative address:    0x800C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH7TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH7TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH7TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH7TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH7TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH7TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH7TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH7TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH7TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH7TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH7TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH7TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7TCTL2
    Offset name:         HOST_DMA_O_CH7TCTL2
    Relative address:    0x8030
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH7TCTL2_CMD_W                                      3U
#define HOST_DMA_CH7TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH7TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7TSTA
    Offset name:         HOST_DMA_O_CH7TSTA
    Relative address:    0x8014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH7TSTA_STA                                         0x00000001U
#define HOST_DMA_CH7TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH7TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH7TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH7TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH7TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH7TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH7TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH7TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH7JCTL
    Offset name:         HOST_DMA_O_CH7JCTL
    Relative address:    0x801C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH7JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH7JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH7JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH7JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH7JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH7JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH7JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH7JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH7JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH7JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH7JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH7JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH7JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH7JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH7JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH7JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH7JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH7JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH7JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH7JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH7JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8STA
    Offset name:         HOST_DMA_O_CH8STA
    Relative address:    0x9000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH8STA_HWEVENT_W                                    3U
#define HOST_DMA_CH8STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH8STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH8STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH8STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH8STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH8STA_RUN                                          0x00010000U
#define HOST_DMA_CH8STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH8STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8TIPTR
    Offset name:         HOST_DMA_O_CH8TIPTR
    Relative address:    0x9004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH8TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH8TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH8TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8TOPTR
    Offset name:         HOST_DMA_O_CH8TOPTR
    Relative address:    0x9008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH8TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH8TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH8TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8TCTL
    Offset name:         HOST_DMA_O_CH8TCTL
    Relative address:    0x900C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH8TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH8TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH8TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH8TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH8TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH8TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH8TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH8TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH8TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH8TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH8TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH8TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8TCTL2
    Offset name:         HOST_DMA_O_CH8TCTL2
    Relative address:    0x9010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH8TCTL2_CMD_W                                      3U
#define HOST_DMA_CH8TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH8TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8TSTA
    Offset name:         HOST_DMA_O_CH8TSTA
    Relative address:    0x9014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH8TSTA_STA                                         0x00000001U
#define HOST_DMA_CH8TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH8TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH8TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH8TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH8TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH8TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH8TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH8TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH8JCTL
    Offset name:         HOST_DMA_O_CH8JCTL
    Relative address:    0x901C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH8JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH8JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH8JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH8JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH8JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH8JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH8JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH8JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH8JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH8JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH8JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH8JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH8JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH8JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH8JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH8JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH8JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH8JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH8JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH8JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH8JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9STA
    Offset name:         HOST_DMA_O_CH9STA
    Relative address:    0xA000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH9STA_HWEVENT_W                                    3U
#define HOST_DMA_CH9STA_HWEVENT_M                                    0x00000007U
#define HOST_DMA_CH9STA_HWEVENT_S                                    0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH9STA_FSMSTATE_W                                   4U
#define HOST_DMA_CH9STA_FSMSTATE_M                                   0x00000F00U
#define HOST_DMA_CH9STA_FSMSTATE_S                                   8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH9STA_RUN                                          0x00010000U
#define HOST_DMA_CH9STA_RUN_M                                        0x00010000U
#define HOST_DMA_CH9STA_RUN_S                                        16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9TIPTR
    Offset name:         HOST_DMA_O_CH9TIPTR
    Relative address:    0xA004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH9TIPTR_IPTR_W                                     32U
#define HOST_DMA_CH9TIPTR_IPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH9TIPTR_IPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9TOPTR
    Offset name:         HOST_DMA_O_CH9TOPTR
    Relative address:    0xA008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH9TOPTR_OPTR_W                                     32U
#define HOST_DMA_CH9TOPTR_OPTR_M                                     0xFFFFFFFFU
#define HOST_DMA_CH9TOPTR_OPTR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9TCTL
    Offset name:         HOST_DMA_O_CH9TCTL
    Relative address:    0xA00C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH9TCTL_TRANSB_W                                    14U
#define HOST_DMA_CH9TCTL_TRANSB_M                                    0x00003FFFU
#define HOST_DMA_CH9TCTL_TRANSB_S                                    0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH9TCTL_BURSTREQ                                    0x00010000U
#define HOST_DMA_CH9TCTL_BURSTREQ_M                                  0x00010000U
#define HOST_DMA_CH9TCTL_BURSTREQ_S                                  16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH9TCTL_SPARE                                       0x00020000U
#define HOST_DMA_CH9TCTL_SPARE_M                                     0x00020000U
#define HOST_DMA_CH9TCTL_SPARE_S                                     17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH9TCTL_ENDIANESS_W                                 2U
#define HOST_DMA_CH9TCTL_ENDIANESS_M                                 0x03000000U
#define HOST_DMA_CH9TCTL_ENDIANESS_S                                 24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9TCTL2
    Offset name:         HOST_DMA_O_CH9TCTL2
    Relative address:    0xA010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH9TCTL2_CMD_W                                      3U
#define HOST_DMA_CH9TCTL2_CMD_M                                      0x00000007U
#define HOST_DMA_CH9TCTL2_CMD_S                                      0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9TSTA
    Offset name:         HOST_DMA_O_CH9TSTA
    Relative address:    0xA014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH9TSTA_STA                                         0x00000001U
#define HOST_DMA_CH9TSTA_STA_M                                       0x00000001U
#define HOST_DMA_CH9TSTA_STA_S                                       0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH9TSTA_OFFSET_W                                    8U
#define HOST_DMA_CH9TSTA_OFFSET_M                                    0x0000FF00U
#define HOST_DMA_CH9TSTA_OFFSET_S                                    8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH9TSTA_REMAINB_W                                   14U
#define HOST_DMA_CH9TSTA_REMAINB_M                                   0x3FFF0000U
#define HOST_DMA_CH9TSTA_REMAINB_S                                   16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH9JCTL
    Offset name:         HOST_DMA_O_CH9JCTL
    Relative address:    0xA01C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH9JCTL_WORDSIZE_W                                  2U
#define HOST_DMA_CH9JCTL_WORDSIZE_M                                  0x00000003U
#define HOST_DMA_CH9JCTL_WORDSIZE_S                                  0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH9JCTL_BLKSIZE_W                                   6U
#define HOST_DMA_CH9JCTL_BLKSIZE_M                                   0x003F0000U
#define HOST_DMA_CH9JCTL_BLKSIZE_S                                   16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH9JCTL_DMASIGBPS                                   0x04000000U
#define HOST_DMA_CH9JCTL_DMASIGBPS_M                                 0x04000000U
#define HOST_DMA_CH9JCTL_DMASIGBPS_S                                 26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH9JCTL_FIFOMODS                                    0x08000000U
#define HOST_DMA_CH9JCTL_FIFOMODS_M                                  0x08000000U
#define HOST_DMA_CH9JCTL_FIFOMODS_S                                  27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH9JCTL_FIFOMODD                                    0x10000000U
#define HOST_DMA_CH9JCTL_FIFOMODD_M                                  0x10000000U
#define HOST_DMA_CH9JCTL_FIFOMODD_S                                  28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH9JCTL_SRCDSTCFG                                   0x20000000U
#define HOST_DMA_CH9JCTL_SRCDSTCFG_M                                 0x20000000U
#define HOST_DMA_CH9JCTL_SRCDSTCFG_S                                 29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH9JCTL_ENCLR                                       0x40000000U
#define HOST_DMA_CH9JCTL_ENCLR_M                                     0x40000000U
#define HOST_DMA_CH9JCTL_ENCLR_S                                     30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10STA
    Offset name:         HOST_DMA_O_CH10STA
    Relative address:    0xB000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH10STA_HWEVENT_W                                   3U
#define HOST_DMA_CH10STA_HWEVENT_M                                   0x00000007U
#define HOST_DMA_CH10STA_HWEVENT_S                                   0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH10STA_FSMSTATE_W                                  4U
#define HOST_DMA_CH10STA_FSMSTATE_M                                  0x00000F00U
#define HOST_DMA_CH10STA_FSMSTATE_S                                  8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH10STA_RUN                                         0x00010000U
#define HOST_DMA_CH10STA_RUN_M                                       0x00010000U
#define HOST_DMA_CH10STA_RUN_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10TIPTR
    Offset name:         HOST_DMA_O_CH10TIPTR
    Relative address:    0xB004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH10TIPTR_IPTR_W                                    32U
#define HOST_DMA_CH10TIPTR_IPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH10TIPTR_IPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10TOPTR
    Offset name:         HOST_DMA_O_CH10TOPTR
    Relative address:    0xB008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH10TOPTR_OPTR_W                                    32U
#define HOST_DMA_CH10TOPTR_OPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH10TOPTR_OPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10TCTL
    Offset name:         HOST_DMA_O_CH10TCTL
    Relative address:    0xB00C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH10TCTL_TRANSB_W                                   14U
#define HOST_DMA_CH10TCTL_TRANSB_M                                   0x00003FFFU
#define HOST_DMA_CH10TCTL_TRANSB_S                                   0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH10TCTL_BURSTREQ                                   0x00010000U
#define HOST_DMA_CH10TCTL_BURSTREQ_M                                 0x00010000U
#define HOST_DMA_CH10TCTL_BURSTREQ_S                                 16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH10TCTL_SPARE                                      0x00020000U
#define HOST_DMA_CH10TCTL_SPARE_M                                    0x00020000U
#define HOST_DMA_CH10TCTL_SPARE_S                                    17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH10TCTL_ENDIANESS_W                                2U
#define HOST_DMA_CH10TCTL_ENDIANESS_M                                0x03000000U
#define HOST_DMA_CH10TCTL_ENDIANESS_S                                24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10TCTL2
    Offset name:         HOST_DMA_O_CH10TCTL2
    Relative address:    0xB010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH10TCTL2_CMD_W                                     3U
#define HOST_DMA_CH10TCTL2_CMD_M                                     0x00000007U
#define HOST_DMA_CH10TCTL2_CMD_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10TSTA
    Offset name:         HOST_DMA_O_CH10TSTA
    Relative address:    0xB014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH10TSTA_STA                                        0x00000001U
#define HOST_DMA_CH10TSTA_STA_M                                      0x00000001U
#define HOST_DMA_CH10TSTA_STA_S                                      0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH10TSTA_OFFSET_W                                   8U
#define HOST_DMA_CH10TSTA_OFFSET_M                                   0x0000FF00U
#define HOST_DMA_CH10TSTA_OFFSET_S                                   8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH10TSTA_REMAINB_W                                  14U
#define HOST_DMA_CH10TSTA_REMAINB_M                                  0x3FFF0000U
#define HOST_DMA_CH10TSTA_REMAINB_S                                  16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH10JCTL
    Offset name:         HOST_DMA_O_CH10JCTL
    Relative address:    0xB01C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH10JCTL_WORDSIZE_W                                 2U
#define HOST_DMA_CH10JCTL_WORDSIZE_M                                 0x00000003U
#define HOST_DMA_CH10JCTL_WORDSIZE_S                                 0U
/*

        Field:           BLKSIZE
        From..to bits:   16...23
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH10JCTL_BLKSIZE_W                                  8U
#define HOST_DMA_CH10JCTL_BLKSIZE_M                                  0x00FF0000U
#define HOST_DMA_CH10JCTL_BLKSIZE_S                                  16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH10JCTL_DMASIGBPS                                  0x04000000U
#define HOST_DMA_CH10JCTL_DMASIGBPS_M                                0x04000000U
#define HOST_DMA_CH10JCTL_DMASIGBPS_S                                26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH10JCTL_FIFOMODS                                   0x08000000U
#define HOST_DMA_CH10JCTL_FIFOMODS_M                                 0x08000000U
#define HOST_DMA_CH10JCTL_FIFOMODS_S                                 27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH10JCTL_FIFOMODD                                   0x10000000U
#define HOST_DMA_CH10JCTL_FIFOMODD_M                                 0x10000000U
#define HOST_DMA_CH10JCTL_FIFOMODD_S                                 28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH10JCTL_SRCDSTCFG                                  0x20000000U
#define HOST_DMA_CH10JCTL_SRCDSTCFG_M                                0x20000000U
#define HOST_DMA_CH10JCTL_SRCDSTCFG_S                                29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH10JCTL_ENCLR                                      0x40000000U
#define HOST_DMA_CH10JCTL_ENCLR_M                                    0x40000000U
#define HOST_DMA_CH10JCTL_ENCLR_S                                    30U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11STA
    Offset name:         HOST_DMA_O_CH11STA
    Relative address:    0xC000
    Description:         Channel Status FSM state and run indication.
    Default Value:       0x00000000

        Field:           HWEVENT
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     HW event status.
                         Channel status is a bit mask. Multiple bits can be set at the same time
                         0. PROCESSING
                         1. TRANS DONE
                         2. ABORT
                         4. EXCEPTION

*/
#define HOST_DMA_CH11STA_HWEVENT_W                                   3U
#define HOST_DMA_CH11STA_HWEVENT_M                                   0x00000007U
#define HOST_DMA_CH11STA_HWEVENT_S                                   0U
/*

        Field:           FSMSTATE
        From..to bits:   8...11
        DefaultValue:    0x0
        Access type:     read-only
        Description:     FSM state:
                         0x0. IDLE
                         0x2. EXCEPTION
                         0x3. DRAIN
                         0x4. ABORT
                         0x8. PENDING ARB
                         0x9. COPY
                         0xA. COPY LAST
                         0xC. DONE
                         0xD. SAVE CTX
                         0xE. WAIT NEXT TRANS
                         0xF. LAST

*/
#define HOST_DMA_CH11STA_FSMSTATE_W                                  4U
#define HOST_DMA_CH11STA_FSMSTATE_M                                  0x00000F00U
#define HOST_DMA_CH11STA_FSMSTATE_S                                  8U
/*

        Field:           RUN
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Indication that channel is currently transfering data and is not idle.
                         Channels that are waiting on arbitration are considered running.

*/
#define HOST_DMA_CH11STA_RUN                                         0x00010000U
#define HOST_DMA_CH11STA_RUN_M                                       0x00010000U
#define HOST_DMA_CH11STA_RUN_S                                       16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11TIPTR
    Offset name:         HOST_DMA_O_CH11TIPTR
    Relative address:    0xC004
    Description:         32 bit address pointer of channel current input.
    Default Value:       0x00000000

        Field:           IPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current input.

*/
#define HOST_DMA_CH11TIPTR_IPTR_W                                    32U
#define HOST_DMA_CH11TIPTR_IPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH11TIPTR_IPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11TOPTR
    Offset name:         HOST_DMA_O_CH11TOPTR
    Relative address:    0xC008
    Description:         32 bit address pointer of channel current output.
    Default Value:       0x00000000

        Field:           OPTR
        From..to bits:   0...31
        DefaultValue:    0x0
        Access type:     read-write
        Description:     32 bit address pointer of channel current output.

*/
#define HOST_DMA_CH11TOPTR_OPTR_W                                    32U
#define HOST_DMA_CH11TOPTR_OPTR_M                                    0xFFFFFFFFU
#define HOST_DMA_CH11TOPTR_OPTR_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11TCTL
    Offset name:         HOST_DMA_O_CH11TCTL
    Relative address:    0xC00C
    Description:         Transaction control
    Default Value:       0x00000000

        Field:           TRANSB
        From..to bits:   0...13
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Number of bytes of the transaction to move from source to destination.

*/
#define HOST_DMA_CH11TCTL_TRANSB_W                                   14U
#define HOST_DMA_CH11TCTL_TRANSB_M                                   0x00003FFFU
#define HOST_DMA_CH11TCTL_TRANSB_S                                   0U
/*

        Field:           BURSTREQ
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-write
        Description:     In case number of words to tranfer smaller than block size, DMA would use signle request and work with block size of 1 word. In case we know request would be set on altough number of words to tranfer is smaller than block size, we can set this field on and DMA will wait for block_request and transact all remaining words in one block.

*/
#define HOST_DMA_CH11TCTL_BURSTREQ                                   0x00010000U
#define HOST_DMA_CH11TCTL_BURSTREQ_M                                 0x00010000U
#define HOST_DMA_CH11TCTL_BURSTREQ_S                                 16U
/*

        Field:           SPARE
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-write
        Description:     spare

*/
#define HOST_DMA_CH11TCTL_SPARE                                      0x00020000U
#define HOST_DMA_CH11TCTL_SPARE_M                                    0x00020000U
#define HOST_DMA_CH11TCTL_SPARE_S                                    17U
/*

        Field:           ENDIANESS
        From..to bits:   24...25
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 -no endianess, 1 - byte endianess, 2 - bit endianess

*/
#define HOST_DMA_CH11TCTL_ENDIANESS_W                                2U
#define HOST_DMA_CH11TCTL_ENDIANESS_M                                0x03000000U
#define HOST_DMA_CH11TCTL_ENDIANESS_S                                24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11TCTL2
    Offset name:         HOST_DMA_O_CH11TCTL2
    Relative address:    0xC010
    Description:         DMA command interface
    Default Value:       0x00000000

        Field:           CMD
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     write-only
        Description:     1 - run command. Start a transaction.
                         2-  abort command - stop reansaction.
                         4-  init command - init new transaction afet abort/error.

*/
#define HOST_DMA_CH11TCTL2_CMD_W                                     3U
#define HOST_DMA_CH11TCTL2_CMD_M                                     0x00000007U
#define HOST_DMA_CH11TCTL2_CMD_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11TSTA
    Offset name:         HOST_DMA_O_CH11TSTA
    Relative address:    0xC014
    Description:         Job completion reason - either last transaction or exception
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     channel OCP rstatus recieved at one of the primary ports.
                         Once an error is encountered the channel will enter an Exception state and stay the until an init command is recieved.
                         ICLR does not affect this status.

*/
#define HOST_DMA_CH11TSTA_STA                                        0x00000001U
#define HOST_DMA_CH11TSTA_STA_M                                      0x00000001U
#define HOST_DMA_CH11TSTA_STA_S                                      0U
/*

        Field:           OFFSET
        From..to bits:   8...15
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Offset in words from block boundary. Actually number of word have been transferred in this block

*/
#define HOST_DMA_CH11TSTA_OFFSET_W                                   8U
#define HOST_DMA_CH11TSTA_OFFSET_M                                   0x0000FF00U
#define HOST_DMA_CH11TSTA_OFFSET_S                                   8U
/*

        Field:           REMAINB
        From..to bits:   16...29
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Number of bytes remaining to complete the transaction.

*/
#define HOST_DMA_CH11TSTA_REMAINB_W                                  14U
#define HOST_DMA_CH11TSTA_REMAINB_M                                  0x3FFF0000U
#define HOST_DMA_CH11TSTA_REMAINB_S                                  16U


/*-----------------------------------REGISTER------------------------------------
    Register name:       CH11JCTL
    Offset name:         HOST_DMA_O_CH11JCTL
    Relative address:    0xC01C
    Description:         Job control register
    Default Value:       0x00000000

        Field:           WORDSIZE
        From..to bits:   0...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     00 -word size is 32 bits
                         01 -word size is 16 bits
                         10 -word size is 8  bits

*/
#define HOST_DMA_CH11JCTL_WORDSIZE_W                                 2U
#define HOST_DMA_CH11JCTL_WORDSIZE_M                                 0x00000003U
#define HOST_DMA_CH11JCTL_WORDSIZE_S                                 0U
/*

        Field:           BLKSIZE
        From..to bits:   16...21
        DefaultValue:    0x0
        Access type:     read-write
        Description:     size of the block in words. If block mode is enabled, defines the address wrap around.
                         Since channel arbitration decisions are made every block, this also effect how much bandwidth is given to a specific channel.



*/
#define HOST_DMA_CH11JCTL_BLKSIZE_W                                  6U
#define HOST_DMA_CH11JCTL_BLKSIZE_M                                  0x003F0000U
#define HOST_DMA_CH11JCTL_BLKSIZE_S                                  16U
/*

        Field:           DMASIGBPS
        From..to bits:   26...26
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Tie high channel DMA req signal. This is useful for memory to memort transaction

*/
#define HOST_DMA_CH11JCTL_DMASIGBPS                                  0x04000000U
#define HOST_DMA_CH11JCTL_DMASIGBPS_M                                0x04000000U
#define HOST_DMA_CH11JCTL_DMASIGBPS_S                                26U
/*

        Field:           FIFOMODS
        From..to bits:   27...27
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Source pointer fifo  mode

*/
#define HOST_DMA_CH11JCTL_FIFOMODS                                   0x08000000U
#define HOST_DMA_CH11JCTL_FIFOMODS_M                                 0x08000000U
#define HOST_DMA_CH11JCTL_FIFOMODS_S                                 27U
/*

        Field:           FIFOMODD
        From..to bits:   28...28
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Destination pointer fifo  mode

*/
#define HOST_DMA_CH11JCTL_FIFOMODD                                   0x10000000U
#define HOST_DMA_CH11JCTL_FIFOMODD_M                                 0x10000000U
#define HOST_DMA_CH11JCTL_FIFOMODD_S                                 28U
/*

        Field:           SRCDSTCFG
        From..to bits:   29...29
        DefaultValue:    0x0
        Access type:     read-write
        Description:     0 - Sorce is periph: transaction from periph to memory.
                         1 - Destination is periph  :transaction from Memory to periph

*/
#define HOST_DMA_CH11JCTL_SRCDSTCFG                                  0x20000000U
#define HOST_DMA_CH11JCTL_SRCDSTCFG_M                                0x20000000U
#define HOST_DMA_CH11JCTL_SRCDSTCFG_S                                29U
/*

        Field:           ENCLR
        From..to bits:   30...30
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Enable DMA to set a rd/wr clear pulse at the beginning of a job (one cycle after run cmd)

*/
#define HOST_DMA_CH11JCTL_ENCLR                                      0x40000000U
#define HOST_DMA_CH11JCTL_ENCLR_M                                    0x40000000U
#define HOST_DMA_CH11JCTL_ENCLR_S                                    30U

#endif /* __HW_HOST_DMA_H__*/
