//
//  TapGestureRecognizer.h
//  EnjoyYourMoney
//
//  Created by Erawppa on 2011/9/3.
//  Copyright 2011年 __MyCompanyName__. All rights reserved.
//
#ifndef __TAP_GESTURE_RECOGNIZER_H__
#define __TAP_GESTURE_RECOGNIZER_H__

#include "eplibs\GestureRecognizer\GestureRecognizer.h"

class TapGestureRecognizer : public GestureRecognizer
{
public:
    static TapGestureRecognizer* recognizer();
    
    eGestureRecognizerType getRecognizerType();
};

#endif//__TAP_GESTURER_ECOGNIZER_H__