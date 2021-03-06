#ifdef ARM9
#include <stdbool.h>
///// From MoonShell2.00b5 / M3Sakura /////

// for M3 extention pack.

//0x400000: SST read only
//0x400004: SST read/write

//0x400002: PSRAM read only
//0x400006: PSRAM read/write

//0x400003: CF read only
//0x400007: CF read/write

static uint16 M3_SetChipReg(uint32 Data)
{
	vuint16 i,j;

	i = *(volatile uint16*)(0x700001*2+0x8000000);
	
	i = *(volatile uint16*)(0x000007*2+0x8000000);
	i = *(volatile uint16*)(0x400ffe*2+0x8000000);
	i = *(volatile uint16*)(0x000825*2+0x8000000);
	
	i = *(volatile uint16*)(0x400309*2+0x8000000);
	i = *(volatile uint16*)(0x000000*2+0x8000000);
	i = *(volatile uint16*)(0x400db3*2+0x8000000);
	
	i = *(volatile uint16*)((Data*2)+0x8000000);
		
	j = *(volatile uint16*)(0x000407*2+0x8000000);
	i = *(volatile uint16*)(0x000000*2+0x8000000);	

	if(i){}
	return j;
}

static bool SelectOpration(uint16 Data)
{
	vuint16 i,j;
	i = *(volatile uint16*)(0x000000*2+0x9000000);
	
	i = *(volatile uint16*)(0xFFFFF0*2+0x8000000);
	
	i = *(volatile uint16*)(0xFFFFF6*2+0x8000000);
	i = *(volatile uint16*)(0xFFFFF6*2+0x8000000);
	i = *(volatile uint16*)(0xFFFFF6*2+0x8000000);
	
	i = *(volatile uint16*)(0xFFFFFE*2+0x8000000);
	i = *(volatile uint16*)(0xFFFFFE*2+0x8000000);
	i = *(volatile uint16*)(0xFFFFFE*2+0x8000000);
	
	i = *(volatile uint16*)(0xFFFFA5*2+0x8000000);
	i = *(volatile uint16*)(0xFFFFA5*2+0x8000000);
	i = *(volatile uint16*)(0xFFFFA5*2+0x8000000);

	i = *(volatile uint16*)((0x900000+Data)*2+0x8000000);
	
	i = *(volatile uint16*)(0xFFFFF8*2+0x8000000);
	j = *(volatile uint16*)(0xFFFFF4*2+0x8000000);

	if(i||j){}
	return true;
}
static uint16 G6_SetChipReg(uint16 Data) 
{
	return SelectOpration(Data);
}



static uint16 GetExtWData(uint32 Address)
{
	return *(volatile uint16*)Address;
}
//==================================================
#if 0
static void ResetCPLD(void)
{
	vuint16 i;
  
  	i=GetExtWData(0x000009*2+0x8000000);
   	i=GetExtWData(0x400a3c*2+0x8000000);
  	i=GetExtWData(0x000f58*2+0x8000000);
  	i=GetExtWData(0x400321*2+0x8000000);    
  	i=GetExtWData(0x000000*2+0x8000000);
  	i=GetExtWData(0x4000f8*2+0x8000000);
  	i=GetExtWData(0x400001*2+0x8000000);

    if(i){}
}
#endif
static void InitCPLD(void)
{
	vuint16 i;

  	i=GetExtWData(0xFFFFF0*2+0x8000000);
  
  	i=GetExtWData(0xFFFFF6*2+0x8000000);
  	i=GetExtWData(0xFFFFF6*2+0x8000000);
  	i=GetExtWData(0xFFFFF6*2+0x8000000);    

  	i=GetExtWData(0xFFFFFE*2+0x8000000);
  	i=GetExtWData(0xFFFFFE*2+0x8000000);
  	i=GetExtWData(0xFFFFFE*2+0x8000000);    
  
  	i=GetExtWData(0xFFFFA5*2+0x8000000);
  	i=GetExtWData(0xFFFFA5*2+0x8000000);
  	i=GetExtWData(0xFFFFA5*2+0x8000000);    

  	if(i){}
}
#if 0
static bool SelectRAM(void)
{
  	uint16 i;

  	InitCPLD();
  	i=GetExtWData(0x900006*2+0x8000000);  
  	i=GetExtWData(0xFFFFF8*2+0x8000000)&0x07;
  	
  	if(i==0x06)
  		return true;
	else
  		return false;
}
#endif
//-------
static bool DisableRAM(void)
{
  	vuint16 i,j;
  	
  	
  	InitCPLD();
 	i=GetExtWData(0x900002*2+0x8000000);  
  	i=GetExtWData(0xFFFFF8*2+0x8000000)&0x07;  
  	j=GetExtWData(0xFFFFF4*2+0x8000000)&0x07;   
  	if(i||j){} 	
  	return true;
}



/*********************SDRAM FUNCTION******************/
static void sdram_setcmd(uint32 command)
{

	vuint32 i;	
	
	i = *(volatile uint8*)(0x0000+0xa000000);
	//-----------------------------------------
	i = *(volatile uint8*)(0x9999+0xa000000);
	i = *(volatile uint8*)(0x9999+0xa000000);
	i = *(volatile uint8*)(0x6666+0xa000000);
	i = *(volatile uint8*)(0x6666+0xa000000);
	//-----------------------------------------
	i = *(volatile uint8*)(command+0xa000000);	
	//-----------------------------------------
	if(i){}
}


static void sdram_NOP(void)
{
	vuint32 i;	

	sdram_setcmd(0x1);
	i = *(volatile uint16*)(0x000000*2+0x8000000);
	if(i){}
}

static void sdram_PRECHARGE(void)
{
	vuint32 i;	

	sdram_setcmd(0x6);
	i = *(volatile uint16*)(0x000400*2+0x8000000);
	if(i){}
}

static void sdram_LOAD_MR(void)
{
	vuint32 i;	

	sdram_setcmd(0x8);
	i = *(volatile uint16*)(0x800020*2+0x8000000);
	
	sdram_setcmd(0x8);
	i = *(volatile uint16*)(0x000030*2+0x8000000);
	if(i){}
}

static void sdram_REFRESH(void)
{
	vuint32 i;	

	sdram_setcmd(0x7);
	i = *(volatile uint16*)(0x000000*2+0x8000000);
	if(i){}
}

static void sdram_init(void)
{
	
	vuint32 i, tmpdata=0;	

	for(i=0;i<0xf;i++)			//delay 
    {tmpdata = tmpdata>>8;}
         
	sdram_NOP();
	sdram_PRECHARGE();
	sdram_LOAD_MR();
	sdram_PRECHARGE();
	sdram_REFRESH();
	sdram_setcmd(0x3);			
	
}

static void sdram_PowerDown(void)
{
	vuint32	i;
	
	sdram_setcmd(0x5);
	i = *(volatile uint16*)(0x000000*2+0x8000000);
	if(i){}
}

static void sdram_Wakeup(void)
{
	vuint32	i;
	sdram_setcmd(0xa);
	i = *(volatile uint16*)(0x000000*2+0x8000000);
	sdram_setcmd(0x3);
	if(i){}
}

static vuint16* M3ExtPack_Start(){
  M3_SetChipReg(0x400006);	// enable write 0x8000000 
  G6_SetChipReg(0x6);

  sdram_init();
  sdram_PowerDown();
  sdram_Wakeup();
  
  return (vuint16*)0x08000000;
}

static void M3ExtPack_InitReadOnly(){
	DisableRAM();
}
#endif