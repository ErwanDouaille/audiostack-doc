[...]

AudiostackContext context;
context.setLicenseKeyFromFile("LICENSE.aslc");

context.createInput(0,JackInput, 1U);
context.createOutput(1,JackOutput,1U);
// Please launch your jack daemon before running audiostack.

context.connect(0,1);

context.play();

char c;
do{
	std::cout<<"Feel free to connect jack ports (with program such as 'qjackctl').\n\tPress q to quit."<<std::endl;
	std::cin>>c;
}while(c!='q');

context.stop();

[...]
