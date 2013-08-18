#include "TextCountX.h"

namespace ht {
	
	TextCountX::TextCountX() {
               
		WNDCLASSEX wc;

		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpszClassName = "TextCountX";
		wc.lpfnWndProc	 = TextCountX::_WndProc;
		wc.hInstance	 = GValue::GetHinstance();
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "TextCountX Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		} else {				
			this->_hwnd = CreateWindow(
	        		"TextCountX",
	        		"Caption",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_WANTRETURN,
	        		UI_LEFT(0), UI_TOP(0), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::GetHwnd(),
	        		(HMENU)IDC_TEXT_COUNTX,
	        		GValue::GetHinstance(),
	        		0
	        		);
			
			ShowWindow(this->_hwnd, SW_SHOW);
		}
	}
	
	
	TextCountX::~TextCountX() {		
	}
	
	
	void TextCountX::OnLeftClick() {
    }	
	
	
	void TextCountX::OnRightClick() {
		MessageBox ( NULL,"test", "my_message", MB_OK );
	}
	
	
	LRESULT CALLBACK TextCountX::_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		
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
    
	
	TextCountX* TextCountX::GetInstance() {
        if(_instance == NULL){
            _instance = new TextCountX();             
        }
        return _instance;
	}	
	
	
	HWND TextCountX::GetHwnd() {
		return _hwnd;
	}
    
	
	//-----------------------------------------------
    TextCountX* TextCountX::_instance = NULL;    
	
}
