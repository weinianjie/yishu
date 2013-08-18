#ifndef _CHECKBOXENCODE_H
#define _CHECKBOXENCODE_H

#include <windows.h>
#include "GValue.h"

namespace ht {

	class CheckboxEncode {
		
		public:
			static CheckboxEncode* 				GetInstance();
			HWND 						GetHwnd();
			
			
		
		private:
			CheckboxEncode();
			~CheckboxEncode();
			
			static LRESULT CALLBACK 			_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			
			static void OnLeftClick();
			static void OnRightClick();			
			
			static CheckboxEncode* 				_instance;
			HWND 						_hwnd;
	};
}

#endif

