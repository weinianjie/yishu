#ifndef _ARTICLE_H
#define _ARTICLE_H

#include <windows.h>
#include "GValue.h"

namespace ht {

	class TextArticle {
		
		public:
			static TextArticle* 				GetInstance();
			HWND 						GetHwnd();
			
			
		
		private:
			TextArticle();
			~TextArticle();
			
			static LRESULT CALLBACK 			_WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
			
			static void OnLeftClick();
			static void OnRightClick();			
			
			static TextArticle* 				_instance;
			HWND 						_hwnd;
	};
}

#endif

