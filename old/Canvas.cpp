#include "Canvas.h"
#include "Screen.h"

namespace ht {
	
	Canvas::Canvas() {
               
		WNDCLASSEX wc;

		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpszClassName = "Canvas";
		wc.lpfnWndProc	 = Canvas::_WndProc;
		wc.hInstance	 = GValue::GetHinstance();
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "Canvas Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		} else {				
			this->_hwnd = CreateWindow(
	        		"Canvas",
	        		"Caption",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_WANTRETURN,
	        		10, 10, 760, 460,
	        		Screen::GetInstance()->GetHwnd(),
	        		(HMENU)IDC_CANVAS,
	        		GValue::GetHinstance(),
	        		0
	        		);
			
			ShowWindow(this->_hwnd, SW_SHOW);
		}
	}
	
	
	Canvas::~Canvas() {		
	}
	
	
	void Canvas::OnLeftClick() {
    }	
	
	
	void Canvas::OnRightClick() {
		MessageBox ( NULL,"test", "my_message", MB_OK );
	}
	
	
	LRESULT CALLBACK Canvas::_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		
		static int   wmId, wmEvent ;
		switch(Message) {
			
			case WM_PAINT: {

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
    
	
	Canvas* Canvas::GetInstance() {
        if(_instance == NULL){
            _instance = new Canvas();             
        }
        return _instance;
	}	
	
	
	HWND Canvas::GetHwnd() {
		return _hwnd;
	}
    
	
	//-----------------------------------------------
    Canvas* Canvas::_instance = NULL;    
	
}
