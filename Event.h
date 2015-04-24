#include <windows.h>
#include "GValue.h"

#ifndef _EVENT_H
#define _EVENT_H

   
namespace ht {
	
	void DrawCanvas();
	
	void ResizeWindow();
	
	void TrySeveDeskBmp();
	
	void VscrollChange(WPARAM wParam, LPARAM lParam); 
	
	void HscrollChange(WPARAM wParam, LPARAM lParam); 
	
	void ResizeScreen(WPARAM wParam, LPARAM lParam);
	
}

#endif

