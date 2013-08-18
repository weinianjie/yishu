#include "Button.h"
#include "Canvas.h"

namespace ht {
	
	Button::Button() {
               
		WNDCLASSEX wc;

		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpszClassName = "Button";
		wc.lpfnWndProc	 = Button::_WndProc;
		wc.hInstance	 = GValue::GetHinstance();
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "Button Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		} else {				
			this->_hwnd = CreateWindow(
	        		"Button",
	        		"Caption",
	        		WS_VISIBLE|WS_CHILD,
	        		UI_LEFT(3), UI_TOP(0), UI_COM_WIDTH, UI_COM_HEIGHT,
	        		GValue::GetHwnd(),
	        		(HMENU)IDC_BUTTON,
	        		GValue::GetHinstance(),
	        		0
	        		);
			
			ShowWindow(this->_hwnd, SW_SHOW);
		}
	}
	
	
	Button::~Button() {		
	}
	
	
	void Button::OnLeftClick() {
		TrySeveDeskBmp(Canvas::GetInstance()->GetHwnd());
    }	
	
	
	void Button::OnRightClick() {
		MessageBox ( NULL,"test", "my_message", MB_OK );
	}
	
	
	LRESULT CALLBACK Button::_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		
		static int   wmId, wmEvent ;
		switch(Message) {
			
			case WM_LBUTTONDOWN: {
				Button::OnLeftClick();
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
    
	
	Button* Button::GetInstance() {
        if(_instance == NULL){
            _instance = new Button();             
        }
        return _instance;
	}	
	
	
	HWND Button::GetHwnd() {
		return _hwnd;
	}
    
	
	//-----------------------------------------------
    Button* Button::_instance = NULL;    
	
}
