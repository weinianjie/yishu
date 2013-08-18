#include "CheckboxEncode.h"

namespace ht {
	
	CheckboxEncode::CheckboxEncode() {
               
		WNDCLASSEX wc;

		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpszClassName = "CheckboxEncode";
		wc.lpfnWndProc	 = CheckboxEncode::_WndProc;
		wc.hInstance	 = GValue::GetHinstance();
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "CheckboxEncode Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		} else {				
			this->_hwnd = CreateWindow(
	        		"CheckboxEncode",
	        		"Caption",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_WANTRETURN,
	        		UI_LEFT(2), UI_TOP(1), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::GetHwnd(),
	        		(HMENU)IDC_CHECKBOX_ENCODE,
	        		GValue::GetHinstance(),
	        		0
	        		);
			
			ShowWindow(this->_hwnd, SW_SHOW);
		}
	}
	
	
	CheckboxEncode::~CheckboxEncode() {		
	}
	
	
	void CheckboxEncode::OnLeftClick() {
    }	
	
	
	void CheckboxEncode::OnRightClick() {
		MessageBox ( NULL,"test", "my_message", MB_OK );
	}
	
	
	LRESULT CALLBACK CheckboxEncode::_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		
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
    
	
	CheckboxEncode* CheckboxEncode::GetInstance() {
        if(_instance == NULL){
            _instance = new CheckboxEncode();             
        }
        return _instance;
	}	
	
	
	HWND CheckboxEncode::GetHwnd() {
		return _hwnd;
	}
    
	
	//-----------------------------------------------
    CheckboxEncode* CheckboxEncode::_instance = NULL;    
	
}
