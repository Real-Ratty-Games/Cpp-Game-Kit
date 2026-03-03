
#include <WADFile.hpp>

int main()
{
	std::vector<uint8> buffer;

	WADFile file;
	file.Open("Data.wad");
	file.Read("MyTexture", buffer);
	file.Clear();
}
