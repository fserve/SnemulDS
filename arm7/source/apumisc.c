#include <nds/memory.h>
#include <nds.h>
#include <string.h>
#include "pocketspc.h"
#include "apu.h"
#include "apumisc.h"
#include "ipc_libnds_extended.h"

// archeide: shared structure with SNEmul

u8 apuShowRom;

void ApuWriteControlByte(u8 byte) {
    u8 orig = APU_MEM[APU_CONTROL_REG];
    if ((orig & 0x1) == 0 && (byte & 0x1) != 0) {
        MyIPC->TIM0 = 0;
        APU_MEM[APU_COUNTER0] = 0;
	}
    if ((orig & 0x2) == 0 && (byte & 0x2) != 0) {
        MyIPC->TIM1 = 0;    	
        APU_MEM[APU_COUNTER1] = 0;
	}
    if ((orig & 0x4) == 0 && (byte & 0x4) != 0) {
        MyIPC->TIM2 = 0;    	
        APU_MEM[APU_COUNTER2] = 0;
	}

	if (byte & 0x10) {
		// Clear port 0 and 1
		APU_MEM[0xF4] = 0;
		APU_MEM[0xF5] = 0;
        PORT_SNES_TO_SPC[0] = 0;
        PORT_SNES_TO_SPC[1] = 0;
//        PORT_SPC_TO_SNES[0] = 0;
//        PORT_SPC_TO_SNES[1] = 0;
	}
	if (byte & 0x20) {
		// Clear port 0 and 1
		APU_MEM[0xF6] = 0;
		APU_MEM[0xF7] = 0;
        PORT_SNES_TO_SPC[2] = 0;
        PORT_SNES_TO_SPC[3] = 0;
//        PORT_SPC_TO_SNES[2] = 0;
//        PORT_SPC_TO_SNES[3] = 0;
	}

	if (byte & 0x80) {
		if (!apuShowRom) {
			apuShowRom = 1;
			memcpy(APU_MEM+0xFFC0, iplRom, 0x40);
			
			//for (int i=0; i<=0x3F; i++) APU_MEM[0xFFC0 + i] = iplRom[i];
		}
	} else {
		if (apuShowRom) {
			apuShowRom = 0;
            memcpy(APU_MEM+0xFFC0, APU_EXTRA_MEM, 0x40);
			
			//for (int i=0; i<=0x3F; i++) APU_MEM[0xFFC0 + i] = APU_EXTRA_MEM[i];
		}
	}
}

void ApuPrepareStateAfterReload() {
/*    APU_MEM[APU_COUNTER0] &= 0xf;
    APU_MEM[APU_COUNTER1] &= 0xf;
    APU_MEM[APU_COUNTER2] &= 0xf;*/

	int i=0;
    for (i = 0; i < 4; i++) PORT_SNES_TO_SPC[i] = APU_MEM[0xF4 + i];

	// archeide
	MyIPC->TIM0 = 0;
	MyIPC->TIM1 = 0;
	MyIPC->TIM2 = 0;	

	apuShowRom = APU_MEM[APU_CONTROL_REG] >> 7;
    if (apuShowRom) {
		for (int i=0; i<=0x3F; i++) APU_MEM[0xFFC0 + i] = iplRom[i];
	}
	else {
		for (int i=0; i<=0x3F; i++) APU_MEM[0xFFC0 + i] = APU_EXTRA_MEM[i];
	}
}


void ApuWriteUpperByte(u8 byte, u32 address) {
    APU_EXTRA_MEM[address - 0xFFC0] = byte;

    if (apuShowRom)
        APU_MEM[address] = iplRom[address - 0xFFC0];
	}

void ApuSetShowRom()
{
	apuShowRom = 0;
}
