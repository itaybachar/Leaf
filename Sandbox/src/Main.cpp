
namespace Leaf {

	__declspec(dllimport) void print();
}
int main() {
	Leaf::print();
	return 0;
}