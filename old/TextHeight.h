#ifndef _TEXTHEIGHT_H
#define _TEXTHEIGHT_H

#include <windows.h>
#include "GValue.h"

namespace ht {

	class TextHeight {
		
		public:
			static TextHeight* 				GetInstance();
			HWND 						GetHwnd();
			
			
		
		private:
			TextHeight();
			~TextHeight();
			
			static LRESULT CALLBACK 			_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			
			static void OnLeftClick();
			static void OnRightClick();			
			
			static TextHeight* 				_instance;
			HWND 						_hwnd;
	};
}

#endif

