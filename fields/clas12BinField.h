#ifndef C12BIN_FIELDS_H
#define C12BIN_FIELDS_H

#include "fieldFactory.h"

// uses David's Heddle cmag: https://github.com/JeffersonLab/clas12-cmag

class clas12BinField : public fieldFactory
{
public:
	~clas12BinField(){}

	// save map list for loadFieldMap
	map<string, vector<string> > validC12MapNames;

	// fields used in real data:
	// https://github.com/JeffersonLab/clas12-offline-software/blob/development/etc/services/data.yaml
	
	// constructor:  create map list with hardcoded names
	// hardcoding names here
	clas12BinField() {
		validC12MapNames[TorusSymm2018Solenoid2018] = {"Symm_solenoid_r601_phi1_z1201_13June2018.dat", "Symm_torus_r2501_phi16_z251_24Apr2018.dat"};
		validC12MapNames[TorusFull2020Solenoid2018] = {"Symm_solenoid_r601_phi1_z1201_13June2018.dat", "Full_torus_r251_phi181_z251_03March2020.dat"};
		validC12MapNames[TorusFull2021Solenoid2018] = {"Symm_solenoid_r601_phi1_z1201_13June2018.dat", "Full_torus_r251_phi181_z251_25Jan2021.dat"};
	}

	// check if the binary map filename is a match for a pre-defined list
	// also set the map filenames
	bool isEligible(string);

	// load field definitions
	gfield loadField(string, goptions);
	
	// load field map. This is a dispatcher function for the various types of fields below
	void loadFieldMap(gMappedField*, double)              {} // empty implementation
	void loadFieldMap_Dipole(gMappedField*, double)       {} // empty implementation
	void loadFieldMap_Cylindrical(gMappedField*, double)  {} // empty implementation
	void loadFieldMap_phiSegmented(gMappedField*, double) {} // empty implementation
	void loadFieldMap_cartesian3d(gMappedField*, double)  {} // empty implementation

	// clas12 specific. Notice: this should be in a dedicated binary factory
	// however:
	// - clas12 would be the only map using it. Not really worth it, also considering that:
	// - gemc is moving to gemc3 with a better (plugin) mechanism to load fields
	virtual void loadFieldMap(gclas12BinaryMappedField*, double); // load clas12 binary field map.
		
	static fieldFactory *createFieldFactory() {
		return new clas12BinField;
	}
	
	double solenoidScale = 1;
	double torusScale    = 1;
	
};


#endif
