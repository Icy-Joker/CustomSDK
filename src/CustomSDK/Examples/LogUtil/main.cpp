#include "LogManager.h"

#include <thread>

int main (int argc, char* argv[])
{
	LogManager manager;
	manager.initialize();

	for (auto j=0;j<10;j++)
	{
		std::thread thread_test([&manager,j]
		{
			for (auto i = 0; i < 100; i++)
			{
				char a[1024]="";
				sprintf(a, "Ïß³Ì:%d,ÐÐºÅ:%d", j, i);
				manager.log_warn(a);
			}
		});
		thread_test.detach();
	}
	system("pause");
	return 0;
}
