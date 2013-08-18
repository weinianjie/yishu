#ifndef _BUTTON_H
#define _BUTTON_H

#include <windows.h>
#include "GValue.h"

namespace ht {

	class Button {
		
		public:
			static Button* 				GetInstance();
			HWND 						GetHwnd();
			
			
		
		private:
			Button();
			~Button();
			
			static LRESULT CALLBACK 			_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			
			static void OnLeftClick();
			static void OnRightClick();			
			
			static Button* 				_instance;
			HWND 						_hwnd;
	};
}

#endif

