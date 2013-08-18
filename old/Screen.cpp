#include "Screen.h"

namespace ht {
	
	Screen::Screen() {
               
		WNDCLASSEX wc;

		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpszClassName = "Screen";
		wc.lpfnWndProc	 = Screen::_WndProc;
		wc.hInstance	 = GValue::GetHinstance();
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "Screen Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		} else {				
			this->_hwnd = CreateWindow(
	        		"Screen",
	        		"Caption",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_WANTRETURN,
	        		0, UI_TOP(2), 780, 480,
	        		GValue::GetHwnd(),
	        		(HMENU)IDC_SCREEN,
	        		GValue::GetHinstance(),
	        		0
	        		);
			
			ShowWindow(this->_hwnd, SW_SHOW);
		}
	}
	
	
	Screen::~Screen() {		
	}
	
	
	void Screen::OnLeftClick() {
    }	
	
	
	void Screen::OnRightClick() {
		MessageBox ( NULL,"test", "my_message", MB_OK );
	}
	
	
	LRESULT CALLBACK Screen::_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		
		static int   wmId, wmEvent ;
		switch(Message) {
			
//			case WM_PAINT: {
//
//				break;
//			}		
		
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
    
	
	Screen* Screen::GetInstance() {
        if(_instance == NULL){
            _instance = new Screen();             
        }
        return _instance;
	}	
	
	
	HWND Screen::GetHwnd() {
		return _hwnd;
	}
    
	
	//-----------------------------------------------
    Screen* Screen::_instance = NULL;    
	
}
