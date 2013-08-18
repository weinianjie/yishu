#ifndef _SCREEN_H
#define _SCREEN_H

#include <windows.h>
#include "GValue.h"

namespace ht {

	class Screen {
		
		public:
			static Screen* 				GetInstance();
			HWND 						GetHwnd();
			
			
		
		private:
			Screen();
			~Screen();
			
			static LRESULT CALLBACK 			_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			
			static void OnLeftClick();
			static void OnRightClick();			
			
			static Screen* 				_instance;
			HWND 						_hwnd;
	};
}

#endif

