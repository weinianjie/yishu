#include "TextWidth.h"

namespace ht {
	
	TextWidth::TextWidth() {
               
		WNDCLASSEX wc;

		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpszClassName = "TextWidth";
		wc.lpfnWndProc	 = TextWidth::_WndProc;
		wc.hInstance	 = GValue::GetHinstance();
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "TextWidth Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		} else {				
			this->_hwnd = CreateWindow(
	        		"TextWidth",
	        		"Caption",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_WANTRETURN,
	        		UI_LEFT(1), UI_TOP(0), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::GetHwnd(),
	        		(HMENU)IDC_TEXT_WIDTH,
	        		GValue::GetHinstance(),
	        		0
	        		);
			
			ShowWindow(this->_hwnd, SW_SHOW);
		}
	}
	
	
	TextWidth::~TextWidth() {		
	}
	
	
	void TextWidth::OnLeftClick() {
    }	
	
	
	void TextWidth::OnRightClick() {
		MessageBox ( NULL,"test", "my_message", MB_OK );
	}
	
	
	LRESULT CALLBACK TextWidth::_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		
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
    
	
	TextWidth* TextWidth::GetInstance() {
        if(_instance == NULL){
            _instance = new TextWidth();             
        }
        return _instance;
	}	
	
	
	HWND TextWidth::GetHwnd() {
		return _hwnd;
	}
    
	
	//-----------------------------------------------
    TextWidth* TextWidth::_instance = NULL;    
	
}
