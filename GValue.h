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

#define  UI_COM_LEFT					15
#define  UI_COM_TOP						10
#define  UI_COM_WIDTH					40
#define  UI_COM_HEIGHT						20
   
namespace ht {

	int rgb2hex(int r,int g,int b);
	
	COLORREF hex2rgb(int hex);
	
	int UI_LEFT(int n);
	int UI_TOP(int n);
	
	long max(long a, long b); 
	long min(long a, long b);

    class GValue{
        public:	
        	static       HINSTANCE G_hinstance;
        	static       HWND      G_hwnd;  
			static		HWND	G_hwnd_countX;
			static		HWND	G_hwnd_countY;
			static		HWND	G_hwnd_width;
			static		HWND	G_hwnd_height;
			static		HWND	G_hwnd_limiter;
			static		HWND	G_hwnd_encoder;   
			static		HWND	G_hwnd_button;
			static		HWND	G_hwnd_article;
			static		HWND	G_hwnd_screen;
			static		HWND	G_hwnd_canvas; 
    };
}

#endif

