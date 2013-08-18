#ifndef _TEXTWIDTH_H
#define _TEXTWIDTH_H

#include <windows.h>
#include "GValue.h"

namespace ht {

	class TextWidth {
		
		public:
			static TextWidth* 				GetInstance();
			HWND 						GetHwnd();
			
			
		
		private:
			TextWidth();
			~TextWidth();
			
			static LRESULT CALLBACK 			_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			
			static void OnLeftClick();
			static void OnRightClick();			
			
			static TextWidth* 				_instance;
			HWND 						_hwnd;
	};
}

#endif

