static bool mustStop = false;

void atEndCallback(){
	std::cout<<"Callback received"<<std::endl;
	mustStop = true;
}

[...]

int fileId = 0;
int outputId = 1;

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE_FILE.aslc");

context.createInput(fileId,AudioFileReader,"FILE.wav");
context.createOutput(outputId,OpenALOutput,false);

context.setParameter("source/0/loop",false);			// File will not loop (otherwise, end callback cannot be called)
context.setParameter("source/0/start_on_awake",true);

context.setCallback("source/0/at_end",&atEndCallback);
// at_end callback from our will call atEndCallback method

context.connect(fileId,outputId);
context.play();
	
do{
	
}while(!mustStop);

context.stop();

[...]