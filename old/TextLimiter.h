#ifndef _TEXTLIMITER_H
#define _TEXTLIMITER_H

#include <windows.h>
#include "GValue.h"

namespace ht {

	class TextLimiter {
		
		public:
			static TextLimiter* 				GetInstance();
			HWND 						GetHwnd();
			
			
		
		private:
			TextLimiter();
			~TextLimiter();
			
			static LRESULT CALLBACK 			_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			
			static void OnLeftClick();
			static void OnRightClick();			
			
			static TextLimiter* 				_instance;
			HWND 						_hwnd;
	};
}

#endif

