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

	    
	
	    hdc = BeginPaint(GValue::G_hwnd_canvas, &ps); //为了防止死循环，在WM_PAINT里面必须要begin 
		
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

		//TODO 防止过慢，宽最大2000，高最大1000 
		char _xNum[5]; //最后1位强制用来保留结束符，千算4位，最大输出9999 
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
		
//		bool isCheck = (IsDlgButtonChecked(GValue::G_hwnd_encoder, IDC_CHECKBOX_ENCODE) == BST_CHECKED);//SengMesage方法由于WM_COMMAND的原因可能发送失败 
		bool isCheck = (SendDlgItemMessage(GValue::G_hwnd, IDC_CHECKBOX_ENCODE, BM_GETCHECK, 0, 0) == BST_CHECKED);
		
		if(xNum == 0 || yNum == 0 || width == 0 || height == 0) {
			EndPaint(GValue::G_hwnd_canvas, &ps);
			return;
		}
		
		if(xNum > 2000) {
			MessageBox(NULL, TEXT("横向最多2000点！") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			//SetWindowText(GValue::G_hwnd_countX, "2000");
			EndPaint(GValue::G_hwnd_canvas, &ps);
			return; 
		} 
		
		if(yNum > 1000) {
			MessageBox(NULL, TEXT("纵向最多1000点！") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			//SetDlgItemInt(GValue::G_hwnd_countX, IDC_TEXT_COUNTY, 1000, false);
			EndPaint(GValue::G_hwnd_canvas, &ps);
			return; 
		} 
		
		//调整画布大小 
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
		
		RECT rect;//不需要初始化，手工填充 
		HBRUSH bBrush;	
		//bBrush=CreateSolidBrush(RGB(250,250,250));
		bBrush = (HBRUSH)GetStockObject(DC_BRUSH);//默认是白色，只有这样拿到的画刷才能调用SetDCBrushColor更改颜色 
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

/*====================就得获取和转换函数begin========================== 
		char sText[2000000];// = {"天天向上"}; 
		GetWindowText(GValue::G_hwnd_article, sText,2000000);
		
		DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, sText, -1, NULL, 0);//
		//DWORD dwNum = MultiByteToWideChar (CP_UTF8, 0, sText, -1, NULL, 0);

		wchar_t *pwText;
		pwText = new wchar_t[dwNum];
		
		MultiByteToWideChar (CP_ACP, 0, sText, -1, pwText, dwNum);
		//MultiByteToWideChar (CP_UTF8, 0, sText, -1, pwText, dwNum);
		
		//最后一个是结束符不可用，不能超过矩阵大小 
		long total = min(--dwNum, xNum * yNum);
====================就得获取和转换函数end==========================*/
		 
		wchar_t wText[1000000];//wchar_t数组最大就是1000000了，再大运行直接报错 
		//wchar_t wText[5] = {'1','2','3','4','5'}; 
		long total = GetWindowTextW(GValue::G_hwnd_article, wText,1000000);//成功返回字符串个数（不含最后的null），失败或者为空返回0 		
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
			
			if(isCheck) {//输出文字
				pwText2[0] = wText[i]/*pwText[i]*/;
				TextOutW(hdc, rect.left, rect.bottom, pwText2, 1);
			}
		}
	
		delete []pwText2;//new的对象要删除，如果是数组用这样方式删除 
		DeleteObject(bBrush);
	    EndPaint(GValue::G_hwnd_canvas, &ps);   
	     
	}
	
	
	void TrySeveDeskBmp()
	{
		HDC HDeskDC= GetDC(GValue::G_hwnd_canvas);
//		HDC HDeskDC= GetDC(GetDesktopWindow());//锟斤拷锟芥窗锟节伙拷图锟斤拷锟�
		HDC MemDC=CreateCompatibleDC(HDeskDC);//锟斤拷锟斤拷锟斤拷锟借备

//		GetClientRect(GetDesktopWindow(),&rc);//锟斤拷锟芥窗锟节达拷小
		//int width=rc.right-rc.left;
		//int height=rc.bottom-rc.top;
//================================begin=============================================		
		char _xNum[5]; //最后1位强制用来保留结束符，千算4位，最大输出9999 
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
			MessageBox(NULL, TEXT("横向最多2000点！") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			DeleteDC(MemDC);
			return; 
		} 
		
		if(yNum > 1000) {
			MessageBox(NULL, TEXT("纵向最多1000点！") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			DeleteDC(MemDC);
			return; 
		}
		
		char _limiter[5];
		GetWindowText(GValue::G_hwnd_limiter, _limiter, 5);
		int limiter = atoi(_limiter);		
		
		if(GValue::canvas_width > 6000 || GValue::canvas_height > 3000) {//暂时性保护 
			MessageBox(NULL, TEXT("太大了不给你保存！") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			DeleteDC(MemDC);
			return;
		}
		
//================================end======================================		
		
		HBITMAP hBmp=CreateCompatibleBitmap(HDeskDC,GValue::canvas_width,GValue::canvas_height);//锟斤拷锟斤拷锟斤拷为锟斤拷锟斤拷锟侥达拷锟斤拷位图
		SelectObject(MemDC,hBmp);//绑定后，可以自由作图了 
		//BitBlt(MemDC,0,0,width,height,HDeskDC,0,0,SRCCOPY);//像素转移 
		
		
		
//=================================begin======================================		
		
		
		RECT rect;
		HBRUSH bBrush;
		//bBrush=CreateSolidBrush(RGB(250,250,250));
		bBrush = (HBRUSH)GetStockObject(DC_BRUSH);//默认是白色，只有这样拿到的画刷才能调用SetDCBrushColor更改颜色
		SelectObject(MemDC,bBrush);
		SetBkMode(MemDC, TRANSPARENT);
		SetTextColor(MemDC, RGB(0,0,222));
		
		//填充背景 
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
		
		wchar_t wText[1000000];//wchar_t数组最大就是1000000了，再大运行直接报错 
		long total = GetWindowTextW(GValue::G_hwnd_article, wText,1000000);//成功返回字符串个数（不含最后的null），失败或者为空返回0 		
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
			
			if(isCheck) {//输出文字
				pwText2[0] = wText[i];
				TextOutW(MemDC, rect.left, rect.bottom, pwText2, 1);
			}
		}
		
		delete []pwText2;
		DeleteObject(bBrush);
		
		
//==============================end=====================================================		
		
		
		
		
		BITMAP BmpInfo;
		GetObject(hBmp,sizeof(BITMAP),&BmpInfo);//锟斤拷取位图锟斤拷息
		int datasize=BmpInfo.bmWidthBytes*BmpInfo.bmHeight;
		char*data=(char*)malloc(datasize);
		if (data==NULL)
		{
			printf("malloc err!\n");
			return;
		}

		BITMAPINFO binfo={0};//bmp锟斤拷息

		binfo.bmiHeader.biBitCount=BmpInfo.bmBitsPixel;//锟斤拷色位锟斤拷
		binfo.bmiHeader.biClrImportant=0;
		binfo.bmiHeader.biCompression=0;
		binfo.bmiHeader.biHeight=GValue::canvas_height;
		binfo.bmiHeader.biPlanes=BmpInfo.bmPlanes;//锟斤拷锟斤拷?锟斤拷锟斤拷为1
		binfo.bmiHeader.biSize=sizeof(BITMAPINFO);
		binfo.bmiHeader.biSizeImage=datasize;
		binfo.bmiHeader.biWidth=GValue::canvas_width;
		binfo.bmiHeader.biXPelsPerMeter=0;
		binfo.bmiHeader.biYPelsPerMeter=0;

		GetDIBits(MemDC,hBmp,0,BmpInfo.bmHeight,data,&binfo,DIB_RGB_COLORS);//RGB锟斤拷莼锟饺�
		//锟斤拷锟斤拷为锟借备锟斤拷锟轿煌硷拷锟斤拷始扫锟斤拷锟叫ｏ拷锟斤拷锟斤拷扫锟斤拷锟叫ｏ拷要锟斤拷锟斤拷锟斤拷锟斤拷锟斤拷位图锟斤拷息锟斤拷锟斤拷色锟斤拷式
		//(锟斤拷前锟斤拷锟斤拷锟斤拷色锟斤拷锟斤拷锟介保锟斤拷,锟斤拷锟节讹拷24锟斤拷32锟斤拷锟斤拷锟斤拷锟斤拷)
//		ChangColor(data,datasize,BmpInfo.bmBitsPixel);//锟斤拷珊诎锟�
		BITMAPFILEHEADER bfh={0};//bmp锟侥硷拷头
		bfh.bfType=MAKEWORD('B','M');
		bfh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFO);//锟斤拷锟狡拷锟�
		bfh.bfSize=bfh.bfOffBits+datasize;//锟侥硷拷锟杰达拷小
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
		DeleteObject(hBmp);//删锟斤拷锟斤拷璞�
		DeleteDC(MemDC);
		
//		if(RiWnd!=NULL)
//		ShowWindow(RiWnd,SW_SHOW);
		MessageBox(NULL, "保存成功","",MB_ICONEXCLAMATION|MB_OK);
	}
	
	
	void ResizeWindow() {
		RECT rc;
		GetClientRect(GValue::G_hwnd,&rc); 
		
		int width=rc.right-rc.left;
		int height=rc.bottom-rc.top;
		
		MoveWindow(GValue::G_hwnd_article, UI_LEFT(2), UI_TOP(0), (width - UI_LEFT(2) - UI_COM_LEFT), (UI_COM_HEIGHT * 5 + UI_COM_TOP), true); 
		MoveWindow(GValue::G_hwnd_screen, 0, UI_TOP(4), width, (height - UI_TOP(4)), true);
	}
	
	//竖直方向滚动条事件，与上面相似不解释了
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
	
	//水平方向滚动条事件
	void HscrollChange(WPARAM wParam, LPARAM lParam) {
			
		SCROLLINFO  si;
		si.cbSize=sizeof(SCROLLINFO);
		si.fMask=SIF_ALL;
		GetScrollInfo(GValue::G_hwnd_screen,SB_HORZ,&si);//先拿滚动条信息
		
		switch(LOWORD(wParam)){//这里只处理按下滚动条拖动的事件，其他滚动条事件自己实现吧
		
			//分析可知按住滚动条拖动过程中，需要修改当前位置、然后基于当前位置移动画布，最后修改滚动条位置（你不修改的话视觉效果上会弹回去的）、
			case SB_THUMBTRACK: {										
				GValue::position_width = si.nTrackPos * (GValue::canvas_width - GValue::screen_width) / 100;//更改当前位置		
				MoveWindow(GValue::G_hwnd_canvas, 0 - GValue::position_width, 0 - GValue::position_height, GValue::canvas_width, GValue::canvas_height, true);//移动画布
				
				si.nPos=si.nTrackPos;
				break;
			}
			
			//TODO 滚动条的其他事件				
			
			default: {
				break;
			}
		}
		
		//回写滚动条滚动块的位置，时视觉上正常
		si.fMask=SIF_POS;
		SetScrollInfo(GValue::G_hwnd_screen, SB_HORZ, &si, true);	
	}
	
	//窗口大小改变时，更新全局变量中的屏幕大小，更新滚动条上滚动块的位置
	void ResizeScreen(WPARAM wParam, LPARAM lParam) {
		//更新屏幕大小begin-----------------------------
		GValue::screen_width = LOWORD (lParam);
		GValue::screen_height = HIWORD (lParam);
		//更新屏幕大小end-----------------------------
		
		//更新滚动条上滚动块的位置begin----------------------
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
		//更新滚动条上滚动块的位置end----------------------
		
		
		//其实还应该更新滚动条上滚动块的长度，这里先忽略吧
		//int hb_length = GValue::s_width * (GValue::s_width - 40) / GValue::c_width;
		//int vb_length = GValue::s_height * (GValue::s_height - 40) / GValue::c_height;
		
		//更新画布
		UpdateWindow(GValue::G_hwnd_canvas); 
	}
}
