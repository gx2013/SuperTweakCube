#include <memory>  // for auto_ptr
#include "audiere.h"
#include <cstring>
using namespace std;
using namespace audiere;

class Audio{
public:
	Audio(string name,bool repeat,float volume);
	int play();
private:
	string name;
	bool repeat;
	float volume;
	auto_ptr<Stream> stream;
};