#ifndef __REFLECTION_H__
#define __REFLECTION_H__

#define DEFINE_STRUCT(STRUCT_NAME, ...)                                                \
struct STRUCT_NAME{                                                                   \
    template <typename, size_t> struct FIELD;                                 \
    static constexpr size_t _field_count_ = GET_ARG_COUNT(__VA_ARGS__);       \
    PASTE(FOR_EACH_, GET_ARG_COUNT(__VA_ARGS__)) (FIELD_EACH, 0, __VA_ARGS__) \
};


#endif //!__REFLECTION_H__
