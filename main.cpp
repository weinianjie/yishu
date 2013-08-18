#include <windows.h>
#include<iostream>
#include <stdio.h>
#include <stdlib.h>
#include <TIME.H>

#include "resource.h"
#include "GValue.h"
#include "Component.h"
#include "Event.h"


using namespace ht;

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	WNDCLASSEX wc; /* A properties struct of our window */
	HWND hwnd; /* A 'HANDLE', hence the H, or a pointer to our window */
	MSG Msg; /* A temporary location for all messages */

	/* zero out the struct and set the stuff we want to modify */
	memset(&wc,0,sizeof(wc));
	wc.cbSize		 = sizeof(WNDCLASSEX);
	wc.lpfnWndProc	 = WndProc; /* This is where we will send messages to */
	wc.hInstance	 = hInstance;
	wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
	
	/* White, COLOR_WINDOW is just a #define for a system color, try Ctrl+Clicking it */
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
	wc.lpszClassName = "WindowClass";
//	wc.hIcon		 = LoadIcon(NULL, IDI_APPLICATION); /* Load a standard icon */
//	wc.hIcon		 = (HICON)LoadImage(NULL,"DZYX.ico",IMAGE_ICON,0,0,LR_LOADFROMFILE);
	wc.hIcon 		 = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_MWIND));
//	wc.hIconSm		 = LoadIcon(NULL, IDI_WINLOGO);//不设置就使用hIcon的 

	if(!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	

	hwnd = CreateWindowEx(WS_EX_CLIENTEDGE,"WindowClass","艺术家神器",WS_VISIBLE|WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, /* x */
		CW_USEDEFAULT, /* y */
		800, /* width */
		600, /* height */
		NULL,NULL,hInstance,NULL);

	if(hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		return 0;
	}
	
    GValue::G_hinstance = hInstance;
    GValue::G_hwnd = hwnd;
    
	AddCountX();
	AddCountY();
	AddWidth();
	AddHeight();
	AddLimiter();
	AddEncoder();
	AddButton();
	AddArticle();
	AddScreen();
	AddCanvas();
    
	
    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

	while(GetMessage(&Msg, NULL, 0, 0) > 0) { /* If no error is received... */
		TranslateMessage(&Msg); /* Translate keycodes to chars if present */
		DispatchMessage(&Msg); /* Send it to WndProc */
	}
	return Msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
	
	int wmId, wmEvent;
	
	switch(Message) {
		
		case WM_PAINT: {
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(GValue::G_hwnd, &ps);
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(0,0,222));
			TextOut(hdc, UI_LEFT(0) - 12, UI_TOP(0) + 4, TEXT("X"), 1);
			TextOut(hdc, UI_LEFT(1) - 12, UI_TOP(0) + 4, TEXT("Y"), 1);
			TextOut(hdc, UI_LEFT(0) - 12, UI_TOP(1) + 4, TEXT("W"), 1);
			TextOut(hdc, UI_LEFT(1) - 12, UI_TOP(1) + 4, TEXT("H"), 1);
			TextOut(hdc, UI_LEFT(0) - 12, UI_TOP(2) + 4, TEXT("L"), 1);
			TextOut(hdc, UI_LEFT(1) - 12, UI_TOP(2) + 4, TEXT("S"), 1);
			EndPaint(GValue::G_hwnd, &ps);
			
			break;
		}	
			
		case WM_COMMAND: {
	   		wmId    = LOWORD(wParam); 
   			wmEvent = HIWORD(wParam);
   			
   			//按钮事件 
   			if(wmId == IDC_BUTTON){
   				TrySeveDeskBmp();
   				break;
   			}
			
			//文本改变 || 状态按钮点击 
			if(wmEvent == EN_CHANGE || wmId == IDC_CHECKBOX_ENCODE) {
				RECT rc;
				GetClientRect(hwnd,&rc);
				
				//先强行设置整个画布无效，否则调用UpdateWindow的时候只更新被覆盖的地方 
				InvalidateRect(hwnd, &rc, true);//第三个参数指明重画时是否擦除背景 
				
				UpdateWindow(GValue::G_hwnd_canvas);
				break;
				
				/*switch(wmId) {
					//文章改变 
					case IDC_TEXT_ARTICLE: {
						//先强行设置整个画布无效，否则调用UpdateWindow的时候只更新被覆盖的地方 
						InvalidateRect(hwnd, &rc, true);//第三个参数指明重画时是否擦除背景 
						
						UpdateWindow(GValue::G_hwnd_canvas);
						break;
					}
					
					//配置改变
					case IDC_TEXT_COUNTX: 
						GValue::G_CountX = GetDlgItemInt(GValue::G_hwnd_countX, IDC_TEXT_COUNTX, NULL, false);
					case IDC_TEXT_COUNTY: 
					case IDC_TEXT_WIDTH: 
					case IDC_TEXT_HEIGHT: 
					case IDC_TEXT_LIMITER: {
						//MessageBox(NULL, "Window Creation Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
						break;
					}
					
					default:
						break;
				}*/
			}
			break;
		} 
		
		//resize the window
		case WM_SIZE: {
			ResizeWindow();
			break;
		} 
		/* trap the WM_CLOSE (clicking X) message, and actually tell the window to close */
		case WM_CLOSE: {
			DestroyWindow(hwnd);
			break;
		}
		
		/* Upon destruction, tell the main thread to stop */
		case WM_DESTROY: {
			PostQuitMessage(0);
			break;
		}
		
		/* All other messages (a lot of them) are processed using default procedures */
		default:
			return DefWindowProc(hwnd, Message, wParam, lParam);
	}
	return 0;
}

