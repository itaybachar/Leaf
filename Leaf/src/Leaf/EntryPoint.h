#pragma once

#ifdef LF_PLATFORM_WINDOWS

extern Leaf::Application* Leaf::CreateLeaf();

int main(int argc, char* argv)
{
	Leaf::Logger::InitLogger();
	
	LF_CORE_CRITICAL("BAD STUFF");
	int i = 4;
	LF_CORE_INFO("Var i = {0}", i);

	auto leaf = Leaf::CreateLeaf();
	leaf->Run();
	delete leaf;
}
#endif