#include "windows.h"
#include "Component.h"
#include "Event.h"

using namespace ht;

namespace ht {
	
	void AddCountX(){
			GValue::G_hwnd_countX = CreateWindowEx(
					0,
	        		"EDIT",
	        		//itoa(i, buf1, 10),
	        		"60",
	        		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | WS_BORDER | ES_NUMBER,
	        		UI_LEFT(0), UI_TOP(0), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::G_hwnd,
	        		(HMENU)IDC_TEXT_COUNTX,
	        		GValue::G_hinstance,
	        		0
	        		);
			//SetDlgItemInt(GValue::G_hwnd_countX, IDC_TEXT_COUNTX, 100, false); 
			ShowWindow(GValue::G_hwnd_countX, SW_SHOW);
	}
	void AddCountY(){
			GValue::G_hwnd_countY = CreateWindowEx(
					0,
	        		"EDIT",
	        		"40",
	        		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | WS_BORDER | ES_NUMBER,
	        		UI_LEFT(1), UI_TOP(0), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::G_hwnd,
	        		(HMENU)IDC_TEXT_COUNTY,
	        		GValue::G_hinstance,
	        		0
	        		);
			//SetDlgItemInt(GValue::G_hwnd_countY, IDC_TEXT_COUNTY, 80, false); 
			ShowWindow(GValue::G_hwnd_countY, SW_SHOW);
	}
	void AddWidth(){
			GValue::G_hwnd_width = CreateWindowEx(
					0,
	        		"EDIT",
	        		"10",
	        		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | WS_BORDER | ES_NUMBER,
	        		UI_LEFT(0), UI_TOP(1), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::G_hwnd,
	        		(HMENU)IDC_TEXT_WIDTH,
	        		GValue::G_hinstance,
	        		0
	        		);
			//SetDlgItemInt(GValue::G_hwnd_width, IDC_TEXT_WIDTH, 10, false); 
			ShowWindow(GValue::G_hwnd_width, SW_SHOW);
	}
	void AddHeight(){
			GValue::G_hwnd_height = CreateWindowEx(
					0,
	        		"EDIT",
	        		"10",
	        		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | WS_BORDER | ES_NUMBER,
	        		UI_LEFT(1), UI_TOP(1), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::G_hwnd,
	        		(HMENU)IDC_TEXT_HEIGHT,
	        		GValue::G_hinstance,
	        		0
	        		);
			//SetDlgItemInt(GValue::G_hwnd_height, IDC_TEXT_HEIGHT, 10, false); 
			ShowWindow(GValue::G_hwnd_height, SW_SHOW);
	}
	void AddLimiter(){
			GValue::G_hwnd_limiter = CreateWindowEx(
					0,
	        		"EDIT",
	        		"1",
	        		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | WS_BORDER | ES_NUMBER,
	        		UI_LEFT(0), UI_TOP(2), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::G_hwnd,
	        		(HMENU)IDC_TEXT_LIMITER,
	        		GValue::G_hinstance,
	        		0
	        		);
			//SetDlgItemInt(GValue::G_hwnd_limiter, IDC_TEXT_LIMITER, 1, false); 
			ShowWindow(GValue::G_hwnd_limiter, SW_SHOW);
	}
	void AddEncoder(){
			GValue::G_hwnd_encoder = CreateWindowEx(
					0,
	        		"BUTTON",
	        		"",
	        		WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_GROUP | WS_BORDER | BS_AUTOCHECKBOX,
	        		UI_LEFT(1), UI_TOP(2), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::G_hwnd,
	        		(HMENU)IDC_CHECKBOX_ENCODE,
	        		GValue::G_hinstance,
	        		0
	        		);
			
			ShowWindow(GValue::G_hwnd_encoder, SW_SHOW);
	}
	void AddButton(){
			GValue::G_hwnd_button = CreateWindowEx(
					0,
	        		"BUTTON",
	        		"导出图片",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_WANTRETURN,
	        		UI_LEFT(0), UI_TOP(3), (UI_COM_WIDTH * 2 + UI_COM_LEFT), UI_COM_HEIGHT,
	        		GValue::G_hwnd,
	        		(HMENU)IDC_BUTTON,
	        		GValue::G_hinstance,
	        		0
	        		);
			
			ShowWindow(GValue::G_hwnd_button, SW_SHOW);
	}
	void AddArticle(){
			RECT rc;
			GetClientRect(GValue::G_hwnd,&rc); 
		
			int width=rc.right-rc.left;
			int height=rc.bottom-rc.top;
		
			GValue::G_hwnd_article = CreateWindowEx(
					0,
	        		"EDIT",
	        		"此时无声胜有声",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_HSCROLL | ES_WANTRETURN | ES_MULTILINE | ES_AUTOHSCROLL | ES_AUTOVSCROLL,
	        		UI_LEFT(2), UI_TOP(0), (width - UI_LEFT(2) - UI_COM_LEFT), (UI_COM_HEIGHT * 5 + UI_COM_TOP),
	        		GValue::G_hwnd,
	        		(HMENU)IDC_TEXT_ARTICLE,
	        		GValue::G_hinstance,
	        		0
	        		);
	        		
			//设置最大字符数，默认只有64000， 
			SendDlgItemMessage(GValue::G_hwnd, IDC_TEXT_ARTICLE, EM_SETLIMITTEXT, 2000000, 0);
			
			ShowWindow(GValue::G_hwnd_article, SW_SHOW);
	}
	LRESULT CALLBACK ScreenProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		switch(Message) {		
		
			case WM_CLOSE: {
				DestroyWindow(hwnd);
				break;
			}
			
			case WM_DESTROY: {
				PostQuitMessage(0);
				break;
			}
			
			default:
				return DefWindowProc(hwnd, Message, wParam, lParam);
		}
	}
	void AddScreen(){
		WNDCLASSEX wc;

		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpszClassName = "Screen";
		wc.lpfnWndProc	 = ScreenProc;
		wc.hInstance	 = GValue::G_hinstance;
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "Screen Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		} else {
			
			RECT rc;
			GetClientRect(GValue::G_hwnd,&rc); 
		
			int width=rc.right-rc.left;
			int height=rc.bottom-rc.top;
			
			
			GValue::G_hwnd_screen = CreateWindowEx(
					0,
	        		"Screen",
	        		"",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_WANTRETURN,
	        		0, UI_TOP(4), width, (height - UI_TOP(4)),
	        		GValue::G_hwnd,
	        		(HMENU)IDC_SCREEN,
	        		GValue::G_hinstance,
	        		0
	        		);
			
			ShowWindow(GValue::G_hwnd_screen, SW_SHOW);
		}
	}
	LRESULT CALLBACK CanvasProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		switch(Message) {
			case WM_PAINT:{
				DrawCanvas();
				break;
			}
			
			case WM_CLOSE: {
				DestroyWindow(hwnd);
				break;
			}
			
			case WM_DESTROY: {
				PostQuitMessage(0);
				break;
			}
			
			default:
				return DefWindowProc(hwnd, Message, wParam, lParam);
		}
	}
	void AddCanvas(){
		WNDCLASSEX wc;

		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpszClassName = "Canvas";
		wc.lpfnWndProc	 = CanvasProc;
		wc.hInstance	 = GValue::G_hinstance;
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND);
		
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "Canvas Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		} else {
			RECT rc;
			GetClientRect(GValue::G_hwnd,&rc); 
		
			int width=rc.right-rc.left;
			int height=rc.bottom-rc.top;
			
			GValue::G_hwnd_canvas = CreateWindowEx(
					0,
	        		"Canvas",
	        		"",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER,
	        		10, 10, width - 20, (height - UI_TOP(4) - 20),
	        		GValue::G_hwnd_screen,
	        		(HMENU)IDC_CANVAS,
	        		GValue::G_hinstance,
	        		0
	        		);
			
			ShowWindow(GValue::G_hwnd_canvas, SW_SHOW);
		}
	}
	
}
