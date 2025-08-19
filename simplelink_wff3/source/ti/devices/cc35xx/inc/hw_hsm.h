/******************************************************************************
*  Filename:       hw_hsm.h
*
*  Description:    Defines and prototypes for the HSM peripheral.
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
#ifndef __HW_HSM_H__
#define __HW_HSM_H__
/*-------------------------------------------------------------------------------

This section defines the register offsets of the HSM component

--------------------------------------------------------------------------------- */

//Input MAILBOX1
#define HSM_O_EIP130_072_MAILBOX1_IN                                 0x00000000U

//Input MAILBOX2
#define HSM_O_EIP130_072_MAILBOX2_IN                                 0x00000400U

//AIC Polarity Control Register
#define HSM_O_AIC_POL_CTRL                                           0x00003E00U

//AIC Type Control Register
#define HSM_O_AIC_TYPE_CTRL                                          0x00003E04U

//AIC Enable Control Register
#define HSM_O_AIC_ENABLE_CTRL                                        0x00003E08U

//AIC Raw Source Status Register
#define HSM_O_AIC_RAW_STAT                                           0x00003E0CU

//AIC Enable Set Registers
#define HSM_O_AICENSET                                               0x00003E0CU

//AIC Enabled Status Register
#define HSM_O_AIC_ENABLED_STAT                                       0x00003E10U

//AIC Acknowledge Register
#define HSM_O_AICACK                                                 0x00003E10U

//AIC Enable Clear Register
#define HSM_O_AIC_ENABLE_CLR                                         0x00003E14U

//AIC Options Register
#define HSM_O_AIC_OPTIONS                                            0x00003E18U

//AIC Version Register
#define HSM_O_AIC_VERSION                                            0x00003E1CU

//Mailbox Status Register
#define HSM_O_MAILBOX_STAT                                           0x00003F00U

//Mailbox Control Register
#define HSM_O_MBXCTL                                                 0x00003F00U

//Raw (unmasked) Mailbox Status Register
#define HSM_O_MAILBOX_RAWSTAT                                        0x00003F04U

//Mailbox Reset Register
#define HSM_O_MBXRST                                                 0x00003F04U

//Mailbox Status - linked Host IDs Register
#define HSM_O_MAILBOX_LINKID                                         0x00003F08U

//Mailbox Status - output Host IDs Register
#define HSM_O_MAILBOX_OUTID                                          0x00003F0CU

//Host/Mailbox1-4  lockout control Register
#define HSM_O_MAILBOX_LOCKOUT                                        0x00003F10U

//Module Status Register
#define HSM_O_MODULE_STATUS                                          0x00003FE0U

//VaultIP configured options(2)
#define HSM_O_EIP_OPTIONS2                                           0x00003FF4U

//VaultIP configured options(1)
#define HSM_O_EIP_OPTIONS                                            0x00003FF8U

//Standard EIP version register
#define HSM_O_EIP_VERSION                                            0x00003FFCU



/*-----------------------------------REGISTER------------------------------------
    Register name:       EIP130_072_MAILBOX1_IN
    Offset name:         HSM_O_EIP130_072_MAILBOX1_IN
    Relative address:    0x0
    Description:         Input MAILBOX1
    Default Value:       0x000000
*/

/*-----------------------------------REGISTER------------------------------------
    Register name:       EIP130_072_MAILBOX2_IN
    Offset name:         HSM_O_EIP130_072_MAILBOX2_IN
    Relative address:    0x400
    Description:         Input MAILBOX2
    Default Value:       0x000000
*/

/*-----------------------------------REGISTER------------------------------------
    Register name:       AIC_POL_CTRL
    Offset name:         HSM_O_AIC_POL_CTRL
    Relative address:    0x3E00
    Description:         AIC Polarity Control Register
    Default Value:       0x00000000

        Field:           CTL0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Individual polarity (high level/rising edge or low level/falling edge) control bits per interrupt input: 0b = Low level/falling edge 1b = High level/rising edge.

*/
#define HSM_AIC_POL_CTRL_CTL0                                        0x00000001U
#define HSM_AIC_POL_CTRL_CTL0_M                                      0x00000001U
#define HSM_AIC_POL_CTRL_CTL0_S                                      0U
/*

        Field:           CTL1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Individual polarity (high level/rising edge or low level/falling edge) control bits per interrupt input: 0b = Low level/falling edge 1b = High level/rising edge.

*/
#define HSM_AIC_POL_CTRL_CTL1                                        0x00000002U
#define HSM_AIC_POL_CTRL_CTL1_M                                      0x00000002U
#define HSM_AIC_POL_CTRL_CTL1_S                                      1U
/*

        Field:           CTL2
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Individual polarity (high level/rising edge or low level/falling edge) control bits per interrupt input: 0b = Low level/falling edge 1b = High level/rising edge.

*/
#define HSM_AIC_POL_CTRL_CTL2                                        0x00000004U
#define HSM_AIC_POL_CTRL_CTL2_M                                      0x00000004U
#define HSM_AIC_POL_CTRL_CTL2_S                                      2U
/*

        Field:           CTL3
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Individual polarity (high level/rising edge or low level/falling edge) control bits per interrupt input: 0b = Low level/falling edge 1b = High level/rising edge.

*/
#define HSM_AIC_POL_CTRL_CTL3                                        0x00000008U
#define HSM_AIC_POL_CTRL_CTL3_M                                      0x00000008U
#define HSM_AIC_POL_CTRL_CTL3_S                                      3U
/*

        Field:           CTL4
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Individual polarity (high level/rising edge or low level/falling edge) control bits per interrupt input: 0b = Low level/falling edge 1b = High level/rising edge.

*/
#define HSM_AIC_POL_CTRL_CTL4                                        0x00000010U
#define HSM_AIC_POL_CTRL_CTL4_M                                      0x00000010U
#define HSM_AIC_POL_CTRL_CTL4_S                                      4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIC_TYPE_CTRL
    Offset name:         HSM_O_AIC_TYPE_CTRL
    Relative address:    0x3E04
    Description:         AIC Type Control Register
    Default Value:       0x00000000

        Field:           CTL0
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Signal type (level or edge) control bits for each interrupt input: 0b = level (the interrupt source level determines the raw status). 1b = edge (the interrupt source is connected to an edge detector and the edge detector output determines the raw status).

*/
#define HSM_AIC_TYPE_CTRL_CTL0                                       0x00000001U
#define HSM_AIC_TYPE_CTRL_CTL0_M                                     0x00000001U
#define HSM_AIC_TYPE_CTRL_CTL0_S                                     0U
/*

        Field:           CTL1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Signal type (level or edge) control bits for each interrupt input: 0b = level (the interrupt source level determines the raw status). 1b = edge (the interrupt source is connected to an edge detector and the edge detector output determines the raw status).

*/
#define HSM_AIC_TYPE_CTRL_CTL1                                       0x00000002U
#define HSM_AIC_TYPE_CTRL_CTL1_M                                     0x00000002U
#define HSM_AIC_TYPE_CTRL_CTL1_S                                     1U
/*

        Field:           CTL2
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Signal type (level or edge) control bits for each interrupt input: 0b = level (the interrupt source level determines the raw status). 1b = edge (the interrupt source is connected to an edge detector and the edge detector output determines the raw status).

*/
#define HSM_AIC_TYPE_CTRL_CTL2                                       0x00000004U
#define HSM_AIC_TYPE_CTRL_CTL2_M                                     0x00000004U
#define HSM_AIC_TYPE_CTRL_CTL2_S                                     2U
/*

        Field:           CTL3
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Signal type (level or edge) control bits for each interrupt input: 0b = level (the interrupt source level determines the raw status). 1b = edge (the interrupt source is connected to an edge detector and the edge detector output determines the raw status).

*/
#define HSM_AIC_TYPE_CTRL_CTL3                                       0x00000008U
#define HSM_AIC_TYPE_CTRL_CTL3_M                                     0x00000008U
#define HSM_AIC_TYPE_CTRL_CTL3_S                                     3U
/*

        Field:           CTL4
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Signal type (level or edge) control bits for each interrupt input: 0b = level (the interrupt source level determines the raw status). 1b = edge (the interrupt source is connected to an edge detector and the edge detector output determines the raw status).

*/
#define HSM_AIC_TYPE_CTRL_CTL4                                       0x00000010U
#define HSM_AIC_TYPE_CTRL_CTL4_M                                     0x00000010U
#define HSM_AIC_TYPE_CTRL_CTL4_S                                     4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIC_ENABLE_CTRL
    Offset name:         HSM_O_AIC_ENABLE_CTRL
    Relative address:    0x3E08
    Description:         AIC Enable Control Register
    Default Value:       0x00000000

        Field:           CTL
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-write
        Description:     Individual enable control bits per interrupt input: 0b = Disabled. 1b = Enabled

*/
#define HSM_AIC_ENABLE_CTRL_CTL_W                                    5U
#define HSM_AIC_ENABLE_CTRL_CTL_M                                    0x0000001FU
#define HSM_AIC_ENABLE_CTRL_CTL_S                                    0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIC_RAW_STAT
    Offset name:         HSM_O_AIC_RAW_STAT
    Relative address:    0x3E0C
    Description:         AIC Raw Source Status Register
    Default Value:       0x0000000F

        Field:           STA0
        From..to bits:   0...0
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Individual interrupt status bit before masking with enable_ctrl_r[0] (programmable, reset to 'low level' mode): 0b = Inactive, 1b = Pending.

*/
#define HSM_AIC_RAW_STAT_STA0                                        0x00000001U
#define HSM_AIC_RAW_STAT_STA0_M                                      0x00000001U
#define HSM_AIC_RAW_STAT_STA0_S                                      0U
/*

        Field:           STA1
        From..to bits:   1...1
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Individual interrupt status bit before masking with enable_ctrl_r[1] (programmable, reset to 'low level' mode): 0b = Inactive, 1b = Pending.

*/
#define HSM_AIC_RAW_STAT_STA1                                        0x00000002U
#define HSM_AIC_RAW_STAT_STA1_M                                      0x00000002U
#define HSM_AIC_RAW_STAT_STA1_S                                      1U
/*

        Field:           STA2
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Individual interrupt status bit before masking with enable_ctrl_r[2] (programmable, reset to 'low level' mode): 0b = Inactive, 1b = Pending.

*/
#define HSM_AIC_RAW_STAT_STA2                                        0x00000004U
#define HSM_AIC_RAW_STAT_STA2_M                                      0x00000004U
#define HSM_AIC_RAW_STAT_STA2_S                                      2U
/*

        Field:           STA3
        From..to bits:   3...3
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Individual interrupt status bit before masking with enable_ctrl_r[3] (programmable, reset to 'low level' mode): 0b = Inactive, 1b = Pending.

*/
#define HSM_AIC_RAW_STAT_STA3                                        0x00000008U
#define HSM_AIC_RAW_STAT_STA3_M                                      0x00000008U
#define HSM_AIC_RAW_STAT_STA3_S                                      3U
/*

        Field:           STA4
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Individual interrupt status bit before masking with enable_ctrl_r[4] (programmable, reset to 'low level' mode): 0b = Inactive, 1b = Pending.

*/
#define HSM_AIC_RAW_STAT_STA4                                        0x00000010U
#define HSM_AIC_RAW_STAT_STA4_M                                      0x00000010U
#define HSM_AIC_RAW_STAT_STA4_S                                      4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AICENSET
    Offset name:         HSM_O_AICENSET
    Relative address:    0x3E0C
    Description:         AIC Enable Set Registers
    Default Value:       NA

        Field:           ENSET
        From..to bits:   0...4
        DefaultValue:    NA
        Access type:     write-only
        Description:     Individual interrupt enable bits per interrupt input: 0b = No effect. 1b = Set the corresponding bit in the AIC_ENABLE_CTRL register, enabling the interrupt. After writing a 1b, there is no need to write a 0b.

*/
#define HSM_AICENSET_ENSET_W                                         5U
#define HSM_AICENSET_ENSET_M                                         0x0000001FU
#define HSM_AICENSET_ENSET_S                                         0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIC_ENABLED_STAT
    Offset name:         HSM_O_AIC_ENABLED_STAT
    Relative address:    0x3E10
    Description:         AIC Enabled Status Register
    Default Value:       0x00000000

        Field:           STA
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     These bits reflect the status of the interrupts after polarity control and optional edge detection, gated with bits in AIC_ENABLE_CTRL register: 0b = Inactive. 1b = Pending.

*/
#define HSM_AIC_ENABLED_STAT_STA_W                                   5U
#define HSM_AIC_ENABLED_STAT_STA_M                                   0x0000001FU
#define HSM_AIC_ENABLED_STAT_STA_S                                   0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AICACK
    Offset name:         HSM_O_AICACK
    Relative address:    0x3E10
    Description:         AIC Acknowledge Register
    Default Value:       NA

        Field:           ACK0
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     read-write
        Description:     Used to clear edge-detect interrupts: 0b = No effect. 1b = Acknowledge the interrupt signal, clears the edge detector and status bit when in edge detect mode (bit [0] of TYPE_CTRL == 1b). After writing a 1b, there is no need to write a 0b.

*/
#define HSM_AICACK_ACK0                                              0x00000001U
#define HSM_AICACK_ACK0_M                                            0x00000001U
#define HSM_AICACK_ACK0_S                                            0U
/*

        Field:           ACK1
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     read-write
        Description:     Used to clear edge-detect interrupts: 0b = No effect. 1b = Acknowledge the interrupt signal, clears the edge detector and status bit when in edge detect mode (bit [1] of TYPE_CTRL == 1b). After writing a 1b, there is no need to write a 0b.

*/
#define HSM_AICACK_ACK1                                              0x00000002U
#define HSM_AICACK_ACK1_M                                            0x00000002U
#define HSM_AICACK_ACK1_S                                            1U
/*

        Field:           ACK2
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     read-write
        Description:     Used to clear edge-detect interrupts: 0b = No effect. 1b = Acknowledge the interrupt signal, clears the edge detector and status bit when in edge detect mode (bit [2] of TYPE_CTRL == 1b). After writing a 1b, there is no need to write a 0b.

*/
#define HSM_AICACK_ACK2                                              0x00000004U
#define HSM_AICACK_ACK2_M                                            0x00000004U
#define HSM_AICACK_ACK2_S                                            2U
/*

        Field:           ACK3
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     read-write
        Description:     Used to clear edge-detect interrupts: 0b = No effect. 1b = Acknowledge the interrupt signal, clears the edge detector and status bit when in edge detect mode (bit [3] of TYPE_CTRL == 1b). After writing a 1b, there is no need to write a 0b.

*/
#define HSM_AICACK_ACK3                                              0x00000008U
#define HSM_AICACK_ACK3_M                                            0x00000008U
#define HSM_AICACK_ACK3_S                                            3U
/*

        Field:           ACK4
        From..to bits:   4...4
        DefaultValue:    NA
        Access type:     read-write
        Description:     Used to clear edge-detect interrupts: 0b = No effect. 1b = Acknowledge the interrupt signal, clears the edge detector and status bit when in edge detect mode (bit [4] of TYPE_CTRL == 1b). After writing a 1b, there is no need to write a 0b.

*/
#define HSM_AICACK_ACK4                                              0x00000010U
#define HSM_AICACK_ACK4_M                                            0x00000010U
#define HSM_AICACK_ACK4_S                                            4U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIC_ENABLE_CLR
    Offset name:         HSM_O_AIC_ENABLE_CLR
    Relative address:    0x3E14
    Description:         AIC Enable Clear Register
    Default Value:       0x00000000

        Field:           CLR
        From..to bits:   0...4
        DefaultValue:    0x0
        Access type:     write-only
        Description:     Individual interrupt disable bits per interrupt input: 0b = No effect. 1b = Clear the corresponding bit in the AIC_ENABLE_CTRL register, disabling the interrupt. After writing a 1b, there is no need to write a 0b.

*/
#define HSM_AIC_ENABLE_CLR_CLR_W                                     5U
#define HSM_AIC_ENABLE_CLR_CLR_M                                     0x0000001FU
#define HSM_AIC_ENABLE_CLR_CLR_S                                     0U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIC_OPTIONS
    Offset name:         HSM_O_AIC_OPTIONS
    Relative address:    0x3E18
    Description:         AIC Options Register
    Default Value:       0x00000005

        Field:           NUMOFIN
        From..to bits:   0...5
        DefaultValue:    0x5
        Access type:     read-only
        Description:     The number of interrupt request inputs.

*/
#define HSM_AIC_OPTIONS_NUMOFIN_W                                    6U
#define HSM_AIC_OPTIONS_NUMOFIN_M                                    0x0000003FU
#define HSM_AIC_OPTIONS_NUMOFIN_S                                    0U
/*

        Field:           EXTMAP
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Extended register map.

*/
#define HSM_AIC_OPTIONS_EXTMAP                                       0x00000080U
#define HSM_AIC_OPTIONS_EXTMAP_M                                     0x00000080U
#define HSM_AIC_OPTIONS_EXTMAP_S                                     7U
/*

        Field:           MINIMAP
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Mini register map.

*/
#define HSM_AIC_OPTIONS_MINIMAP                                      0x00000100U
#define HSM_AIC_OPTIONS_MINIMAP_M                                    0x00000100U
#define HSM_AIC_OPTIONS_MINIMAP_S                                    8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       AIC_VERSION
    Offset name:         HSM_O_AIC_VERSION
    Relative address:    0x3E1C
    Description:         AIC Version Register
    Default Value:       0x014036C9

        Field:           EIPNUM
        From..to bits:   0...7
        DefaultValue:    0xC9
        Access type:     read-only
        Description:     These bits encode the Rambus EIP number.

*/
#define HSM_AIC_VERSION_EIPNUM_W                                     8U
#define HSM_AIC_VERSION_EIPNUM_M                                     0x000000FFU
#define HSM_AIC_VERSION_EIPNUM_S                                     0U
/*

        Field:           EIPNUMCOMP
        From..to bits:   8...15
        DefaultValue:    0x36
        Access type:     read-only
        Description:     These bits simply contain the complement of bits [7:0], used by a driver to ascertain that this version register is indeed read.

*/
#define HSM_AIC_VERSION_EIPNUMCOMP_W                                 8U
#define HSM_AIC_VERSION_EIPNUMCOMP_M                                 0x0000FF00U
#define HSM_AIC_VERSION_EIPNUMCOMP_S                                 8U
/*

        Field:           PATCHLVL
        From..to bits:   16...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     These bits encode the hardware patch level for the EIP-201 module, starting at value 0 on the first release.

*/
#define HSM_AIC_VERSION_PATCHLVL_W                                   4U
#define HSM_AIC_VERSION_PATCHLVL_M                                   0x000F0000U
#define HSM_AIC_VERSION_PATCHLVL_S                                   16U
/*

        Field:           MINORVER
        From..to bits:   20...23
        DefaultValue:    0x4
        Access type:     read-only
        Description:     These bits encode the minor version number for the EIP-201 module.

*/
#define HSM_AIC_VERSION_MINORVER_W                                   4U
#define HSM_AIC_VERSION_MINORVER_M                                   0x00F00000U
#define HSM_AIC_VERSION_MINORVER_S                                   20U
/*

        Field:           MAJORVER
        From..to bits:   24...27
        DefaultValue:    0x1
        Access type:     read-only
        Description:     These bits encode the major version number for the EIP-201 module.

*/
#define HSM_AIC_VERSION_MAJORVER_W                                   4U
#define HSM_AIC_VERSION_MAJORVER_M                                   0x0F000000U
#define HSM_AIC_VERSION_MAJORVER_S                                   24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MAILBOX_STAT
    Offset name:         HSM_O_MAILBOX_STAT
    Relative address:    0x3F00
    Description:         Mailbox Status Register
    Default Value:       0x00000088

        Field:           INFULL1
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-Input Mailbox contains a token that is handed over to Internal Controller, (Clear)-Input Mailbox is ready to rceive new token

*/
#define HSM_MAILBOX_STAT_INFULL1                                     0x00000001U
#define HSM_MAILBOX_STAT_INFULL1_M                                   0x00000001U
#define HSM_MAILBOX_STAT_INFULL1_S                                   0U
/*

        Field:           OUTFULL1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-Output Mailbox contains an output token, (Clear)-Output Mailbox is empty

*/
#define HSM_MAILBOX_STAT_OUTFULL1                                    0x00000002U
#define HSM_MAILBOX_STAT_OUTFULL1_M                                  0x00000002U
#define HSM_MAILBOX_STAT_OUTFULL1_S                                  1U
/*

        Field:           LINKED1
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-This Host is linked to Mailbox, (Clear)-This Host is not linked to Mailbox

*/
#define HSM_MAILBOX_STAT_LINKED1                                     0x00000004U
#define HSM_MAILBOX_STAT_LINKED1_M                                   0x00000004U
#define HSM_MAILBOX_STAT_LINKED1_S                                   2U
/*

        Field:           AVAIL1
        From..to bits:   3...3
        DefaultValue:    0x1
        Access type:     read-only
        Description:     (set)-Input Mailbox is linked to a Host or is filled, (Clear)- Input Mailbox is available for linking by this Host

*/
#define HSM_MAILBOX_STAT_AVAIL1                                      0x00000008U
#define HSM_MAILBOX_STAT_AVAIL1_M                                    0x00000008U
#define HSM_MAILBOX_STAT_AVAIL1_S                                    3U
/*

        Field:           INFULL2
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-Input Mailbox contains a token that is handed over to Internal Controller, (Clear)-Input Mailbox is ready to rceive new token

*/
#define HSM_MAILBOX_STAT_INFULL2                                     0x00000010U
#define HSM_MAILBOX_STAT_INFULL2_M                                   0x00000010U
#define HSM_MAILBOX_STAT_INFULL2_S                                   4U
/*

        Field:           OUTFULL2
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-Output Mailbox contains an output token, (Clear)-Output Mailbox is empty

*/
#define HSM_MAILBOX_STAT_OUTFULL2                                    0x00000020U
#define HSM_MAILBOX_STAT_OUTFULL2_M                                  0x00000020U
#define HSM_MAILBOX_STAT_OUTFULL2_S                                  5U
/*

        Field:           LINKED2
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-This Host is linked to Mailbox, (Clear)-This Host is not linked to Mailbox

*/
#define HSM_MAILBOX_STAT_LINKED2                                     0x00000040U
#define HSM_MAILBOX_STAT_LINKED2_M                                   0x00000040U
#define HSM_MAILBOX_STAT_LINKED2_S                                   6U
/*

        Field:           AVAIL2
        From..to bits:   7...7
        DefaultValue:    0x1
        Access type:     read-only
        Description:     (set)-Input Mailbox is linked to a Host or is filled, (Clear)- Input Mailbox is available for linking by this Host

*/
#define HSM_MAILBOX_STAT_AVAIL2                                      0x00000080U
#define HSM_MAILBOX_STAT_AVAIL2_M                                    0x00000080U
#define HSM_MAILBOX_STAT_AVAIL2_S                                    7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MBXCTL
    Offset name:         HSM_O_MBXCTL
    Relative address:    0x3F00
    Description:         Mailbox Control Register
    Default Value:       NA

        Field:           INFULL1
        From..to bits:   0...0
        DefaultValue:    NA
        Access type:     write-only
        Description:     Set only - The Host linked to mailbox can set the mbx_in_full bit in MAILBOX_STAT by writing 1b here.

*/
#define HSM_MBXCTL_INFULL1                                           0x00000001U
#define HSM_MBXCTL_INFULL1_M                                         0x00000001U
#define HSM_MBXCTL_INFULL1_S                                         0U
/*

        Field:           OUTEMP1
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     write-only
        Description:     Set only - The Host for whom the token in Output Mailbox is meant can clear the mbx_out_full bit in MAILBOX_STAT by writing 1b here.

*/
#define HSM_MBXCTL_OUTEMP1                                           0x00000002U
#define HSM_MBXCTL_OUTEMP1_M                                         0x00000002U
#define HSM_MBXCTL_OUTEMP1_S                                         1U
/*

        Field:           LINK1
        From..to bits:   2...2
        DefaultValue:    NA
        Access type:     write-only
        Description:     Writing a 1b here links Mailbox to this Host - only if Mailbox not filled and not linked to another host

*/
#define HSM_MBXCTL_LINK1                                             0x00000004U
#define HSM_MBXCTL_LINK1_M                                           0x00000004U
#define HSM_MBXCTL_LINK1_S                                           2U
/*

        Field:           UNLINK1
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     Set only - Writing a 1b here unlinks the MAilbox from this HOST and clears the mbx_linked bit in MAILBOX_STAT

*/
#define HSM_MBXCTL_UNLINK1                                           0x00000008U
#define HSM_MBXCTL_UNLINK1_M                                         0x00000008U
#define HSM_MBXCTL_UNLINK1_S                                         3U
/*

        Field:           INFULL2
        From..to bits:   4...4
        DefaultValue:    NA
        Access type:     write-only
        Description:     Set only - The Host linked to mailbox can set the mbx_in_full bit in MAILBOX_STAT by writing 1b here.

*/
#define HSM_MBXCTL_INFULL2                                           0x00000010U
#define HSM_MBXCTL_INFULL2_M                                         0x00000010U
#define HSM_MBXCTL_INFULL2_S                                         4U
/*

        Field:           OUTEMP2
        From..to bits:   5...5
        DefaultValue:    NA
        Access type:     write-only
        Description:     Set only - The Host for whom the token in Output Mailbox is meant can clear the mbx_out_full bit in MAILBOX_STAT by writing 1b here.

*/
#define HSM_MBXCTL_OUTEMP2                                           0x00000020U
#define HSM_MBXCTL_OUTEMP2_M                                         0x00000020U
#define HSM_MBXCTL_OUTEMP2_S                                         5U
/*

        Field:           LINK2
        From..to bits:   6...6
        DefaultValue:    NA
        Access type:     write-only
        Description:     Writing a 1b here links Mailbox to this Host - only if Mailbox not filled and not linked to another host

*/
#define HSM_MBXCTL_LINK2                                             0x00000040U
#define HSM_MBXCTL_LINK2_M                                           0x00000040U
#define HSM_MBXCTL_LINK2_S                                           6U
/*

        Field:           UNLINK2
        From..to bits:   7...7
        DefaultValue:    NA
        Access type:     write-only
        Description:     Set only - Writing a 1b here unlinks the MAilbox from this HOST and clears the mbx_linked bit in MAILBOX_STAT

*/
#define HSM_MBXCTL_UNLINK2                                           0x00000080U
#define HSM_MBXCTL_UNLINK2_M                                         0x00000080U
#define HSM_MBXCTL_UNLINK2_S                                         7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MAILBOX_RAWSTAT
    Offset name:         HSM_O_MAILBOX_RAWSTAT
    Relative address:    0x3F04
    Description:         Raw (unmasked) Mailbox Status Register
    Default Value:       0x00000000

        Field:           INFULL1
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-Input Mailbox contains a token that is handed over to Internal Controller, (Clear)-Input Mailbox mbx%d is ready to rceive new token

*/
#define HSM_MAILBOX_RAWSTAT_INFULL1                                  0x00000001U
#define HSM_MAILBOX_RAWSTAT_INFULL1_M                                0x00000001U
#define HSM_MAILBOX_RAWSTAT_INFULL1_S                                0U
/*

        Field:           OUTFULL1
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-Output Mailbox contains an output token, (Clear)-Output Mailbox mbx%d is empty

*/
#define HSM_MAILBOX_RAWSTAT_OUTFULL1                                 0x00000002U
#define HSM_MAILBOX_RAWSTAT_OUTFULL1_M                               0x00000002U
#define HSM_MAILBOX_RAWSTAT_OUTFULL1_S                               1U
/*

        Field:           LINKED1
        From..to bits:   2...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-This Host is linked to Mailbox mbx%d , (Clear)-This Host is not linked to  Mailbox mbx%d

*/
#define HSM_MAILBOX_RAWSTAT_LINKED1                                  0x00000004U
#define HSM_MAILBOX_RAWSTAT_LINKED1_M                                0x00000004U
#define HSM_MAILBOX_RAWSTAT_LINKED1_S                                2U
/*

        Field:           INFULL2
        From..to bits:   4...4
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-Input Mailbox contains a token that is handed over to Internal Controller, (Clear)-Input Mailbox mbx%d is ready to rceive new token

*/
#define HSM_MAILBOX_RAWSTAT_INFULL2                                  0x00000010U
#define HSM_MAILBOX_RAWSTAT_INFULL2_M                                0x00000010U
#define HSM_MAILBOX_RAWSTAT_INFULL2_S                                4U
/*

        Field:           OUTFULL2
        From..to bits:   5...5
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-Output Mailbox contains an output token, (Clear)-Output Mailbox mbx%d is empty

*/
#define HSM_MAILBOX_RAWSTAT_OUTFULL2                                 0x00000020U
#define HSM_MAILBOX_RAWSTAT_OUTFULL2_M                               0x00000020U
#define HSM_MAILBOX_RAWSTAT_OUTFULL2_S                               5U
/*

        Field:           LINKED2
        From..to bits:   6...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     (set)-This Host is linked to Mailbox mbx%d , (Clear)-This Host is not linked to  Mailbox mbx%d

*/
#define HSM_MAILBOX_RAWSTAT_LINKED2                                  0x00000040U
#define HSM_MAILBOX_RAWSTAT_LINKED2_M                                0x00000040U
#define HSM_MAILBOX_RAWSTAT_LINKED2_S                                6U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MBXRST
    Offset name:         HSM_O_MBXRST
    Relative address:    0x3F04
    Description:         Mailbox Reset Register
    Default Value:       NA

        Field:           OUTEMP1
        From..to bits:   1...1
        DefaultValue:    NA
        Access type:     write-only
        Description:     Set only - Master Host can clear mbx_out_full bit in MAILBOX_STAT by writing 1b here.

*/
#define HSM_MBXRST_OUTEMP1                                           0x00000002U
#define HSM_MBXRST_OUTEMP1_M                                         0x00000002U
#define HSM_MBXRST_OUTEMP1_S                                         1U
/*

        Field:           UNLINK1
        From..to bits:   3...3
        DefaultValue:    NA
        Access type:     write-only
        Description:     Set only - Master Host can unlink mbx from it's current Host by writing 1b here.

*/
#define HSM_MBXRST_UNLINK1                                           0x00000008U
#define HSM_MBXRST_UNLINK1_M                                         0x00000008U
#define HSM_MBXRST_UNLINK1_S                                         3U
/*

        Field:           OUTEMP2
        From..to bits:   5...5
        DefaultValue:    NA
        Access type:     write-only
        Description:     Set only - Master Host can clear mbx_out_full bit in MAILBOX_STAT by writing 1b here.

*/
#define HSM_MBXRST_OUTEMP2                                           0x00000020U
#define HSM_MBXRST_OUTEMP2_M                                         0x00000020U
#define HSM_MBXRST_OUTEMP2_S                                         5U
/*

        Field:           UNLINK2
        From..to bits:   7...7
        DefaultValue:    NA
        Access type:     write-only
        Description:     Set only - Master Host can unlink mbx from it's current Host by writing 1b here.

*/
#define HSM_MBXRST_UNLINK2                                           0x00000080U
#define HSM_MBXRST_UNLINK2_M                                         0x00000080U
#define HSM_MBXRST_UNLINK2_S                                         7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MAILBOX_LINKID
    Offset name:         HSM_O_MAILBOX_LINKID
    Relative address:    0x3F08
    Description:         Mailbox Status - linked Host IDs Register
    Default Value:       0x00000000

        Field:           LINKID1
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bits[1:0]Host cpu_id of the Host linked to the Mailbox, bit[2] Set - Mailbox is only accessible if Host uses protected access, Clear - Mailbox accessed with protected of non-protected access

*/
#define HSM_MAILBOX_LINKID_LINKID1_W                                 3U
#define HSM_MAILBOX_LINKID_LINKID1_M                                 0x00000007U
#define HSM_MAILBOX_LINKID_LINKID1_S                                 0U
/*

        Field:           PROTACC1
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     0: Mailbox 1 can be accessed by the Host using protected or non-protected access. 1: Mailbox 1 is only accessible if the Host uses protected access.

*/
#define HSM_MAILBOX_LINKID_PROTACC1                                  0x00000008U
#define HSM_MAILBOX_LINKID_PROTACC1_M                                0x00000008U
#define HSM_MAILBOX_LINKID_PROTACC1_S                                3U
/*

        Field:           LINKID2
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bits[1:0]Host cpu_id of the Host linked to the Mailbox, bit[2] Set - Mailbox is only accessible if Host uses protected access, Clear - Mailbox accessed with protected of non-protected access

*/
#define HSM_MAILBOX_LINKID_LINKID2_W                                 3U
#define HSM_MAILBOX_LINKID_LINKID2_M                                 0x00000070U
#define HSM_MAILBOX_LINKID_LINKID2_S                                 4U
/*

        Field:           PORTACC2
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     0: Mailbox 2 can be accessed by the Host using protected or non-protected access. 1: Mailbox 2 is only accessible if the Host uses protected access.

*/
#define HSM_MAILBOX_LINKID_PORTACC2                                  0x00000080U
#define HSM_MAILBOX_LINKID_PORTACC2_M                                0x00000080U
#define HSM_MAILBOX_LINKID_PORTACC2_S                                7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MAILBOX_OUTID
    Offset name:         HSM_O_MAILBOX_OUTID
    Relative address:    0x3F0C
    Description:         Mailbox Status - output Host IDs Register
    Default Value:       0x00000000

        Field:           OUTID1
        From..to bits:   0...2
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bit[1,0] Host cpu_id of the Host allowed to read a result from the Mailbox, bit[2] Set - Out Mailbox is only accessible if Host uses protected access, Clear - Output Mailbox accessed with protected of non-protected access

*/
#define HSM_MAILBOX_OUTID_OUTID1_W                                   3U
#define HSM_MAILBOX_OUTID_OUTID1_M                                   0x00000007U
#define HSM_MAILBOX_OUTID_OUTID1_S                                   0U
/*

        Field:           PROTACC1
        From..to bits:   3...3
        DefaultValue:    0x0
        Access type:     read-only
        Description:     0: Output mailbox 1 can be accessed by the Host using protected or non-protected access. 1: Output mailbox 1 is only accessible if the Host uses protected access.

*/
#define HSM_MAILBOX_OUTID_PROTACC1                                   0x00000008U
#define HSM_MAILBOX_OUTID_PROTACC1_M                                 0x00000008U
#define HSM_MAILBOX_OUTID_PROTACC1_S                                 3U
/*

        Field:           OUTID2
        From..to bits:   4...6
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bit[1,0] Host cpu_id of the Host allowed to read a result from the Mailbox, bit[2] Set - Out Mailbox is only accessible if Host uses protected access, Clear - Output Mailbox accessed with protected of non-protected access

*/
#define HSM_MAILBOX_OUTID_OUTID2_W                                   3U
#define HSM_MAILBOX_OUTID_OUTID2_M                                   0x00000070U
#define HSM_MAILBOX_OUTID_OUTID2_S                                   4U
/*

        Field:           PORTACC2
        From..to bits:   7...7
        DefaultValue:    0x0
        Access type:     read-only
        Description:     0: Output mailbox 2 can be accessed by the Host using protected or non-protected access. 1: Output mailbox 2 is only accessible if the Host uses protected access.

*/
#define HSM_MAILBOX_OUTID_PORTACC2                                   0x00000080U
#define HSM_MAILBOX_OUTID_PORTACC2_M                                 0x00000080U
#define HSM_MAILBOX_OUTID_PORTACC2_S                                 7U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MAILBOX_LOCKOUT
    Offset name:         HSM_O_MAILBOX_LOCKOUT
    Relative address:    0x3F10
    Description:         Host/Mailbox1-4  lockout control Register
    Default Value:       0x00000E0E

        Field:           LOCKOUT1
        From..to bits:   0...7
        DefaultValue:    0xE
        Access type:     read-write
        Description:     Bit map indicates which Hosts are blocked from accessing mailbox

*/
#define HSM_MAILBOX_LOCKOUT_LOCKOUT1_W                               8U
#define HSM_MAILBOX_LOCKOUT_LOCKOUT1_M                               0x000000FFU
#define HSM_MAILBOX_LOCKOUT_LOCKOUT1_S                               0U
/*

        Field:           LOCKOUT2
        From..to bits:   8...15
        DefaultValue:    0xE
        Access type:     read-write
        Description:     Bit map indicates which Hosts are blocked from accessing mailbox

*/
#define HSM_MAILBOX_LOCKOUT_LOCKOUT2_W                               8U
#define HSM_MAILBOX_LOCKOUT_LOCKOUT2_M                               0x0000FF00U
#define HSM_MAILBOX_LOCKOUT_LOCKOUT2_S                               8U


/*-----------------------------------REGISTER------------------------------------
    Register name:       MODULE_STATUS
    Offset name:         HSM_O_MODULE_STATUS
    Relative address:    0x3FE0
    Description:         Module Status Register
    Default Value:       0x00000100

        Field:           FIPSMOD
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read-Only. Set if VaultIP is in FIPS mode

*/
#define HSM_MODULE_STATUS_FIPSMOD                                    0x00000001U
#define HSM_MODULE_STATUS_FIPSMOD_M                                  0x00000001U
#define HSM_MODULE_STATUS_FIPSMOD_S                                  0U
/*

        Field:           NFIPSMOD
        From..to bits:   1...1
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read-Only. Set if VaultIP is in non-FIPS mode

*/
#define HSM_MODULE_STATUS_NFIPSMOD                                   0x00000002U
#define HSM_MODULE_STATUS_NFIPSMOD_M                                 0x00000002U
#define HSM_MODULE_STATUS_NFIPSMOD_S                                 1U
/*

        Field:           CRCBUSY
        From..to bits:   8...8
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Read-Only. Set if CRC on ProgramROM is busy

*/
#define HSM_MODULE_STATUS_CRCBUSY                                    0x00000100U
#define HSM_MODULE_STATUS_CRCBUSY_M                                  0x00000100U
#define HSM_MODULE_STATUS_CRCBUSY_S                                  8U
/*

        Field:           CRCOK
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read-Only. Set if CRC on ProgramROM is passes

*/
#define HSM_MODULE_STATUS_CRCOK                                      0x00000200U
#define HSM_MODULE_STATUS_CRCOK_M                                    0x00000200U
#define HSM_MODULE_STATUS_CRCOK_S                                    9U
/*

        Field:           CRCERR
        From..to bits:   10...10
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read-Only. Set if CRC on ProgramROM is fails

*/
#define HSM_MODULE_STATUS_CRCERR                                     0x00000400U
#define HSM_MODULE_STATUS_CRCERR_M                                   0x00000400U
#define HSM_MODULE_STATUS_CRCERR_S                                   10U
/*

        Field:           FATALERR
        From..to bits:   31...31
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Read-Only. Set if fatal error occured

*/
#define HSM_MODULE_STATUS_FATALERR                                   0x80000000U
#define HSM_MODULE_STATUS_FATALERR_M                                 0x80000000U
#define HSM_MODULE_STATUS_FATALERR_S                                 31U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EIP_OPTIONS2
    Offset name:         HSM_O_EIP_OPTIONS2
    Relative address:    0x3FF4
    Description:         VaultIP configured options(2)
    Default Value:       0x0020003C

        Field:           DESAES
        From..to bits:   0...0
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set - (3)DES/AES combination crypto core available

*/
#define HSM_EIP_OPTIONS2_DESAES                                      0x00000001U
#define HSM_EIP_OPTIONS2_DESAES_M                                    0x00000001U
#define HSM_EIP_OPTIONS2_DESAES_S                                    0U
/*

        Field:           SHA
        From..to bits:   2...2
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Set - SHA1/SHA2 combination core available

*/
#define HSM_EIP_OPTIONS2_SHA                                         0x00000004U
#define HSM_EIP_OPTIONS2_SHA_M                                       0x00000004U
#define HSM_EIP_OPTIONS2_SHA_S                                       2U
/*

        Field:           TRNG
        From..to bits:   3...3
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Set - TRNG engine available

*/
#define HSM_EIP_OPTIONS2_TRNG                                        0x00000008U
#define HSM_EIP_OPTIONS2_TRNG_M                                      0x00000008U
#define HSM_EIP_OPTIONS2_TRNG_S                                      3U
/*

        Field:           CRC
        From..to bits:   4...4
        DefaultValue:    0x1
        Access type:     read-only
        Description:     CRC calculation available

*/
#define HSM_EIP_OPTIONS2_CRC                                         0x00000010U
#define HSM_EIP_OPTIONS2_CRC_M                                       0x00000010U
#define HSM_EIP_OPTIONS2_CRC_S                                       4U
/*

        Field:           PKCP
        From..to bits:   5...5
        DefaultValue:    0x1
        Access type:     read-only
        Description:     PKCP Engine available

*/
#define HSM_EIP_OPTIONS2_PKCP                                        0x00000020U
#define HSM_EIP_OPTIONS2_PKCP_M                                      0x00000020U
#define HSM_EIP_OPTIONS2_PKCP_S                                      5U
/*

        Field:           CCPU
        From..to bits:   8...8
        DefaultValue:    0x0
        Access type:     read-only
        Description:     C capable local cpu available

*/
#define HSM_EIP_OPTIONS2_CCPU                                        0x00000100U
#define HSM_EIP_OPTIONS2_CCPU_M                                      0x00000100U
#define HSM_EIP_OPTIONS2_CCPU_S                                      8U
/*

        Field:           PRAM
        From..to bits:   9...9
        DefaultValue:    0x0
        Access type:     read-only
        Description:     1b = downloadable RAM based firmware program memory. 0b = ROM only firmware program memory.

*/
#define HSM_EIP_OPTIONS2_PRAM                                        0x00000200U
#define HSM_EIP_OPTIONS2_PRAM_M                                      0x00000200U
#define HSM_EIP_OPTIONS2_PRAM_S                                      9U
/*

        Field:           BUSIF
        From..to bits:   12...12
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Bus interface type, for both Master and Slave: 0b = 32-bit AHB, 1b = 32-bit AXI

*/
#define HSM_EIP_OPTIONS2_BUSIF                                       0x00001000U
#define HSM_EIP_OPTIONS2_BUSIF_M                                     0x00001000U
#define HSM_EIP_OPTIONS2_BUSIF_S                                     12U
/*

        Field:           ADDCE1
        From..to bits:   16...16
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set - an additional crypto engine is available in hardware as custom engine1

*/
#define HSM_EIP_OPTIONS2_ADDCE1                                      0x00010000U
#define HSM_EIP_OPTIONS2_ADDCE1_M                                    0x00010000U
#define HSM_EIP_OPTIONS2_ADDCE1_S                                    16U
/*

        Field:           ADDCE2
        From..to bits:   17...17
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set - an additional crypto engine is available in hardware as custom engine2

*/
#define HSM_EIP_OPTIONS2_ADDCE2                                      0x00020000U
#define HSM_EIP_OPTIONS2_ADDCE2_M                                    0x00020000U
#define HSM_EIP_OPTIONS2_ADDCE2_S                                    17U
/*

        Field:           ADDCE3
        From..to bits:   18...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set - an additional crypto engine is available in hardware as custom engine3

*/
#define HSM_EIP_OPTIONS2_ADDCE3                                      0x00040000U
#define HSM_EIP_OPTIONS2_ADDCE3_M                                    0x00040000U
#define HSM_EIP_OPTIONS2_ADDCE3_S                                    18U
/*

        Field:           ADDCE4
        From..to bits:   19...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set - an additional crypto engine is available in hardware as custom engine4

*/
#define HSM_EIP_OPTIONS2_ADDCE4                                      0x00080000U
#define HSM_EIP_OPTIONS2_ADDCE4_M                                    0x00080000U
#define HSM_EIP_OPTIONS2_ADDCE4_S                                    19U
/*

        Field:           ADDCE5
        From..to bits:   20...20
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set - an additional crypto engine is available in hardware as custom engine5

*/
#define HSM_EIP_OPTIONS2_ADDCE5                                      0x00100000U
#define HSM_EIP_OPTIONS2_ADDCE5_M                                    0x00100000U
#define HSM_EIP_OPTIONS2_ADDCE5_S                                    20U
/*

        Field:           ADDCE6
        From..to bits:   21...21
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Set - an additional crypto engine is available in hardware as custom engine6

*/
#define HSM_EIP_OPTIONS2_ADDCE6                                      0x00200000U
#define HSM_EIP_OPTIONS2_ADDCE6_M                                    0x00200000U
#define HSM_EIP_OPTIONS2_ADDCE6_S                                    21U
/*

        Field:           ADDCE7
        From..to bits:   22...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set - an additional crypto engine is available in hardware as custom engine7

*/
#define HSM_EIP_OPTIONS2_ADDCE7                                      0x00400000U
#define HSM_EIP_OPTIONS2_ADDCE7_M                                    0x00400000U
#define HSM_EIP_OPTIONS2_ADDCE7_S                                    22U
/*

        Field:           ADDCE8
        From..to bits:   23...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set - an additional crypto engine is available in hardware as custom engine8

*/
#define HSM_EIP_OPTIONS2_ADDCE8                                      0x00800000U
#define HSM_EIP_OPTIONS2_ADDCE8_M                                    0x00800000U
#define HSM_EIP_OPTIONS2_ADDCE8_S                                    23U
/*

        Field:           ADDCE9
        From..to bits:   24...24
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set - an additional crypto engine is available in hardware as custom engine9

*/
#define HSM_EIP_OPTIONS2_ADDCE9                                      0x01000000U
#define HSM_EIP_OPTIONS2_ADDCE9_M                                    0x01000000U
#define HSM_EIP_OPTIONS2_ADDCE9_S                                    24U
/*

        Field:           ADDCE10
        From..to bits:   25...25
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Set - an additional crypto engine is available in hardware as custom engine10

*/
#define HSM_EIP_OPTIONS2_ADDCE10                                     0x02000000U
#define HSM_EIP_OPTIONS2_ADDCE10_M                                   0x02000000U
#define HSM_EIP_OPTIONS2_ADDCE10_S                                   25U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EIP_OPTIONS
    Offset name:         HSM_O_EIP_OPTIONS
    Relative address:    0x3FF8
    Description:         VaultIP configured options(1)
    Default Value:       0x01800F12

        Field:           NUMOFMBX
        From..to bits:   0...3
        DefaultValue:    0x2
        Access type:     read-only
        Description:     Number of Input/Output Mailbox pairs

*/
#define HSM_EIP_OPTIONS_NUMOFMBX_W                                   4U
#define HSM_EIP_OPTIONS_NUMOFMBX_M                                   0x0000000FU
#define HSM_EIP_OPTIONS_NUMOFMBX_S                                   0U
/*

        Field:           MBXSIZE
        From..to bits:   4...5
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Implemented size of Mailbox pairs - 00b-128bytes, 01b-256bytes, 10b-512bytes, 11b-1Kbyte

*/
#define HSM_EIP_OPTIONS_MBXSIZE_W                                    2U
#define HSM_EIP_OPTIONS_MBXSIZE_M                                    0x00000030U
#define HSM_EIP_OPTIONS_MBXSIZE_S                                    4U
/*

        Field:           HOSTID
        From..to bits:   8...15
        DefaultValue:    0xF
        Access type:     read-only
        Description:     Bits to indicate which of the 8 possible cpu_id codes on the bus interface are active

*/
#define HSM_EIP_OPTIONS_HOSTID_W                                     8U
#define HSM_EIP_OPTIONS_HOSTID_M                                     0x0000FF00U
#define HSM_EIP_OPTIONS_HOSTID_S                                     8U
/*

        Field:           MASID
        From..to bits:   16...18
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Value of the cpu_id that designates the Master Host

*/
#define HSM_EIP_OPTIONS_MASID_W                                      3U
#define HSM_EIP_OPTIONS_MASID_M                                      0x00070000U
#define HSM_EIP_OPTIONS_MASID_S                                      16U
/*

        Field:           MYID
        From..to bits:   20...22
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Slave & Master interface support protection bit (secure/non-secure) accesses

*/
#define HSM_EIP_OPTIONS_MYID_W                                       3U
#define HSM_EIP_OPTIONS_MYID_M                                       0x00700000U
#define HSM_EIP_OPTIONS_MYID_S                                       20U
/*

        Field:           MYIDSEC
        From..to bits:   23...23
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Indicates the current protection bit values of the Host actually reading the register

*/
#define HSM_EIP_OPTIONS_MYIDSEC                                      0x00800000U
#define HSM_EIP_OPTIONS_MYIDSEC_M                                    0x00800000U
#define HSM_EIP_OPTIONS_MYIDSEC_S                                    23U
/*

        Field:           HOSTIDSEC
        From..to bits:   24...31
        DefaultValue:    0x1
        Access type:     read-only
        Description:     Bits to indicate which of the 8 possible cpu_id codes on the bus interface are active Hosts with secure access

*/
#define HSM_EIP_OPTIONS_HOSTIDSEC_W                                  8U
#define HSM_EIP_OPTIONS_HOSTIDSEC_M                                  0xFF000000U
#define HSM_EIP_OPTIONS_HOSTIDSEC_S                                  24U


/*-----------------------------------REGISTER------------------------------------
    Register name:       EIP_VERSION
    Offset name:         HSM_O_EIP_VERSION
    Relative address:    0x3FFC
    Description:         Standard EIP version register
    Default Value:       0x04007D82

        Field:           EIPNUM
        From..to bits:   0...7
        DefaultValue:    0x82
        Access type:     read-only
        Description:     RAMBUS EIP number - EIP130

*/
#define HSM_EIP_VERSION_EIPNUM_W                                     8U
#define HSM_EIP_VERSION_EIPNUM_M                                     0x000000FFU
#define HSM_EIP_VERSION_EIPNUM_S                                     0U
/*

        Field:           EIPNUMCOMP
        From..to bits:   8...15
        DefaultValue:    0x7D
        Access type:     read-only
        Description:     Bit by Bit compliment of EIP Number

*/
#define HSM_EIP_VERSION_EIPNUMCOMP_W                                 8U
#define HSM_EIP_VERSION_EIPNUMCOMP_M                                 0x0000FF00U
#define HSM_EIP_VERSION_EIPNUMCOMP_S                                 8U
/*

        Field:           PATCHLVL
        From..to bits:   16...19
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Hardware Patch Level for this module

*/
#define HSM_EIP_VERSION_PATCHLVL_W                                   4U
#define HSM_EIP_VERSION_PATCHLVL_M                                   0x000F0000U
#define HSM_EIP_VERSION_PATCHLVL_S                                   16U
/*

        Field:           MINORVER
        From..to bits:   20...23
        DefaultValue:    0x0
        Access type:     read-only
        Description:     Minor Version release number for this module

*/
#define HSM_EIP_VERSION_MINORVER_W                                   4U
#define HSM_EIP_VERSION_MINORVER_M                                   0x00F00000U
#define HSM_EIP_VERSION_MINORVER_S                                   20U
/*

        Field:           MAJORVER
        From..to bits:   24...27
        DefaultValue:    0x4
        Access type:     read-only
        Description:     Major Version release number for this module

*/
#define HSM_EIP_VERSION_MAJORVER_W                                   4U
#define HSM_EIP_VERSION_MAJORVER_M                                   0x0F000000U
#define HSM_EIP_VERSION_MAJORVER_S                                   24U

#endif /* __HW_HSM_H__*/
