[...]

int hello,bus,effect,asioOut;
hello = 0;
bus = 1;
effect= 2;
asioOut=3;

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

context.createInput(hello,HelloInput);
context.createOutput(asioOut,AsioOutput,"DRIVER_NAME:OUT1_NAME,OUT2_NAME");
// Use Asio Inspector provided with our installer to get the name of your asio driver and outputs

context.createBus(bus);
context.createEffect(attenuation,bus,AttenuationEffect,0U,1U);
context.createEffect(effect,bus,BinauralSpatializationAspic);

context.connect(hello, bus);
context.connect(bus,asioOut);

context.play();

float sourcePos[]   =   {0.0, 0.0, -1.0};
float listenerPos[] =   {0.0, 0.0, 1.0};
float listenerRot[] =   {0.0, 0.0, 0.0};
context.setParameter("listener/3/position",listenerPos);
context.setParameter("source/0/position",sourcePos);

char c;
do{
	std::cout<<"Press r or l to rotate the listener, press q to exit"<<std::endl;
	std::cin>>c;

	switch(c){
	case 'l':
		listenerRot[1]-=10;
		context.setParameter("listener/3/rotation",listenerRot);
		break;
	case 'r':
		listenerRot[1]+=10;
		context.setParameter("listener/3/rotation",listenerRot);
		break;
	}
}while(c!='q');

context.stop();

[...]