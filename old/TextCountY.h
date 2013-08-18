#ifndef _TEXTCOUNTY_H
#define _TEXTCOUNTY_H

#include <windows.h>
#include "GValue.h"

namespace ht {

	class TextCountY {
		
		public:
			static TextCountY* 				GetInstance();
			HWND 						GetHwnd();
			
			
		
		private:
			TextCountY();
			~TextCountY();
			
			static LRESULT CALLBACK 			_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			
			static void OnLeftClick();
			static void OnRightClick();			
			
			static TextCountY* 				_instance;
			HWND 						_hwnd;
	};
}

#endif

