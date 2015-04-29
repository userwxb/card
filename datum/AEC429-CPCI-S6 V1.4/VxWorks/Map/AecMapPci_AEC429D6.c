#include "copyright_wrs.h"

#ifdef VXWORKSP
#include <configInum.h>
#else
#include <intlib.h> 
#endif

#include <iv.h>

#include "vxWorks.h"
#include "sysLib.h"
#include "vmlib.h"
#include "config.h"
#include "memLib.h"


/**************************************************/
/* Add MMU mappings for Excalibur card:           */
/**************************************************/

STATUS AecMapPci_AEC429D6(void)
{
	STATUS retval=0;
	int busNo=0, devNo=0, funcNo=0;
	unsigned long address=0, data32=0;
	int i=0;
	unsigned long barlen[6]={0};
	unsigned long PdcMemBase[6]={0};
	unsigned char canloop=1;
	int cardID=0;

	while ((canloop==1)&&(cardID<256))
	{
		retval = pciFindDevice(0x1ba0, 0x0100, cardID, &busNo, &devNo, &funcNo);
		if (retval != OK)
		{ /* no device found */
			canloop = 0;
			if (cardID==0)
				return ERROR; /* can not find any card */
		}
		else
		{
			for (i=0;i<6;i++)
			{
				/* Get Bar Base Address */
				pciConfigInLong(busNo, devNo, funcNo, 0x10+i*4, &address);
				PdcMemBase[i] = address;
				/* Get Bar Base Address */
				pciConfigInLong(busNo, devNo, funcNo, 0x10+i*4, &address);
				/* Get Bar Range */
				pciConfigOutLong(busNo, devNo, funcNo, 0x10+i*4, 0xffffffff);
				pciConfigInLong(busNo, devNo, funcNo, 0x10+i*4, &data32);
				/* Write Address Back */
				pciConfigOutLong(busNo, devNo, funcNo, 0x10+i*4, address);
				if(address & 0x00000001)
				{/* IO */
					data32&=0xfffffffc;
					address&=0xfffffffc;
				}
				else
				{/* Memory */
					data32&=0xfffffff0;
					address&=0xfffffff0;
				}
				PdcMemBase[i] = address;
				if(data32 == 0)
					barlen[i]=0;
				else
					barlen[i]=(~data32)+1;
			}

			/* BAR0 */
			address = PdcMemBase[0];
			retval = sysMmuMapAdd((void *)address, barlen[0], VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_PCI);
			if (retval != OK)
				return ERROR;

			/* BAR2 */
			address = PdcMemBase[2];
			retval = sysMmuMapAdd((void *)address, barlen[2], VM_STATE_MASK_FOR_ALL, VM_STATE_FOR_PCI);
			if (retval != OK)
				return ERROR;
		}
		cardID++;
	}

	return OK;
}
