#include <windows.h>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TIME.H>

#ifndef _GVALUE_H
#define _GVALUE_H

#define  IDC_TEXT_COUNTX                  110
#define  IDC_TEXT_COUNTY                  120
#define  IDC_TEXT_WIDTH                  130
#define  IDC_TEXT_HEIGHT                  140
#define  IDC_TEXT_LIMITER                  150
#define  IDC_TEXT_ARTICLE                  160
#define  IDC_CHECKBOX_ENCODE                  170
#define  IDC_BUTTON                  180
#define  IDC_SCREEN                  190
#define  IDC_CANVAS                  200

#define  UI_COM_LEFT					10
#define  UI_COM_TOP						10
#define  UI_COM_WIDTH					40
#define  UI_COM_HEIGHT						20
   
namespace ht {

	int rgb2hex(int r,int g,int b);
	
	COLORREF hex2rgb(int hex);
	
	int UI_LEFT(int n);
	int UI_TOP(int n);
	
	void TrySeveDeskBmp(HWND RiWnd=NULL);

    class GValue{
        public:
        
        	static       HINSTANCE 			GetHinstance();
        	
        	static       HWND				GetHwnd();
        	
        	static       void 				SetHinstance(HINSTANCE hinstance);
        	
        	static       void				SetHwnd(HWND hwnd);
        	
        private:	
                 
        	static       HINSTANCE _hinstance;
        	static       HWND      _hwnd;        	
    };
}

#endif

