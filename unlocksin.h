

enum class TdrErrorType {
    TDR_NO_ERROR = 0,
    TDR_ERR_SHORT_BUF_FOR_WRITE = -1,
    TDR_ERR_SHORT_BUF_FOR_READ = -2,
    TDR_ERR_STR_LEN_TOO_BIG = -3,
    TDR_ERR_STR_LEN_TOO_SMALL = -4,
    TDR_ERR_STR_LEN_CONFLICT = -5,
    TDR_ERR_MINUS_REFER_VALUE = -6,
    TDR_ERR_REFER_SURPASS_COUNT = -7,
    TDR_ERR_ARG_IS_NULL = -8,
    TDR_ERR_CUTVER_TOO_SMALL = -9,
    TDR_ERR_CUTVER_CONFILICT = -10,
    TDR_ERR_PARSE_TDRIP_FAILED = -11,
    TDR_ERR_INVALID_TDRIP_VALUE = -12,
    TDR_ERR_INVALID_TDRTIME_VALUE = -13,
    TDR_ERR_INVALID_TDRDATE_VALUE = -14,
    TDR_ERR_INVALID_TDRDATETIME_VALUE = -15,
    TDR_ERR_FUNC_LOCALTIME_FAILED = -16,
    TDR_ERR_INVALID_HEX_STR_LEN = -17,
    TDR_ERR_INVALID_HEX_STR_FORMAT = -18,
    TDR_ERR_INVALID_BUFFER_PARAMETER = -19,
    TDR_ERR_NET_CUTVER_INVALID = -20,
    TDR_ERR_ACCESS_VILOATION_EXCEPTION = -21,
    TDR_ERR_ARGUMENT_NULL_EXCEPTION = -22,
    TDR_ERR_USE_HAVE_NOT_INIT_VARIABLE_ARRAY = -23,
    TDR_ERR_INVALID_FORMAT = -24,
    TDR_ERR_HAVE_NOT_SET_SIZEINFO = -25,
    TDR_ERR_VAR_STRING_LENGTH_CONFILICT = -26,
    TDR_ERR_VAR_ARRAY_CONFLICT = -27,
    TDR_ERR_BAD_TLV_MAGIC = -28,
    TDR_ERR_UNMATCHED_LENGTH = -29,
    TDR_ERR_UNION_SELECTE_FIELD_IS_NULL = -30,
    TDR_ERR_SUSPICIOUS_SELECTOR = -31,
    TDR_ERR_UNKNOWN_TYPE_ID = -32,
    TDR_ERR_LOST_REQUIRED_FIELD = -33,
    TDR_ERR_NULL_ARRAY = -34
	//
};

class TdrReadBuf {
private:
    std::vector<uint8_t> beginPtr;
    int32_t position;
    int32_t length;
    bool isNetEndian;
public:
    bool isUseCache;
	//
};

namespace CSProtocol {
	class COMDT_HERO_COMMON_INFO {
    public:
        uint32_t getdwHeroID() {
			if (this == nullptr) {return 0;}
			return *(uint32_t *)((uint64_t)this + 0x10);
		};
        uint16_t getwSkinID() {
			if (this == nullptr) {return 0;}
			return *(uint16_t *)((uint64_t)this + 0x42);
		};
		
		void setdwHeroID(uint32_t dwHeroID) {
			if (this == nullptr) {return;}
			*(uint32_t *)((uint64_t)this + 0x10) = dwHeroID;
		};
        void setwSkinID(uint16_t wSkinID) {
			if (this == nullptr) {return;}
			*(uint16_t *)((uint64_t)this + 0x42) = wSkinID;
		};
		//
    };
	
	struct saveData {
        static uint32_t heroId;
        static uint16_t skinId;
		static bool enable;
		static std::vector<std::pair<COMDT_HERO_COMMON_INFO*, uint16_t>> arrayUnpackSkin;
		
        static void setData(uint32_t hId, uint16_t sId) {
            heroId = hId;
            skinId = sId;
        }
		
		static void setEnable(bool eb) {
            enable = eb;
        }
		
        static uint32_t getHeroId() {
            return heroId;
        }

        static uint16_t getSkinId() {
            return skinId;
        }
		
		static bool getEnable() {
            return enable;
        }
		
		static void resetArrayUnpackSkin() {
    		if (!saveData::arrayUnpackSkin.empty()) {
        		for (const auto& skinInfo : saveData::arrayUnpackSkin) {
            		COMDT_HERO_COMMON_INFO* heroInfo = skinInfo.first;
            		uint16_t skinId = skinInfo.second;
			
            		heroInfo->setwSkinID(skinId);
        		}
        		saveData::arrayUnpackSkin.clear();
    		}
		}
		//
    };
	
    uint32_t saveData::heroId = 0;
    uint16_t saveData::skinId = 0;
	bool saveData::enable = false;
	std::vector<std::pair<COMDT_HERO_COMMON_INFO*, uint16_t>> saveData::arrayUnpackSkin;
	//
}

// void hook_unpack(CSProtocol::COMDT_HERO_COMMON_INFO* instance) {
// 	if (!CSProtocol::saveData::enable) {return;}
// 	if (
// 	instance->getdwHeroID() == CSProtocol::saveData::heroId
// 	&& CSProtocol::saveData::heroId != 0
// 	&& CSProtocol::saveData::skinId != 0
// 	) {
// 		CSProtocol::saveData::arrayUnpackSkin.emplace_back(instance, instance->getwSkinID());
// 		instance->setwSkinID(CSProtocol::saveData::skinId);
// 	}
// 	//
// }

// TdrErrorType (*old_unpack)(CSProtocol::COMDT_HERO_COMMON_INFO* instance, TdrReadBuf& srcBuf, int32_t cutVer);
// TdrErrorType unpack(CSProtocol::COMDT_HERO_COMMON_INFO* instance, TdrReadBuf& srcBuf, int32_t cutVer) {

// 	TdrErrorType result = old_unpack(instance, srcBuf, cutVer);
// 		if (unlockskin) {
// 	hook_unpack(instance);
// 	}
//     return result;
// 	//
// }
