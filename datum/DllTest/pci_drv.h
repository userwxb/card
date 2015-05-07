#include <windows.h>

typedef  int * AFDXPCI_HANDLE;
typedef void (*USER_INTERRUPT_HANDLER)(AFDXPCI_HANDLE handle);




#if defined(__cplusplus)

extern "C" AFDXPCI_HANDLE AFDX_OpenDevDrv( unsigned int DevID);     /*打开AFDX设备*/
extern "C" void AFDX_CloseDevDrv(AFDXPCI_HANDLE *DevDeviceHandle);  /*关闭AFDX设备*/ 
extern "C" unsigned short  AFDX_ReadDpram (AFDXPCI_HANDLE DevDeviceHandle,unsigned int dwOffset); /*读AFDX双口*/
extern "C" void AFDX_WriteDpram(AFDXPCI_HANDLE DevDeviceHandle,unsigned int dwOffset, unsigned short data);/*写AFDX双口*/
extern "C" unsigned int AFDX_GetDparamBase(AFDXPCI_HANDLE DevDeviceHandle);/*获取AFDX双口基地址*/    
extern "C" BOOL AFDX_DMAReadBlock(AFDXPCI_HANDLE DevDeviceHandle, DWORD dwLocalAddr, PVOID buf, DWORD dwBytes);/*DMA 读取双口*/
extern "C" BOOL AFDX_DMAWriteBlock(AFDXPCI_HANDLE DevDeviceHandle, DWORD dwLocalAddr, PVOID buf, DWORD dwBytes);/*DMA 写双口*/
extern "C" BOOL AFDX_IntEnable (AFDXPCI_HANDLE hPlx, USER_INTERRUPT_HANDLER funcIntHandler);/*中断连接*/
extern "C" void AFDX_IntDisable (AFDXPCI_HANDLE hPlx);/*断开终端连接*/
extern "C" int AFDX_Read_FIFO(AFDXPCI_HANDLE DevDeviceHandle,unsigned int  *packetbuf,unsigned int *Packetlen);
extern "C" int AFDX_Init_MAC(AFDXPCI_HANDLE DevDeviceHandle, char MAC_address1[6], char MAC_address2[6]); 
extern "C" void AFDX_Set_TxCtrl(AFDXPCI_HANDLE DevDeviceHandle,int VLID_PHY,int VL_Enable,int Lmax,int NetSel,int VLID,unsigned int BAGValue);
extern "C" void AFDX_Set_RxCtrl(AFDXPCI_HANDLE DevDeviceHandle,int VLID_PHY,int VL_Enable,int skewmax,int IC,unsigned int RM,int VLID);
extern "C" int AFDX_Read_FIFO(AFDXPCI_HANDLE DevDeviceHandle,unsigned int  *packetbuf,unsigned int *Packetlen);
extern "C" int AFDX_WriteVL_FIFO(AFDXPCI_HANDLE DevDeviceHandle,int VLID_PHY,unsigned int *buf,int packetlen);

#else
    
    AFDXPCI_HANDLE AFDX_OpenDevDrv( unsigned int DevID);     /*打开AFDX设备*/
	void AFDX_CloseDevDrv(AFDXPCI_HANDLE *DevDeviceHandle);  /*关闭AFDX设备*/ 
	unsigned short  AFDX_ReadDpram (AFDXPCI_HANDLE DevDeviceHandle,unsigned int dwOffset); /*读AFDX双口*/
    void AFDX_WriteDpram(AFDXPCI_HANDLE DevDeviceHandle,unsigned int dwOffset, unsigned short data);/*写AFDX双口*/
	unsigned int AFDX_GetDparamBase(AFDXPCI_HANDLE DevDeviceHandle);/*获取AFDX双口基地址*/    
	BOOL AFDX_DMAReadBlock(AFDXPCI_HANDLE DevDeviceHandle, DWORD dwLocalAddr, PVOID buf, DWORD dwBytes);/*DMA 读取双口*/
    BOOL AFDX_DMAWriteBlock(AFDXPCI_HANDLE DevDeviceHandle, DWORD dwLocalAddr, PVOID buf, DWORD dwBytes);/*DMA 写双口*/
    BOOL AFDX_IntEnable (AFDXPCI_HANDLE DevDeviceHandle, USER_INTERRUPT_HANDLER funcIntHandler);/*中断连接*/
	void AFDX_IntDisable (AFDXPCI_HANDLE DevDeviceHandle);/*断开终端连接*/
	int AFDX_WriteVL_FIFO(AFDXPCI_HANDLE DevDeviceHandle,int VLID_PHY,unsigned int buf[],int packetlen);
	int AFDX_Read_FIFO(AFDXPCI_HANDLE DevDeviceHandle,unsigned int  *packetbuf,unsigned int *Packetlen);
    int AFDX_Init_MAC(AFDXPCI_HANDLE DevDeviceHandle, char MAC_address1[6], char MAC_address2[6]); 
	void AFDX_Set_TxCtrl(AFDXPCI_HANDLE DevDeviceHandle,int VLID_PHY,int VL_Enable,int Lmax,int NetSel, int VLID,unsigned int BAGValue);
	int AFDX_GET_FPGAVersion(AFDXPCI_HANDLE DevDeviceHandle);/*获取FPGA版本号*/
    int AFDX_Read_FIFO(AFDXPCI_HANDLE DevDeviceHandle,unsigned int  *packetbuf,unsigned int *Packetlen);
#endif
