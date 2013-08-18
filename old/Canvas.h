#ifndef _CANVAS_H
#define _CANVAS_H

#include <windows.h>
#include "GValue.h"

namespace ht {

	class Canvas {
		
		public:
			static Canvas* 				GetInstance();
			HWND 						GetHwnd();
			
			
		
		private:
			Canvas();
			~Canvas();
			
			static LRESULT CALLBACK 			_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			
			static void OnLeftClick();
			static void OnRightClick();			
			
			static Canvas* 				_instance;
			HWND 						_hwnd;
	};
}

#endif

