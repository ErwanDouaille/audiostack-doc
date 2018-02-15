[...]

int hello,bus,effect,asioOut1,asioOut2,attenuation;
hello = 0;
bus = 1;
effect= 2;
attenuation = 3;
asioOut1=4;
asioOut2=5;

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

context.createInput(hello,HelloInput);
context.createOutput(asioOut1,AsioOutput,"DRIVER_NAME:OUT1_NAME,OUT2_NAME");
context.createOutput(asioOut2,AsioOutput,"DRIVER_NAME:OUT3_NAME,OUT4_NAME");
// Use Asio Inspector provided with our installer to get the name of your asio driver and outputs

context.createBus(bus);
context.createEffect(attenuation,bus,AttenuationEffect,0U,1U);
context.createEffect(effect,bus,BinauralSpatializationAspic);
context.setLastEffectCount(bus,2);
// We force this bus to output 2 separate outputs. Each output is stereo (thanks to binaural spat).

context.connect(hello, "out",bus,"in_0");
context.connect(hello, "out",bus,"in_1");
context.connect(bus,"out_0",asioOut1,"in");
context.connect(bus,"out_1",asioOut2,"in");
// Since our bus holds 2 outputs and inputs, connection may use explicit naming

context.play();

// Audio source starts between the two listeners. They are both looking toward the source.
float pos[] = {0.0,0.0,0.0};
float listPos[] = {-10.0,0.0,0.0};
float listRot[] = {0.0,90.0,0.0};
context.setParameter("source/0/position",pos);
context.setParameter("listener/4/position",listPos);
context.setParameter("listener/4/rotation",listRot);
listPos[0] = 10.0f;
listRot[1] = 270.0f;
context.setParameter("listener/5/position",listPos);
context.setParameter("listener/5/rotation",listRot);

char c;
do{
	std::cout<<"Press f or b to move the source. The source starts between the listeners and can be moved. Press q to exit"<<std::endl;
	std::cout<<"Current source position: "<<pos[2]<<std::endl;
	std::cin>>c;

	switch(c){
	case 'f':
		pos[2]-=1.0;
		context.setParameter("source/0/position",pos);
		break;
	case 'b':
		pos[2]+=1.0;
		context.setParameter("source/0/position",pos);
		break;
	}
}while(c!='q');

context.stop();

[...]