#include <stdio.h>
#include <Windows.h>
#include "resource.h"

INT_PTR CALLBACK Dlgproc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	WCHAR szText1[128]{ 0 };
	WCHAR szText2[128]{ 0 };
	WCHAR szText3[128]{ 0 };

	int nCount, nText1Lenth, nText2Lenth, nText3Lenth;
	HWND hTarget;
	switch (message)
	{
	case WM_COMMAND:
	{
		WORD id = LOWORD(wParam);
		switch (id)
		{
		case IDOK:
		{
			if (IDNO == MessageBox(hwnd, L"确认要轰炸吗？", L"提示", MB_YESNO | MB_ICONEXCLAMATION))
			{
				break;
			}

			GetDlgItemText(hwnd, IDC_EDIT1, szText1, 128);
			GetDlgItemText(hwnd, IDC_EDIT2, szText2, 128);
			GetDlgItemText(hwnd, IDC_EDIT3, szText3, 128);

			nText1Lenth = wcslen(szText1);
			nText2Lenth = wcslen(szText2);
			nText3Lenth = wcslen(szText3);

			if (!(nText1Lenth && nText2Lenth && nText3Lenth))
			{
				MessageBox(hwnd, L"把信息输入完毕才能轰炸！", L"提示", MB_OK | MB_ICONERROR);
				break;
			}

			hTarget = FindWindow(0, szText1);
			if (!hTarget)
			{
				MessageBox(hwnd, L"未找到该窗口！请核对窗口名称后重试！！", L"提示", MB_OK | MB_ICONERROR);
				break;
			}

			nCount = _wtoi(szText2);

			//剪贴板操作
			OpenClipboard(NULL);
			EmptyClipboard();
			HGLOBAL hGol = GlobalAlloc(GMEM_MOVEABLE, 128 * sizeof(WCHAR));
			LPWSTR lpStrcpy = (LPWSTR)GlobalLock(hGol);
			memcpy(lpStrcpy, szText3, 128 * sizeof(WCHAR));
			GlobalUnlock(hGol);
			SetClipboardData(CF_UNICODETEXT, hGol);
			CloseClipboard();

			while (nCount-- > 0)
			{
				SendMessage(hTarget, WM_PASTE, 0, 0);
				SendMessage(hTarget, WM_KEYDOWN, VK_RETURN, 0);
			}

			MessageBox(hwnd, L"轰炸成功！！", L"恭喜!!", MB_OK);

			break;
		}

		case IDC_BUTTON1:
			MessageBox(hwnd, L"@copyright ZACK_0013\n版本号V1.0\n仅供学习娱乐，切勿恶意轰炸他人！！\n否则后果自负！！", L"关于", MB_OK);
			break;

		case IDC_BUTTON2:
			MessageBox(hwnd, L"1.轰炸对象栏请输入聊天窗口的名称，注意字符间隔，不然容易查找错误，可以点开聊天窗口上面，进入查看个人详细信息页面，复制名字.\n2.轰炸次数不宜输入过多，容易造成服务器与电脑卡顿，严重可能会被封号！！\n3.感谢您使用QQ轰炸器，该轰炸器对类似QQ的聊天窗口都能正常使用！\n4.如果遇到BUG,或者交流学术，欢迎添加作者QQ：1136414142", L"帮助", MB_OK);
			break;
		}
		break;
	}

	case WM_CLOSE:
		MessageBox(hwnd, L"感谢您的使用！！", L"再见！", MB_OK);
		EndDialog(hwnd, FALSE);
		//PostQuitMessage(0);
		break;

	case WM_DESTROY:
		DestroyWindow(hwnd);
		PostQuitMessage(0);
		break;

	default:
		return FALSE;
	}
	return TRUE;
}


LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	RECT rect;
	TEXTMETRIC tm;
	static int cxChar, cyChar, cxClient, cyClient;
	HGDIOBJ original = NULL;
	TCHAR szBuffer[128];
	size_t iTarget;

	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, Dlgproc);
	return 0;
}
