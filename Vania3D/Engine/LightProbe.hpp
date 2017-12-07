
#ifndef LightProbe_hpp
#define LightProbe_hpp

class LightProbe {
private:

public:
	LightProbe(const char* path);
	~LightProbe();

	unsigned int cubemap, irradiance, prefilter, brdf;

	static unsigned int loadHDR(const char* path);
	static unsigned int genCubemap(unsigned int hdr, int size, bool mipmap);
	static unsigned int genIrradianceMap(unsigned int cubemap, int size);
	static unsigned int genPrefilterMap(unsigned int cubemap, int size);
	static unsigned int genBRDFLUTTexture(int size);
};

#endif /* LightProbe_hpp */
