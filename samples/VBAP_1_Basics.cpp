[...]

int helloIn=0,jackOut=1,bus=2,vbap=3;

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE.aslc");

context.createInput(helloIn,HelloInput);
context.createOutput(jackOut,JackOutput,(unsigned int)4);

context.createBus(bus);
context.createEffect(vbap,bus,MultiChannelSpatialization,(unsigned int)4);

float pos1[] = {-1,0,1};
float pos2[] = {-1,0,-1};
float pos3[] = {1,0,-1};
float pos4[] = {1,0,1};

context.setParameter("hardware/0/position",pos1);
context.setParameter("hardware/1/position",pos2);
context.setParameter("hardware/2/position",pos3);
context.setParameter("hardware/3/position",pos4);

context.connect(helloIn, bus);
context.connect(bus,jackOut);

context.play();

float pos[] = {0.0,0.0,-1.0};
float listPos[] = {0.0,0.0,0.0};
float listRot[] = {0.0,0.0,0.0};
context.setParameter("source/0/position",pos);
context.setParameter("listener/1/position",listPos);
context.setParameter("listener/1/rotation",listRot);

char c;
do{
	std::cout<<"Feel free to connect jack ports (with program such as 'qjackctl').\n\tPress r or l to rotate the listener, press q to exit"<<std::endl;
	std::cin>>c;
switch(c){
	case 'l':
		listRot[1]-=10;
		context.setParameter("listener/1/rotation",listRot);
	break;

	case 'r':
	listRot[1]+=10;
	context.setParameter("listener/1/rotation",listRot);
	break;

	}
}while(c!='q');

context.stop();

[...]

