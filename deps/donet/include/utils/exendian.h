//
// Created by StevensChew on 17/1/10.
//

#ifndef KATRINA_EXENDIAN_H
#define KATRINA_EXENDIAN_H

#include<cstdint>

namespace donet {
    inline uint16_t ConvertHostToNetworkShort(uint16_t hostl) {
        return htobe16(hostl);
    }

    inline uint32_t ConvertHostToNetworkLong(uint32_t hostl) {
        return htobe32(hostl);
    }

    inline uint64_t ConvertHostToNetworkLongLong(uint64_t hostl) {
        return htobe64(hostl);
    }

    inline uint16_t ConvertNetworkToHostShort(uint16_t networks) {
        return be16toh(networks);
    }

    inline uint32_t ConvertNetworkToHostLong(uint32_t networkl) {
        return be32toh(networkl);
    }

    inline uint64_t ConvertNetworkToHostLongLong(uint64_t networkll) {
        return be64toh(networkll);
    }
}

#endif //KATRINA_EXENDIAN_H
