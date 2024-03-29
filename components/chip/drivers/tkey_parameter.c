/***********************************************************************//** 
 * \file  tkey_parameter.c
 * \brief  csi tkey parameter
 * \copyright Copyright (C) 2015-2022 @ ASMCHIP
 * <table>
 * <tr><th> Date  <th>Version  <th>Author  <th>Description
 * <tr><td> 2020-11-24 <td>V0.0  <td>ASM AE Team   <td>initial
 * </table>
 * *********************************************************************
*/ 

#include "tkey.h"

/****************************************************
//TCHx GPIO Map
*****************************************************/  
/*
 *------------------*   *------------------*   *------------------*   *------------------*
 | PIN    | tkey CH |   | PIN    | tkey CH |   | PIN    | tkey CH |   | PIN    | tkey CH |   
 |--------|---------|   |--------|---------|   |--------|---------|   |--------|---------|
 | PB0.1  |  TCH0   |   | PA0.8  |  TCH8   |   | PB0.5  |  TCH16  |   | PB0.13 |  TCH24  |
 |--------|---------|   |--------|---------|   |--------|---------|   *------------------*
 | PA0.0  |  TCH1   |   | PA0.9  |  TCH9   |   | PB0.6  |  TCH17  |
 |--------|---------|   |--------|---------|   |--------|---------|
 | PA0.1  |  TCH2   |   | PA0.10 |  TCH10  |   | PB0.7  |  TCH18  |
 |--------|---------|   |--------|---------|   |--------|---------|
 | PA0.2  |  TCH3  *|   | PA0.11 |  TCH11  |   | PB0.8  |  TCH19  |
 |--------|---------|   |--------|---------|   |--------|---------|
 | PA0.3  |  TCH4   |   | PA0.12 |  TCH12  |   | PB0.9  |  TCH20  |
 |--------|---------|   |--------|---------|   |--------|---------|
 | PA0.4  |  TCH5   |   | PA0.13 |  TCH13  |   | PB0.10 |  TCH21  |
 |--------|---------|   |--------|---------|   |--------|---------|
 | PB0.2  |  TCH6   |   | PB0.0  |  TCH14  |   | PB0.11 |  TCH22  |
 |--------|---------|   |--------|---------|   |--------|---------|
 | PB0.3  |  TCH7   |   | PB0.4  |  TCH15  |   | PB0.12 |  TCH23  |
 *------------------*   *------------------*   *------------------*
 */

//Pins with * are special pins,Special pin description:
//TCH3---> fvr


void tkey_parameter_init(void)
{
/****************************************************
//TK basic parameters
*****************************************************/
	dwTkeyIoEnable=TCH_EN(0)|TCH_EN(1)|TCH_EN(2)|TCH_EN(4)|TCH_EN(5)|TCH_EN(6)|TCH_EN(7)|TCH_EN(8)|TCH_EN(9)|TCH_EN(10)|TCH_EN(11)
				   |TCH_EN(12)|TCH_EN(13)|TCH_EN(14)|TCH_EN(15)|TCH_EN(16)|TCH_EN(17)|TCH_EN(18)|TCH_EN(19)|TCH_EN(20)
				   |TCH_EN(21)|TCH_EN(22)|TCH_EN(23)|TCH_EN(24);
	byTkeyGlobalSens=2;								//TK Global Tkey Sensitivity,0=invalid;
	hwTkeyGlobalTrigger=50;							//TK Global Tkey Trigger,0=invalid;
	byTkeyGlobalIcon=4;								//TK Global Tkey Icon,0=invalid;
	byPressDebounce=3;								//Press debounce 1~10
	byReleaseDebounce=3;							//Release debounce 1~10
	byKeyMode=1;									//Key mode 0=first singlekey,1=multi key,2=strongest single-key
	byMultiTimesFilter=0;							//MultiTimes Filter,>4 ENABLE <4 DISABLE
	byValidKeyNum=4;								//Valid Key number when touched
	byBaseUpdateSpeed=10;							//baseline update speed
	byTkeyRebuildTime=16;							//longpress rebuild time = byTkeyRebuildTime*1s  0=disable
/****************************************************
//TK parameter fine-tuning
*****************************************************/
	byTkeyFineTurn=DISABLE;							//Tkey sensitivity fine tuning ENABLE/DISABLE
	byTkeyChxSens[0]=2;								//TCHx manual Sensitivity
	byTkeyChxSens[1]=2;								//TCHx manual Sensitivity
	byTkeyChxIcon[0]=5;								//TCHx manual ICON
	byTkeyChxIcon[1]=5;								//TCHx manual ICON
/****************************************************
//TK special parameter define
*****************************************************/
	hwTkeyPselMode=TK_PWRSRC_AVDD;					//tk power sel:TK_PWRSRC_FVR/TK_PWRSRC_AVDD   when select TK_PSEL_FVR PA0.0(TCH24) need a 104 cap
	hwTkeyEcLevel=TK_ECLVL_3V6;						//C0 voltage sel:TK_ECLVL_1V/TK_ECLVL_2V/TK_ECLVL_3V/TK_ECLVL_3V6
	hwTkeyFvrLevel=TK_FVR_2048V;					//FVR level:TK_FVR_2048V/TK_FVR_4096V/TK_FVR_NONE
/****************************************************
//TK low power function define(not included)
*****************************************************/
	//byTkeyLowPowerMode=ENABLE;						//touch key can goto sleep when TK lowpower mode enable
	//byTkeyLowPowerLevel=5;							//0=none 1=16ms 2=32ms 3=64ms 4=128ms,>4=186ms Scan interval when sleep
	//byTkeyWakeupLevel=6;							//0~7;The larger the value the higher the wakeup threshold
/****************************************************
//TK Hidden function define
*****************************************************/
	//byTkeyDstStatus=1;							
	//byTkeyIntrStatus=1;							
	//byTkeyImtvtimTime=0;
	//byTkeyNegBuildBounce=10;						
	//byTkeyPosBuildBounce=10;						
}                  
