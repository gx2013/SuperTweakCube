#include "audio.h"
Audio::Audio(string name,bool repeat,float volume){
	this->name=name;
	this->repeat=repeat;
	this->volume=volume;
}

int Audio::play(){
	const char * name = this->name.data();
    auto_ptr<Context> context(CreateContext(0));
    if (!context.get()) {
       return EXIT_FAILURE;
    }

    // open a stream
    auto_ptr<Stream> stream1(context->openStream(name));
	stream=stream1;
    if (!stream.get()) {
       return EXIT_FAILURE;
    }
	stream->setRepeat(repeat);
	stream->setVolume(volume);
    stream->play(); // play the song
	//getchar();
    return EXIT_SUCCESS;
}