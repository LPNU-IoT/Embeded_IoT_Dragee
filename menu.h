#ifndef MENU_SETUP_H

#define MENU_SETUP_H


#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <MenuLib.h>

#include "settings.h"
#include "charList.h"

Menu menu;

//menu
Screen* mainS;
Screen* Heat, *Cooling, *FAN, *STOP;
Line* TempSetH, *TempCurH, *TempSetC, *TempCurC, *TempCurF, *TempCurS;
//float tcH = 0, tcC = 0 ;
//________________________________



// STATUS_C menuSetup()
// {
//     while(1){

//     }

//     return STATUS_OK;
// }


//  Temperature          = 0.0;          // Variable for the current temperature
// float  TargetTemp           = 25;         // Default thermostat value for set temperature
// int    FrostTemp            = 5; 
STATUS_C initSection(){
    menu = *(initMenu());

    if(&menu){

        Heat = menu.addScreen_ptr(&menu, (char*)HeatName);
        Cooling = menu.addScreen_ptr(&menu, (char*)CoolingName);
        FAN = menu.addScreen_ptr(&menu, (char*)Fan);
        STOP = menu.addScreen_ptr(&menu, (char*)Stop);

        if(Heat){
            TempSetH = Heat->newLine_ptr(Heat, (char*)TSet, (char*)TempSet, NULL);
            TempSetH->val->setfloat(TempSetH->val, TargetTemp);
            TempCurH = Heat->newLine_ptr(Heat, (char*)TCur ,(char*)TempCurr, NULL);
            TempCurH->val->setfloat(TempCurH->val, Temperature);
        }else{
            return FAILURE;
        }


        if(Cooling){
            TempSetC = Cooling->newLine_ptr(Cooling, (char*)TSet, (char*)TempCurr, NULL);
            TempSetC->val->setfloat(TempSetC->val, TargetTemp);
            TempCurC = Cooling->newLine_ptr(Cooling, (char*)TCur, (char*)TempCurr, NULL);
            TempCurC->val->setfloat(TempCurC->val, Temperature);
        }else{
            return FAILURE;
        }

        if(FAN){
            TempCurF = FAN->newLine_ptr(FAN, (char*)TCur, (char*)TempCurr, NULL);
            TempCurF->val->setfloat(TempCurF->val, Temperature);
        }else{
            return FAILURE;
        }

        if(STOP){
            TempCurS = STOP->newLine_ptr(STOP, (char*)Stop, (char*)Empty, NULL);
        }else{
            return FAILURE;
        }
        return STATUS_OK;
    }
    return FAILURE;
} 

bool lcdLoop()
{
    if(CHECK_UPDATE_MENU){
        menu.printScreen(&menu);
    }
}

#endif