#include "TextLimiter.h"

namespace ht {
	
	TextLimiter::TextLimiter() {
               
		WNDCLASSEX wc;

		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpszClassName = "TextLimiter";
		wc.lpfnWndProc	 = TextLimiter::_WndProc;
		wc.hInstance	 = GValue::GetHinstance();
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "TextLimiter Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		} else {				
			this->_hwnd = CreateWindow(
	        		"TextLimiter",
	        		"Caption",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_WANTRETURN,
	        		UI_LEFT(2), UI_TOP(0), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::GetHwnd(),
	        		(HMENU)IDC_TEXT_LIMITER,
	        		GValue::GetHinstance(),
	        		0
	        		);
			
			ShowWindow(this->_hwnd, SW_SHOW);
		}
	}
	
	
	TextLimiter::~TextLimiter() {		
	}
	
	
	void TextLimiter::OnLeftClick() {
    }	
	
	
	void TextLimiter::OnRightClick() {
		MessageBox ( NULL,"test", "my_message", MB_OK );
	}
	
	
	LRESULT CALLBACK TextLimiter::_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		
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
    
	
	TextLimiter* TextLimiter::GetInstance() {
        if(_instance == NULL){
            _instance = new TextLimiter();             
        }
        return _instance;
	}	
	
	
	HWND TextLimiter::GetHwnd() {
		return _hwnd;
	}
    
	
	//-----------------------------------------------
    TextLimiter* TextLimiter::_instance = NULL;    
	
}
