User guide

Installation - 

Installation of the software here included is simple if you adhere to the follwoing steps. 
1) Download the zip file and extract its contents to a directory of your choosing.
2) Open up a terminal window inside your Linux environment. (WSL for windows, using Ubuntu as the distro also works)
3) Navigate to the directory in which you extracted the files, and go to the Warhol directory. Run the make command. The makefile included will compile and link the files necessary to create the warholE and warholD binaries (E for encoder, D for decoder)

You should now have two binaries called warholE and warholD.

Usage - 

	Before we begin using the programs, take note of the directory structure that has been laid out for you as this will be helpful in using the programs correctly.

	Directories - 

		Images - Put images that you want to encode inside this directory. Remember that the programs only accept images in the tga format. An image will be included here for you so you can experiment with using the program as described in the Binaries section later on.

		Keys - The key that is written after encoding an image can be found inside this directory. This is a useful storage place for when you want to directly pipe a key as input for the decoder. Remember that keys can get very long and so it is generally helpful to pipe them as text files rather than writing the key directly in the terminal.

		Outputs - Any outputted images will be placed here. Encrypted images will be found here, and thus it is important to remember this when typing in the filepath to the decoder.

		Source - Contains source files used in both the Encoder and Decoder program. Modify these if you would like to experiment with creating new Warhol filters or expand upon the project.

		Encoder/Decoder - Each respectively contains the Encoder/Decoder programs. Modify these at your risk and only once you understand how the source files work.

	Binaries (example usage)

		These are examples on how to run the programs.

		Encryption - ./warholE filePath
			Example - ./warholE Images/a.tga

		Decryption - ./warholD filePath xDimension yDimension
			Example - ./warholD Outputs/Warhol.tga 2 2
			(The x and y dimension pertain to the image that you want to decode, as it could be a 2x2, 3x3, 5x1, etc. You must look at the image to determine this)
	
			Piped key example - ./warholD Outputs/Warhol.tga 2 2 < Keys/key.txt
			(This examples pipes in the key as input directly instead of taking it from the user's keyboard)

Bugs - 
With correct usage as directed, you should not encounter any bugs. However, it should be noted that the program only support chars up to 127, and so any ascii values past this will not be properly encoded/decoded. This is by design.

Bug reporting - 
Send me bug reports to sreina@ufl.edu