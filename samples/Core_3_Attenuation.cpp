[...]

int micId = 0;
int outputId = 1;
int busId = 2;
int attenuationId = 3;

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

context.createInput(micId, HelloInput);
context.createOutput(outputId, OpenALOutput,false);
// We use a mono output

context.createBus(busId);                                       
context.createEffect(attenuationId,busId,AttenuationEffect,0U,1U);
// Effect apply a linear attenuation on mono channels.

context.connect(micId,busId);                                   
context.connect(busId,outputId);        

float sourcePos[] = {0.0, 0.0, -1.0};
context.setParameterAtInitVec3("source/0/position",sourcePos);
err(context);
/* Parameters can be set before play(), thanks to setParameterAtInit functions. 
Microphone contains variable %src_id automatically set to micId (0) by default. 
Therefore, "source/0/..." addresses are available.
*/

float listenerPos[] = {0.0, 0.0, 0.0};
context.setParameterAtInitVec3("listener/1/position",listenerPos);
// OpenALOutput variable %list_id automatically set to outputId (1).

context.play();

char c;
do{
	std::cout<<"Press f or b to move the source forward/backward. Press q to quit."<<std::endl;
	std::cin>>c;

	switch(c){
	case 'f':
		sourcePos[2]-=1.0;
		context.setParameter("source/0/position",sourcePos);
		break;
	case 'b':
		sourcePos[2]+=1.0;
		context.setParameter("source/0/position",sourcePos);
		break;
	}
}while(c!='q');

context.stop();
		
[...]