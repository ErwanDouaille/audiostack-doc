[...]

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE.aslc");

context.createInput(0,AudioFileReader,"FILE.wav");
// file is a mono, 48kHz/16bits wav file located on disk
// OR context.createInput(0,AudioFileReader,"KEY") if in server
context.createOutput(1,OpenALOutput,false);
// Output is mono, in order to accept mono file.

context.setParameter("source/0/loop",true);             // file will play in loop
context.setParameter("source/0/start_on_awake",true);   // start file reading automatically

context.connect(0,1);

context.play();

char c;
do{
	std::cout<<"Press r to play, p to pause and s to stop. Press q to quit."<<std::endl;
	std::cin>>c;

	switch(c){
	case 'r':
		context.sendCommand("source/0/play");
		break;

	case 'p':
		context.sendCommand("source/0/pause");
		break;

	case 's':
		context.sendCommand("source/0/stop");
		break;
	}
}while(c!='q');

context.stop();

[...]