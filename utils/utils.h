#pragma once

#define INRANGE(x, a, b) (x >= a && x <= b)
#define GET_BYTE(x) (GET_BITS(x[0]) << 4 | GET_BITS(x[1]))
#define GET_BITS(x) (INRANGE((x & (~0x20)), 'A', 'F') ? ((x & (~0x20)) - 'A' + 0xa) : (INRANGE(x, '0', '9') ? x - '0' : 0))

template <unsigned int IIdx, typename TRet, typename... TArgs>
static auto CallVFunc(void* thisptr, TArgs... argList) -> TRet {
	using Fn = TRet(__thiscall*)(void*, decltype(argList)...);
	return (*static_cast<Fn**>(thisptr))[IIdx](thisptr, argList...);
}

template <typename R, typename... Args>
static auto CallFunc(void* func, Args... args) -> R
{
	return ((R(*)(Args...))func)(args...);
}

static uintptr_t mStart = 0;
static uintptr_t mEnd = 0;

static uintptr_t FindSig(const char* sig) {
    const char* pattern = sig;
    uintptr_t firstMatch = 0;

    BYTE patByte = GET_BYTE(pattern);
    const char* oldPat = pattern;

    for (uintptr_t pCur = mStart; pCur < mEnd; pCur++) {
        if (!*pattern)
            return firstMatch;

        while (*(PBYTE)pattern == ' ')
            pattern++;

        if (!*pattern)
            return firstMatch;

        if (oldPat != pattern) {
            oldPat = pattern;
            if (*(PBYTE)pattern != '\?')
                patByte = GET_BYTE(pattern);
        };

        if (*(PBYTE)pattern == '\?' || *(BYTE*)pCur == patByte) {
            if (!firstMatch)
                firstMatch = pCur;

            if (!pattern[2])
                return firstMatch;

            pattern += 2;
        }
        else {
            pattern = sig;
            firstMatch = 0;
        };
    };
}

void sortStringsByLength(std::vector<std::string>& strings) {
    // Comparison function
    auto compareStringLength = [](const std::string& s1, const std::string& s2) {
        return s1.length() > s2.length();
    };

    std::sort(strings.begin(), strings.end(), compareStringLength);
}

bool IsPointerWriteProtected(const void* ptr)
{
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery(ptr, &mbi, sizeof(mbi)) != 0)
    {
        DWORD protection = mbi.Protect;
        return (protection & PAGE_READONLY) || (protection & PAGE_EXECUTE_READ) || (protection & PAGE_WRITECOPY) || (protection & PAGE_EXECUTE_WRITECOPY);
    }
    return false;
}

DWORD AddrUnprotect(void* address) {
    DWORD oldProtect;
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(address, &mbi, sizeof(mbi));
    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, PAGE_READWRITE, &oldProtect);
    return oldProtect;
}

void AddrProtect(void* address, DWORD oldProtect) {
    MEMORY_BASIC_INFORMATION mbi;
    VirtualQuery(address, &mbi, sizeof(mbi));
    DWORD temp;
    VirtualProtect(mbi.BaseAddress, mbi.RegionSize, oldProtect, &temp);
}

POINT GetWindowMiddle(HWND hWnd){
    RECT rect;
    POINT middle;

    // Get the window's client area rectangle
    GetClientRect(hWnd, &rect);

    // Calculate the middle coordinates
    middle.x = (rect.right + rect.left) / 2;
    middle.y = (rect.bottom + rect.top) / 2;

    // Convert client coordinates to screen coordinates
    ClientToScreen(hWnd, &middle);

    return middle;
}

std::vector<std::string> splitStringToVector(const std::string& input) {
    std::vector<std::string> output;

    for (char c : input) {
        output.push_back(std::string(1, c));
    }

    return output;
}