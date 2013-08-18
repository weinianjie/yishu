#include "TextArticle.h"
#include "Canvas.h"

namespace ht {
	
	TextArticle::TextArticle() {
               
		WNDCLASSEX wc;

		memset(&wc,0,sizeof(wc));
		wc.cbSize		 = sizeof(WNDCLASSEX);
		wc.lpszClassName = "TextArticle";
		wc.lpfnWndProc	 = TextArticle::_WndProc;
		wc.hInstance	 = GValue::GetHinstance();
		wc.hCursor		 = LoadCursor(NULL, IDC_ARROW);
		wc.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
		
		if(!RegisterClassEx(&wc)) {
			MessageBox(NULL, "TextArticle Registration Failed!","Error!",MB_ICONEXCLAMATION|MB_OK);
		} else {				
			this->_hwnd = CreateWindow(
	        		"TextArticle",
	        		"Caption",
	        		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_GROUP | WS_TABSTOP | ES_WANTRETURN,
	        		UI_LEFT(4), UI_TOP(0), 630, (UI_COM_HEIGHT * 2 + UI_COM_TOP),
	        		GValue::GetHwnd(),
	        		(HMENU)IDC_TEXT_ARTICLE,
	        		GValue::GetHinstance(),
	        		0
	        		);
			
			ShowWindow(this->_hwnd, SW_SHOW);
		}
	}
	
	
	TextArticle::~TextArticle() {		
	}
	
	
	void TextArticle::OnLeftClick() {
	    PAINTSTRUCT ps;
	    HDC hdc;
	    
		//hdc=BeginPaint(hwnd,&ps);
		//LineTo(hdc, 300, 800);
		//EndPaint(hwnd,&ps);

	    RECT rect2;
	
	    hdc = BeginPaint(Canvas::GetInstance()->GetHwnd(), &ps);
	
	    // TODO: �ڴ���������ͼ����...
	
		//wchar_t wch = '��';
		//wchar_t wStr[10] = TEXT("text"); 
		
	    //GetClientRect(hwnd,&rect2);
	    //DrawText(hdc,TEXT("Hello!"),-1,&rect2,DT_CENTER);
	    //DrawText(hdc, wch,-1,&rect2,DT_CENTER);
		
		
		HBRUSH bBrush;
		bBrush=CreateSolidBrush(RGB(100,100,100));
		SelectObject(hdc,bBrush);
		
		int xNum = 10;
		int yNum = 20;
		int width = 10;
		int height = 10;
		int limiter = 1;
		RECT rect;
		
		//�Ȼ������� 
		for(int i=0;i<xNum;i++) {
			for(int j=0;j<yNum;j++) {
                rect.left = i * width + limiter;
                rect.top = j * height + limiter;
                rect.right = rect.left + width - 1;//(i + 1) * width;
                rect.bottom = rect.top + height - 1;//(j + 1) * height;
				FillRect(hdc, &rect, bBrush);
				//Rectangle(hdc,i * width + limiter, j * height + limiter, (i + 1) * width, (j + 1) * height);
			}
		}	

		char sText[3000] = {"为什么放弃治疗"};
		DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, sText, -1, NULL, 0);//
		//DWORD dwNum = MultiByteToWideChar (CP_UTF8, 0, sText, -1, NULL, 0);
		
		wchar_t *pwText;
		pwText = new wchar_t[dwNum];
		
		MultiByteToWideChar (CP_ACP, 0, sText, -1, pwText, dwNum);
		//MultiByteToWideChar (CP_UTF8, 0, sText, -1, pwText, dwNum);
		
		//int total = sizeof(pwText)/2;
		int total = dwNum;
		for(int i=0;i<total;i++) {
			bBrush=CreateSolidBrush(hex2rgb((pwText[i] - 19968) * 801));
			
            rect.left = i % xNum * width + limiter;
            rect.top = i / xNum * height + limiter;
            rect.right = rect.left + width - 1;//(i + 1) * width;
            rect.bottom = rect.top + height - 1;//(j + 1) * height;
			FillRect(hdc, &rect, bBrush);
		}		
	
		DeleteObject(bBrush);
	    EndPaint(Canvas::GetInstance()->GetHwnd(), &ps);         
    }	
	
	
	void TextArticle::OnRightClick() {
		MessageBox ( NULL,"test", "my_message", MB_OK );
	}
	
	
	LRESULT CALLBACK TextArticle::_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
		
		static int   wmId, wmEvent ;
		switch(Message) {
			
//			case WM_PAINT: {
//
//				break;
//			}
		
			case WM_LBUTTONDOWN: {
				TextArticle::OnLeftClick();
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
    
	
	TextArticle* TextArticle::GetInstance() {
        if(_instance == NULL){
            _instance = new TextArticle();             
        }
        return _instance;
	}	
	
	
	HWND TextArticle::GetHwnd() {
		return _hwnd;
	}
    
	
	//-----------------------------------------------
    TextArticle* TextArticle::_instance = NULL;    
	
}
