[...]


int producerIn=0, networkIn=1, networkOut=2, audioOut=3;

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE.aslc");

RtpInterface::Load(context.impl);

L16Codec codec;

context.createInput(networkIn,RtpInput,codec.serialize());

context.createInput(producerIn,HelloInput);

context.createOutput(networkOut,RtpOutput,codec.serialize());

context.createOutput(audioOut,OpenALOutput,false);

context.setParameter("source/1/port",(unsigned int)9040);
// Input will read audio on port 9040

context.setParameter("listener/2/port",(unsigned int)9040);
context.setParameter("listener/2/ip_address","127.0.0.1");
// Output will send audio to remote host 127.0.0.1:9040

context.setParameter("application/buffer_size",(unsigned int)4096U);

context.connect(producerIn,networkOut);
context.connect(networkIn,audioOut);

context.play();

char c;
std::cout<<"Press q to quit."<<std::endl;
do{
	std::cin>>c;
}while(c!='q');

context.stop();

[...]
