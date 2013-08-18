#include "GValue.h"

using namespace ht;

namespace ht {
	
	int rgb2hex(int r,int g,int b) {
		return r<<16 | g <<8 |b;
	}	
	
	COLORREF hex2rgb(int hex) {
		if(hex <  0x0 && hex > 0xffffff) {
			return RGB(0, 0, 0);
		}
		COLORREF color = RGB((( 0xff <<16 & hex ) >> 16),(( 0xff <<8 & hex ) >> 8),(0xff & hex));
		return color;
    }	
	
	int UI_LEFT(int n) {
		return UI_COM_LEFT * (n + 1) + UI_COM_WIDTH * n;
	}
	
	int UI_TOP(int n) {
		return UI_COM_TOP * (n + 1) + UI_COM_HEIGHT *n;		
	}
	
	//-----------------------------------------------------------------
	HINSTANCE 			GValue::GetHinstance() {
		return _hinstance;
	}
	
	HWND				GValue::GetHwnd() {
		return _hwnd;
	}
	
	void 				GValue::SetHinstance(HINSTANCE hinstance) {
		_hinstance = hinstance;
	}
	
	void				GValue::SetHwnd(HWND hwnd) {
		_hwnd = hwnd;
	}
	
	HINSTANCE GValue::_hinstance             = NULL;
	HWND GValue::_hwnd                       = NULL;
	
	
	//---------------------------------------------------------------------
	
	
	void TrySeveDeskBmp(HWND RiWnd)
	{
//		if(RiWnd!=NULL)
//		ShowWindow(RiWnd,SW_HIDE);
		
		Sleep(100);
		HDC HDeskDC= GetDC(RiWnd);
//		HDC HDeskDC= GetDC(GetDesktopWindow());//���洰�ڻ�ͼ���
		HDC MemDC=CreateCompatibleDC(HDeskDC);//�������豸
		RECT rc;
		GetClientRect(RiWnd,&rc);
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
	}
	
}
