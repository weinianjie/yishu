#include "windows.h"
#include "Event.h"

using namespace ht;

char filename[] = "log.txt";

namespace ht {

	
	void DrawCanvas() {
	    PAINTSTRUCT ps;
	    HDC hdc;
	    
		//hdc=BeginPaint(hwnd,&ps);
		//LineTo(hdc, 300, 800);
		//EndPaint(hwnd,&ps);

	    
	
	    hdc = BeginPaint(GValue::G_hwnd_canvas, &ps); //ÎªÁË·ÀÖ¹ËÀÑ­»·£¬ÔÚWM_PAINTÀïÃæ±ØÐëÒªbegin 
		
		//MessageBox(NULL, "1","Error!",MB_ICONEXCLAMATION|MB_OK);
		
//		int xNum = GetDlgItemInt(GValue::G_hwnd_countX, IDC_TEXT_COUNTX, NULL, false);
//		int yNum = GetDlgItemInt(GValue::G_hwnd_countY, IDC_TEXT_COUNTY, NULL, false);
//		int width = GetDlgItemInt(GValue::G_hwnd_width, IDC_TEXT_WIDTH, NULL, false);
//		int height = GetDlgItemInt(GValue::G_hwnd_height, IDC_TEXT_HEIGHT, NULL, false);
//		int limiter = GetDlgItemInt(GValue::G_hwnd_limiter, IDC_TEXT_LIMITER, NULL, false);
		
//		int xNum = 100;//GetDlgItemInt(GValue::G_hwnd_countX, IDC_TEXT_COUNTX, NULL, false);
//		int yNum = 80;//GetDlgItemInt(GValue::G_hwnd_countY, IDC_TEXT_COUNTY, NULL, false);
//		int width = 10;//GetDlgItemInt(GValue::G_hwnd_width, IDC_TEXT_WIDTH, NULL, false);
//		int height = 10;//GetDlgItemInt(GValue::G_hwnd_height, IDC_TEXT_HEIGHT, NULL, false);
//		int limiter = 1;//GetDlgItemInt(GValue::G_hwnd_limiter, IDC_TEXT_LIMITER, NULL, false);

		//TODO ·ÀÖ¹¹ýÂý£¬¿í×î´ó2000£¬¸ß×î´ó1000 
		char _xNum[5]; //×îºó1Î»Ç¿ÖÆÓÃÀ´±£Áô½áÊø·û£¬Ç§Ëã4Î»£¬×î´óÊä³ö9999 
		GetWindowText(GValue::G_hwnd_countX, _xNum, 5);
		int xNum = atoi(_xNum);
		
		char _yNum[5];
		GetWindowText(GValue::G_hwnd_countY, _yNum,5);
		int yNum = atoi(_yNum);
		
		char _width[5];
		GetWindowText(GValue::G_hwnd_width, _width, 5);
		int width = atoi(_width);
		
		char _height[5];
		GetWindowText(GValue::G_hwnd_height, _height, 5);
		int height = atoi(_height);
		
		char _limiter[5];
		GetWindowText(GValue::G_hwnd_limiter, _limiter, 5);
		int limiter = atoi(_limiter);
		
//		bool isCheck = (IsDlgButtonChecked(GValue::G_hwnd_encoder, IDC_CHECKBOX_ENCODE) == BST_CHECKED);//SengMesage·½·¨ÓÉÓÚWM_COMMANDµÄÔ­Òò¿ÉÄÜ·¢ËÍÊ§°Ü 
		bool isCheck = (SendDlgItemMessage(GValue::G_hwnd, IDC_CHECKBOX_ENCODE, BM_GETCHECK, 0, 0) == BST_CHECKED);
		
		if(xNum == 0 || yNum == 0 || width == 0 || height == 0) {
			EndPaint(GValue::G_hwnd_canvas, &ps);
			return;
		}
		
		if(xNum > 2000) {
			MessageBox(NULL, TEXT("ºáÏò×î¶à2000µã£¡") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			//SetWindowText(GValue::G_hwnd_countX, "2000");
			EndPaint(GValue::G_hwnd_canvas, &ps);
			return; 
		} 
		
		if(yNum > 1000) {
			MessageBox(NULL, TEXT("×ÝÏò×î¶à1000µã£¡") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			//SetDlgItemInt(GValue::G_hwnd_countX, IDC_TEXT_COUNTY, 1000, false);
			EndPaint(GValue::G_hwnd_canvas, &ps);
			return; 
		} 
		
		//µ÷Õû»­²¼´óÐ¡ 
		GValue::canvas_width = (width + limiter) * xNum - limiter;
		if(!isCheck) {
			GValue::canvas_height = (height + limiter) * yNum - limiter;
		} else {
			GValue::canvas_height = (height + limiter) * yNum * 2 - limiter;
		}
		
		
		MoveWindow(GValue::G_hwnd_canvas, 0 - GValue::position_width, 0 - GValue::position_height, GValue::canvas_width, GValue::canvas_height, true);
		
	    //GetClientRect(hwnd,&rect2);
	    //DrawText(hdc,TEXT("Hello!"),-1,&rect2,DT_CENTER);
	    //DrawText(hdc, wch,-1,&rect2,DT_CENTER);
		
		RECT rect;//²»ÐèÒª³õÊ¼»¯£¬ÊÖ¹¤Ìî³ä 
		HBRUSH bBrush;	
		//bBrush=CreateSolidBrush(RGB(250,250,250));
		bBrush = (HBRUSH)GetStockObject(DC_BRUSH);//Ä¬ÈÏÊÇ°×É«£¬Ö»ÓÐÕâÑùÄÃµ½µÄ»­Ë¢²ÅÄÜµ÷ÓÃSetDCBrushColor¸ü¸ÄÑÕÉ« 
		SelectObject(hdc,bBrush);
		
		SetBkMode(hdc, TRANSPARENT);
		SetTextColor(hdc, RGB(0,0,222));

		for(long i=0;i<xNum;i++) {
			for(long j=0;j<yNum;j++) {
                rect.left = i * (width + limiter);
                rect.top = j * (height + limiter);
                if(isCheck) {
                	rect.top = rect.top * 2;
                } 
                rect.right = rect.left + width;//(i + 1) * width;
                rect.bottom = rect.top + height;//(j + 1) * height;
				FillRect(hdc, &rect, bBrush);
				//Rectangle(hdc,i * width + limiter, j * height + limiter, (i + 1) * width, (j + 1) * height);
			}
		}	

/*====================¾ÍµÃ»ñÈ¡ºÍ×ª»»º¯Êýbegin========================== 
		char sText[2000000];// = {"ÌìÌìÏòÉÏ"}; 
		GetWindowText(GValue::G_hwnd_article, sText,2000000);
		
		DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, sText, -1, NULL, 0);//
		//DWORD dwNum = MultiByteToWideChar (CP_UTF8, 0, sText, -1, NULL, 0);

		wchar_t *pwText;
		pwText = new wchar_t[dwNum];
		
		MultiByteToWideChar (CP_ACP, 0, sText, -1, pwText, dwNum);
		//MultiByteToWideChar (CP_UTF8, 0, sText, -1, pwText, dwNum);
		
		//×îºóÒ»¸öÊÇ½áÊø·û²»¿ÉÓÃ£¬²»ÄÜ³¬¹ý¾ØÕó´óÐ¡ 
		long total = min(--dwNum, xNum * yNum);
====================¾ÍµÃ»ñÈ¡ºÍ×ª»»º¯Êýend==========================*/
		 
		wchar_t wText[1000000];//wchar_tÊý×é×î´ó¾ÍÊÇ1000000ÁË£¬ÔÙ´óÔËÐÐÖ±½Ó±¨´í 
		//wchar_t wText[5] = {'1','2','3','4','5'}; 
		long total = GetWindowTextW(GValue::G_hwnd_article, wText,1000000);//³É¹¦·µ»Ø×Ö·û´®¸öÊý£¨²»º¬×îºóµÄnull£©£¬Ê§°Ü»òÕßÎª¿Õ·µ»Ø0 		
		total = min(total, xNum * yNum); 

		wchar_t *pwText2;
		pwText2 = new wchar_t[1];
		for(long i=0;i<total;i++) {
//			DeleteObject(bBrush);
//			bBrush=CreateSolidBrush(hex2rgb((/*pwText[i]*/wText[i] - 19968) * 801));
			SetDCBrushColor(hdc, hex2rgb((/*pwText[i]*/wText[i] - 19968) * 801));
			
            rect.left = i % xNum * (width + limiter);
            rect.top = i / xNum * (height + limiter);
            if(isCheck) {
            	rect.top = rect.top * 2;
            }
            rect.right = rect.left + width;//(i + 1) * width;
            rect.bottom = rect.top + height;//(j + 1) * height;
			FillRect(hdc, &rect, bBrush);
			
			if(isCheck) {//Êä³öÎÄ×Ö
				pwText2[0] = wText[i]/*pwText[i]*/;
				TextOutW(hdc, rect.left, rect.bottom, pwText2, 1);
			}
		}
	
		delete []pwText2;//newµÄ¶ÔÏóÒªÉ¾³ý£¬Èç¹ûÊÇÊý×éÓÃÕâÑù·½Ê½É¾³ý 
		DeleteObject(bBrush);
	    EndPaint(GValue::G_hwnd_canvas, &ps);   
	     
	}
	
	
	void TrySeveDeskBmp()
	{
		HDC HDeskDC= GetDC(GValue::G_hwnd_canvas);
//		HDC HDeskDC= GetDC(GetDesktopWindow());//ï¿½ï¿½ï¿½æ´°ï¿½Ú»ï¿½Í¼ï¿½ï¿½ï¿½
		HDC MemDC=CreateCompatibleDC(HDeskDC);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½è±¸

//		GetClientRect(GetDesktopWindow(),&rc);//ï¿½ï¿½ï¿½æ´°ï¿½Ú´ï¿½Ð¡
		//int width=rc.right-rc.left;
		//int height=rc.bottom-rc.top;
//================================begin=============================================		
		char _xNum[5]; //×îºó1Î»Ç¿ÖÆÓÃÀ´±£Áô½áÊø·û£¬Ç§Ëã4Î»£¬×î´óÊä³ö9999 
		GetWindowText(GValue::G_hwnd_countX, _xNum, 5);
		int xNum = atoi(_xNum);
		
		char _yNum[5];
		GetWindowText(GValue::G_hwnd_countY, _yNum,5);
		int yNum = atoi(_yNum);
		
		char _width[5];
		GetWindowText(GValue::G_hwnd_width, _width, 5);
		int width = atoi(_width);
		
		char _height[5];
		GetWindowText(GValue::G_hwnd_height, _height, 5);
		int height = atoi(_height);
		
		bool isCheck = (SendDlgItemMessage(GValue::G_hwnd, IDC_CHECKBOX_ENCODE, BM_GETCHECK, 0, 0) == BST_CHECKED);
		
		if(xNum == 0 || yNum == 0 || width == 0 || height == 0) {
			DeleteDC(MemDC);
			return;
		}
		
		if(xNum > 2000) {
			MessageBox(NULL, TEXT("ºáÏò×î¶à2000µã£¡") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			DeleteDC(MemDC);
			return; 
		} 
		
		if(yNum > 1000) {
			MessageBox(NULL, TEXT("×ÝÏò×î¶à1000µã£¡") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			DeleteDC(MemDC);
			return; 
		}
		
		char _limiter[5];
		GetWindowText(GValue::G_hwnd_limiter, _limiter, 5);
		int limiter = atoi(_limiter);		
		
		if(GValue::canvas_width > 6000 || GValue::canvas_height > 3000) {//ÔÝÊ±ÐÔ±£»¤ 
			MessageBox(NULL, TEXT("Ì«´óÁË²»¸øÄã±£´æ£¡") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			DeleteDC(MemDC);
			return;
		}
		
//================================end======================================		
		
		HBITMAP hBmp=CreateCompatibleBitmap(HDeskDC,GValue::canvas_width,GValue::canvas_height);//ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Îªï¿½ï¿½ï¿½ï¿½ï¿½Ä´ï¿½ï¿½ï¿½Î»Í¼
		SelectObject(MemDC,hBmp);//°ó¶¨ºó£¬¿ÉÒÔ×ÔÓÉ×÷Í¼ÁË 
		//BitBlt(MemDC,0,0,width,height,HDeskDC,0,0,SRCCOPY);//ÏñËØ×ªÒÆ 
		
		
		
//=================================begin======================================		
		
		
		RECT rect;
		HBRUSH bBrush;
		//bBrush=CreateSolidBrush(RGB(250,250,250));
		bBrush = (HBRUSH)GetStockObject(DC_BRUSH);//Ä¬ÈÏÊÇ°×É«£¬Ö»ÓÐÕâÑùÄÃµ½µÄ»­Ë¢²ÅÄÜµ÷ÓÃSetDCBrushColor¸ü¸ÄÑÕÉ«
		SelectObject(MemDC,bBrush);
		SetBkMode(MemDC, TRANSPARENT);
		SetTextColor(MemDC, RGB(0,0,222));
		
		//Ìî³ä±³¾° 
		rect.top = 0;
		rect.left = 0;
		rect.bottom = GValue::canvas_height;
		rect.right = GValue::canvas_width; 
		SetDCBrushColor(MemDC, RGB(200,200,200));
		FillRect(MemDC, &rect, bBrush);
		
		SetDCBrushColor(MemDC, RGB(255,255,255));

		for(long i=0;i<xNum;i++) {
			for(long j=0;j<yNum;j++) {
                rect.left = i * (width + limiter);
                rect.top = j * (height + limiter);
                if(isCheck) {
                	rect.top = rect.top * 2;
                } 
                rect.right = rect.left + width;//(i + 1) * width;
                rect.bottom = rect.top + height;//(j + 1) * height;
				FillRect(MemDC, &rect, bBrush);
				//Rectangle(hdc,i * width + limiter, j * height + limiter, (i + 1) * width, (j + 1) * height);
			}
		}	
		
		wchar_t wText[1000000];//wchar_tÊý×é×î´ó¾ÍÊÇ1000000ÁË£¬ÔÙ´óÔËÐÐÖ±½Ó±¨´í 
		long total = GetWindowTextW(GValue::G_hwnd_article, wText,1000000);//³É¹¦·µ»Ø×Ö·û´®¸öÊý£¨²»º¬×îºóµÄnull£©£¬Ê§°Ü»òÕßÎª¿Õ·µ»Ø0 		
		total = min(total, xNum * yNum); 

		wchar_t *pwText2;
		pwText2 = new wchar_t[1];
		for(long i=0;i<total;i++) {
			//bBrush=CreateSolidBrush(hex2rgb((wText[i] - 19968) * 801));
			SetDCBrushColor(MemDC, hex2rgb((/*pwText[i]*/wText[i] - 19968) * 801));
			
            rect.left = i % xNum * (width + limiter);
            rect.top = i / xNum * (height + limiter);
            if(isCheck) {
            	rect.top = rect.top * 2;
            }
            rect.right = rect.left + width;//(i + 1) * width;
            rect.bottom = rect.top + height;//(j + 1) * height;
			FillRect(MemDC, &rect, bBrush);
			
			if(isCheck) {//Êä³öÎÄ×Ö
				pwText2[0] = wText[i];
				TextOutW(MemDC, rect.left, rect.bottom, pwText2, 1);
			}
		}
		
		delete []pwText2;
		DeleteObject(bBrush);
		
		
//==============================end=====================================================		
		
		
		
		
		BITMAP BmpInfo;
		GetObject(hBmp,sizeof(BITMAP),&BmpInfo);//ï¿½ï¿½È¡Î»Í¼ï¿½ï¿½Ï¢
		int datasize=BmpInfo.bmWidthBytes*BmpInfo.bmHeight;
		char*data=(char*)malloc(datasize);
		if (data==NULL)
		{
			printf("malloc err!\n");
			return;
		}

		BITMAPINFO binfo={0};//bmpï¿½ï¿½Ï¢

		binfo.bmiHeader.biBitCount=BmpInfo.bmBitsPixel;//ï¿½ï¿½É«Î»ï¿½ï¿½
		binfo.bmiHeader.biClrImportant=0;
		binfo.bmiHeader.biCompression=0;
		binfo.bmiHeader.biHeight=GValue::canvas_height;
		binfo.bmiHeader.biPlanes=BmpInfo.bmPlanes;//ï¿½ï¿½ï¿½ï¿½?ï¿½ï¿½ï¿½ï¿½Îª1
		binfo.bmiHeader.biSize=sizeof(BITMAPINFO);
		binfo.bmiHeader.biSizeImage=datasize;
		binfo.bmiHeader.biWidth=GValue::canvas_width;
		binfo.bmiHeader.biXPelsPerMeter=0;
		binfo.bmiHeader.biYPelsPerMeter=0;

		GetDIBits(MemDC,hBmp,0,BmpInfo.bmHeight,data,&binfo,DIB_RGB_COLORS);//RGBï¿½ï¿½Ý»ï¿½È¡
		//ï¿½ï¿½ï¿½ï¿½Îªï¿½è±¸ï¿½ï¿½ï¿½Î»Í¼ï¿½ï¿½ï¿½Ê¼É¨ï¿½ï¿½ï¿½Ð£ï¿½ï¿½ï¿½ï¿½ï¿½É¨ï¿½ï¿½ï¿½Ð£ï¿½Òªï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½Î»Í¼ï¿½ï¿½Ï¢ï¿½ï¿½ï¿½ï¿½É«ï¿½ï¿½Ê½
		//(ï¿½ï¿½Ç°ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½É«ï¿½ï¿½ï¿½ï¿½ï¿½é±£ï¿½ï¿½,ï¿½ï¿½ï¿½Ú¶ï¿½24ï¿½ï¿½32ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½ï¿½)
//		ChangColor(data,datasize,BmpInfo.bmBitsPixel);//ï¿½ï¿½ÉºÚ°ï¿½
		BITMAPFILEHEADER bfh={0};//bmpï¿½Ä¼ï¿½Í·
		bfh.bfType=MAKEWORD('B','M');
		bfh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFO);//ï¿½ï¿½ï¿½Æ«ï¿½ï¿½
		bfh.bfSize=bfh.bfOffBits+datasize;//ï¿½Ä¼ï¿½ï¿½Ü´ï¿½Ð¡
		char*filename=(char*)malloc(256);
		if (filename==NULL)
		{
			printf("malloc err!\n");
			return;
		}
		sprintf(filename,"%d.bmp",time(NULL));
		FILE*fp=fopen(filename,"wb");
		if (fp==NULL)	
			return;
		fwrite(&bfh,1,sizeof(BITMAPFILEHEADER),fp);
		fwrite(&binfo,1,sizeof(BITMAPINFO),fp);
		fwrite(data,1,BmpInfo.bmWidthBytes*BmpInfo.bmHeight,fp);
		fclose(fp);
		free(filename);
		free(data);
		DeleteObject(hBmp);//É¾ï¿½ï¿½ï¿½ï¿½è±¸
		DeleteDC(MemDC);
		
//		if(RiWnd!=NULL)
//		ShowWindow(RiWnd,SW_SHOW);
		MessageBox(NULL, "±£´æ³É¹¦","",MB_ICONEXCLAMATION|MB_OK);
	}
	
	
	void ResizeWindow() {
		RECT rc;
		GetClientRect(GValue::G_hwnd,&rc); 
		
		int width=rc.right-rc.left;
		int height=rc.bottom-rc.top;
		
		MoveWindow(GValue::G_hwnd_article, UI_LEFT(2), UI_TOP(0), (width - UI_LEFT(2) - UI_COM_LEFT), (UI_COM_HEIGHT * 5 + UI_COM_TOP), true); 
		MoveWindow(GValue::G_hwnd_screen, 0, UI_TOP(4), width, (height - UI_TOP(4)), true);
	}
	
	//ÊúÖ±·½Ïò¹ö¶¯ÌõÊÂ¼þ£¬ÓëÉÏÃæÏàËÆ²»½âÊÍÁË
	void VscrollChange(WPARAM wParam, LPARAM lParam) {
		SCROLLINFO  si;
		si.cbSize=sizeof(SCROLLINFO);
		si.fMask=SIF_ALL;
		GetScrollInfo(GValue::G_hwnd_screen, SB_VERT, &si);
		
		switch(LOWORD(wParam)){
			case SB_THUMBTRACK: {
				
				GValue::position_height = si.nTrackPos * (GValue::canvas_height - GValue::screen_height) / 100;
				MoveWindow(GValue::G_hwnd_canvas, 0 - GValue::position_width, 0 - GValue::position_height, GValue::canvas_width, GValue::canvas_height, true);
				
				si.nPos=si.nTrackPos;
				break;
			}
			
			default: {
				break;
			}
		}
		
		si.fMask=SIF_POS;
		SetScrollInfo(GValue::G_hwnd_screen, SB_VERT, &si, true);			
	}
	
	//Ë®Æ½·½Ïò¹ö¶¯ÌõÊÂ¼þ
	void HscrollChange(WPARAM wParam, LPARAM lParam) {
			
		SCROLLINFO  si;
		si.cbSize=sizeof(SCROLLINFO);
		si.fMask=SIF_ALL;
		GetScrollInfo(GValue::G_hwnd_screen,SB_HORZ,&si);//ÏÈÄÃ¹ö¶¯ÌõÐÅÏ¢
		
		switch(LOWORD(wParam)){//ÕâÀïÖ»´¦Àí°´ÏÂ¹ö¶¯ÌõÍÏ¶¯µÄÊÂ¼þ£¬ÆäËû¹ö¶¯ÌõÊÂ¼þ×Ô¼ºÊµÏÖ°É
		
			//·ÖÎö¿ÉÖª°´×¡¹ö¶¯ÌõÍÏ¶¯¹ý³ÌÖÐ£¬ÐèÒªÐÞ¸Äµ±Ç°Î»ÖÃ¡¢È»ºó»ùÓÚµ±Ç°Î»ÖÃÒÆ¶¯»­²¼£¬×îºóÐÞ¸Ä¹ö¶¯ÌõÎ»ÖÃ£¨Äã²»ÐÞ¸ÄµÄ»°ÊÓ¾õÐ§¹ûÉÏ»áµ¯»ØÈ¥µÄ£©¡¢
			case SB_THUMBTRACK: {										
				GValue::position_width = si.nTrackPos * (GValue::canvas_width - GValue::screen_width) / 100;//¸ü¸Äµ±Ç°Î»ÖÃ		
				MoveWindow(GValue::G_hwnd_canvas, 0 - GValue::position_width, 0 - GValue::position_height, GValue::canvas_width, GValue::canvas_height, true);//ÒÆ¶¯»­²¼
				
				si.nPos=si.nTrackPos;
				break;
			}
			
			//TODO ¹ö¶¯ÌõµÄÆäËûÊÂ¼þ				
			
			default: {
				break;
			}
		}
		
		//»ØÐ´¹ö¶¯Ìõ¹ö¶¯¿éµÄÎ»ÖÃ£¬Ê±ÊÓ¾õÉÏÕý³£
		si.fMask=SIF_POS;
		SetScrollInfo(GValue::G_hwnd_screen, SB_HORZ, &si, true);	
	}
	
	//´°¿Ú´óÐ¡¸Ä±äÊ±£¬¸üÐÂÈ«¾Ö±äÁ¿ÖÐµÄÆÁÄ»´óÐ¡£¬¸üÐÂ¹ö¶¯ÌõÉÏ¹ö¶¯¿éµÄÎ»ÖÃ
	void ResizeScreen(WPARAM wParam, LPARAM lParam) {
		//¸üÐÂÆÁÄ»´óÐ¡begin-----------------------------
		GValue::screen_width = LOWORD (lParam);
		GValue::screen_height = HIWORD (lParam);
		//¸üÐÂÆÁÄ»´óÐ¡end-----------------------------
		
		//¸üÐÂ¹ö¶¯ÌõÉÏ¹ö¶¯¿éµÄÎ»ÖÃbegin----------------------
		if(GValue::canvas_width - GValue::screen_width == 0) {
			GValue::hb_pos = 0;
		} else {
			GValue::hb_pos = GValue::position_width * 100 / (GValue::canvas_width - GValue::screen_width);
		}
		
		if(GValue::canvas_height - GValue::screen_height == 0) {
			GValue::vb_pos = 0;
		} else {
			GValue::vb_pos = GValue::position_height * 100 / (GValue::canvas_height - GValue::screen_height);
		}
		
		SCROLLINFO  si;
		si.cbSize=sizeof(SCROLLINFO);			
		si.fMask=SIF_POS;			
					
		si.nPos = GValue::vb_pos;
		SetScrollInfo(GValue::G_hwnd_screen,SB_VERT,&si,true);
					
		si.nPos = GValue::hb_pos;
		SetScrollInfo(GValue::G_hwnd_screen,SB_HORZ,&si,true);			
		//¸üÐÂ¹ö¶¯ÌõÉÏ¹ö¶¯¿éµÄÎ»ÖÃend----------------------
		
		
		//ÆäÊµ»¹Ó¦¸Ã¸üÐÂ¹ö¶¯ÌõÉÏ¹ö¶¯¿éµÄ³¤¶È£¬ÕâÀïÏÈºöÂÔ°É
		//int hb_length = GValue::s_width * (GValue::s_width - 40) / GValue::c_width;
		//int vb_length = GValue::s_height * (GValue::s_height - 40) / GValue::c_height;
		
		//¸üÐÂ»­²¼
		UpdateWindow(GValue::G_hwnd_canvas); 
	}
}
