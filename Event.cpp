#include "windows.h"
#include "Event.h"

using namespace ht;

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
		
	    //GetClientRect(hwnd,&rect2);
	    //DrawText(hdc,TEXT("Hello!"),-1,&rect2,DT_CENTER);
	    //DrawText(hdc, wch,-1,&rect2,DT_CENTER);
		
		RECT rect;
		HBRUSH bBrush;	
		bBrush=CreateSolidBrush(RGB(250,250,250));
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
		
		char sText[2000000];// = {"��������"}; //����������2000000�ˣ��ٴ�����ֱ�ӱ��� 
		GetWindowText(GValue::G_hwnd_article, sText,2000000);
		
		DWORD dwNum = MultiByteToWideChar (CP_ACP, 0, sText, -1, NULL, 0);//
		//DWORD dwNum = MultiByteToWideChar (CP_UTF8, 0, sText, -1, NULL, 0);
		
//		char str2[20];

//		itoa(dwNum, str2, 10);
//		
//		MessageBox(NULL, str2 ,"Error!",MB_ICONEXCLAMATION|MB_OK);

		wchar_t *pwText;
		pwText = new wchar_t[dwNum];
		
		MultiByteToWideChar (CP_ACP, 0, sText, -1, pwText, dwNum);
		//MultiByteToWideChar (CP_UTF8, 0, sText, -1, pwText, dwNum);
		 
		//int total = sizeof(pwText)/2;
		
		//���һ���ǽ����������ã����ܳ��������С 
		long total = min(--dwNum, xNum * yNum);
		
		for(long i=0;i<total;i++) {
			bBrush=CreateSolidBrush(hex2rgb((pwText[i] - 19968) * 801));
			
            rect.left = i % xNum * (width + limiter);
            rect.top = i / xNum * (height + limiter);
            if(isCheck) {
            	rect.top = rect.top * 2;
            }
            rect.right = rect.left + width;//(i + 1) * width;
            rect.bottom = rect.top + height;//(j + 1) * height;
			FillRect(hdc, &rect, bBrush);
			
			if(isCheck) {//�������
				
				wchar_t *pwText2;
				pwText2 = new wchar_t[1];
				pwText2[1] = pwText[i];
				
				DWORD dsNum = WideCharToMultiByte(CP_UTF8, NULL, pwText2, -1, NULL,0,NULL,FALSE);
				
				char *psText;
				psText = new char[dsNum];
				
				WideCharToMultiByte (CP_UTF8,NULL,pwText2,-1,psText,dsNum,NULL,FALSE);

				TextOut(hdc, rect.left, rect.bottom, psText, 1);
				delete []psText;
			}
		}
	
		DeleteObject(bBrush);
	    EndPaint(GValue::G_hwnd_canvas, &ps);   
	     
	}
	
	
	void TrySeveDeskBmp()
	{
//		char str[6];
//		//itoa(GetDlgItemInt(GValue::G_hwnd_countX, IDC_TEXT_COUNTX, NULL, false), str, 10);
//		GetWindowText(GValue::G_hwnd_countX, str, 6);
//		
//		int aa = atoi(str);
//		
//		aa++;
//		
//		char str2[6];
//		
//		itoa(aa, str2, 10);
//		
//		MessageBox(NULL, str2 ,"Error!",MB_ICONEXCLAMATION|MB_OK);
		
//		char sText[3000];// = {""};
//		GetWindowText(GValue::G_hwnd_article, sText,3000);
//		MessageBox(NULL, sText ,"Error!",MB_ICONEXCLAMATION|MB_OK);


//		return;
		
//		if(RiWnd!=NULL)
//		ShowWindow(RiWnd,SW_HIDE);
//		Sleep(100);
		
		HDC HDeskDC= GetDC(GValue::G_hwnd_canvas);
//		HDC HDeskDC= GetDC(GetDesktopWindow());//���洰�ڻ�ͼ���
		HDC MemDC=CreateCompatibleDC(HDeskDC);//�������豸
		RECT rc;
		GetClientRect(GValue::G_hwnd_canvas,&rc);
//		GetClientRect(GetDesktopWindow(),&rc);//���洰�ڴ�С
		int width=rc.right-rc.left;
		int height=rc.bottom-rc.top;
		HBITMAP hBmp=CreateCompatibleBitmap(HDeskDC,width,height);//������Ϊ�����Ĵ���λͼ
		SelectObject(MemDC,hBmp);
		BitBlt(MemDC,0,0,width,height,HDeskDC,0,0,SRCCOPY);//������ͼ�񱣴浽�µĻ�ͼ�豸��
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
		binfo.bmiHeader.biHeight=height;
		binfo.bmiHeader.biPlanes=BmpInfo.bmPlanes;//����?����Ϊ1
		binfo.bmiHeader.biSize=sizeof(BITMAPINFO);
		binfo.bmiHeader.biSizeImage=datasize;
		binfo.bmiHeader.biWidth=width;
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
		
		MoveWindow(GValue::G_hwnd_canvas, 10, 10, width - 20, (height - UI_TOP(4) - 20), true);
	}
}
