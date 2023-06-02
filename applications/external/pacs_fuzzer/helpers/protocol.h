#pragma once

#include <stdint.h>

typedef enum {
    DS1990,
    Metakom,
    Cyfral,
    // Reserved
    FuzzerProtoMax,
} FuzzerProtos;

struct ProtoDict {
    const uint8_t* val;
    const uint8_t len;
};

typedef struct ProtoDict ProtoDict;

struct FuzzerProtocol {
    const char* name;
    const uint8_t data_size;
    const ProtoDict dict;
};

typedef struct FuzzerProtocol FuzzerProtocol;

extern const FuzzerProtocol fuzzer_proto_items[];