main:
	g++ -o warholE Encoder/Encoder.cpp Source/Composite.cpp Source/Image.cpp Source/Pixel.cpp
	g++ -o warholD Decoder/Decoder.cpp Source/Composite.cpp Source/Image.cpp Source/Pixel.cpp

clean:
	rm warholE