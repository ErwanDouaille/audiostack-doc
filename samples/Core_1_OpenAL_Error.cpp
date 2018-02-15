void err(const AudiostackContext& _context){
	if(_context.getError())
		throw std::runtime_error(_context.getLastErrorMessage());
} 

[...]

try{
	int micId = 0;
	int outputId = 1;

	AudiostackContext context;
	context.setLicenseKeyFromFile("LICENSE_FILE.aslc");
	err(context);

	context.createInput(micId,OpenALInput);
	context.createOutput(outputId,OpenALOutput,false); 
	err(context);

	context.connect(micId,outputId);
	err(context);

	context.play();
	err(context);

	char c;
	std::cout<<"Mic capture in progress. Press q to quit."<<std::endl;
	do{ std::cin>>c;} while(c!='q');  

	context.stop();
	err(context);

}catch(std::exception& e){
	std::cout<<e.what()<<std::endl;
	
}catch(...){
	std::cout<<"Unhandled error"<<std::endl;
	
}

	
[...]