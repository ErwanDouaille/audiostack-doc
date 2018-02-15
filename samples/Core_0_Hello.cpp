[...]

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

int helloId = 0;
int outputId = 1;

context.createInput(helloId,HelloInput);
context.createOutput(outputId,OpenALOutput,false);
// Output is mono, in order to accept mono microphone.

context.connect(helloId,outputId);
// No need of bus in this sample.
			
context.play();

char c;
std::cout<<"Aspic Audiostack says Hello. Press q to quit."<<std::endl;
do{
	std::cin>>c;
} while(c!='q');			

context.stop();

	
[...]