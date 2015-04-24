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

	    
	
	    hdc = BeginPaint(GValue::G_hwnd_canvas, &ps); //Ϊ�˷�ֹ��ѭ������WM_PAINT�������Ҫbegin 
		
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

		//TODO ��ֹ�����������2000�������1000 
		char _xNum[5]; //���1λǿ������������������ǧ��4λ��������9999 
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
		
//		bool isCheck = (IsDlgButtonChecked(GValue::G_hwnd_encoder, IDC_CHECKBOX_ENCODE) == BST_CHECKED);//SengMesage��������WM_COMMAND��ԭ����ܷ���ʧ�� 
		bool isCheck = (SendDlgItemMessage(GValue::G_hwnd, IDC_CHECKBOX_ENCODE, BM_GETCHECK, 0, 0) == BST_CHECKED);
		
		if(xNum == 0 || yNum == 0 || width == 0 || height == 0) {
			EndPaint(GValue::G_hwnd_canvas, &ps);
			return;
		}
		
		if(xNum > 2000) {
			MessageBox(NULL, TEXT("�������2000�㣡") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			//SetWindowText(GValue::G_hwnd_countX, "2000");
			EndPaint(GValue::G_hwnd_canvas, &ps);
			return; 
		} 
		
		if(yNum > 1000) {
			MessageBox(NULL, TEXT("�������1000�㣡") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			//SetDlgItemInt(GValue::G_hwnd_countX, IDC_TEXT_COUNTY, 1000, false);
			EndPaint(GValue::G_hwnd_canvas, &ps);
			return; 
		} 
		
		//����������С 
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
		
		RECT rect;//����Ҫ��ʼ�����ֹ���� 
		HBRUSH bBrush;	
		//bBrush=CreateSolidBrush(RGB(250,250,250));
		bBrush = (HBRUSH)GetStockObject(DC_BRUSH);//Ĭ���ǰ�ɫ��ֻ�������õ��Ļ�ˢ���ܵ���SetDCBrushColor������ɫ 
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

/*====================�͵û�ȡ��ת������begin========================== 
		char sText[2000000];// = {"��������"}; 
		GetWindowText(GValue::G_hwnd_article, sText,2000000);
		
		DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, sText, -1, NULL, 0);//
		//DWORD dwNum = MultiByteToWideChar (CP_UTF8, 0, sText, -1, NULL, 0);

		wchar_t *pwText;
		pwText = new wchar_t[dwNum];
		
		MultiByteToWideChar (CP_ACP, 0, sText, -1, pwText, dwNum);
		//MultiByteToWideChar (CP_UTF8, 0, sText, -1, pwText, dwNum);
		
		//���һ���ǽ����������ã����ܳ��������С 
		long total = min(--dwNum, xNum * yNum);
====================�͵û�ȡ��ת������end==========================*/
		 
		wchar_t wText[1000000];//wchar_t����������1000000�ˣ��ٴ�����ֱ�ӱ��� 
		//wchar_t wText[5] = {'1','2','3','4','5'}; 
		long total = GetWindowTextW(GValue::G_hwnd_article, wText,1000000);//�ɹ������ַ�����������������null����ʧ�ܻ���Ϊ�շ���0 		
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
			
			if(isCheck) {//�������
				pwText2[0] = wText[i]/*pwText[i]*/;
				TextOutW(hdc, rect.left, rect.bottom, pwText2, 1);
			}
		}
	
		delete []pwText2;//new�Ķ���Ҫɾ���������������������ʽɾ�� 
		DeleteObject(bBrush);
	    EndPaint(GValue::G_hwnd_canvas, &ps);   
	     
	}
	
	
	void TrySeveDeskBmp()
	{
		HDC HDeskDC= GetDC(GValue::G_hwnd_canvas);
//		HDC HDeskDC= GetDC(GetDesktopWindow());//���洰�ڻ�ͼ���
		HDC MemDC=CreateCompatibleDC(HDeskDC);//�������豸

//		GetClientRect(GetDesktopWindow(),&rc);//���洰�ڴ�С
		//int width=rc.right-rc.left;
		//int height=rc.bottom-rc.top;
//================================begin=============================================		
		char _xNum[5]; //���1λǿ������������������ǧ��4λ��������9999 
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
			MessageBox(NULL, TEXT("�������2000�㣡") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			DeleteDC(MemDC);
			return; 
		} 
		
		if(yNum > 1000) {
			MessageBox(NULL, TEXT("�������1000�㣡") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			DeleteDC(MemDC);
			return; 
		}
		
		char _limiter[5];
		GetWindowText(GValue::G_hwnd_limiter, _limiter, 5);
		int limiter = atoi(_limiter);		
		
		if(GValue::canvas_width > 6000 || GValue::canvas_height > 3000) {//��ʱ�Ա��� 
			MessageBox(NULL, TEXT("̫���˲����㱣�棡") ,"Error!",MB_ICONEXCLAMATION|MB_OK);
			DeleteDC(MemDC);
			return;
		}
		
//================================end======================================		
		
		HBITMAP hBmp=CreateCompatibleBitmap(HDeskDC,GValue::canvas_width,GValue::canvas_height);//������Ϊ�����Ĵ���λͼ
		SelectObject(MemDC,hBmp);//�󶨺󣬿���������ͼ�� 
		//BitBlt(MemDC,0,0,width,height,HDeskDC,0,0,SRCCOPY);//����ת�� 
		
		
		
//=================================begin======================================		
		
		
		RECT rect;
		HBRUSH bBrush;
		//bBrush=CreateSolidBrush(RGB(250,250,250));
		bBrush = (HBRUSH)GetStockObject(DC_BRUSH);//Ĭ���ǰ�ɫ��ֻ�������õ��Ļ�ˢ���ܵ���SetDCBrushColor������ɫ
		SelectObject(MemDC,bBrush);
		SetBkMode(MemDC, TRANSPARENT);
		SetTextColor(MemDC, RGB(0,0,222));
		
		//��䱳�� 
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
		
		wchar_t wText[1000000];//wchar_t����������1000000�ˣ��ٴ�����ֱ�ӱ��� 
		long total = GetWindowTextW(GValue::G_hwnd_article, wText,1000000);//�ɹ������ַ�����������������null����ʧ�ܻ���Ϊ�շ���0 		
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
			
			if(isCheck) {//�������
				pwText2[0] = wText[i];
				TextOutW(MemDC, rect.left, rect.bottom, pwText2, 1);
			}
		}
		
		delete []pwText2;
		DeleteObject(bBrush);
		
		
//==============================end=====================================================		
		
		
		
		
		BITMAP BmpInfo;
		GetObject(hBmp,sizeof(BITMAP),&BmpInfo);//��ȡλͼ��Ϣ
		int datasize=BmpInfo.bmWidthBytes*BmpInfo.bmHeight;
		char*data=(char*)malloc(datasize);
		if (data==NULL)
		{
			printf("malloc err!\n");
			return;
		}

		BITMAPINFO binfo={0};//bmp��Ϣ

		binfo.bmiHeader.biBitCount=BmpInfo.bmBitsPixel;//��ɫλ��
		binfo.bmiHeader.biClrImportant=0;
		binfo.bmiHeader.biCompression=0;
		binfo.bmiHeader.biHeight=GValue::canvas_height;
		binfo.bmiHeader.biPlanes=BmpInfo.bmPlanes;//����?����Ϊ1
		binfo.bmiHeader.biSize=sizeof(BITMAPINFO);
		binfo.bmiHeader.biSizeImage=datasize;
		binfo.bmiHeader.biWidth=GValue::canvas_width;
		binfo.bmiHeader.biXPelsPerMeter=0;
		binfo.bmiHeader.biYPelsPerMeter=0;

		GetDIBits(MemDC,hBmp,0,BmpInfo.bmHeight,data,&binfo,DIB_RGB_COLORS);//RGB��ݻ�ȡ
		//����Ϊ�豸���λͼ���ʼɨ���У�����ɨ���У�Ҫ����������λͼ��Ϣ����ɫ��ʽ
		//(��ǰ������ɫ�����鱣��,���ڶ�24��32��������)
//		ChangColor(data,datasize,BmpInfo.bmBitsPixel);//��ɺڰ�
		BITMAPFILEHEADER bfh={0};//bmp�ļ�ͷ
		bfh.bfType=MAKEWORD('B','M');
		bfh.bfOffBits=sizeof(BITMAPFILEHEADER)+sizeof(BITMAPINFO);//���ƫ��
		bfh.bfSize=bfh.bfOffBits+datasize;//�ļ��ܴ�С
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
		DeleteObject(hBmp);//ɾ����豸
		DeleteDC(MemDC);
		
//		if(RiWnd!=NULL)
//		ShowWindow(RiWnd,SW_SHOW);
		MessageBox(NULL, "����ɹ�","",MB_ICONEXCLAMATION|MB_OK);
	}
	
	
	void ResizeWindow() {
		RECT rc;
		GetClientRect(GValue::G_hwnd,&rc); 
		
		int width=rc.right-rc.left;
		int height=rc.bottom-rc.top;
		
		MoveWindow(GValue::G_hwnd_article, UI_LEFT(2), UI_TOP(0), (width - UI_LEFT(2) - UI_COM_LEFT), (UI_COM_HEIGHT * 5 + UI_COM_TOP), true); 
		MoveWindow(GValue::G_hwnd_screen, 0, UI_TOP(4), width, (height - UI_TOP(4)), true);
	}
	
	//��ֱ����������¼������������Ʋ�������
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
	
	//ˮƽ����������¼�
	void HscrollChange(WPARAM wParam, LPARAM lParam) {
			
		SCROLLINFO  si;
		si.cbSize=sizeof(SCROLLINFO);
		si.fMask=SIF_ALL;
		GetScrollInfo(GValue::G_hwnd_screen,SB_HORZ,&si);//���ù�������Ϣ
		
		switch(LOWORD(wParam)){//����ֻ�����¹������϶����¼��������������¼��Լ�ʵ�ְ�
		
			//������֪��ס�������϶������У���Ҫ�޸ĵ�ǰλ�á�Ȼ����ڵ�ǰλ���ƶ�����������޸Ĺ�����λ�ã��㲻�޸ĵĻ��Ӿ�Ч���ϻᵯ��ȥ�ģ���
			case SB_THUMBTRACK: {										
				GValue::position_width = si.nTrackPos * (GValue::canvas_width - GValue::screen_width) / 100;//���ĵ�ǰλ��		
				MoveWindow(GValue::G_hwnd_canvas, 0 - GValue::position_width, 0 - GValue::position_height, GValue::canvas_width, GValue::canvas_height, true);//�ƶ�����
				
				si.nPos=si.nTrackPos;
				break;
			}
			
			//TODO �������������¼�				
			
			default: {
				break;
			}
		}
		
		//��д�������������λ�ã�ʱ�Ӿ�������
		si.fMask=SIF_POS;
		SetScrollInfo(GValue::G_hwnd_screen, SB_HORZ, &si, true);	
	}
	
	//���ڴ�С�ı�ʱ������ȫ�ֱ����е���Ļ��С�����¹������Ϲ������λ��
	void ResizeScreen(WPARAM wParam, LPARAM lParam) {
		//������Ļ��Сbegin-----------------------------
		GValue::screen_width = LOWORD (lParam);
		GValue::screen_height = HIWORD (lParam);
		//������Ļ��Сend-----------------------------
		
		//���¹������Ϲ������λ��begin----------------------
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
		//���¹������Ϲ������λ��end----------------------
		
		
		//��ʵ��Ӧ�ø��¹������Ϲ�����ĳ��ȣ������Ⱥ��԰�
		//int hb_length = GValue::s_width * (GValue::s_width - 40) / GValue::c_width;
		//int vb_length = GValue::s_height * (GValue::s_height - 40) / GValue::c_height;
		
		//���»���
		UpdateWindow(GValue::G_hwnd_canvas); 
	}
}
