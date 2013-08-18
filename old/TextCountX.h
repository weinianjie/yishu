#ifndef _TEXTCOUNTX_H
#define _TEXTCOUNTX_H

#include <windows.h>
#include "GValue.h"

namespace ht {

	class TextCountX {
		
		public:
			static TextCountX* 				GetInstance();
			HWND 						GetHwnd();
			
			
		
		private:
			TextCountX();
			~TextCountX();
			
			static LRESULT CALLBACK 			_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			
			static void OnLeftClick();
			static void OnRightClick();			
			
			static TextCountX* 				_instance;
			HWND 						_hwnd;
	};
}

#endif

