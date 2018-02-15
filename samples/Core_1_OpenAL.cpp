[...]

int micId = 0;
int outputId = 1;

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

context.createInput(micId,OpenALInput);
context.createOutput(outputId,OpenALOutput,false);
// Output is mono, in order to accept mono microphone.

context.connect(micId,outputId);
// No need of bus in this sample.

context.play();

char c;
std::cout<<"Mic capture in progress. Press q to quit."<<std::endl;
do{
	std::cin>>c;
} while(c!='q');    

context.stop();

[...]