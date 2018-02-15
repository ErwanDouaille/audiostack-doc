[...]

int micId = 0;
int outputId = 1;
int busId = 2;
int gainId = 3;

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

context.createInput(micId, OpenALInput);
context.createOutput(outputId, OpenALOutput,true);					
// We use a stereo output

context.createBus(busId);										
// Our bus holds the id '2'

context.createEffect(gainId, busId, MultiChannelSimpleGain,(unsigned int)2);	
// We add a gain with the ability to split the signal in 2 subchannels

context.connect(micId,busId);									
context.connect(busId,outputId);								
// Connections are matching, because subchannel equality rule is observed

context.play();

[...]