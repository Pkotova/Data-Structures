#include "pch.h"
#include "Form2.h"

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
	Application::Run(gcnew CppCLRWinformsProjekt::Form2()); 
	return 0;
}