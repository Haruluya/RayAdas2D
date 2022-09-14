#define BIT(x) (1 << x)

#define RA_ASSERT(x, ...) { if(!(x)) { RA_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define RA_CORE_ASSERT(x, ...) { if(!(x)) { RA_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#define RA_BIND_EVENT_FN(fn) std::bind(&fn, this, std::placeholders::_1)