#include "pch.h"
#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;

//int main(array<System::String ^> ^args)
//{
//    return 0;
//}



[STAThread]
int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Application::Run(gcnew CppCLRWinformsProjekt::Form1()); 
	return 0;
}