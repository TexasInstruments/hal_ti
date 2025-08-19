/*****************************************************************************

 FILENAME:       ble_if.c

 DESCRIPTION:    implements the BLE host-controller interface

 AUTHOR:         Guy M.
 Copyright (c) 2022 Texas Instruments Inc.
 All Rights Reserved This program is the confidential and proprietary
 product of Texas Instruments Inc.  Any Unauthorized use, reproduction or
 transfer of this program is strictly prohibited.

 *****************************************************************************/
#include "ble_if.h"
#include "ble_transport.h"
#include "hci_transport.h"
#include "uart_hci.h"
#include "osi_type.h"
#include "osi_kernel.h"
#include "control_cmd_fw.h"


/*****************************************************************************/
/* DEFINITIONS & GLOBALS                                                     */
/*****************************************************************************/
ble_if_cb_t bleIfCb;


/*****************************************************************************/
/* IMPLEMENTATION                                                            */
/*****************************************************************************/
int BleIf_OpenTransport(ble_if_transport_e transport)
{
    if (transport == BLE_IF_TRANSPORT_SERIAL)
    {
        if (HciTransport_IsInitialized(HCI_TRANSPORT_UART_BLE) == FALSE)
        {
            //Open the UART for HCI
            UartHciOpen();

            //Initialize the HCI transport
            HciTransport_Init(HCI_TRANSPORT_UART_BLE, &uartForHci);
        }

        //Register callbacks
        bleIfCb.cmd_cb = HciTransport_WriteHciPacketToCtrl;
        bleIfCb.event_cb_reg = HciTransport_HciRxCallbackbRegister;

        Report("\n\rBLE Serial transport opened\r\n");
    }
    else
    {
        //Note: shared transport was previously opened when WLAN started
        //It will not be opened here

        //Register callbacks
        bleIfCb.cmd_cb = BleTransport_SendCommand;
        bleIfCb.event_cb_reg = BleTransport_EventCallbackbRegister;

        Report("\n\rBLE Shared transport opened\r\n");
    }

    return 0;
}

int BleIf_CloseTransport()
{
    if (HciTransport_IsInitialized(HCI_TRANSPORT_UART_BLE) == TRUE)
    {
        //Close the UART for HCI
        UartHciClose();

        //Release the HCI transport
        HciTransport_Release(HCI_TRANSPORT_UART_BLE);
    }
    //Note: shared transport was previously opened when WLAN started
    //It will not be closed here

    return 0;
}

int BleIf_SendCommand(uint8_t* cmd, uint16_t cmdLen)
{
    return bleIfCb.cmd_cb(cmd, cmdLen);
}

int BleIf_EventCbRegister(ble_event_cb_t cb)
{
    if (cb == NULL)
    {
        return (-1);
    }

    bleIfCb.event_cb_reg(cb);
    return 0;
}

int BleIf_EnableBLE()
{
    int ret = 0;

#ifdef CC35XX
    //Get new seed from HSM
    uint8_t seed[MAX_SEED_SIZE];
    os_memset(seed, 0x55, MAX_SEED_SIZE);

    //Send set initial seed to the controller
    ret = ctrlCmdFw_SetSeedCmd(seed, MAX_SEED_SIZE);

    if (OSI_OK != ret)
    {
        Report("\n\r BleIf_EnableBLE: Failed to set initial seed. error number: %d", ret);
    }
#endif

    //Send BLE enable command to the controller
    ret = ctrlCmdFw_EnableBLECmd();

    if (OSI_OK != ret)
    {
        Report("\n\r BleIf_EnableBLE: Failed to enable BLE. error number: %d", ret);
    }
    //Wait for the controller to be enabled before starting host
    //Currently use sleep. TODO: Wait for FW ready massage
    Report("\n\r-------------- Wait for BLE Controller");
    osi_Sleep(2);

    return ret;
}

int BleIf_SetBdAddr(const unsigned char *pBdAddr)
{
    return ctrlCmdFw_SetBdAddrCmd(pBdAddr);
}

int BleIf_SetSeed(uint8_t *pSeed, uint8_t size)
{
    return ctrlCmdFw_SetSeedCmd(pSeed, size);
}
