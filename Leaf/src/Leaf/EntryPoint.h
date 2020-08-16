#pragma once

#ifdef LF_PLATFORM_WINDOWS

extern Leaf::Application* Leaf::CreateLeaf();

int main(int argc, char* argv)
{
	auto leaf = Leaf::CreateLeaf();
	leaf->Run();
	delete leaf;
}

 

#endif