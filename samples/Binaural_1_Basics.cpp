[...]

int helloId = 0;
int outputId = 1;
int busId = 2;
int spatId = 3;

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE.aslc");

context.createInput(helloId, HelloInput);
context.createOutput(outputId, OpenALOutput,true);                 
// Output is stereo, because binaural effect produces a stereo output.

context.createBus(busId);                                       
context.createEffect(spatId,busId,BinauralSpatializationAspic);

context.connect(helloId,busId);
context.connect(busId,outputId);

context.play();

float sourcePos[]   =   {0.0, 0.0, -1.0};
float listenerPos[] =   {0.0, 0.0, 1.0};
float listenerRot[] =   {0.0, 0.0, 0.0};

context.setParameter("listener/1/position",listenerPos);

char c;
do{

	std::cout<<"Press r or l to rotate the listener, press q to exit"<<std::endl;
	std::cin>>c;

	switch(c){
	case 'l':
		listenerRot[1]-=10;
		context.setParameter("listener/1/rotation",listenerRot);
		err(context);
		break;
	case 'r':
		listenerRot[1]+=10;
		context.setParameter("listener/1/rotation",listenerRot);
		err(context);
		break;
	}
}while(c!='q');


context.stop();

[...]