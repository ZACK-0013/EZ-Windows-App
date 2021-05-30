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
			if (IDNO == MessageBox(hwnd, L"ȷ��Ҫ��ը��", L"��ʾ", MB_YESNO | MB_ICONEXCLAMATION))
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
				MessageBox(hwnd, L"����Ϣ������ϲ��ܺ�ը��", L"��ʾ", MB_OK | MB_ICONERROR);
				break;
			}

			hTarget = FindWindow(0, szText1);
			if (!hTarget)
			{
				MessageBox(hwnd, L"δ�ҵ��ô��ڣ���˶Դ������ƺ����ԣ���", L"��ʾ", MB_OK | MB_ICONERROR);
				break;
			}

			nCount = _wtoi(szText2);

			//���������
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

			MessageBox(hwnd, L"��ը�ɹ�����", L"��ϲ!!", MB_OK);

			break;
		}

		case IDC_BUTTON1:
			MessageBox(hwnd, L"@copyright ZACK_0013\n�汾��V1.0\n����ѧϰ���֣���������ը���ˣ���\n�������Ը�����", L"����", MB_OK);
			break;

		case IDC_BUTTON2:
			MessageBox(hwnd, L"1.��ը���������������촰�ڵ����ƣ�ע���ַ��������Ȼ���ײ��Ҵ��󣬿��Ե㿪���촰�����棬����鿴������ϸ��Ϣҳ�棬��������.\n2.��ը��������������࣬������ɷ���������Կ��٣����ؿ��ܻᱻ��ţ���\n3.��л��ʹ��QQ��ը�����ú�ը��������QQ�����촰�ڶ�������ʹ�ã�\n4.�������BUG,���߽���ѧ������ӭ�������QQ��1136414142", L"����", MB_OK);
			break;
		}
		break;
	}

	case WM_CLOSE:
		MessageBox(hwnd, L"��л����ʹ�ã���", L"�ټ���", MB_OK);
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
