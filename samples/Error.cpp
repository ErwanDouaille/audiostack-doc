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
	err(context);	// Get license errors
	
	context.createInput(micId,OpenALInput);
	context.createOutput(outputId,OpenALOutput,false);
	err(context);	// Get last error, raised by createInput or createOutput
	
	context.connect(micId,outputId);			
	err(context);	// Get potentiel connection errors
	
	context.play();
	err(context);	// Get errors raised at startup

	char c;
	do{
		std::cin>>c;
	} while(c!='q');		

	context.stop();
	err(context);	// Get errors raised when shutting down audio

}catch(std::exception& e){
	std::cout<<e.what()<<std::endl;
}catch(...){
	std::cout<<"Unhandled error"<<std::endl;
}

[...]
