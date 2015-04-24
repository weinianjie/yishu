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
//		COLORREF color = RGB((( 0xff <<8 & hex ) >> 8),(( 0xff <<16 & hex ) >> 16),(0xff & hex));//����R��G
//		COLORREF color = RGB((0xff & hex),(( 0xff <<8 & hex ) >> 8),(( 0xff <<16 & hex ) >> 16));//����R��B 
//		COLORREF color = RGB((( 0xff <<16 & hex ) >> 16),(0xff & hex),(( 0xff <<8 & hex ) >> 8));//����G��B 
		return color;
    }	
	
	int UI_LEFT(int n) {
		return UI_COM_LEFT * (n + 1) + UI_COM_WIDTH * n;
	}
	
	int UI_TOP(int n) {
		return UI_COM_TOP * (n + 1) + UI_COM_HEIGHT *n;		
	}
	
	long max(long a, long b) {
		if (a > b) {
			return a;
		}
		return b;
	}
	
	long min(long a, long b) {
		if (a > b) {
			return b;
		}
		return a;
	}
	
	HINSTANCE GValue::G_hinstance             = NULL;
	HWND GValue::G_hwnd                       = NULL;
	HWND GValue::G_hwnd_countX             = NULL;
	HWND GValue::G_hwnd_countY             = NULL;
	HWND GValue::G_hwnd_width             = NULL;
	HWND GValue::G_hwnd_height             = NULL;
	HWND GValue::G_hwnd_limiter             = NULL;
	HWND GValue::G_hwnd_encoder             = NULL;  
	HWND GValue::G_hwnd_button             = NULL;
	HWND GValue::G_hwnd_article             = NULL;
	HWND GValue::G_hwnd_screen             = NULL;
	HWND GValue::G_hwnd_canvas             = NULL;


int			GValue::canvas_width 		= 0;//��������
int 		GValue::canvas_height 		= 0;//�������

int			GValue::screen_width 		= 0;//��Ļ����
int			GValue::screen_height 		= 0;//��Ļ���

int			GValue::position_width 		= 0;//��ǰλ�õĺ�����
int			GValue::position_height 	= 0;//��ǰλ�õ�������

int			GValue::hb_pos 				= 0;//��ֱ�����������ǰλ��
int			GValue::vb_pos 				= 0;//ˮƽ�����������ǰλ��
	//---------------------------------------------------------------------
	

}
