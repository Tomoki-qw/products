#include "public.sdk/source/main/pluginfactory.h"

#include "myvst3fuid.h"
#include "processor.h"
#include "controller.h"

#define MYVST_VENDOR   "KInstruments"
#define MYVST_URL      ""
#define MYVST_EMAIL    ""
#define MYVST_VSTNAME  "KSynth beta"
#define MYVST_VERSION  "0" 
#define MYVST_SUBCATEGORIES Vst::PlugType::kInstrument




BEGIN_FACTORY_DEF(MYVST_VENDOR, MYVST_URL, MYVST_EMAIL)

	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ProcessorUID),
	PClassInfo::kManyInstances,
	kVstAudioEffectClass,
	MYVST_VSTNAME,
	Vst::kDistributable,
	MYVST_SUBCATEGORIES,
	MYVST_VERSION,
	kVstVersionString,
	Steinberg::Vst::MyVSTProcessor::createInstance)

	DEF_CLASS2(INLINE_UID_FROM_FUID(Steinberg::Vst::ControllerUID),
	PClassInfo::kManyInstances,
	kVstComponentControllerClass,
	MYVST_VSTNAME " Controller",	
	0,						    
	"",						  
	MYVST_VERSION,
	kVstVersionString,
	Steinberg::Vst::MyVSTController::createInstance)

END_FACTORY